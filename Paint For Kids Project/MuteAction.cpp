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
	pManager->setcheckvoice(0); //turn the voice off

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
