#include"StopRecord.h"

StopRecordAction::StopRecordAction(ApplicationManager* pApp) :Action(pApp)
{
}

void StopRecordAction::ReadActionParameters()
{
	Output* out = pManager->GetOutput();
	Input* in = pManager->GetInput();
}

void StopRecordAction::Execute()
{
	ReadActionParameters();
	Output* out = pManager->GetOutput();
	if (pManager->isrecorded())
	{
	}
	else
	{
		out->PrintMessage("ERROR: this function only works when you use record action");
	}
}

void StopRecordAction::Execure_recording_actions()
{
	//this action isnt recorded
}

void StopRecordAction::undo()
{
}

void StopRecordAction::redo()
{
}
