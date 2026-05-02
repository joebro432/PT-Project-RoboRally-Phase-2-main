#pragma once
#include "Action.h"

class AddAntennaAction : public Action
{
private:
    CellPosition pos; // The position where the antenna will be placed

public:
    AddAntennaAction(ApplicationManager* pApp);
    virtual void ReadActionParameters(); // Reads the antenna position
    virtual void Execute(); // Creates and adds an antenna to the grid
     ~AddAntennaAction();
};
