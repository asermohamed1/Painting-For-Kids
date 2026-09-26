#ifndef switchdrwAction_h
#define switchdrwAction_h
#include"Actions/Action.h"

class switchdrwAction :public Action
{


public:
	switchdrwAction(ApplicationManager*);
	virtual void Execute();
	virtual void ReadActionParameters();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};
#endif
