#include "AddWaterPitAction.h"
AddWaterPitAction::AddWaterPitAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddWaterPitAction::~AddWaterPitAction()
{
}

void AddWaterPitAction::ReadActionParameters()
{
	//pointer ll input w el output 
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//validations
	bool valid = false;
	while (!valid) {
		pOut->PrintMessage("Click on water pit position...");
		pitpos = pIn->GetCellClicked();
		valid = true;
		if (!pitpos.IsValidCell()) {
			pGrid->PrintErrorMessage("Invalid cell clicked. Try Again !");
			valid = false;
		}
		else if (pitpos.GetCellNum() == 1 || pitpos.GetCellNum() == 55) {
			pGrid->PrintErrorMessage("Cannot place water pit on 1 or 55 cell! Try again !");
			valid = false;
		}
	}
	pOut->ClearStatusBar();
}


void AddWaterPitAction::Execute() {
	ReadActionParameters();
	//waterpit object created 
	WaterPit* pWaterPit = new WaterPit(pitpos);
	//pointer to grid 
	Grid* pGrid = pManager->GetGrid();
	//add waterpit object to gameobject of its cell 
	bool added = pGrid->AddObjectToCell(pWaterPit);

	if (!added) {
		pGrid->PrintErrorMessage("Cell already has an object! Action failed.");
		delete pWaterPit; // avoid memory leak
	}
}

