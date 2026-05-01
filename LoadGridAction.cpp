#include "LoadGridAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Belt.h"
#include <fstream>
#include <string>
#include "DangerZone.h"
#include "Antenna.h"
#include "WaterPit.h"
#include "Workshop.h"
#include "RotatingGear.h"
#include "Flag.h"

LoadGridAction::LoadGridAction(ApplicationManager* pApp)
    : Action(pApp)
{
}

void LoadGridAction::ReadActionParameters()
{
  //no parameters to read  
}

void LoadGridAction::Execute()
{
    ReadActionParameters(); // Reads parameters required for action to execute
    ifstream Infile("SavedGrid.txt"); // open the file to load the grid data from it
    if (!Infile.is_open()) // check if the file is open
    {
        pManager->GetGrid()->PrintErrorMessage("Error: Unable to open file for loading.");
        return;
    }
    Grid *pGrid= pManager->GetGrid(); // get the grid pointer from the application manager
    string type; // to store the type of the game object in each line of the file
    while (Infile >> type) // read the file line by line
    {
        if (type == "Belt") // if the line indicates a belt obj
        {
            int startCell, endCell;
            Infile >> startCell >> endCell; // read the belt's start and end cell
            Belt *pBelt = new Belt(CellPosition(startCell), CellPosition(endCell)); // create a new belt object with the read data
            pGrid->AddObjectToCell(pBelt); // add the belt to the grid

        }
        else if (type == "Flag")// if the line indicates flag obj
        {
            int cellNum;
            Infile >> cellNum;// read the flag's cell number
            Flag *pFlag = new Flag(CellPosition(cellNum)); // create a new flag object with the read data
            pGrid->AddObjectToCell(pFlag); // add the flag to the grid
        }
        else if (type == "DangerZone")//indicating if the obj is dangerzone
        {
            int cellNum;
            Infile >> cellNum;// read the dangerzone's cell number
            DangerZone* pDangerZone = new DangerZone(CellPosition(cellNum)); // create a new dangerzone object with the read data
            pGrid->AddObjectToCell(pDangerZone); // add the dangerzone to the grid

        }
        else if (type == "WaterPit")
        {
            int cellNum;
            Infile >> cellNum;// read the waterpit's cell number
            WaterPit* pWaterPit = new WaterPit(CellPosition(cellNum)); // create a new waterpit object with the read data
            pGrid->AddObjectToCell(pWaterPit); // add the waterpit to the grid

        }
        else if (type == "Workshop")
        {
            int cellNum;
            Infile >> cellNum;// read the workshop's cell number
          //  Workshop* pWork = new Workshop(CellPosition(cellNum));
           // pGrid->AddObjectToCell(pWork); // add the workshop to the grid
        }
        else if (type == "Antenna") 
        {
            int cellNum;
            Infile >> cellNum;
            Antenna* pAnt = new Antenna(CellPosition(cellNum));
                        pGrid->AddObjectToCell(pAnt);

        }
        else if (type == "RotatingGear")
        {
            int cellNum, rotationDir;
            Infile >> cellNum >> rotationDir;
            RotatingGear* pGear = new RotatingGear(CellPosition(cellNum), rotationDir);
            pGrid->AddObjectToCell(pGear);
        }
    }
    Infile.close(); // close the file after loading
         pManager->UpdateInterface(); // update the interface to show the loaded grid
}


LoadGridAction::~LoadGridAction()
{
}
