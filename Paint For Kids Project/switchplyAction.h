#ifndef switchplyAction_h
#define switchplyAction_h
#include"Actions/Action.h"

class switchplyAction :public Action
{
	 
public:
	switchplyAction(ApplicationManager*);
	virtual void Execute();
	virtual void ReadActionParameters();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};
#endif
