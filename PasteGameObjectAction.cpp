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
//
//void PasteGameObjectAction::Execute()
//{
//    Grid* pGrid = pManager->GetGrid();
//    ReadActionParameters();// sees if there is cut or copy first
//
//    //getting location of da cell
//    GameObject* pObject = pGrid->GetClipboard();
//    if (pObject)
//    {
//
//        if (!pos.IsValidCell())//checking if its out of bounce 
//        {
//            pGrid->PrintErrorMessage("Invalid cell position. Try again.");
//        }
//        else
//        {
//            pObject->SetPosition(pos);//setting the position of the object
//        }
//        if (pGrid->AddObjectToCell(pObject))//adding the object
//        {
//            // if cut pastes one time
//            if (pGrid->IsClipboardFromCut())
//            {
//                pGrid->ClearClipboard();
//            }
//        }
//        else
//        {
//            // cell already has an object
//            pGrid->PrintErrorMessage("there is already an object here");
//        }
//    }
//    else
//    {
//
//        pGrid->PrintErrorMessage("Clipboard is empty sooo Nothing to paste.");
//    }
//
//    pManager->UpdateInterface();
//}

void PasteGameObjectAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    ReadActionParameters();

    GameObject* pObject = pGrid->GetClipboard();
    if (pObject)
    {
        if (!pos.IsValidCell())
        {
            pGrid->PrintErrorMessage("Invalid cell position. Try again.");
            pManager->UpdateInterface();
            return;
        }

        // Check if destination cell has a water pit or other object
        Cell* pDestCell = pGrid->GetCell(pos);
        if (pDestCell && (pDestCell->HasWaterPit() || pDestCell->GetGameObject()))
        {
            pGrid->PrintErrorMessage("Cannot paste on a cell with an object");
            pManager->UpdateInterface();
            return;
        }

        // Set position and add to cell
        pObject->SetPosition(pos);

        if (pGrid->AddObjectToCell(pObject))
        {
            if (pGrid->IsClipboardFromCut())
            {
                pGrid->ClearClipboard();
            }
        }
        else
        {
            pGrid->PrintErrorMessage("Cannot paste object here.");
        }
    }
    else
    {
        pGrid->PrintErrorMessage("Clipboard is empty. Nothing to paste.");
    }

    pManager->UpdateInterface();
}

PasteGameObjectAction::~PasteGameObjectAction()
{
}