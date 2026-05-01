#include "CutGameObjectAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "ApplicationManager.h"
//same idea as copy but this time we just delete the selected object
CutGameObjectAction::CutGameObjectAction(ApplicationManager* pApp) : Action(pApp)
{
}

void CutGameObjectAction::ReadActionParameters()
{
    Output* pOut = pManager->GetGrid()->GetOutput();
    Input* pIn = pManager->GetGrid()->GetInput();
    pOut->PrintMessage("Click on cell to cut ");
    pos = pIn->GetCellClicked();
    pOut->ClearStatusBar();
}

void CutGameObjectAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    ReadActionParameters();

    //getting location of da cell
    Cell* pCell = pGrid->GetCell(pos);
    if (pCell)
    {
        //js figuring out what object is this
        GameObject* pObject = pCell->GetGameObject();
        if (pObject)
        {
            // Cut the object 
            pGrid->SetClipboard(pObject);
            pGrid->RemoveObjectFromCell(pos);//the only difference
        }
    }

    pManager->UpdateInterface();
}

CutGameObjectAction::~CutGameObjectAction()
{
}
