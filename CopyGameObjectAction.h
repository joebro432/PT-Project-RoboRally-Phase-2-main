#pragma once
#include "Action.h"

class CopyGameObjectAction : public Action
{
private:
    CellPosition pos; // The position of the game object to copy

public:
    CopyGameObjectAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();// Reads action parameters 
    virtual void Execute();
     ~CopyGameObjectAction();
};
