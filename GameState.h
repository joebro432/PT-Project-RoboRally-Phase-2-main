#pragma once

#include "UI_Info.h"
#include "DEFS.h"

// Forward declarations (includes are in GameState.cpp)
class Grid;
class Player;
class Output;

// ============================================================
// GameState: owns everything that changes during the game.
//
// Responsibilities:
//   - Which player is currently taking their turn (turn order)
//   - What phase of the round we are in (movement, [shooting bonus])
//   - Whether the game has ended
//   - The Player objects themselves
//
// Responsibilities that do NOT belong here:
//   - The board layout (cells, game objects)  --> Grid
//   - Drawing / input                         --> Grid (via Output/Input)
// ============================================================
class GameState
{
	Player* PlayerList[MaxPlayerCount]; // Owns all Player objects

	int currPlayerNumber; // index of the player whose turn it is (0..MaxPlayerCount-1)

	PhaseType currentPhase; // Which phase of the current round we are in
	bool endGame;           // True once a win/loss condition is detected

public:

	// Constructor: creates all Player objects starting at Grid's start cell.
	// Takes Grid* only to fetch the starting Cell* and Output* for initial drawing.
	GameState(Grid* pGrid);

	~GameState(); // Deletes all Player objects

	// ========== Player Access ==========

	Player* GetCurrentPlayer() const;           // Returns the player whose turn it is
	Player* GetPlayer(int playerNum) const;     // Returns any player by index (0-based)

	// ========== Turn Management ==========

	void AdvanceCurrentPlayer(); // Moves to the next player (cycles: 0 -> 1 -> ... -> 0)

	// SetFirstPlayer: tells the GameState which player goes first this round.
	// Called by Antenna::Apply() after it computes distances.
	// The remaining players follow in ascending index order.
	//
	// Example (2 players): SetFirstPlayer(1) --> turn order is [1, 0]
	//
	// [OPTIONAL] For 3+ players with full sorting, replace this with
	//            SetPlayerOrder(int sortedOrder[], int count).
	void SetFirstPlayer(int playerNum);

	// ========== Phase Management ==========
	// All phase-transition logic belongs here.
	// Actions (ExecuteCommandsAction, etc.) call AdvancePhase() when a phase ends.

	PhaseType GetCurrentPhase() const;
	void SetCurrentPhase(PhaseType phase);

	// Advances to the next phase in the round.
	// [OPTIONAL BONUS] To add PHASE_SHOOTING, update this function body:
	//   MOVEMENT --> SHOOTING --> MOVEMENT
	void AdvancePhase();

	// ========== End-Game ==========

	bool GetEndGame() const;
	void SetEndGame(bool end); // Call when a player reaches the Flag or falls into a WaterPit

	// ========== Drawing Helpers (called by Grid::UpdateInterface) ==========

	void DrawAllPlayers(Output* pOut) const;          // Draw every player's token
	void AppendPlayersInfo(string& info) const;       // Build the play-mode status string
};
