#include "LoadGridAction.h"
#include "ApplicationManager.h"
#include "Grid.h"
#include "Belt.h"
#include <fstream>
#include <string>

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
    //not complete implementation
}


LoadGridAction::~LoadGridAction()
{
}
