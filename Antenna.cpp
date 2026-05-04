#include "Antenna.h"
#include "GameState.h"
#include "Player.h"
#include <fstream>

//function to calculate the distance, used in Apply
int absolute(int a, int b) {
	return (a - b < 0) ? -(a - b) : (a - b);
}


Antenna::Antenna(const CellPosition & antennaPosition):GameObject(antennaPosition)
{
}

void Antenna::Draw(Output * pOut) const
{
	pOut->DrawAntenna(position);
}

void Antenna::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

	///(DONE) TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "the antenna will decide the turn of players. Click to continue ..." and wait mouse click
	
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("The antenna will decide the turn of players. Click to continue...");
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);
	
	// 2- Determine turn order based on each player's distance from the antenna.
	//    Hint: distance = |dV| + |dH|
	//    The player closest to the antenna plays first. Ties are broken by player number.
	//    Use pState to update the turn order accordingly.
	
	Player* p1 = pState->GetPlayer(0);
	Player* p2 = pState->GetPlayer(1);

	CellPosition antennaPos = this->GetPosition();
	CellPosition p1Pos = p1->GetCell()->GetCellPosition();
	CellPosition p2Pos = p2->GetCell()->GetCellPosition();

	int d1 = absolute(antennaPos.VCell(), p1Pos.VCell()) + absolute(antennaPos.HCell(), p1Pos.HCell());

	int d2 = absolute(antennaPos.VCell(), p2Pos.VCell()) + absolute(antennaPos.HCell(), p2Pos.HCell());

	int firstIndex;

	if (d1 < d2) {
		firstIndex = 0;
	}
	else if (d2 < d1) {
		firstIndex = 1;
	}
	else { // tie
		firstIndex = (p1->getPlayerNum() < p2->getPlayerNum()) ? 0 : 1;
	}

	pState->SetFirstPlayer(firstIndex);
	// 3- Print a message indicating which player will play first
	Player* first = pState->GetPlayer(firstIndex);

	pOut->PrintMessage("Player " + to_string(first->getPlayerNum() + 1) + " will play first! Click to continue...");
	pGrid->GetInput()->GetPointClicked(x, y);

	// Reset hack flags for the new round
	pState->ResetHackedStates();

	pGrid->UpdateInterface(pState);
	pOut->ClearStatusBar();

}


Antenna::~Antenna()
{
}


void Antenna::Save(ofstream& OutFile) {
	OutFile << "ANTENNA" << " " << position.GetCellNum() << endl;
		//save el cell position bta3t el antenna 
}


void Antenna::Load(ifstream& Infile) {

	int cellnum;
	Infile >> cellnum;
	position = CellPosition(cellnum);
}