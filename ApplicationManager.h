#pragma once

#include "DEFS.h"
#include "UI_Info.h"

class Input;
class Output;
class Grid;
class GameState;

// Main class that manages everything in the application.
//
// Owns two main objects:
//   Grid      -- the game board (cells, game objects, I/O)
//   GameState -- the game state (players, turn order, phase, end-game flag)
//
// Actions call GetGrid() for board operations and GetGameState() for game-logic operations.
class ApplicationManager
{
	Grid*      pGrid;      // The game board
	GameState* pGameState; // The game state (owns the Player objects)

	// pIn and pOut are owned by Grid; kept here so GetUserAction() can forward to pIn.
	Input*  pIn;
	Output* pOut;

public:

	ApplicationManager();  // Creates Output, Input, Grid, then GameState (in that order)
	~ApplicationManager(); // Deletes GameState then Grid (Grid deletes pIn and pOut)

	// ========== Interface Management ==========

	Grid*      GetGrid()      const; // Returns the game board
	GameState* GetGameState() const; // Returns the game state

	void UpdateInterface() const;    // Redraws everything: delegates to pGrid->UpdateInterface(pGameState)

	// ========== Action-Related ==========

	ActionType GetUserAction() const; // Reads user input; returns the corresponding ActionType
	void       ExecuteAction(ActionType); // Creates and executes the matching Action object
};
