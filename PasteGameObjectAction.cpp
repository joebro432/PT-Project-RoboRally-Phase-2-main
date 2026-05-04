#include "PasteGameObjectAction.h"
#include "Grid.h"
#include "Output.h"
#include "Input.h"
#include "ApplicationManager.h"
#include <fstream>
#include "Belt.h"
#include "Flag.h"
#include "WaterPit.h"
#include "DangerZone.h"
#include "Workshop.h"
#include "Antenna.h"
#include "RotatingGear.h"
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
    GameObject* pClipboard = pGrid->GetClipboard();
    if (!pClipboard)
        return;

    //CUT  move object
    if (pGrid->IsClipboardFromCut())
    {
        pClipboard->SetPosition(pos);
        pGrid->AddObjectToCell(pClipboard);
        pGrid->ClearClipboard();
    }
    else
    {


        //  Save clipboard object temporarily
        ofstream tempOut("temp.txt");
        pClipboard->Save(tempOut);
        tempOut.close();


        ifstream tempIn("temp.txt");// Open the temporary file to read the saved data

        GameObject* newObj = nullptr;


        string type;
        tempIn >> type;


        // Create correct object
        if (type == "BELT")
        {
            newObj = new Belt(CellPosition(1), CellPosition(1));
        }
        else if (type == "FLAG")
        {
            
                pGrid->PrintErrorMessage("there is a flag already placed");
            
            
        }
        else if (type == "DANGERZONE")
        {
            newObj = new DangerZone(CellPosition(1));
        }
        else if (type == "WATERPIT")
        {
            newObj = new WaterPit(CellPosition(1));
        }
        else if (type == "WORKSHOP")
        {
            newObj = new Workshop(CellPosition(1));
        }
        else if (type == "ANTENNA")
        {
           
            pGrid->PrintErrorMessage("there is an antenna already placed");
        }
        else if (type == "ROTATINGGEAR")
        {
            newObj = new RotatingGear(CellPosition(1), 0);
        }

        // load data into object
        if (newObj)
        {
            newObj->Load(tempIn);
            newObj->SetPosition(pos);
            pGrid->AddObjectToCell(newObj);
        }

        tempIn.close();

        if (newObj)
        {
            newObj->SetPosition(pos);
            pGrid->AddObjectToCell(newObj);
        }


        pManager->UpdateInterface();

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
        }

    }
}


PasteGameObjectAction::~PasteGameObjectAction()
{
}