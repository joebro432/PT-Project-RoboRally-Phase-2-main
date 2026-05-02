#pragma once
#include "Action.h"
//selection for movement
// same idea as any action
class SelectCommandAction : public Action
{
private:
    Command selectedCommand;//The command selected by the player

public:
    SelectCommandAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();//Reads the input
    virtual void Execute();//adding the commands (current player)
    virtual ~SelectCommandAction();
};
