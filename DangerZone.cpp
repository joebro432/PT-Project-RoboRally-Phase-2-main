#include "DangerZone.h"
#include <fstream>
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "Player.h"
#include "GameState.h"

DangerZone::DangerZone(const CellPosition & dangerZonePosition): GameObject(dangerZonePosition)
{
}

void DangerZone::Draw(Output * pOut) const
{
	pOut->DrawDangerZone(position);
}

void DangerZone::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	///TODO:(DONE) Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a danger zone. Click to continue ..." and wait mouse click
	pGrid->GetOutput()->PrintMessage("You have reached a danger zone. Click to continue ...");
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);
	// 2- Apply the danger zone's effect by reducing the health of the player by 1 
	int health = pPlayer->GetHealth();
	int newHealth = health - 1;
	pPlayer->SetHealth(newHealth);//new health ll player 

	//hn display message ll user 
	pGrid->GetOutput()->PrintMessage("Your Health has been reduced by 1. Click to continue... ");
	pGrid->GetInput()->GetPointClicked(x, y);

	//check lw hwa kda dead
	if (newHealth <= 0) {
		pGrid->GetOutput()->PrintMessage("You have fallen into a danger zone and lost the game! Click to continue ...");
		pGrid->GetInput()->GetPointClicked(x, y);
		pState->SetEndGame(true);
	}
	
	// 3- Update the players info which is displayed (check Grid class and decide which function to use)
	pGrid->UpdateInterface(pState);
	pGrid->GetOutput()->ClearStatusBar();
}


DangerZone::~DangerZone()
{
}
void DangerZone::Save(ofstream& OutFile)
{
	OutFile << "DANGERZONE" << " " << position.GetCellNum() << endl;
}
void DangerZone::Load(ifstream& Infile)
{
	int cellnum;
	Infile >> cellnum;

	position= CellPosition(cellnum);


}