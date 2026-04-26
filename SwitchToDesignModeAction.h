#pragma once
#include "Action.h"

// Action that switches the application from Play Mode back to Design Mode.
//
// ALL mode-switching logic belongs inside Execute() of this class:
//   - Change UI.InterfaceMode to MODE_DESIGN
//   - Redraw the toolbar for Design Mode
//   - Clean up any play-mode state if needed
class SwitchToDesignModeAction : public Action
{
public:
	SwitchToDesignModeAction(ApplicationManager* pApp);

	virtual void ReadActionParameters(); // No parameters needed for a mode switch

	virtual void Execute(); // Performs the switch to Design Mode

	virtual ~SwitchToDesignModeAction();
};
