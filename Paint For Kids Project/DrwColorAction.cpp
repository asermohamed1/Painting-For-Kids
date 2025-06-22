#include "DrwColorAction.h"
#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"
DrwColorAction::DrwColorAction(ApplicationManager* pApp) :Action(pApp)
{
}





void DrwColorAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();

	if (pManager->getSelectedFigure()==NULL) {         // Check if there is selected figure
		pOut->PrintMessage("Draw Color icon ... Please select figure first ");
	}
	else
	{
		pOut->PrintMessage("Draw Color icon ... Please choose the color ");        // Get the color to change
		do {
			Act = pManager->GetUserAction();
			if (!(Act == rED || Act == gREEN || Act == yELLOW || Act == oRANGEE || Act == bLUE || Act == bLACK))
				pOut->PrintMessage("Invalid....Please choose color from color icons ");
		} while (!(Act == rED || Act == gREEN || Act == yELLOW || Act == oRANGEE || Act == bLUE || Act == bLACK));
		pOut->ClearStatusBar();
	}
}
void DrwColorAction::Execute()
{

		ReadActionParameters();
		Output* pOut = pManager->GetOutput();
		if (pManager->getSelectedFigure() != NULL) {
		figure = pManager->get_figure_with_id(pManager->getSelectedFigure()->get_id());
		undo_color = figure->return_draw_color();
		switch (Act) {
		case rED:
			UI.DrawColor = RED;
			break;
		case gREEN:
			UI.DrawColor = GREEN;
			break;
		case yELLOW:
			UI.DrawColor = YELLOW;
			break;
		case oRANGEE:
			UI.DrawColor = ORANGE;
			break;
		case bLUE:
			UI.DrawColor = BLUE;
			break;
		case bLACK:
			UI.DrawColor = BLACK;
			break;
		}
		    redo_color = UI.DrawColor;
			pManager->getSelectedFigure()->ChngDrawClr(pOut->getCrntDrawColor()); // change the selected figure's draw color
			pManager->PrintSelectedInfo(); //Print information about the selected figure
		}


}

void DrwColorAction::Execure_recording_actions()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->getSelectedFigure() != NULL) {
		figure = pManager->get_figure_with_id(pManager->getSelectedFigure()->get_id());
		undo_color = figure->return_draw_color();
		switch (Act) {
		case rED:
			UI.DrawColor = RED;
			break;
		case gREEN:
			UI.DrawColor = GREEN;
			break;
		case yELLOW:
			UI.DrawColor = YELLOW;
			break;
		case oRANGEE:
			UI.DrawColor = ORANGE;
			break;
		case bLUE:
			UI.DrawColor = BLUE;
			break;
		case bLACK:
			UI.DrawColor = BLACK;
			break;
		}
		redo_color = UI.DrawColor;
		pManager->getSelectedFigure()->ChngDrawClr(pOut->getCrntDrawColor()); // change the selected figure's draw color
		pManager->PrintSelectedInfo(); //Print information about the selected figure
	}
}

void DrwColorAction::undo()
{
	UI.DrawColor = undo_color;
	if (undo_color == WHITE)
	{
		//set_fill_color_NULL();
		//get_figure()->null_fill_color();
	}
	//else
	//{
	get_figure()->ChngDrawClr(undo_color);
	//}
	UI.DrawColor = pManager->return_final_figure()->return_draw_color();
	pManager->PrintSelectedInfo();
}

CFigure* DrwColorAction::get_figure()
{
	return figure;
}

void DrwColorAction::redo()
{
	figure->ChngDrawClr(redo_color);
	pManager->UpdateInterface();
	//pManager->change_redo_color(figure->get_id(), figure->return_draw_color());
	UI.DrawColor = redo_color;
	//UI.DrawColor = pManager->return_final_figure()->return_draw_color();
	pManager->PrintSelectedInfo();
}
