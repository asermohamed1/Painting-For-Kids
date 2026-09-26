#pragma once
#include "Actions/Action.h"
#include"Figures/CFigure.h"
//Add Square Action class
class AddHexaAction : public Action
{
private:
	Point Center; // Hexagon Center
	GfxInfo HexaGfxInfo;
	CFigure* Hexa;
	//Check validation of the center point
	bool isvalid(Point center);

public:
	AddHexaAction(ApplicationManager* pApp);

	//Reads Hexagon parameters
	virtual void ReadActionParameters();

	//Add Hexagon to the ApplicationManager
	virtual void Execute();
	virtual void Execure_recording_actions();
	virtual void undo();
	virtual void redo();
};


