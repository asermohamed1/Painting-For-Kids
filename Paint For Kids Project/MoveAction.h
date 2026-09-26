#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H
#include "Actions/Action.h"
#include"Figures/CFigure.h"
enum MoveType  { non,click,drag };
// move Action Class 
class MoveAction :public Action
{
private:
	Point P;
	bool isvalid(Point P) const;  //check the validation of the point
	Point undo_center;
	CFigure* fig;
	int id;
	MoveType type;

public:
	MoveAction(ApplicationManager* pApp);

	//Reads parameters (the point wich the figure move to)
	virtual void ReadActionParameters();

	// Excute move Action
	virtual void Execute();

	virtual void Execure_recording_actions();

	CFigure* get_figure();

	virtual void undo();
	virtual void redo();
	void GetMoveType(Point p) ; // Get the of the move

};

#endif





