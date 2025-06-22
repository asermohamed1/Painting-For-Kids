#include "ExitAction.h"
#include"GUI/Output.h"
#include"GUI/Input.h"
#include"ApplicationManager.h"
ExitAction::ExitAction(ApplicationManager* pApp):Action(pApp)
{
}
void ExitAction::ReadActionParameters()
{
}

void ExitAction::Execute()
{
	pManager->clearall();
}

void ExitAction::undo()
{
}

void ExitAction::redo()
{
}

void ExitAction::Execure_recording_actions()
{
}
