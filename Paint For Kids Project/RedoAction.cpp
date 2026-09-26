#include "RedoAction.h"
#include "GUI/Output.h"
#include"ApplicationManager.h"
RedoAction::RedoAction(ApplicationManager* pApp) :Action(pApp)
{
}

void RedoAction::ReadActionParameters()
{
	Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();
}

void RedoAction::Execute()
{
	Output* pout = pManager->GetOutput();
	pout->PrintMessage("you just clicked redo action and you have " + to_string(5) + " actions can do sequently");
	ReadActionParameters();
	pout->ClearDrawArea();
	pManager->redo_display();
}

void RedoAction::undo()
{
}

void RedoAction::redo()
{
}

void RedoAction::Execure_recording_actions()
{
	Output* pout = pManager->GetOutput();
	pout->PrintMessage("you just clicked redo action and you have " + to_string(5) + " actions can do sequently");
	ReadActionParameters();
	pout->ClearDrawArea();
	pManager->redo_display();
}
