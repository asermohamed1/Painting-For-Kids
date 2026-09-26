#pragma once
#include"ApplicationManager.h"
#include"Actions/Action.h"
class StopRecordAction :public Action
{
public:
	StopRecordAction(ApplicationManager* pApp);
	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
	//Execute recording actions used only with actions that can be recorded
	virtual void Execure_recording_actions();
	virtual void undo();
	virtual void redo();
};

