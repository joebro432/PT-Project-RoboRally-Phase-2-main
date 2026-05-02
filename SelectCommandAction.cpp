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

    int commandcounter = pIn->GetSelectedCommandIndex();

  // we could use cast or enum but forbidden so logically copy paste avaliable commands
    Command availableCommands[] = {
        MOVE_FORWARD_ONE_STEP,
        MOVE_BACKWARD_ONE_STEP,
        MOVE_FORWARD_TWO_STEPS,
        MOVE_BACKWARD_TWO_STEPS,
        MOVE_FORWARD_THREE_STEPS,
        MOVE_BACKWARD_THREE_STEPS,
        ROTATE_CLOCKWISE,
        ROTATE_COUNTERCLOCKWISE
    };

    if (commandcounter >= 0 && commandcounter < 8)// 8 commands
    {
        selectedCommand = availableCommands[commandcounter];
    }
    else
    {
        selectedCommand = NO_COMMAND;
    }
}
// same idea of any action
void SelectCommandAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    GameState* pState = pManager->GetGameState();
    Output* pOut = pGrid->GetOutput();

    if (!pState || !pGrid || selectedCommand == NO_COMMAND)
    {
        pGrid->PrintErrorMessage("Invalid command selection!");
        return;
    }

  
    if (pState->GetCurrentPhase() != PHASE_PLANNING)//making sure that its plan phase
    {
        pGrid->PrintErrorMessage("Commands can only be selected during the Planning phase");
        return;
    }

    Player* currentplayer = pState->GetCurrentPlayer();
    if (!currentplayer)
    {
        return;
    }

    
    currentplayer->AddSavedCommand(selectedCommand);//adds the command

   
    pManager->UpdateInterface();//redraw the command interface
}

SelectCommandAction::~SelectCommandAction()
{
}
