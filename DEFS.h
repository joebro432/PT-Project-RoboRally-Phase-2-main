#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

// This file contains some global constants and definitions to be used in the project.

// ============================================================
// GAME FLOW OVERVIEW
// ============================================================
// The game has two top-level modes (GUI_MODE in UI_Info.h):
//   1. Design Mode  --> player sets up the board
//   2. Play Mode    --> players take turns executing commands
//
// Within Play Mode, each round consists of phases (PhaseType below).
//
// WHERE TO IMPLEMENT GAME-STATE CHANGES:
//   - Switching between Design <-> Play mode: SwitchToPlayModeAction / SwitchToDesignModeAction
//   - Switching between play phases: GameState::AdvancePhase()
//   - Checking/setting the current phase: GameState::GetCurrentPhase() / GameState::SetCurrentPhase()
// ============================================================

enum ActionType // The actions supported (add more as needed)
{
	//  [1] Actions of Design Mode
	SET_FLAG_CELL,	// Set Flag on a Cell
	EXIT,			// Exit Application
	TO_PLAY_MODE,	// Go to Play Mode  --> handled by SwitchToPlayModeAction
	ADD_BELT,
	ADD_ROTATINGGEAR,
	ADD_FLAG,
	///TODO: Add more action types of Design Mode

	//  [2] Actions of Play Mode

	EXECUTE_COMMANDS,	// Execute the saved commands
	SELECT_COMMAND,		// Select a command from the available ones to be executed

	TO_DESIGN_MODE,	// Go to Design Mode  --> handled by SwitchToDesignModeAction

	///TODO: Add more action types of Play Mode

	//  [3] Others

	EMPTY,							// Empty Area in ToolBar (NOT inside any action icon)
	GRID_AREA,						// Inside Grid Area
	STATUS 							// Inside StatusBar Area
};

// PhaseType: the phases within a single Play Mode round.
// [OPTIONAL BONUS] Add more phases as needed (e.g. a shooting phase).
enum PhaseType
{
	PHASE_MOVEMENT,  // players execute their saved commands

	///TODO: Add more phases here as needed
};

enum Direction // Directions of the game
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

///TODO: Set the maximum number of commands a player can save per round
const int MaxSavedCommands = 5;

enum Command
{
	NO_COMMAND,
	MOVE_FORWARD_ONE_STEP,
	MOVE_BACKWARD_ONE_STEP,
	MOVE_FORWARD_TWO_STEPS,
	MOVE_BACKWARD_TWO_STEPS,
	MOVE_FORWARD_THREE_STEPS,
	MOVE_BACKWARD_THREE_STEPS,
	ROTATE_CLOCKWISE,
	ROTATE_COUNTERCLOCKWISE,

	COMMANDS_COUNT,
};

#endif