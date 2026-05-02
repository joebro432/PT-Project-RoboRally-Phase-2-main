#include "RebootAndRepairAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"

RebootAndRepairAction::RebootAndRepairAction(ApplicationManager* pApp) : Action(pApp)
{
}

void RebootAndRepairAction::ReadActionParameters()
{
//none needed
}

void RebootAndRepairAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    GameState* pState = pManager->GetGameState();
    Output* pOut = pGrid->GetOutput();

    if (!pState || !pGrid)
    {
        return;
    }

    Player* currentplayer = pState->GetCurrentPlayer();
    if (!currentplayer)
    {
        return;
    }

    
    int currentHealth = currentplayer->GetHealth();//go back to 10 health
    if (currentHealth < 10)
    {
        currentplayer->SetHealth(10);
        pGrid->PrintErrorMessage("Player repaired! Health restored to 10.");
    }
    else
    {
        pGrid->PrintErrorMessage("Player is already at maximum health!");
    }

    pManager->UpdateInterface();//redraw interface
}

RebootAndRepairAction::~RebootAndRepairAction()
{
}
