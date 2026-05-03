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

    //getting location of da cell
    GameObject* pObject = pGrid->GetClipboard();
    if (pObject)
    {

        if (!pos.IsValidCell())//checking if its out of bounce 
        {
            pGrid->PrintErrorMessage("Invalid cell position. Try again.");
        }
        else
        {
            pObject->SetPosition(pos);//setting the position of the object
        }
        if (pGrid->AddObjectToCell(pObject))//adding the object
        {
            // if cut pastes one time
            if (pGrid->IsClipboardFromCut())
            {
                pGrid->ClearClipboard();
            }
        }
        else
        {
            // cell already has an object
            pGrid->PrintErrorMessage("there is already a cell here");
        }
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