#include "AddCircleAction.h"
#include "CCircle.h"

#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"

AddCircleAction::AddCircleAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddCircleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//get points of the Circle
	pOut->PrintMessage("New Circle: Click at Center point");
	if (pManager->getcheckvoice() == 1)
		PlaySound(TEXT("lets draw circle"), NULL, SND_FILENAME | SND_ASYNC);
	do
	{
		do
		{
			pIn->GetPointClicked(Center.x, Center.y);
			if (!isvalidPoint(Center))   //Check the validation of the center
			{
				pOut->PrintMessage("the center point is invalid,enter it again");
			}
			else
			{
				pOut->PrintMessage("OK...enter another point on the circle");
			}
		} while (!isvalidPoint(Center));
		do
		{
			pIn->GetPointClicked(point.x, point.y);
			if (!isvalidPoint(point) || (point.x == Center.x && point.y == Center.y))       // Check the validation of the point on the circle
			{
				pOut->PrintMessage("the second point is invalid");
			}
		} while (!isvalidPoint(point)||(point.x==Center.x && point.y == Center.y));
		
		if (!isvalidradius(Center,point))
		{
			pOut->PrintMessage("the radius is invalid,click another two points");
		}
	} while (!isvalidradius(Center, point));


	CircGfxInfo.isFilled = fill;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddCircleAction::Execute()
{
	

	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a Circle with the parameters read from the user
	CCircle* R = new CCircle(Center, point, CircGfxInfo);
	circle = R;
	//Add the Circle to the list of figures
	pManager->AddFigure(R);

	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void AddCircleAction::Execure_recording_actions()
{
	//Create a Circle with the parameters read from the user
	CCircle* R = new CCircle(Center, point, CircGfxInfo);
	circle = R;
	//Add the Circle to the list of figures
	pManager->AddFigure(R);

	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void AddCircleAction::undo()
{
	pManager->decrease_undo_array();

}

void AddCircleAction::redo()
{
	pManager->AddFigure(circle);
	pManager->PrintSelectedInfo();
}

bool AddCircleAction::isvalidPoint(Point P) const
{
	if (P.y < UI.ToolBarHeight || P.y>(UI.height - UI.StatusBarHeight))
		return false;
	else return true;
}
bool AddCircleAction::isvalidradius(Point center,Point point) const
{
	float  radius = sqrt((center.x - point.x) * (center.x - point.x) + (center.y - point.y) * (center.y - point.y));
	if ((center.y - radius) < UI.ToolBarHeight || (center.y + radius) > (UI.height - UI.StatusBarHeight) || center.x - radius < 0 || center.x + radius>UI.width-15)
		return false;
	else return true;
}