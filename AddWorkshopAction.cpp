#include "AddWorkshopAction.h"

AddWorkshopAction::AddWorkshopAction(ApplicationManager* pApp):Action(pApp){}


void AddWorkshopAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	//validations
	bool valid = false;
	while (!valid) {
		pOut->PrintMessage("Click on workshop position...");
		workshopPos = pIn->GetCellClicked();
		valid = true;
		if (!workshopPos.IsValidCell()) {
			pGrid->PrintErrorMessage("Invalid cell clicked. Try Again !");
			valid = false;
		}
		else if (workshopPos.GetCellNum() == 1 || workshopPos.GetCellNum() == 55) {
			pGrid->PrintErrorMessage("Cannot place workshop on 1 or 55 cell! Try again !");
			valid = false;
		}
	}
	pOut->ClearStatusBar();
}


void AddWorkshopAction::Execute()
{
	ReadActionParameters();
	//workshop object created 
	Workshop* pWorkshop = new Workshop(workshopPos);
	//pointer to grid 
	Grid* pGrid = pManager->GetGrid();
	//add workshop object to gameobject of its cell 
	bool added = pGrid->AddObjectToCell(pWorkshop);
	if (!added) {
		pGrid->PrintErrorMessage("Cell already has an object! Action failed.");
		delete pWorkshop; // avoid memory leak
	}
}


AddWorkshopAction::~AddWorkshopAction(){}