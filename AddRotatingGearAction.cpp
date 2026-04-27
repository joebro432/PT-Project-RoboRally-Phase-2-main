#include "AddRotatingGearAction.h"

AddRotatingGearAction::AddRotatingGearAction(ApplicationManager * pApp):Action(pApp)
{
}

void AddRotatingGearAction::ReadActionParameters()
{
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	bool valid = false;

	// 2- Read the gearPos
	while (!valid) {
		pOut->PrintMessage("Click on cell to add Rotating Gear");
		gearPos = pIn->GetCellClicked();
		valid = true;

		if(!gearPos.IsValidCell()){
			pGrid->PrintErrorMessage("Invalid cell clicked! Try again !");
			valid = false;
		
		}
		else if(gearPos.GetCellNum() == 1 || gearPos.GetCellNum() == 55) {
			pGrid->PrintErrorMessage("Cannot place gear on 1 or 55 cell! Try again !");
			valid = false;
		}


	}


	// 3- Read whether the direction will be clockwise or not
	valid = false;
	while (!valid) {

		pOut->PrintMessage("Click on 'C' for Clockwise or 'K' for Counter-Clockwise...");
		string input = pIn->GetString(pOut);

	}


	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
}

void AddRotatingGearAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1-Create a rotating gear object
	// 2-get a pointer to the Grid from the ApplicationManager
	// 3-Add the rotating object to the GameObject of its Cell:
	// 4-Check if the rotating gear was added and print an errror message if flag couldn't be added
}

AddRotatingGearAction::~AddRotatingGearAction()
{
}
