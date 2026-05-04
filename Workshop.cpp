#include "Workshop.h"
#include "Player.h"
#include "GameState.h"
#include<fstream>
#include"Grid.h"

Workshop::Workshop(const CellPosition & workshopPosition):GameObject( workshopPosition)
{

}


void Workshop::Draw(Output * pOut) const
{
	pOut->DrawWorkshop(position);
}

void Workshop::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	///TODO: Implement this function
	// Apply the workshop's effect on the player
	// [OPTIONAL BONUS] Consumables can be given to the player here

	if (!pPlayer) return;

	pPlayer->SetHealth(pPlayer->GetHealth()+3); // Increase player's health by 3

	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("You have reached a workshop, your health will increase! Click to continue...");

	Input* pIn = pGrid->GetInput();
	int x, y;
	pIn->GetPointClicked(x, y);
	pGrid->UpdateInterface(pState);
	pOut->ClearStatusBar();

}

Workshop::~Workshop()
{
}

void Workshop::Save(ofstream& OutFile)
{
	// Save the cell number of the workshop
	OutFile <<"WORKSHOP" <<" "<< position.GetCellNum() << " ";
}

void Workshop::Load(ifstream& Infile)
{
	int cellnum;
	Infile >> cellnum;
	position = CellPosition(cellnum);
}
