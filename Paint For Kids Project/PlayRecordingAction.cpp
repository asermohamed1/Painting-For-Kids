#include "PlayRecordingAction.h"
PlayRecordingAction::PlayRecordingAction(ApplicationManager* pApp):Action(pApp)
{
}

void PlayRecordingAction::ReadActionParameters()
{
	Input* in = pManager->GetInput();
	Output* out = pManager->GetOutput();
	out->PrintMessage("you selected play button , we will display the previous recording ");
}

void PlayRecordingAction::Execute()
{
	ReadActionParameters();
	pManager->displayAction();  //calling display functions
}

void PlayRecordingAction::undo()
{
}

void PlayRecordingAction::redo()
{
}

void PlayRecordingAction::Execure_recording_actions()
{
}
