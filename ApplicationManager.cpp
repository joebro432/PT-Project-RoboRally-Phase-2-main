#include "ApplicationManager.h"

#include "Grid.h"

#include "AddBeltAction.h"
#include "AddRotatingGearAction.h"
#include "AddFlagAction.h"
#include "AddDangerZoneAction.h"
#include "AddWaterPitAction.h"
#include "AddWorkshopAction.h"
#include "AddAntennaAction.h"
#include "SwitchToPlayModeAction.h"
#include "SwitchToDesignModeAction.h"
#include "LoadGridAction.h"
#include "SaveGridAction.h"
#include "DeleteGameObject.h"
#include "CopyGameObjectAction.h"
#include "CutGameObjectAction.h"
#include "PasteGameObjectAction.h"
#include "ExecuteCommandsAction.h"
#include "SelectCommandAction.h"
#include "RebootAndRepairAction.h"
#include "NewGameAction.h"
///TODO: Add #include for all action types done
#include "GameState.h"

ApplicationManager::ApplicationManager()
{
	// Creation order matters:
	//   1. Output / Input  (needed by Grid)
	//   2. Grid            (needed by GameState -- provides the start Cell)
	//   3. GameState       (creates and draws initial players)
	pOut = new Output();
	pIn  = pOut->CreateInput();
	pGrid      = new Grid(pIn, pOut);
	pGameState = new GameState(pGrid);
}

ApplicationManager::~ApplicationManager()
{
	// Deletion order is the reverse of creation:
	//   GameState owns the Players -- delete it first.
	//   Grid owns pIn and pOut     -- delete it last.
	delete pGameState;
	delete pGrid;
}

//==================================================================================//
//								Interface Management Functions						//
//==================================================================================//

Grid* ApplicationManager::GetGrid() const
{
	return pGrid;
}

GameState* ApplicationManager::GetGameState() const
{
	return pGameState;
}

void ApplicationManager::UpdateInterface() const
{
	// Grid draws the board; GameState provides player data for drawing.
	pGrid->UpdateInterface(pGameState);
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//

ActionType ApplicationManager::GetUserAction() const
{
	// Ask the input to get the action from the user.
	return pIn->GetUserAction();
}

////////////////////////////////////////////////////////////////////////////////////

// Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	// According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case ADD_BELT:
		pAct = new AddBeltAction(this);
		break;

	case ADD_ROTATING_GEAR:
		pAct = new AddRotatingGearAction(this);
		break;

	case SET_FLAG_CELL:
		pAct = new AddFlagAction(this);
		break;

	case TO_PLAY_MODE:
		if (pGrid->GridHasFlag())
		{
			pAct = new SwitchToPlayModeAction(this);
		}
		else
		{
			pOut->PrintMessage("Error need flag to start game");
		}
		break;

	case ADD_DANGER_ZONE:
		pAct = new AddDangerZoneAction(this);
		break;

	case ADD_WATER_PITS:
		pAct = new AddWaterPitAction(this);
		break;

	case ADD_WORKSHOP:
		pAct = new AddWorkshopAction(this);
		break;

	case ADD_ANTENNA:
		pAct = new AddAntennaAction(this);
		break;

	case SAVE_GRID:
		pAct = new SaveGridAction(this);
		break;

	case LOAD_GRID:
		pAct = new LoadGridAction(this);
		break;


	case DELETE_GAME_OBJECT:
		pAct = new DeleteGameObject(this);
		break;

	case COPY_GAME_OBJECT:
		pAct = new CopyGameObjectAction(this);
		break;

	case CUT_GAME_OBJECT:
		pAct = new CutGameObjectAction(this);
		break;

	case PASTE_GAME_OBJECT:
		pAct = new PasteGameObjectAction(this);
		break;

	case EXIT:
		break;

	///TODO: Add a case for EACH remaining Design Mode action type done

	case TO_DESIGN_MODE:
		pAct = new SwitchToDesignModeAction(this);
		break;
	case EXECUTE_COMMANDS:
		pAct = new ExecuteCommandsAction(this);
		break;


	case SELECT_COMMAND:
		pAct = new SelectCommandAction(this);
		break;

	case REBOOT_AND_REPAIR:
		pAct = new RebootAndRepairAction(this);
		break;

	case NEW_GAME:
		pAct = new NewGameAction(this);
		break;

	case STATUS:	// a click on the status bar ==> no action // ummm will not touch
		return;
	}
	///TODO: Add a case for EACH remaining Play Mode action type done
	// Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute(); // Execute
		delete pAct;	 // Action is not needed any more after executing ==> delete it
		pAct = NULL;
	}
}
