#include "AddAntennaAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "ApplicationManager.h"
#include "Antenna.h"
// same as any object
AddAntennaAction::AddAntennaAction(ApplicationManager* pApp) : Action(pApp)
{
}

void AddAntennaAction::ReadActionParameters()
{
    Output* pOut = pManager->GetGrid()->GetOutput();
    Input* pIn = pManager->GetGrid()->GetInput();

    pOut->PrintMessage("Click on a Cell to place anttena");
    pos = pIn->GetCellClicked();
    pOut->ClearStatusBar();
}

void AddAntennaAction::Execute()
{
    ReadActionParameters();

    Grid* pGrid = pManager->GetGrid();
	if (pGrid->GridHasAntenna()) //checks if there is already an antenna in the grid or not
    {
        pGrid->PrintErrorMessage("Error: There is already an antenna in the grid! Maximum 1 is allowed! Click to continue ...");
        return;
    }

    Antenna* pAntenna = new Antenna(pos);//creates an antenna

    
    bool added = pGrid->AddObjectToCell(pAntenna);//added to cell

    if (!added)
    {
        pGrid->PrintErrorMessage("Cell already has an object ");
    }

    pManager->UpdateInterface();
}

AddAntennaAction::~AddAntennaAction()
{
}
