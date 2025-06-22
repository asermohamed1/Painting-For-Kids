#ifndef ERASE_H
#define ERASE_H
#include"Actions/Action.h"

class eraseAction :public Action
{
private:
	CFigure* fig;
public:
	eraseAction(ApplicationManager*);
	//Reads Action parameters
	virtual void ReadActionParameters();

	// Excute the Action
	virtual void Execute();

	void Execure_recording_actions();
	CFigure* get_figure();
	virtual void undo();
	virtual void redo();
};
#endif
