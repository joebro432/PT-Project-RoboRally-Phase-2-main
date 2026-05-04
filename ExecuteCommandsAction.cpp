#include "ExecuteCommandsAction.h"
#include "Player.h"
#include "Grid.h" //for move function in player
#include "GameState.h" // for move function in player


ExecuteCommandsAction::ExecuteCommandsAction(ApplicationManager* pApp):Action(pApp){}


void ExecuteCommandsAction::ReadActionParameters()
{
	//no parameters needed
}


void ExecuteCommandsAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();
	
	if (!pState || !pGrid) {
		return;
	}
	
	Player* currPlayer = pState->GetCurrentPlayer();

	if (!currPlayer) {
		return;
	}

	if (pState->GetCurrentPhase() != PHASE_PLANNING) {	// making sure that player was in plan phase
		pGrid->PrintErrorMessage("You must be in planning phase!");
		return;
	}

	if (currPlayer->GetSavedCommandCount() == 0) {
		pGrid->PrintErrorMessage("No commands to execute!");
		return;
	}

	pState->SetCurrentPhase(PHASE_MOVEMENT); //to start moving

	currPlayer->Move(pGrid, pState); 
	pManager->UpdateInterface(); // update the interface after the player moves

	pState->AdvanceCurrentPlayer(); // goes to next player
	pState->SetCurrentPhase(PHASE_PLANNING); // next player goes to planning phase again

	pGrid->GetOutput()->PrintMessage("Commands are being executed...");
}


ExecuteCommandsAction::~ExecuteCommandsAction(){}