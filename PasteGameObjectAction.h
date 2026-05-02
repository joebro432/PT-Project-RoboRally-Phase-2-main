#pragma once
#include "Action.h"

class PasteGameObjectAction : public Action
{
private:
    CellPosition pos; // The position of the cell where the object will be pasted

public:
    PasteGameObjectAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual ~PasteGameObjectAction();
};
