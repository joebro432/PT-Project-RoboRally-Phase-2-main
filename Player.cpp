#include "Player.h"

#include "GameObject.h"
#include "GameState.h"
#include <iostream>

using namespace std;

Player::Player(Cell* pCell, int playerNum)
	: playerNum(playerNum), health(10), currDirection(RIGHT), savedCommandCount(0), maxSavedCommandsForThisRound(5)
{
	this->pCell = pCell;

	// Initialise saved commands to NO_COMMAND
	for (int i = 0; i < MaxSavedCommands; i++)
		savedCommands[i] = NO_COMMAND;

	availableCommandCount = 0;

	for (int i = 0; i < 10; i++)
		availableCommands[i] = NO_COMMAND;

	isHacked = false;

	// Initialize equipment and consumables
	for (int i = 0; i < MaxEquipment; i++)
		equipment[i] = NO_EQUIPMENT;
	equipmentCount = 0;

	for (int i = 0; i < MaxConsumables; i++)
		consumables[i] = NO_CONSUMABLE;
	consumableCount = 0;
}

// ====== Setters and Getters ======

void  Player::SetCell(Cell* cell)   { pCell = cell; }
Cell* Player::GetCell() const       { return pCell; }

void Player::SetHealth(int h)
{
	///(DONE) TODO: Add validation (e.g. clamp to 0..MaxHealth)
	if (h > 0 && h <= 10)
		health = h;
	else if (h <= 0)
		health = 0;
	else if (h > 10)
		health = 10;
}
int Player::GetHealth() const       { return health; }

Direction Player::GetDirection() const      { return currDirection; }
void      Player::SetDirection(Direction d) { currDirection = d; }

// ====== Saved Commands ======

void Player::AddSavedCommand(Command cmd)
{

	if (savedCommandCount >= maxSavedCommandsForThisRound)
		return;

	savedCommands[savedCommandCount++] = cmd;

	// remove from available list
	for (int i = 0; i < availableCommandCount; i++)
	{
		if (availableCommands[i] == cmd)
		{
			availableCommands[i] = NO_COMMAND;
			break;
		}
	}

}

void Player::ClearSavedCommands()
{
	for (int i = 0; i < MaxSavedCommands; i++)
		savedCommands[i] = NO_COMMAND;
	savedCommandCount = 0;
}


int Player::GetSavedCommandCount() const { return savedCommandCount; }


Command Player::GetSavedCommand(int index) const
{
	if (index >= 0 && index < savedCommandCount)
		return savedCommands[index];
	return NO_COMMAND;
}

Command* Player::GetSavedCommands()
{
	return savedCommands;
}



Command* Player::GetAvailableCommands() 
{
	return availableCommands;
}

// ====== Drawing Functions ======


void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];

	///(DONE) TODO: Call the appropriate Output function to draw the player token with playerColor
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor, currDirection);
}

void Player::ClearDrawing(Output* pOut) const
{
	/// (DONE) TODO: Determine the correct background colour for this cell
	//       (hint: may differ from UI.CellColor if cell is a WaterPit or DangerZone)
	color cellColor = UI.CellColor;
	if(pCell->HasWaterPit())
		cellColor = UI.WaterPitsCellColor;
	else if (pCell->HasDangerZone())
		cellColor = UI.DangerZoneCellColor;
	


	///(DONE) TODO: Call the appropriate Output function to draw the token using cellColor (erases it)
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor, currDirection);
}

// ====== Game Logic ======

void Player::Move(Grid* pGrid, GameState* pState)
{
	///(DONE) TODO: Implement this function
// - Execute the saved commands one by one, waiting for a mouse click between each
// - After all commands are executed, apply the game object effect at the final cell (if any)
// - Use CellPosition and Grid to handle movement and cell updates
	if (savedCommandCount <= 0)
		return;

	GameObject* workshopVisited = nullptr;  // Track if player visited a workshop

	for (int i = 0; i < savedCommandCount; i++)
	{
		Command cmd = savedCommands[i];

		// rotations 
		if (cmd == ROTATE_CLOCKWISE)
		{
			ClearDrawing(pGrid->GetOutput());
			switch (currDirection)
			{
			case UP:    currDirection = RIGHT; break;
			case RIGHT: currDirection = DOWN;  break;
			case DOWN:  currDirection = LEFT;  break;
			case LEFT:  currDirection = UP;    break;
			}
			Draw(pGrid->GetOutput());
		}
		else if (cmd == ROTATE_COUNTERCLOCKWISE)
		{
			ClearDrawing(pGrid->GetOutput());
			switch (currDirection)
			{
			case UP:    currDirection = LEFT;  break;
			case LEFT:  currDirection = DOWN;  break;
			case DOWN:  currDirection = RIGHT; break;
			case RIGHT: currDirection = UP;    break;
			}
			Draw(pGrid->GetOutput());
		}
		else if (cmd == NO_COMMAND) continue;
		else
		{
			//Steps
			int steps = 0;
			Direction moveDir = currDirection;

			if (cmd == MOVE_BACKWARD_ONE_STEP || cmd == MOVE_BACKWARD_TWO_STEPS || cmd == MOVE_BACKWARD_THREE_STEPS) {
				switch (currDirection) {
				case UP:    moveDir = DOWN;  break;
				case LEFT:  moveDir = RIGHT;  break;
				case DOWN:  moveDir = UP; break;
				case RIGHT: moveDir = LEFT;    break;
				}

				if (cmd == MOVE_BACKWARD_ONE_STEP)
					steps = 1;
				else if (cmd == MOVE_BACKWARD_TWO_STEPS)
					steps = 2;
				else if (cmd == MOVE_BACKWARD_THREE_STEPS)
					steps = 3;
			}

			else if (cmd == MOVE_FORWARD_ONE_STEP)
				steps = 1;
			else if (cmd == MOVE_FORWARD_TWO_STEPS)
				steps = 2;
			else if (cmd == MOVE_FORWARD_THREE_STEPS)
				steps = 3;
			else
				steps = 0;

			if (steps > 0)
			{
				CellPosition newPos = pCell->GetCellPosition();
				newPos.AddCellNum(steps, moveDir);

				if (newPos.IsValidCell())
				{
					pGrid->UpdatePlayerCell(this, newPos);
					pGrid->UpdateInterface(pState);
					GameObject* obj = pCell->GetGameObject();
					if (obj != NULL && !pCell->HasWorkshop())
					{
						// Apply non-workshop effects immediately
						obj->Apply(pGrid, pState, this);
					}
					else if (obj != NULL && pCell->HasWorkshop())
					{
						// Store workshop for later application
						workshopVisited = obj;
					}
				}
			}
		}

		if (i < savedCommandCount - 1)
		{
			int x, y;
			pGrid->GetInput()->GetPointClicked(x, y);
		}
	}

	// Apply workshop effect after all commands are executed
	if (workshopVisited != nullptr)
	{
		workshopVisited->Apply(pGrid, pState, this);
	}
	// If no workshop was visited but final cell has a workshop, apply it
	else if (pCell->HasWorkshop())
	{
		GameObject* finalObj = pCell->GetGameObject();
		if (finalObj != NULL)
			finalObj->Apply(pGrid, pState, this);
	}
}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	// (DONE) TODO: Modify the Info as needed
	playersInfo += "P" + to_string(playerNum+1) + "("; // +1 to change from [0,1] to [1,2]
	string Strdir;
		switch (currDirection) // Switching Direction to string
		{
		case UP: Strdir = "UP"; break;
		case DOWN: Strdir = "DOWN"; break;
		case RIGHT: Strdir = "RIGHT"; break;
		case LEFT: Strdir =  "LEFT"; break;
		default: Strdir = "UNKNOWN"; break;
		}
	playersInfo += Strdir + ", ";
	playersInfo += to_string(health) + ")";
}


const int Player::getPlayerNum() const
{
	return playerNum;
}

void Player::GenerateRandomCommands()
{
	availableCommandCount = health;
	

	Command base[] = {
		MOVE_FORWARD_ONE_STEP,
		MOVE_BACKWARD_ONE_STEP,
		MOVE_FORWARD_TWO_STEPS,
		MOVE_BACKWARD_TWO_STEPS,
		MOVE_FORWARD_THREE_STEPS,
		MOVE_BACKWARD_THREE_STEPS,
		ROTATE_CLOCKWISE,
		ROTATE_COUNTERCLOCKWISE
	};

	for (int i = 0; i < 10; i++)
	{
		int randomNumber = rand() % 8;	
		availableCommands[i] = base[randomNumber];
	}
		savedCommandCount = 0; // reset every round
}

int Player::GetAvailableCommandCount() const
{
	return availableCommandCount;
}

Command Player::GetAvailableCommand(int index) const
{
	if (index >= 0 && index < availableCommandCount)
		return availableCommands[index];

	return NO_COMMAND;
}

// ====== Equipment and Consumables ======

void Player::AddEquipment(Equipment equip)
{
	if (equipmentCount < MaxEquipment && equip != NO_EQUIPMENT)
	{
		equipment[equipmentCount++] = equip;
		// If extended memory, increase max saved commands
		if (equip == EXTENDED_MEMORY)
		{
			// This requires modifying MaxSavedCommands or creating a dynamic limit
			// For now, we'll just track that they have it
		}
	}
}

bool Player::HasEquipment(Equipment equip) const
{
	for (int i = 0; i < equipmentCount; i++)
	{
		if (equipment[i] == equip)
			return true;
	}
	return false;
}

int Player::GetEquipmentCount() const
{
	return equipmentCount;
}

bool Player::HasExtendedMemory() const
{
	return HasEquipment(EXTENDED_MEMORY);
}



void Player::AddConsumable(Consumable cons)
{
	if (consumableCount < MaxConsumables && cons != NO_CONSUMABLE)
	{
		consumables[consumableCount++] = cons;
	}
}

bool Player::HasConsumable(Consumable cons) const
{
	for (int i = 0; i < consumableCount; i++)
	{
		if (consumables[i] == cons)
			return true;
	}
	return false;
}

Consumable Player::GetConsumable(int index) const
{
	if (index >= 0 && index < consumableCount)
		return consumables[index];
	return NO_CONSUMABLE;
}

void Player::RemoveConsumable(Consumable cons)
{
	for (int i = 0; i < consumableCount; i++)
	{
		if (consumables[i] == cons)
		{
			// Shift remaining consumables down
			for (int j = i; j < consumableCount - 1; j++)
			{
				consumables[j] = consumables[j + 1];
			}
			consumables[consumableCount - 1] = NO_CONSUMABLE;
			consumableCount--;
			break;
		}
	}
}

int Player::GetConsumableCount() const
{
	return consumableCount;
}

int Player::GetMaxSavedCommandsForThisRound() const
{
	// Base is min(5, health), but Extended Memory allows 6
	int baseLimit = min(5, health);
	if (HasExtendedMemory())
		baseLimit = min(6, health);
	return baseLimit;
}

void Player::UpdateMaxSavedCommandsForThisRound()
{
	maxSavedCommandsForThisRound = GetMaxSavedCommandsForThisRound();
}

bool Player::UseToolkit()
{
	if (!HasConsumable(TOOLKIT))
		return false;

	// Repair health by 3
	int newHealth = health + 3;
	if (newHealth > 10)
		newHealth = 10;
	SetHealth(newHealth);
	RemoveConsumable(TOOLKIT);
	return true;
}

bool Player::UseHackDevice(Player* targetPlayer)
{
	if (!HasConsumable(HACK_DEVICE) || !targetPlayer)
		return false;

	// Mark the target player as hacked (will skip their turn)
	targetPlayer->SetIsHacked(true);
	RemoveConsumable(HACK_DEVICE);
	return true;
}

bool Player::IsHacked() const
{
	return isHacked;
}

void Player::SetIsHacked(bool hacked)
{
	isHacked = hacked;
}

void Player::ResetHackState()
{
	isHacked = false;
}



