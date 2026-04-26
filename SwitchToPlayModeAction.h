#pragma once
#include "Action.h"

// Action that switches the application from Design Mode to Play Mode.
//
// ALL mode-switching logic belongs inside Execute() of this class:
//   - Change UI.InterfaceMode to MODE_PLAY
//   - Redraw the toolbar for Play Mode
//   - Reset the current player, phase, or any other play-mode state
class SwitchToPlayModeAction : public Action
{
public:
	SwitchToPlayModeAction(ApplicationManager* pApp);

	virtual void ReadActionParameters(); // No parameters needed for a mode switch

	virtual void Execute(); // Performs the switch to Play Mode

	virtual ~SwitchToPlayModeAction();
};
