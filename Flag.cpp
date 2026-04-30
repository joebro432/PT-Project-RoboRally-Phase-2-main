#include "Flag.h"
#include"Player.h"
#include"GameState.h"
#include <fstream>
Flag::Flag(const CellPosition & flagposition) : GameObject(flagposition)
{

}

void Flag::Draw(Output* pOut) const
{
	pOut->DrawFlag(position);
}

void Flag::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a flag. Click to continue ..." and wait mouse click
	pGrid->GetOutput()->PrintMessage("You have reached a flag. Click to continue ...");
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);
	// 2- Apply the flag's effect by ending the game
	//    Review the "pGrid" functions and decide which function can be used for that

	if (pPlayer->getPlayerNum() == 0) 
		pGrid->GetOutput()->PrintMessage("Player 1 wins! Click to continue ...");
	else
		pGrid->GetOutput()->PrintMessage("Player 2 wins! Click to continue ...");

	pGrid->GetInput()->GetPointClicked(x, y);
	pState->SetEndGame(true);
   
}

Flag::~Flag()
{

}
void Flag::Save(ofstream& OutFile)
{
	// Save the cell number of the flag
	OutFile << position.GetCellNum() << " ";
}

void Flag::Load(ifstream& Infile)
{
}