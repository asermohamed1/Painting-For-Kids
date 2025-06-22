#pragma once
#include"Actions/Action.h"
#include"ApplicationManager.h"
class Clearall : public Action
{
public:
	Clearall(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};

