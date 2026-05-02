#include "Belt.h"
#include "RotatingGear.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "Player.h"     
#include <fstream>
#include <string>


Belt::Belt(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{

	if (startCellPos.VCell() != endCellPos.VCell() &&
		startCellPos.HCell() != endCellPos.HCell()) {
		// Diagonal belt so belt does nothing
		this->endCellPos = startCellPos;
	}
	// Check if start and end are the same cell
	else if (startCellPos.GetCellNum() == endCellPos.GetCellNum()) {
		// Same cell belt does nothing
		this->endCellPos = startCellPos;
	}
	else {
		// Valid belt
		this->endCellPos = endCellPos;
	}
	///TODO: Do the needed validation DONE 
}
void Belt::Draw(Output* pOut) const
{
	pOut->DrawBelt(position, endCellPos);
}

void Belt::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below DONE


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a belt. Click to continue ..." and wait mouse click
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	pOut->PrintMessage("You have reached a belt! You will be moved along the belt. Click to continue.");
	int x, y;
	pGrid->GetInput()->GetPointClicked(x, y);



	// 2- Apply the belt's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for thatr 

	// Move player to the end position of the belt
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

	// Clear status bar after move
	pOut->ClearStatusBar();


}
CellPosition Belt::GetEndPosition() const
{
	return endCellPos;
}

void Belt::Save(ofstream& OutFile)
{
	// Saves start cell and end cell
	OutFile << position.GetCellNum() << " " << endCellPos.GetCellNum() << " ";
}


void Belt::Load(ifstream& Infile)
{

	int endcell;
	int startcell;
	Infile >> endcell>>startcell;
	
	endCellPos = CellPosition::GetCellPositionFromNum(endcell); 
	position = CellPosition::GetCellPositionFromNum(startcell);
}





Belt::~Belt()
{
}
