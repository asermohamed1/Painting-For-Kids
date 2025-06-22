#pragma once
#include"Actions/Action.h"
#include"ApplicationManager.h"
class PlayRecordingAction : public Action
{
public:
	PlayRecordingAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};

