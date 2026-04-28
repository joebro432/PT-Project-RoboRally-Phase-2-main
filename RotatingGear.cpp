#include "RotatingGear.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "Player.h" 
#include <fstream>
#include <string>


RotatingGear::RotatingGear(const CellPosition & gearposition,bool clockwise) : GameObject(gearposition)
{
	isClockWise = clockwise;
}

void RotatingGear::Draw(Output* pOut) const
{
	pOut->DrawRotatingGear(position, isClockWise);
}

void RotatingGear::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below DONE
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message and change the message according to direction of rotation 
	// "You have reached a rotating gear, you will rotate (clockwise/ anti-clockwise) Click to continue ..." and wait mouse click
	Output* pOut = pGrid->GetOutput();
	string directionMsg;
	if (isClockWise == true) {
		directionMsg = "clockwise";
	}
	else {
		directionMsg = "counter-clockwise";
	}
	pOut->PrintMessage("You have reached a rotating gear, You will rotate " + directionMsg + ". Click to continue...");


	Input* pIn = pGrid->GetInput();
	pIn->GetCellClicked();


	//2- Apply the roating gear's effect by rotating the player according to the direction

	Direction currentDir;
	currentDir = pPlayer->GetDirection();
	Direction newDir;
	if (isClockWise) {
		// Clockwise rotation: RIGHT/ DOWN / LEFT / UP / RIGHT 
		switch (currentDir) {
		case RIGHT: newDir = DOWN; break;
		case DOWN:  newDir = LEFT; break;
		case LEFT:  newDir = UP;   break;
		case UP:    newDir = RIGHT; break;
		default:    newDir = currentDir; break;
		}
	}
	else {
		// Counter-clockwise rotation: RIGHT/ UP / LEFT / DOWN / RIGHT
		switch (currentDir) {
		case RIGHT: newDir = UP;    break;
		case UP:    newDir = LEFT;  break;
		case LEFT:  newDir = DOWN;  break;
		case DOWN:  newDir = RIGHT; break;
		default:    newDir = currentDir; break;
		}
	}
	pPlayer->SetDirection(newDir);

	pOut->ClearStatusBar();
}
bool RotatingGear::GetisClockWise() const
{
	return isClockWise;
}

RotatingGear::~RotatingGear()
{
}
void RotatingGear::Save(ofstream& OutFile, int type)
{
	// Save cell number and direction (1 for clockwise, 0 for counter-clockwise)
	OutFile << position.GetCellNum() << " ";
	if (isClockWise == true) {
		OutFile << "1 ";
	}
	else {
		OutFile << "0 ";
	}
}
void RotatingGear::Load(ifstream& Infile){
	int dir;
	Infile >> dir;
	isClockWise = (dir == 1);
}