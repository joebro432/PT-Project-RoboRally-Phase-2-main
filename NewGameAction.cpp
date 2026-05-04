#include "NewGameAction.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "GameState.h"
#include "Player.h"
#include "ApplicationManager.h"

NewGameAction::NewGameAction(ApplicationManager* pApp) : Action(pApp)
{
}

void NewGameAction::ReadActionParameters()
{
//none needed
}

void NewGameAction::Execute()
{
    Grid* pGrid = pManager->GetGrid();
    GameState* pState = pManager->GetGameState();
    Output* pOut = pGrid->GetOutput();

    if (!pState || !pGrid)
    {
        return;
    }


    pState->SetCurrentPhase(PHASE_MOVEMENT);//resets to movement


    pState->SetFirstPlayer(0);//resets players

    for (int i = 0; i < MaxPlayerCount; i++)//clears out all players 
    {
        Player* player = pState->GetPlayer(i);
        if (player)
        {        
            player->ClearSavedCommands();
            player->SetHealth(10);//Reset health
            player->ClearDrawing(pOut);
            player->SetCell(pGrid->GetStartCell());
            player->Draw(pOut);
            
        }
    }


    pState->SetEndGame(false);


    pManager->UpdateInterface();//redraw interface the ui
    pOut->CreatePlayModeToolBar();
    pOut->CreateCommandsBar(pState->GetCurrentPlayer()->GetSavedCommands(),
        pState->GetCurrentPlayer()->GetSavedCommandCount(),
        pState->GetCurrentPlayer()->GetAvailableCommands(),
        pState->GetCurrentPlayer()->GetAvailableCommandCount());
    pGrid->PrintErrorMessage("New game has started");
   
}

NewGameAction::~NewGameAction()
{
}
