#include "WaterPit.h"
#include<fstream>
#include"player.h"
#include"GameState.h"

WaterPit::WaterPit(const CellPosition & waterPitPosition):GameObject(waterPitPosition)
{
}

void WaterPit::Draw(Output * pOut) const
{
	pOut->DrawWaterPit(position);
}

void WaterPit::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///(DONE) TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message, make sure to edit this message according to which player wins "You drowned in a water pit. Player (0/1) wins !  Click to continue ..." and wait mouse click
	if (pPlayer->getPlayerNum() == 0) {
		pGrid->GetOutput()->PrintMessage("You drowned in a water pit. Player 1 wins !  Click to continue ...");
	}
	else {
		pGrid->GetOutput()->PrintMessage("You drowned in a water pit. Player 0 wins !  Click to continue ...");
	}
	int x, y;
	pGrid->GetInput()->GetPointClicked(x,y);

	// 2- Apply the water pit's effect by setting the player's health which drowned to zero and ending the game
	pPlayer->SetHealth(0);
	pState->SetEndGame(true);
	// 3- Update the players info which is displayed (check Grid class and decide which function to use)
	pGrid->UpdateInterface(pState);

	pGrid->GetOutput()->ClearStatusBar();


}
void WaterPit::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum() << " ";
}

void WaterPit::Load(ifstream& Infile)
{
	int cellnum;
	Infile >> cellnum;
	position = CellPosition(cellnum);
}


WaterPit::~WaterPit()
{
}
