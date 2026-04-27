#include "DeleteGameObject.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "ApplicationManager.h"
DeleteGameObject::DeleteGameObject(ApplicationManager* pApp): Action(pApp)
{
}

void DeleteGameObject::ReadActionParameters()
{
	Output* pOut = pManager->GetGrid()->GetOutput(); //output pointer displaying message
		Input* pIn = pManager->GetGrid()->GetInput();  //input pointer to get the cell clicked
		pOut->PrintMessage("Click on cell to delete its object");
				pos = pIn->GetCellClicked();  //get the cell position of the clicked cell
				pOut->ClearStatusBar(); //clear the status bar after getting the cell position
				
}

void DeleteGameObject::Execute()
{
	Grid* pGrid = pManager->GetGrid(); //get the grid pointer to access its functions
	ReadActionParameters(); //read the action parameters (the cell position of the object to delete)
	pGrid->RemoveObjectFromCell(pos); //remove the object from the cell of the passed position
	pManager->UpdateInterface(); //update the interface so the deletion of the object appears on the grid
}

DeleteGameObject::~DeleteGameObject()
{
}
