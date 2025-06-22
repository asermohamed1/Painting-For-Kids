#include "Actions/Action.h"
#include<fstream>
#include"ApplicationManager.h"
#include<cstring>
using namespace std;
class SaveAction :public Action
{
protected:
	string FileName;
	ofstream Outputfile;
public:
	SaveAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};


