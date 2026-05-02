#include "PasteGameObjectAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "ApplicationManager.h"
//again same idea just different execution mmmm
PasteGameObjectAction::PasteGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
}

void PasteGameObjectAction::ReadActionParameters()
{
    Output* pOut = pManager->GetGrid()->GetOutput();
    Input* pIn = pManager->GetGrid()->GetInput();
    pOut->PrintMessage("Click on cell to paste");
    pos = pIn->GetCellClicked();
    pOut->ClearStatusBar();
}

void PasteGameObjectAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    ReadActionParameters();// sees if there is cut or copy first

   
    GameObject* pObject = pGrid->GetClipboard();
    Cell* ptargetcell = pGrid->GetCell(pos);
    pObject->GetPosition() = pos;
    if (pObject != nullptr)
    {
        
        if (!pos.IsValidCell())//checking if its out of bounce 
        {
            pGrid->PrintErrorMessage("Invalid cell position. Try again.");
        }

        
        if (ptargetcell == nullptr)
        {
            pGrid->PrintErrorMessage("Error finding cell.");
            return;
        }
        if (ptargetcell->GetGameObject() != nullptr)
        {
            pGrid->PrintErrorMessage("There is already an object in this cell!");
            return;
        }
        ptargetcell->SetGameObject(pObject);
        pGrid->SetClipboard(nullptr);
    }
    else
    {

        pGrid->PrintErrorMessage("Clipboard is empty sooo Nothing to paste.");
    }

    pManager->UpdateInterface();
}

PasteGameObjectAction::~PasteGameObjectAction()
{
}
