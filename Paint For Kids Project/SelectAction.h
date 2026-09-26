#ifndef SELECT_ACT
#define SELECT_ACT
#include "Actions/Action.h"
class SelectAction : public Action
{
private: 
	Point point;
public:
	SelectAction(ApplicationManager* pApp);

	//Reads the selected figure
	virtual void ReadActionParameters();

	//Add Circle to the ApplicationManager
	virtual void Execute();
	//check validation of the points
	virtual void Execure_recording_actions();
	virtual void undo();
	virtual void redo();
};
#endif
