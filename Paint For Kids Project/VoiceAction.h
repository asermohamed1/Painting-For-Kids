#ifndef VoiceAction_h
#define VoiceAction_h
#include"Actions/Action.h"
class VoiceAction:public Action
{
public:
	VoiceAction(ApplicationManager* );
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};
#endif