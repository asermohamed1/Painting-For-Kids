#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include"eraseAction.h"

eraseAction::eraseAction(ApplicationManager* p) :Action(p)
{
	fig = NULL;
}

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
	if (get_figure() == NULL) //nothing was erased
		return;
	pManager->AddFigure(get_figure());
}

void eraseAction::redo()
{
	if (get_figure() == NULL)
		return;
	pManager->delete_fig(get_figure());
}

