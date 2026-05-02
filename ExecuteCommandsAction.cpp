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
	Grid* pGrid = pManager->GetGrid();
	GameState* pState = pManager->GetGameState();
	
	if (!pState || !pGrid) {
		return;
	}
	
	Player* currPlayer = pState->GetCurrentPlayer();

	if (!currPlayer) {
		return;
	}

	if (pState->GetCurrentPhase() != PHASE_MOVEMENT) {
		pGrid->PrintErrorMessage("Cannot execute commands outside of the Movement phase!");
		return;
	}

	currPlayer->Move(pGrid, pState); 
}


ExecuteCommandsAction::~ExecuteCommandsAction(){}