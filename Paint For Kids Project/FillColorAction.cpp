#include "FillColorAction.h"
#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"

FillColorAction::FillColorAction(ApplicationManager* pApp):Action(pApp)
{
	Act = EMPTY;
	fig = NULL;
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
		PlaySound(TEXT("lets paint.wav"), NULL, SND_FILENAME | SND_ASYNC);
	ReadActionParameters();
	ApplyColor();
}

void FillColorAction::ApplyColor()
{
	Output* pOut = pManager->GetOutput();
	if (pManager->getSelectedFigure()!=NULL) {
	fig = pManager->getSelectedFigure();
	undo_color = fig->return_fill_color();
	undo_filled = fig->is_filled();
	undo_ui_color = UI.FillColor;
	undo_fill = fill;
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
	ApplyColor();
}

void FillColorAction::undo()
{
	if (get_figure() == NULL) //the colour was not changed
		return;
	get_figure()->ChngFillClr(undo_color);
	if (!undo_filled)
		get_figure()->null_fill_color();
	UI.FillColor = undo_ui_color;
	fill = undo_fill;
	pManager->PrintSelectedInfo();
}

void FillColorAction::redo()
{
	if (get_figure() == NULL)
		return;
	get_figure()->ChngFillClr(redo_color);
	UI.FillColor = redo_color;
	fill = true;
	pManager->PrintSelectedInfo();
}

CFigure* FillColorAction::get_figure()
{
	return fig;
}
