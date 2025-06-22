#include "MuteAction.h"
#include"ApplicationManager.h"

MuteAction::MuteAction(ApplicationManager* p) :Action(p)
{

}
void MuteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
}

void MuteAction::Execute()
{
	//Output* pOut = pManager->GetOutput();
	//pOut->PrintMessage("this will stop voice of some action ");
	//Sleep(1000);
	//pManager->setcheckvoice(0);
	
	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void MuteAction::undo()
{
}

void MuteAction::redo()
{
}

void MuteAction::Execure_recording_actions()
{
}
