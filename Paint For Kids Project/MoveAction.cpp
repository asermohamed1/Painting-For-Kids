#include "MoveAction.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"


MoveAction::MoveAction(ApplicationManager* pApp): Action(pApp)
{
	fig = NULL;
	type = non;
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
			fig = pManager->getSelectedFigure();
			undo_center = fig->get_center();   //the position before moving (for undo)
			fig->MoveFig(P);   //move the selected figure
			pOut->ClearDrawArea();
			pManager->UpdateInterface();

		}
		else if (type == drag)
		{
			pOut->PrintMessage("Move by Dragging....click the point you want to move");
			int i = 0;
			fig = pManager->getSelectedFigure();
			undo_center = fig->get_center();   //the position before moving (for undo)
			while (i == 0)
			{
				Point p2 = pOut->GetMouseCoord(); //Get the coordinates of the mouse just after the press on the mouse
				//check if the mouse is pressed & the first click was on the figure
				if (pManager->GetFigure(p2) == pManager->getSelectedFigure() && pOut->GetMouseState())
				{
					//draw every frame on an off-screen buffer, then show it at once (no flicker)
					pOut->StartBuffering();
					pOut->PrintMessage("Move by Dragging....release the mouse to drop the figure");
					Point last = { -1, -1 };
					do
					{
						do
						{
							//Make the figure follow the mouse while the mouse is pressed
							P = pOut->GetMouseCoord();
							if (P.x != last.x || P.y != last.y) //redraw only when the mouse moved
							{
								fig->MoveFig(P);
								pOut->ClearDrawArea();
								pManager->UpdateInterface();
								pOut->FlushBuffer();
								last = P;
							}
							Sleep(10);
						} while (pOut->GetMouseState());
					} while (!isvalid(P));
					pOut->StopBuffering();
					i = 1;
				}
				else if (pManager->GetFigure(p2) != pManager->getSelectedFigure() && pOut->GetMouseState())
				{
					i = 1;
					type = non; //the figure was not dragged
					pOut->ClearDrawArea();
					pManager->UpdateInterface();
				}
				else
				{
					Sleep(10); //wait for the mouse without using all the CPU
				}



			}

		}


		pManager->PrintSelectedInfo(); //Print information about the selected figure
	}
}

void MoveAction::Execure_recording_actions()
{
	if (pManager->getSelectedFigure() != NULL && type != non) //nothing to replay if the figure was not moved
	{
		Output* pOut = pManager->GetOutput();
		fig = pManager->getSelectedFigure();
		undo_center = fig->get_center();
		fig->MoveFig(P);
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
	if (fig != NULL && type != non) //nothing to undo if the figure was not moved
		fig->MoveFig(undo_center);
}

void MoveAction::redo()
{
	if (fig != NULL && type != non)
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