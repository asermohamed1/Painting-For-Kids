#ifndef MuteAction_h
#define MuteAction_h
#include"Actions/Action.h"
class MuteAction :public Action
{
public:
	MuteAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};
#endif
