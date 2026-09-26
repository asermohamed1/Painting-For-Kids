#ifndef ADD_RECT_ACTION_H
#define ADD_RECT_ACTION_H
#include "Action.h"
#include "../Figures/CRectangle.h"
//Add Rectangle Action class
class AddRectAction : public Action
{
private:
	Point P1, P2; //Rectangle Corners
	GfxInfo RectGfxInfo;
	CFigure* Rect;
	//check validation of the corner points
	bool isvalid(Point center);

public:
	AddRectAction(ApplicationManager* pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
	virtual void Execure_recording_actions();
	virtual void undo();
	virtual void redo();
};

#endif