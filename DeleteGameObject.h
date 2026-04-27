#pragma once
#include "Action.h"
class DeleteGameObject :
    public Action
{
    CellPosition pos; // The position of the game object to delete
    public:
                DeleteGameObject(ApplicationManager* pApp);
               virtual void ReadActionParameters();
             virtual   void Execute();
           virtual     ~DeleteGameObject();
};

