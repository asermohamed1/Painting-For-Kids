#ifndef DRW_ACT
#define DRW_ACT
#include "Actions/Action.h"
#include"Figures/CFigure.h"
class DrwColorAction : public Action
{
	ActionType Act;
	color undo_color;
	CFigure* figure;
	color redo_color;
public:
	DrwColorAction(ApplicationManager* pApp);

	//Reads Square parameters
	virtual void ReadActionParameters();

	//Add Sqaure to the ApplicationManager
	virtual void Execute();
	virtual void Execure_recording_actions();
	virtual void undo();
	CFigure* get_figure();
	virtual void redo();

};
#endif DRW_ACT

