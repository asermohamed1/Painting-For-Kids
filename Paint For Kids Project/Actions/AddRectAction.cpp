#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"


AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{}

void AddRectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//get points of corners
	pOut->PrintMessage("New Rectangle: Click at first corner");
	if (pManager->getcheckvoice() == 1)
		PlaySound(TEXT("lets draw rectangle"), NULL, SND_FILENAME | SND_ASYNC);
	do {
		pIn->GetPointClicked(P1.x, P1.y);
		if (!isvalid(P1))
			pOut->PrintMessage("the corner must be in Drawing Area...Click another point");
		else pOut->PrintMessage("Click the second corner");
	} while (!isvalid(P1));
	do {
		pIn->GetPointClicked(P2.x, P2.y);
		if (!isvalid(P2))
			pOut->PrintMessage("the corner must be in Drawing Area...Click another point");
		if(P2.x == P1.x||P2.y==P1.y)
			pOut->PrintMessage("Invalid Second corner....Click another Point");

	} while (!isvalid(P2)|| P2.x==P1.x||P2.y==P1.y);
	RectGfxInfo.isFilled = fill;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddRectAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a rectangle with the parameters read from the user
	CRectangle *R=new CRectangle(P1, P2, RectGfxInfo);
	Rect = R;
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void AddRectAction::Execure_recording_actions()
{
	//Create a rectangle with the parameters read from the user
	CRectangle* R = new CRectangle(P1, P2, RectGfxInfo);
	Rect = R;
	//Add the rectangle to the list of figures
	pManager->AddFigure(R);
	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void AddRectAction::undo()
{
	pManager->decrease_undo_array();
}

void AddRectAction::redo()
{
	pManager->AddFigure(Rect);
	pManager->PrintSelectedInfo();
}

bool AddRectAction::isvalid(Point P)
{
	if (P.y<UI.ToolBarHeight || P.y>(UI.height - UI.StatusBarHeight))
		return false;
	else return true;
}
