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
	pManager->GetGrid()->GetOutput()->PrintMessage("Loading grid from SavedGrid.txt..."); // print a message to the user indicating that the grid is being loaded
    while (Infile >> type) // read the file line by line
    {
        GameObject* pObj = nullptr;
        if (type == "Belt")
        {
            pObj = new Belt(CellPosition(1), CellPosition(1)); // create a temporary belt object to call the Load function and read the belt data from the file
        }
        else if (type == "Flag")
        {
            pObj = new Flag(CellPosition(1));// create a temporary flag object to call the Load function and read the flag data from the file
        }
        else if (type == "DangerZone")
        {
            pObj = new DangerZone(CellPosition(1));//same for dangerzone
        }
        else if (type == "WaterPit")
        {
            pObj = new WaterPit(CellPosition(1));//same for waterpit
        }
        else if (type == "Workshop")
        {
            CellPosition pos(1);
            pObj = new Workshop(pos); //same for workshop
        }
        else if (type == "Antenna")
        {
            pObj = new Antenna(CellPosition(1));//same for antenna
        }
        else if (type == "RotatingGear")
        {
            pObj = new RotatingGear(CellPosition(1), 0);//same for rotatinggear
        }
        if (pObj != nullptr)
        {
            pObj->Load(Infile);               // object reads its own data
            pGrid->AddObjectToCell(pObj);     // then added to grid
        }
    
    }
    Infile.close(); // close the file after loading
         pManager->UpdateInterface(); // update the interface to show the loaded grid
}


LoadGridAction::~LoadGridAction()
{
}
