#pragma once
#include "Action.h"
class SaveGridAction :
    public Action
{
public:
    SaveGridAction(ApplicationManager* pApp); // Constructor
    virtual void ReadActionParameters(); // Reads parameters required for action to execute (code depends on action type so virtual)
    virtual void Execute(); // Executes the action
    virtual ~SaveGridAction();
};

