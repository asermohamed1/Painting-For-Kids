#include "VoiceAction.h"
#include"ApplicationManager.h"

VoiceAction::VoiceAction(ApplicationManager* p) :Action(p)
{

}
void VoiceAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
}

void VoiceAction::Execute()
{
	pManager->setcheckvoice(1);
	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void VoiceAction::undo()
{
}

void VoiceAction::redo()
{
}

void VoiceAction::Execure_recording_actions()
{
}
