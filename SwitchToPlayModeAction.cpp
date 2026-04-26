#include "SwitchToPlayModeAction.h"
#include "Grid.h"
#include "GameState.h"
#include "Output.h"

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

	// 3. Reset game state for the new play session
	pState->SetCurrentPhase(PHASE_MOVEMENT);

	// 4. Redraw the full interface (board + player info bar)
	pManager->UpdateInterface();

	///TODO: Add any other initialisation needed when entering Play Mode.
}

SwitchToPlayModeAction::~SwitchToPlayModeAction()
{
}
