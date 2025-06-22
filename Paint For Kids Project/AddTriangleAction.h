#ifndef ADD_TRAING_ACTION_H
#define ADD_TRIANG_ACTION_H
#include "Actions/Action.h"
#include"Figures/CFigure.h"
class AddTriangleAction : public Action
{
	//Add Traingle Action class


private:
	Point P1, P2, P3; //Rectangle Corners
	GfxInfo TriangGfxInfo;
	CFigure* triangle;
	//check validation of the corner points
	bool isvalid(Point center);

public:
	AddTriangleAction(ApplicationManager* pApp);

	//Reads triangle parameters
	virtual void ReadActionParameters();

	//Add rectangle to the ApplicationManager
	virtual void Execute();
	virtual void Execure_recording_actions();
	virtual void undo();
	virtual void redo();
};
#endif
