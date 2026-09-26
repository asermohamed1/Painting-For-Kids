#include "UndoAction.h"
UndoAction::UndoAction(ApplicationManager* pApp) :Action(pApp)
{
}

void UndoAction::ReadActionParameters()
{
	Output* pout = pManager->GetOutput();
	Input* pin = pManager->GetInput();

}

void UndoAction::Execute()
{
	Output* pout = pManager->GetOutput();
	pout->PrintMessage("you just clicked undo action and you have " + to_string(5) + " actions can do sequently");
	ReadActionParameters();
	pout->ClearDrawArea();
	pManager->decrease_undo_arr();
	/*int n = pManager->get_exeuted_actions();
	if (pManager->get_exeuted_actions() < 5)
	{
		pManager->decrease_undo_arr();
		pManager->set_executed_actions(++n);
	}
	else
	{
		pout->PrintMessage("you cant do more undo action consequently ,do any another action to can do undo");
		pManager->execute_undo_redo();
	}*/
}

void UndoAction::undo() //this function does not do undo
{
}

void UndoAction::redo()
{
}

void UndoAction::Execure_recording_actions()
{
	Output* pout = pManager->GetOutput();
	//pout->PrintMessage("you just clicked undo action and you have " + to_string(5) + " actions can do sequently");
	pout->ClearDrawArea();
	pManager->decrease_undo_arr();
}

