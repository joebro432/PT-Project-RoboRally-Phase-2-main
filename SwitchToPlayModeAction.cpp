#include "SwitchToPlayModeAction.h"
#include "Grid.h"
#include "GameState.h"
#include "Output.h"
#include "Player.h"
#include<iostream>

SwitchToPlayModeAction::SwitchToPlayModeAction(ApplicationManager* pApp) : Action(pApp)
{
}

void SwitchToPlayModeAction::ReadActionParameters()
{
	// No parameters needed -- a mode switch requires no user input
}

void SwitchToPlayModeAction::Execute()
{
	Output*    pOut   = pManager->GetGrid()->GetOutput();
	GameState* pState = pManager->GetGameState();

	// 1. Switch the global interface mode to Play Mode
	UI.InterfaceMode = MODE_PLAY;

	// 2. Redraw the toolbar with Play Mode buttons
	pOut->CreatePlayModeToolBar();

	// 3. Set phase to PLANNING so players can select commands
	pState->SetCurrentPhase(PHASE_PLANNING);

	// 4. Generate available commands for the current player
	pState->GetCurrentPlayer()->GenerateRandomCommands();

	// 5. Initialize the current player's turn (update max saved commands, etc.)
	pState->StartTurn();

	// 6. Redraw the full interface (board + player info bar)
	pManager->UpdateInterface();

	// 7. Display the commands bar with saved and available commands
	pOut->CreateCommandsBar(pState->GetCurrentPlayer()->GetSavedCommands(),
		pState->GetCurrentPlayer()->GetSavedCommandCount(),
		pState->GetCurrentPlayer()->GetAvailableCommands(),
		pState->GetCurrentPlayer()->GetAvailableCommandCount());

}

SwitchToPlayModeAction::~SwitchToPlayModeAction()
{
}
