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

	// a comment indicating that the player fell into water pit 
	pGrid->GetOutput()->PrintMessage("You have fallen into a waterpit and have been sent to the starting cell. Click to cotinue...");
	int x, y;
	pGrid->GetInput()->GetPointClicked(x,y);

	// 2- Apply the water pit's effect by reducing health by 3 w sending to start cell
	int newhealth;
	newhealth = pPlayer ->GetHealth() - 3;
	pPlayer->SetHealth(newhealth); //kda 3mlna new health 

	//nb3to b2a ll bdaya 
	pGrid->UpdatePlayerCell(pPlayer, pGrid->GetStartCell()->GetCellPosition());

	Draw(pGrid->GetOutput());// to reset waterpit cell

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
