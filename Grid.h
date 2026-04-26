#pragma once

#include "UI_Info.h"
#include "DEFS.h"

#include "Input.h"
#include "Output.h"
#include "CellPosition.h"

// Forward declarations (includes are in Grid.cpp)
class Cell;
class GameObject;
class Player;
class Belt;
class GameState;

// ============================================================
// Grid: the game board.
//
// Responsibilities:
//   - The 2-D array of Cells and the GameObjects placed on them
//   - Input / Output interfaces
//   - Clipboard (copy / cut / paste game objects)
//   - Drawing the board and delegating player drawing to GameState
//
// Responsibilities that do NOT belong here:
//   - Turn order / current player      --> GameState
//   - Game phase (movement, shooting)  --> GameState
//   - End-game flag                    --> GameState
//   - Player objects                   --> GameState
// ============================================================
class Grid
{
	Output* pOut;  // Pointer to the Output object
	Input*  pIn;   // Pointer to the Input object

	Cell* CellList[NumVerticalCells][NumHorizontalCells]; // Every cell on the board

	GameObject* Clipboard; // Used in copy / cut / paste

public:

	Grid(Input* pIn, Output* pOut); // Allocates all Cells; does NOT create Players (GameState does that)

	// ========== Board Operations ==========

	bool AddObjectToCell(GameObject* pNewObject);        // Adds object to its cell; returns false if cell is occupied
	void RemoveObjectFromCell(const CellPosition& pos); // Removes the GameObject of the Cell of the passed "position"
	                                                     // Note: You may need to change the return type of this function (Think)

	void UpdatePlayerCell(Player* player, const CellPosition& newPosition); // Update the player's pCell with the CellList's Cell pointer of the "newPosition",
	                                                                          // Clears the player's circle from the previous cell
	    																	  // and Draws it in the new cell

	// Returns the first Belt found at or after 'position' (used when adding connected belts).
	Belt* GetNextBelt(const CellPosition& position);

	// ========== Setters / Getters ==========

	Input*  GetInput()  const;
	Output* GetOutput() const;

	void       SetClipboard(GameObject* gameObject);
	GameObject* GetClipboard() const;

	// Returns the Cell where all players start (bottom-left corner of the board).
	// Called by GameState's constructor to initialise player positions.
	Cell* GetStartCell() const;

	///TODO: Add any additional board-query getters here (e.g. GetCell(CellPosition))

	// ========== User Interface ==========

	// It Updates the Grid according to the last state of the game
	// In Design mode, it draws all cells THEN all game objects THEN all players
	// In Play mode, it only draws the player's info on the right side of the toolbar
	void UpdateInterface(const GameState* pState) const;

	void PrintErrorMessage(string msg); // Shows msg on the status bar, waits for a click, then clears it

	~Grid();
};
