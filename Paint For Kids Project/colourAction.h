#ifndef colourAction_h
#define colourAction_h
#include"Actions/Action.h"

class colourAction :public Action
{

protected:
	Point p1;//use for get user click to know where is the point
	string Colour;//use to pOut which colour to pick
	int CountT;//count true picks
	int CountF;//count false picks
	ActionType check;//check if i break from loop or continue
	int random_number;//use to generate random number
	int counter;//count number of given random colour that generate
	bool pick;// control if i take this shape or it had been taken before
public:
	colourAction(ApplicationManager*);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};
#endif