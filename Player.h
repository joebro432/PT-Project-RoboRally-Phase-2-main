#pragma once

#include "Grid.h"
#include "Cell.h"

// Forward declaration: GameState is needed for Move() but we don't include it
// here to avoid a circular dependency (GameState.h includes Player.h).
class GameState;

class Player
{
	Cell* pCell;           // Pointer to the cell the player currently occupies
	const int playerNum;   // Player index 0..MaxPlayerCount-1 (constant after construction)

	Direction currDirection; // The direction the player is currently facing
	int health;              // Player's current health points

	// ---- Saved Commands (the player's "program" for this round) ----
	// Owned here because they are player-specific state.
	// SelectCommandAction fills this array; Move() executes it; ClearSavedCommands() resets it.
	Command savedCommands[MaxSavedCommands];
	int savedCommandCount; // how many commands have been saved so far (0..MaxSavedCommands)
	int maxSavedCommandsForThisRound; // Dynamic limit based on health and Extended Memory

	Command availableCommands[10];
	int availableCommandCount;

	// ---- [OPTIONAL BONUS] Shooting Phase data members ----
	// Uncomment when adding the shooting phase (see DEFS.h PhaseType):
	 
	int laserDamage; // damage per shot (default = 1; double-laser consumable = 2)
	bool isHacked;   // true = this player skips their turn this round
	// ---- [OPTIONAL BONUS] Workshop Consumables data members ----
// Uncomment when adding consumables (see Workshop.h):
//   Consumable* inventory[MaxConsumables];
//   int inventoryCount;


	// ---- Equipment and Consumables ----
	Equipment equipment[MaxEquipment];//devices that can be carried
	int equipmentCount;	//num of equipments

	Consumable consumables[MaxConsumables];	// One-time use items
	int consumableCount;// num of consumables

public:

	Player(Cell* pCell, int playerNum); // Initialises all data members

	// ====== Setters and Getters ======

	void  SetCell(Cell* cell);


	Cell* GetCell() const;

	void SetHealth(int h);
	int  GetHealth() const;

	Direction GetDirection() const;
	void      SetDirection(Direction d);

	///(DONE) TODO: Add more setters/getters here as needed
	const int getPlayerNum() const;
	// functions for the bonus 
	// ====== Equipment and Consumables ======
	void AddEquipment(Equipment equip);
	bool HasEquipment(Equipment equip) const;
	int GetEquipmentCount() const;

	void AddConsumable(Consumable cons);
	bool HasConsumable(Consumable cons) const;
	Consumable GetConsumable(int index) const;
	void RemoveConsumable(Consumable cons);
	int GetConsumableCount() const;

	bool HasExtendedMemory() const;
	bool HasDoubleLaser() const;

	// ====== Consumable Usage ======
	bool UseToolkit(); // Repairs health by 3 (returns true if successful)
	bool UseHackDevice(Player* targetPlayer); // Hacks target player's turn (returns true if successful)

	// ====== Hack State ======
	bool IsHacked() const { return isHacked; }
	void SetIsHacked(bool hacked) { isHacked = hacked; }
	void ResetIsHacked() { isHacked = false; } // Call at the start of each round

	// ====== Saved Commands ======

	void    AddSavedCommand(Command cmd);         // Appends cmd to savedCommands (called by SelectCommandAction)
	void    ClearSavedCommands();                 // Resets the saved-command list (call at the start of each round)
	int     GetSavedCommandCount() const;
	int		GetMaxSavedCommands() const { return MaxSavedCommands; }
	int		GetMaxSavedCommandsForThisRound() const; // Returns the dynamic limit (5 or 6 based on Extended Memory)
	void    UpdateMaxSavedCommandsForThisRound(); // Call at the start of each planning phase to recalculate the limit
	Command GetSavedCommand(int index) const;
	Command* GetSavedCommands() ; 
	Command* GetAvailableCommands() ;
	Command GetAvailableCommand(int index) const;
	// ====== Drawing ======

	void Draw(Output* pOut) const;         // Draws the player token on its current cell
	void ClearDrawing(Output* pOut) const; // Erases the player token (restores cell colour)

	// ====== Game Logic ======

	void Move(Grid* pGrid, GameState* pState);

	void AppendPlayerInfo(string& playersInfo) const; // Appends "P0(direction, health)" to the string
	
	void GenerateRandomCommands();

	int GetAvailableCommandCount() const;
};
