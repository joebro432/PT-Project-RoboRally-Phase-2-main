#pragma once
#include "Action.h"
//heals player max by 10
class RebootAndRepairAction : public Action
{
public:
    RebootAndRepairAction(ApplicationManager* pApp);
    virtual void ReadActionParameters(); 
    virtual void Execute();//Restores health
    virtual ~RebootAndRepairAction();
};
