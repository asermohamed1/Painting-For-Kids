#pragma once
#include"Actions/Action.h"

class ExitAction:public Action
{
public:
	ExitAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();

};

