#include "Player.h"

#include "GameObject.h"
#include "GameState.h"
#include <iostream>

Player::Player(Cell* pCell, int playerNum)
	: playerNum(playerNum), health(10), currDirection(RIGHT), savedCommandCount(0)
{
	this->pCell = pCell;

	// Initialise saved commands to NO_COMMAND
	for (int i = 0; i < MaxSavedCommands; i++)
		savedCommands[i] = NO_COMMAND;

	availableCommandCount = 0;

	for (int i = 0; i < 10; i++)
		availableCommands[i] = NO_COMMAND;

	laserDamage = 1;
	isHacked = false;
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
	
	if (savedCommandCount >= 5)
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

	for (int i = 0; i < savedCommandCount; i++)
	{
		Command cmd = savedCommands[i];

        // rotations 
		if (cmd == ROTATE_CLOCKWISE)
		{
			switch (currDirection)
			{
			case UP:    currDirection = RIGHT; break;
			case RIGHT: currDirection = DOWN;  break;
			case DOWN:  currDirection = LEFT;  break;
			case LEFT:  currDirection = UP;    break;
			}
		}
		else if (cmd == ROTATE_COUNTERCLOCKWISE)
		{
			switch (currDirection)
			{
			case UP:    currDirection = LEFT;  break;
			case LEFT:  currDirection = DOWN;  break;
			case DOWN:  currDirection = RIGHT; break;
			case RIGHT: currDirection = UP;    break;
			}
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
					if (obj!= NULL && !pCell->HasWorkshop())
						obj->Apply(pGrid, pState, this);
				}
			}
		}
        

		if (i < savedCommandCount - 1)
		{
			int x, y;
			pGrid->GetInput()->GetPointClicked(x, y);
		}
	}

	GameObject* finalObj = pCell->GetGameObject();

	if (finalObj != NULL && pCell->HasWorkshop())
		finalObj->Apply(pGrid, pState, this);

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
	availableCommandCount = 10;

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
		availableCommands[i] = base[i%8];

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



