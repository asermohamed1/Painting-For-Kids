#ifndef ADD_CIRC_ACTION_H
#define ADD_CIRC_ACTION_H
#include "Actions/Action.h"
#include"Figures/CFigure.h"
//Add Circle Action class
class AddCircleAction : public Action
{
private:
	Point Center; //Circle center
	Point point; //A point on the circle 
	GfxInfo CircGfxInfo;
	CFigure* circle;
	//check validation of the points
	bool isvalidPoint(Point center) const;
	bool isvalidradius(Point center, Point point) const;

public:
	AddCircleAction(ApplicationManager* pApp);

	//Reads Circle parameters
	virtual void ReadActionParameters();

	//Add Circle to the ApplicationManager
	virtual void Execute();
	virtual void Execure_recording_actions();
	virtual void undo();
	virtual void redo();
};
#endif
