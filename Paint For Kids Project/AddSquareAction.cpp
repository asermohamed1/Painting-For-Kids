#include "AddSquareAction.h"

#include "ApplicationManager.h"
#include "CSquare.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

AddSquareAction::AddSquareAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddSquareAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Square: Click the center at Drawing Area");
	if (pManager->getcheckvoice() == 1)
		PlaySound(TEXT("lets draw square"), NULL, SND_FILENAME | SND_ASYNC);
	//Read the center of the square
	do
	{
		pIn->GetPointClicked(Center.x, Center.y);
		if (!isvalid(Center))
			pOut->PrintMessage("Invalid point .... Click another point");
	} while (!isvalid(Center));

	

	SquareGfxInfo.isFilled = fill;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	SquareGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}
//Check validation of the center point
bool AddSquareAction:: isvalid(Point center) {
	if (Center.y<UI.ToolBarHeight || Center.y>(UI.height - UI.StatusBarHeight) || Center.y + 100 > (UI.height - UI.StatusBarHeight) ||
		Center.y - 100 < UI.ToolBarHeight || Center.x - 100 < 0 || Center.x + 100 > UI.width-15)
		return false;
	else return true;
}

//Execute the action
void AddSquareAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a Square with the parameters read from the user
	CSquare* R = new CSquare(Center , SquareGfxInfo);
	square = R;
	//Add the Square to the list of figures
	pManager->AddFigure(R);
	pManager->PrintSelectedInfo(); //Print information about the selected figure

}

void AddSquareAction::Execure_recording_actions()
{
	//Create a Square with the parameters read from the user
	CSquare* R = new CSquare(Center, SquareGfxInfo);
	square = R;
	//Add the Square to the list of figures
	pManager->AddFigure(R);
	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void AddSquareAction::undo()
{
	pManager->decrease_undo_array();
}

void AddSquareAction::redo()
{
	//Add the Square to the list of figures
	pManager->AddFigure(square);
	pManager->PrintSelectedInfo();
}
