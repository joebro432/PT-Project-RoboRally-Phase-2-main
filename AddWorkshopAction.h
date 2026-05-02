#pragma once
#include"Input.h"
#include"Output.h"
#include"Action.h"
#include"Workshop.h"
class AddWorkshopAction:public Action
{
	CellPosition workshopPos; //position of the workshop
public:
	AddWorkshopAction(ApplicationManager* pApp);
	virtual void ReadActionParameters(); // Reads action parameters
	virtual void Execute(); // Creates a new workshop Object then Sets this workshop object to the GameObject Pointer of its Cell
	virtual ~AddWorkshopAction();
};

