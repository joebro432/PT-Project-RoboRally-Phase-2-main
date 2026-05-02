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
        
            pGrid->SetClipboard(pObject);//uses for copy or cut

            pCell->SetGameObject(nullptr);//removes the object but doesnt delete it so it can be pasted successfully
        }
    }

    pManager->UpdateInterface();
}

CutGameObjectAction::~CutGameObjectAction()
{
}
