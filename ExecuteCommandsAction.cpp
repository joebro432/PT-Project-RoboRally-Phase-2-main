#include "ExecuteCommandsAction.h"
#include "Player.h"
#include "Grid.h" //for move function in player
#include "GameState.h" // for move function in player
#include "Antenna.h"


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

	// Check if player is hacked and skip their turn
	if (currPlayer->IsHacked())
	{
		pGrid->PrintErrorMessage("This player is hacked and must skip their turn!");
		currPlayer->ResetHackState(); // Reset for next round
		currPlayer->ClearSavedCommands(); // Clear any saved commands

		// Increment move counter even though we're skipping
		pState->IncrementMoveCounter();

		int nextPlayerNum = (pState->GetCurrentPlayer()->getPlayerNum() + 1) % MaxPlayerCount;
		pState->AdvanceCurrentPlayer(); // goes to next player

		pState->SetCurrentPhase(PHASE_PLANNING); // next player goes to planning phase again

		// Check if round is complete (all players have moved or skipped)
		if (pState->IsRoundComplete())
		{
			// Reset move counter for next round
			pState->ResetMoveCounter();

			// Check flag condition after all players have moved
			GameObject* pFlag = pGrid->GetFlag();
			if (pFlag)
			{
				// Check both players to see if any reached the flag
				for (int i = 0; i < MaxPlayerCount; i++)
				{
					Player* player = pState->GetPlayer(i);
					if (player && player->GetCell()->HasFlag())
					{
						pFlag->Apply(pGrid, pState, player);
						pManager->UpdateInterface();
						return; // End execution if flag condition is met
					}
				}
			}

			// Apply antenna to determine next round's turn order
			if (pGrid->GridHasAntenna())
			{
				GameObject* pAntenna = pGrid->GetAntenna();
				if (pAntenna)
				{
					pAntenna->Apply(pGrid, pState, nullptr);
				}
			}
		}

		pState->StartTurn(); // Initialize the next player's turn

		pManager->UpdateInterface();
		return;
	}

	if (currPlayer->GetSavedCommandCount() == 0) {
		pGrid->PrintErrorMessage("No commands to execute!");
		return;
	}

	pState->SetCurrentPhase(PHASE_MOVEMENT); //to start moving

	pGrid->GetOutput()->PrintMessage("Commands are being executed...");
	currPlayer->Move(pGrid, pState); 
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y); // Wait for click before clearing message
	pGrid->GetOutput()->ClearStatusBar();
	pManager->UpdateInterface(); // update the interface after the player moves

	// Increment move counter to track how many players have moved
	pState->IncrementMoveCounter();

	int nextPlayerNum = (pState->GetCurrentPlayer()->getPlayerNum() + 1) % MaxPlayerCount;
	pState->AdvanceCurrentPlayer(); // goes to next player

	pState->SetCurrentPhase(PHASE_PLANNING); // next player goes to planning phase again

	// Check if round is complete (all players have moved)
	if (pState->IsRoundComplete())
	{
		// Reset move counter for next round
		pState->ResetMoveCounter();

		// Check flag condition after all players have moved
		// For 2 players: after 2 moves (count % 2 == 0)
		// For 3 players: after 3 moves (count % 3 == 0), etc.
		GameObject* pFlag = pGrid->GetFlag();
		if (pFlag)
		{
			// Check both players to see if any reached the flag
			for (int i = 0; i < MaxPlayerCount; i++)
			{
				Player* player = pState->GetPlayer(i);
				if (player && player->GetCell()->HasFlag())
				{
					pFlag->Apply(pGrid, pState, player);
					pManager->UpdateInterface();
					return; // End execution if flag condition is met
				}
			}
		}

		// Apply antenna to determine next round's turn order
		if (pGrid->GridHasAntenna())
		{
			GameObject* pAntenna = pGrid->GetAntenna();
			if (pAntenna)
			{
				pAntenna->Apply(pGrid, pState, nullptr);
			}
		}
	}

	pState->StartTurn(); // enters phase plan


}



ExecuteCommandsAction::~ExecuteCommandsAction(){}