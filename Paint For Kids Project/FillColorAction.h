#ifndef FILL_ACT
#define FILL_ACT
#include "Actions/Action.h"
#include"Figures/CFigure.h"
class FillColorAction : public Action
{
	ActionType Act;
	color undo_color;
	color redo_color;
	CFigure* fig;
public:
	FillColorAction(ApplicationManager* pApp);

	//Reads Square parameters
	virtual void ReadActionParameters();
	//Add Sqaure to the ApplicationManager
	virtual void Execute();
	virtual void Execure_recording_actions();
	virtual void undo();
	virtual void redo();
	CFigure* get_figure();
};
#endif FILL_ACT
