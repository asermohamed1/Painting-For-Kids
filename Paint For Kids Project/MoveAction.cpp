#include "MoveAction.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"


MoveAction::MoveAction(ApplicationManager* pApp): Action(pApp)
{
}

void MoveAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	if (pManager->getSelectedFigure() == NULL) // Check if there is selected figure
	{
		pOut->PrintMessage("Move icon ... Please select figure first ");
	}
	else {
		
		pOut->PrintMessage("Move icon ... Please choose wich type of moving"); // Get the Point to move
		pOut->CreateMoveToolBar();
		pIn->GetPointClicked(P.x, P.y);
		GetMoveType(P);
		pOut->ClearStatusBar();

	}

}

void MoveAction::Execute()
{
	ReadActionParameters();
	if (pManager->getSelectedFigure() != NULL) {
		//Get a Pointer to the Input / Output Interfaces
		Output* pOut = pManager->GetOutput();
		Input* pIn = pManager->GetInput();

		// Excute the appropriate Action
		if (type == non)
		{
			pOut->ClearDrawArea();
			pManager->UpdateInterface();
		}
		else if (type == click)
		{
			pOut->PrintMessage("Move by click....click the point you want to move");
			do
			{
				pIn->GetPointClicked(P.x, P.y);
				if (!isvalid(P)) pOut->PrintMessage("Invalid Point ... click another point");
			} while (!isvalid(P));
			fig = pManager->get_figure_with_id(pManager->getSelectedFigure()->get_id());
			pManager->getSelectedFigure()->MoveFig(P);   //move the selected figure
			undo_center = get_figure()->get_center();
			pOut->ClearDrawArea();
			pManager->UpdateInterface();

		}
		else if (type == drag)
		{
			pOut->PrintMessage("Move by Dragging....click the point you want to move");
			int i = 0;
			fig = pManager->get_figure_with_id(pManager->getSelectedFigure()->get_id());
			undo_center = fig->get_center();
			while (i == 0)
			{
				bool f = pOut->GetMouseState(); //Check if the user click on the mouse or not
				Point p2 = pOut->GetMouseCoord(); //Get the coordinates of the mouse just after the press on the mouse
				//check if the mouse is pressed & the first click was on the figure
				if (pManager->GetFigure(p2) == pManager->getSelectedFigure() && pOut->GetMouseState())
				{
					do
					{
						do
						{

							//Make the figure follow the mouse while the noused is pressed
							P = pOut->GetMouseCoord();
							pManager->getSelectedFigure()->MoveFig(P);
							pManager->UpdateInterface();
							Sleep(10);
							pOut->ClearDrawArea();
						} while (pOut->GetMouseState());
					} while (!isvalid(P));
					i = 1;
				}
				else if (pManager->GetFigure(p2) != pManager->getSelectedFigure() && pOut->GetMouseState())
				{
					i = 1;
					pOut->ClearDrawArea();
					pManager->UpdateInterface();
				}



			}

		}


		pManager->PrintSelectedInfo(); //Print information about the selected figure
	}
}

void MoveAction::Execure_recording_actions()
{
	if (pManager->getSelectedFigure() != NULL)
	{
	
		Output* pOut = pManager->GetOutput();
		pManager->getSelectedFigure()->MoveFig(P);
		pOut->ClearDrawArea();
     
		pManager->PrintSelectedInfo(); //Print information about the selected figure
	}
}

CFigure* MoveAction::get_figure()
{
	return fig;
}

void MoveAction::undo()
{
	fig->MoveFig(undo_center);
}

void MoveAction::redo()
{
	fig->MoveFig(P);
}

void MoveAction::GetMoveType(Point p) 
{
	if (p.x > 20.5 * UI.MenuItemWidth && p.x< 21.5 * UI.MenuItemWidth && P.y>UI.ToolBarHeight && P.y < UI.ToolBarHeight + UI.MenuItemWidth)
	{
		type = click;
	}
	else if (p.x > 21.5 * UI.MenuItemWidth && p.x< 22.5 * UI.MenuItemWidth && P.y>UI.ToolBarHeight && P.y < UI.ToolBarHeight + UI.MenuItemWidth)
	{
		type = drag;
	}
	else {
		type = non;
	}

}

bool MoveAction::isvalid(Point P) const // chaek the validation of the point
{

	if (P.y<(UI.ToolBarHeight+3) || P.y>(UI.height - UI.StatusBarHeight)) return false;
	return true;
}