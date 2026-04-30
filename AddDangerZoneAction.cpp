#include "AddDangerZoneAction.h"

AddDangerZoneAction::AddDangerZoneAction(ApplicationManager *pApp) : Action(pApp)
{
}
void AddDangerZoneAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput(); //pointer to input and output 
	bool valid = false; //hnbda2 n get the cell where we want the danger zone to be with validation logic 
	while (!valid) {
		pOut->PrintMessage("Click on danger zone position...");
		DangerZonePos = pIn->GetCellClicked();
		valid = true;
		if (!DangerZonePos.IsValidCell()) {
			pGrid->PrintErrorMessage("Invalid cell clicked. Try Again !");
			valid = false;
		}
		else if (DangerZonePos.GetCellNum() == 1 || DangerZonePos.GetCellNum() == 55) {
			pGrid->PrintErrorMessage("Cannot place Danger Zone  on 1 or 55 cell! Try again !");
			valid = false;
		}
	}
	pOut->ClearStatusBar();
}

void AddDangerZoneAction::Execute()
{
	ReadActionParameters();
	DangerZone* pDangerZone = new DangerZone(DangerZonePos);
	Grid* pGrid = pManager->GetGrid();
	bool added = pGrid->AddObjectToCell(pDangerZone);
	if (!added) {
		pGrid->PrintErrorMessage("Cell already has an object! Action failed. Click to continue...");
		int x, y;
		pGrid->GetInput()->GetPointClicked(x, y);
		delete pDangerZone; // Avoid memory leak
	}
}
AddDangerZoneAction::~AddDangerZoneAction()
{ //destructor 3ady gdn 
}