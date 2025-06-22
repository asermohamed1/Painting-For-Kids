#ifndef ADD_SQR
#define ADD_SQR
#include "Actions/Action.h"
#include"Figures/CFigure.h"
//Add Square Action class

class AddSquareAction : public Action
{
private:
	Point Center; // Square Center
	GfxInfo SquareGfxInfo;
	CFigure* square;

	//Check validation of the center point
	bool isvalid(Point center);

public:
	AddSquareAction(ApplicationManager* pApp);

	//Reads Square parameters
	virtual void ReadActionParameters();

	//Add Sqaure to the ApplicationManager
	virtual void Execute();
	virtual void Execure_recording_actions();
	virtual void undo();
	virtual void redo();
};
#endif
