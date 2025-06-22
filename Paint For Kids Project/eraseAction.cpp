#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include"eraseAction.h"

eraseAction::eraseAction(ApplicationManager* p) :Action(p) {}

void eraseAction::ReadActionParameters()
{

}

void eraseAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (pManager->getSelectedFigure() == NULL)
		pOut->PrintMessage("Delete icon....Pelese select figure first");
	else
	{
		fig = pManager->getSelectedFigure();
		pManager->deleteSelectedFig(); //Delete the Selected figure
		pOut->ClearStatusBar();
	}
}

void eraseAction::Execure_recording_actions()
{
	Execute();
}

CFigure* eraseAction::get_figure()
{
	return fig;
}

void eraseAction::undo()
{
	if (get_figure()->IsSelected())
	{
		pManager->UnSelectFig();
	}
	pManager->AddFigure(get_figure());
}

void eraseAction::redo()
{
	pManager->delete_fig(get_figure());
}

