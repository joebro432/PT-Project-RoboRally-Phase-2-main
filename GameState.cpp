#include "GameState.h"

#include "Grid.h"
#include "Player.h"
#include "Cell.h"
#include "Output.h"

GameState::GameState(Grid* pGrid)
{
	// Create all Player objects starting at the board's designated start cell.
	// The Grid provides the start cell position; the GameState owns the Player objects.
	Cell* startCell = pGrid->GetStartCell();
	Output* pOut = pGrid->GetOutput();

	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i] = new Player(startCell, i);
		PlayerList[i]->Draw(pOut); // draw initial position
	}

	currPlayerNumber = 0;         // Player 0 goes first by default
	currentPhase = PHASE_MOVEMENT;
	endGame = false;
	PlayerList[currPlayerNumber]->GenerateRandomCommands();
}

GameState::~GameState()
{
	for (int i = 0; i < MaxPlayerCount; i++)
		delete PlayerList[i];
}

// ========== Player Access ==========

Player* GameState::GetCurrentPlayer() const
{
	///(DONE) TODO: Return the player whose turn it is
	return PlayerList[currPlayerNumber]; // wrong -- update this (UPDATED FROM 0 -> currPlayerNumber) 
}

Player* GameState::GetPlayer(int playerNum) const
{
	///(DONE) TODO: Return the player with the given player number
	if (playerNum < 0 || playerNum >= MaxPlayerCount) //check validity of playerNum
		return NULL; 

	return PlayerList[playerNum]; // wrong -- update this (UPDATED FROM 0 -> playerNum)
}

// ========== Turn Management ==========

void GameState::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount;
	PlayerList[currPlayerNumber]->GenerateRandomCommands();
}

void GameState::SetFirstPlayer(int playerNum)
{
	///(DONE) TODO: Implement this function to set which player goes first this round
	if (playerNum < 0 || playerNum >= MaxPlayerCount) //check validity of playerNum
		return;
	currPlayerNumber = playerNum;
	// will check the bonus with the Antenna.cpp
	PlayerList[currPlayerNumber]->GenerateRandomCommands();
}

// ========== Phase Management ==========

PhaseType GameState::GetCurrentPhase() const
{
	return currentPhase;
}

void GameState::SetCurrentPhase(PhaseType phase)
{
	currentPhase = phase;
}

void GameState::AdvancePhase()
{
	// Currently only PHASE_MOVEMENT exists.
	// [OPTIONAL BONUS] If you add PHASE_SHOOTING to the PhaseType enum (DEFS.h), [ADDED] need to make any additions for shooting
	// [UPDATED] update this to cycle:  MOVEMENT --> SHOOTING --> MOVEMENT 
	switch (currentPhase)
	{
	case PHASE_MOVEMENT:
	{
		currentPhase = PHASE_SHOOTING; // To switch between the two game mode phases
		break;
	}

	case PHASE_SHOOTING:
	{
		currentPhase = PHASE_MOVEMENT;
		break;

	}
	default:
		currentPhase = PHASE_MOVEMENT; // Default phase
		break;
	}
}

// ========== End-Game ==========

bool GameState::GetEndGame() const
{
	return endGame;
}

void GameState::SetEndGame(bool end)
{
	endGame = end;
}

// ========== Drawing Helpers ==========

void GameState::DrawAllPlayers(Output* pOut) const
{
	///(DONE) TODO: Draw all players
	for (int i = 0; i < MaxPlayerCount; i++)
		PlayerList[i]->Draw(pOut);
}

void GameState::AppendPlayersInfo(string& info) const
{
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		PlayerList[i]->AppendPlayerInfo(info);
		if (i < MaxPlayerCount - 1)
			info += ", ";
	}
	info += " | Curr = " + to_string(currPlayerNumber);
}
