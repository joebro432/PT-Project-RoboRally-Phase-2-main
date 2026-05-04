#include "Workshop.h"
#include "Player.h"
#include "GameState.h"
#include<fstream>
#include"Grid.h"
#include "Output.h"
#include "Input.h"

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

	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 1. Repair the robot - increase health by 3
	pPlayer->SetHealth(pPlayer->GetHealth() + 3);
	pOut->PrintMessage("Welcome to the workshop! Your robot has been repaired (+3 health). Click to continue...");
	int x, y;
	pIn->GetPointClicked(x, y);

	// 2. Offer equipment and consumables at the workshop
	pOut->PrintMessage("Choose an item: [1] Toolkit (Repair without workshop) [2] Hack Device (Disable opponent) [3] Extended Memory (6 commands) [4] Double Laser (2 damage)");
	pIn->GetPointClicked(x, y);

	// For now, give a random item (can be made interactive later)
	int randomItem = rand() % 4;

	switch (randomItem)
	{
	case 0: // Toolkit
		pPlayer->AddConsumable(TOOLKIT);
		pOut->PrintMessage("You received: Toolkit (one-time repair)!");
		break;
	case 1: // Hack Device
		pPlayer->AddConsumable(HACK_DEVICE);
		pOut->PrintMessage("You received: Hack Device (disable opponent this round)!");
		break;
	case 2: // Extended Memory
		pPlayer->AddEquipment(EXTENDED_MEMORY);
		pOut->PrintMessage("You received: Extended Memory (can now save 6 commands)!");
		break;
	case 3: // Double Laser
		pPlayer->AddEquipment(DOUBLE_LASER);
		pOut->PrintMessage("You received: Double Laser (2 damage per shot)!");
		break;
	}

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
