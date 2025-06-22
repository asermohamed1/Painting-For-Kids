#ifndef shapeAction_h
#define shapeAction_h
#include"Actions/Action.h"
class shapeAction :public Action
{
protected:
	Point p1;
	char keyShape;
	int CountT;
	int CountF;
	ActionType check;
	int random_number;
	int counter;//count number of given radom shape that generate
	bool pick;// control if i take this shape or it had been taken before
public:
	shapeAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};
#endif

