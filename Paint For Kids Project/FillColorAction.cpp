#include "FillColorAction.h"
#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"

FillColorAction::FillColorAction(ApplicationManager* pApp):Action(pApp)
{
}

void FillColorAction::ReadActionParameters()
{
	//Get a Pointer to the Output Interfaces
	Output* pOut = pManager->GetOutput();

	if (pManager->getSelectedFigure()==NULL) // Check if there is selected figure
	{         
		pOut->PrintMessage("Fill Color icon ... Please select figure first ");
	}
	
	else
	{
		pOut->PrintMessage("Fill Color icon ... Please choose the color ");        // Get the color to change
		do {
			Act = pManager->GetUserAction();
			if (!(Act == rED || Act == gREEN || Act == yELLOW || Act == oRANGEE || Act == bLUE || Act == bLACK))
				pOut->PrintMessage("Invalid....Please choose color from color icons ");
		} while (!(Act == rED || Act == gREEN || Act == yELLOW || Act == oRANGEE || Act == bLUE || Act == bLACK));
		pOut->ClearStatusBar();
	}

}

void FillColorAction::Execute()
{
	if (pManager->getcheckvoice() == 1)
		PlaySound(TEXT("lets paint"), NULL, SND_FILENAME | SND_ASYNC);
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (pManager->getSelectedFigure()!=NULL) {
	fig = pManager->get_figure_with_id(pManager->getSelectedFigure()->get_id());
	undo_color = fig->return_fill_color();
	switch (Act) {
	case rED:
		UI.FillColor = RED;
		break;
	case gREEN:
		UI.FillColor = GREEN;
		break;
	case yELLOW:
		UI.FillColor = YELLOW;
		break;
	case oRANGEE:
		UI.FillColor = ORANGE;
		break;
	case bLUE:
		UI.FillColor = BLUE;
		break;
	case bLACK:
		UI.FillColor = BLACK;
		break;
	}
	redo_color = UI.FillColor;
		//pManager->ChngSelectedCLR('F'); //change the selected figure's fill color
	 pManager->getSelectedFigure()->ChngFillClr(pOut->getCrntFillColor());  //change the selected figure's fill color
		fill = true;
		pManager->PrintSelectedInfo(); //Print information about the selected figure
		
	}
}

void FillColorAction::Execure_recording_actions()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->getSelectedFigure() != NULL) 
	{
		fig = pManager->get_figure_with_id(pManager->getSelectedFigure()->get_id());
		undo_color = fig->return_fill_color();
		switch (Act) {
		case rED:
			UI.FillColor = RED;
			break;
		case gREEN:
			UI.FillColor = GREEN;
			break;
		case yELLOW:
			UI.FillColor = YELLOW;
			break;
		case oRANGEE:
			UI.FillColor = ORANGE;
			break;
		case bLUE:
			UI.FillColor = BLUE;
			break;
		case bLACK:
			UI.FillColor = BLACK;
			break;
		}
		redo_color = UI.FillColor;
		pManager->getSelectedFigure()->ChngFillClr(pOut->getCrntFillColor());  //change the selected figure's fill color
		fill = true;
		pManager->PrintSelectedInfo(); //Print information about the selected figure

	}
}

void FillColorAction::undo()
{
	UI.FillColor = undo_color;
	if (undo_color == WHITE)
	{
		set_fill_color_NULL();
		get_figure()->null_fill_color();
	}
	else
	{
		get_figure()->ChngFillClr(undo_color);
	}
	UI.FillColor = pManager->return_final_figure()->return_fill_color();
	pManager->PrintSelectedInfo();
}

void FillColorAction::redo()
{
	UI.FillColor = redo_color;
	if (redo_color == WHITE)
	{
		set_fill_color_NULL();
		get_figure()->null_fill_color();
	}
	else
	{
		get_figure()->ChngFillClr(redo_color);
	}
	UI.FillColor = pManager->return_final_figure()->return_fill_color();
	pManager->PrintSelectedInfo();
}

CFigure* FillColorAction::get_figure()
{
	return fig;
}
