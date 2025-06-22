#pragma once
#include "Actions/Action.h"
#include"ApplicationManager.h"
class RecordingAction : public Action
{
public:
	RecordingAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	void Execure_recording_actions();
	virtual void undo();
	virtual void redo();
};

