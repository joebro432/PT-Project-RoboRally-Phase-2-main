#include "CopyGameObjectAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "ApplicationManager.h"

CopyGameObjectAction::CopyGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
    // Initializes the pManager pointer of Action with the passed pointer
}


void CopyGameObjectAction::ReadActionParameters()// the idea of the action parameters is actually the same as any action class 
{
    Output* pOut = pManager->GetGrid()->GetOutput();
    Input* pIn = pManager->GetGrid()->GetInput();
    pOut->PrintMessage("Click on cell to copy");
    pos = pIn->GetCellClicked();// to get the position of what i want to copy
    pOut->ClearStatusBar();//task is completed so we clear everything
}

void CopyGameObjectAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    ReadActionParameters();

    // if cut restored to og pos
    if (pGrid->IsClipboardFromCut())
    {
        GameObject* pPrevCutObject = pGrid->GetClipboard();
        CellPosition ogsourcepos = pGrid->GetCutSourcePosition();
        if (pPrevCutObject && ogsourcepos.IsValidCell())
        {
            pPrevCutObject->SetPosition(ogsourcepos);
            pGrid->AddObjectToCell(pPrevCutObject);
        }
    }

    //getting location of da cell
    Cell* pCell = pGrid->GetCell(pos);
    if (pCell)
    {
        //js figuring out what object is this
        GameObject* pObject = pCell->GetGameObject();
        if (pObject)
        {
            // Copy the object to clipboard
            pGrid->SetClipboard(pObject, false); // Marked as copy
        }
    }

    pManager->UpdateInterface();
}

CopyGameObjectAction::~CopyGameObjectAction()
{
}
