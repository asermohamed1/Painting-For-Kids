#pragma once
#include"Actions/Action.h"
#include"ApplicationManager.h"
class UndoAction :public Action
{
public:
	UndoAction(ApplicationManager* pApp);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};
