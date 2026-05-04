#include "SaveGridAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include <fstream>
SaveGridAction::SaveGridAction(ApplicationManager* pApp): Action(pApp)
{
	// The constructor initializes the ApplicationManager ptr data member of the base Action class
}

void SaveGridAction::ReadActionParameters()
{
	Output* pOut = pManager->GetGrid()->GetOutput(); //output pointer displaying message
	Input* pIn = pManager->GetGrid()->GetInput();  //input pointer to get the cell clicked
	pOut->PrintMessage("Objects saved !");
}

void SaveGridAction::Execute()
{
	ReadActionParameters(); // Reads parameters required for action to execute
	ofstream Outfile("SavedGrid.txt"); // open a file to save the grid data
	if (Outfile.is_open()) // check if the file is open
	{
		pManager->GetGrid()->SaveAll(Outfile); // call the grid's SaveAll function to save the grid data to the file
	pManager->GetGrid()->GetOutput()->PrintMessage("Saving grid to SavedGrid.txt..."); // print a message to the user indicating that the grid is being saved
		Outfile.close(); // close the file after saving
	}
	else
	{
		pManager->GetGrid()->PrintErrorMessage("Error: Unable to open file for saving.");
	}

}

SaveGridAction::~SaveGridAction()
{

}
