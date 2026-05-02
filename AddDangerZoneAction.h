#pragma once
#include "Action.h"
#include "Input.h"
#include "Output.h"
#include "DangerZone.h"
class AddDangerZoneAction:public Action
{
	CellPosition DangerZonePos; //el position bta3 el bta3a 

public:
	AddDangerZoneAction(ApplicationManager* pApp);
	virtual void ReadActionParameters(); 
	virtual void Execute();
	virtual ~AddDangerZoneAction();





};

