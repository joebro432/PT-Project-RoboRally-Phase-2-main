#pragma once
#include "Action.h"

class CutGameObjectAction : public Action
{
private:
    CellPosition pos; // The position of the game object to cut

public:
    CutGameObjectAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();// Reads action parameters 
    virtual void Execute();
    virtual  ~CutGameObjectAction();
};
