#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "WaterPit.h"
class AddWaterPitAction:public Action 
{
	//action parameters
	CellPosition pitpos; //position bta3 el waterpit 

public:
	AddWaterPitAction(ApplicationManager *pApp);
	virtual void ReadActionParameters(); 
	virtual void Execute(); // hnCreate a new water pit Object w nhot el object l gameobjects pointer bta3 el cell
					
	~AddWaterPitAction();

};

