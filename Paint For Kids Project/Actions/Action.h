#ifndef ACTION_H
#define ACTION_H
#include "..\DefS.h"

class ApplicationManager; //forward class declaration


//Base class for all possible actions
class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job
	bool static fill;  //for specify the default state of figures (filled or none)
public:

	Action(ApplicationManager* pApp) :pManager(pApp)
	{}	//constructor

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() =0;
	void set_fill_color_NULL();
	//Execute action (code depends on action type)
	virtual void Execute() =0;
	virtual void Execure_recording_actions()=0;
	virtual void undo() = 0;
	virtual void redo() = 0;
};

#endif