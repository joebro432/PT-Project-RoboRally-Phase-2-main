#include "SelectCommandAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"

SelectCommandAction::SelectCommandAction(ApplicationManager* pApp) : Action(pApp)
{
    selectedCommand = NO_COMMAND;//as initializer
}

void SelectCommandAction::ReadActionParameters()
{
    Grid* pGrid = pManager->GetGrid();
    Input* pIn = pGrid->GetInput();

    int x, y;
    pIn->GetPointClicked(x, y);

    Player* pPlayer = pManager->GetGameState()->GetCurrentPlayer();

    // Calculate slot index based on available commands position and size
    // Available commands are drawn starting at AvailableCommandsXOffset with width = CommandItemWidth/2
    int availableCommandWidth = UI.CommandItemWidth / 2;

    // Check if click is within the available commands area horizontally
    if (x < UI.AvailableCommandsXOffset)
    {
        selectedCommand = NO_COMMAND;
        return;
    }

    // Calculate which slot was clicked
    int relativeX = x - UI.AvailableCommandsXOffset;
    int slotIndex = relativeX / availableCommandWidth;

    // Validate slot index
    if (slotIndex < 0 || slotIndex >= pPlayer->GetAvailableCommandCount())
    {
        selectedCommand = NO_COMMAND;
        return;
    }

    selectedCommand = pPlayer->GetAvailableCommands()[slotIndex];
}

void SelectCommandAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    GameState* pState = pManager->GetGameState();
    Output* pOut = pGrid->GetOutput();

    

    if (!pState || !pGrid)
    {
        pGrid->PrintErrorMessage("Invalid command selection!");
        return;
    }

  
    if (pState->GetCurrentPhase() != PHASE_PLANNING)//making sure that its plan phase
    {
        pGrid->PrintErrorMessage("Commands can only be selected during the Planning phase");
        return;
    }
    ReadActionParameters();
    Player* currentplayer = pState->GetCurrentPlayer();
    if (!currentplayer)
    {
        return;
    }
	if (selectedCommand == NO_COMMAND)
    {
        pGrid->PrintErrorMessage("Please click on a valid command!");
        return;
    }
    int maxCommands = min(5, currentplayer->GetHealth());


	if (currentplayer->GetSavedCommandCount() >= maxCommands)
    {
        pGrid->PrintErrorMessage("You have reached the maximum number of commands for this round!");
        return;
    }
    pOut->PrintMessage("Please Select a command!");
    currentplayer->AddSavedCommand(selectedCommand);//adds the command

   
    pManager->UpdateInterface();//redraw the command interface
}

SelectCommandAction::~SelectCommandAction()
{
}
