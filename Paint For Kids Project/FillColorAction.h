#ifndef FILL_ACT
#define FILL_ACT
#include "Actions/Action.h"
#include"Figures/CFigure.h"
class FillColorAction : public Action
{
	ActionType Act;
	color undo_color;      //fill colour of the figure before the action
	bool undo_filled;      //was the figure filled before the action
	color undo_ui_color;   //current fill colour before the action
	bool undo_fill;        //default fill state before the action
	color redo_color;
	CFigure* fig;
	void ApplyColor();     //change the selected figure's fill colour
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
#endif // FILL_ACT
