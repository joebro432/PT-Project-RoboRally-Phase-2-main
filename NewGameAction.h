#pragma once
#include "Action.h"
// restarts the game.
// and makes a new game duh
class NewGameAction : public Action
{
public:
    NewGameAction(ApplicationManager* pApp);
    virtual void ReadActionParameters(); 
    virtual void Execute(); 
    virtual ~NewGameAction();
};
