#include "AddTriangleAction.h"
#include "CTriangle.h"

#include "ApplicationManager.h"

#include "GUI/Input.h"
#include "GUI/Output.h"



AddTriangleAction::AddTriangleAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddTriangleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//get 3 points of corners
	pOut->PrintMessage("New Triangle: Click at first corner");
	if (pManager->getcheckvoice() == 1)
		PlaySound(TEXT("lets draw triangle"), NULL, SND_FILENAME | SND_ASYNC);
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
		else if (P2.x == P1.x||P2.y==P1.y) 
			pOut->PrintMessage("Invalid second corner...Click another point");
		else pOut->PrintMessage("Click the third corner");

	} while (!isvalid(P2)||P2.x==P1.x||P2.y==P1.y);
	do {
		pIn->GetPointClicked(P3.x, P3.y);
		if (!isvalid(P3))
			pOut->PrintMessage("the corner must be in Drawing Area...Click another point");
		else if(P3.x == P2.x || P3.x == P1.x|| P3.y == P2.y || P3.y == P1.y)
			pOut->PrintMessage("Invalid third corner...Click another point");

	} while (!isvalid(P3)|| P3.x == P2.x || P3.x == P1.x || P3.y == P2.y || P3.y == P1.y);


	TriangGfxInfo.isFilled = fill;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	TriangGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriangGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddTriangleAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a triangle with the parameters read from the user
	CTriangle* R = new CTriangle(P1, P2,P3, TriangGfxInfo);
	triangle = R;
	//Add the triangle to the list of figures
	pManager->AddFigure(R);
	pManager->PrintSelectedInfo(); //Print information about the selected figure

}

void AddTriangleAction::Execure_recording_actions()
{
	//Create a triangle with the parameters read from the user
	CTriangle* R = new CTriangle(P1, P2, P3, TriangGfxInfo);
	triangle = R;
	//Add the triangle to the list of figures
	pManager->AddFigure(R);
	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void AddTriangleAction::undo()
{
	pManager->decrease_undo_array();
}

void AddTriangleAction::redo()
{
	//Create a triangle with the parameters read from the user

	pManager->AddFigure(triangle);
	pManager->PrintSelectedInfo();
}

bool AddTriangleAction::isvalid(Point P)
{
	if (P.y<UI.ToolBarHeight || P.y>(UI.height - UI.StatusBarHeight))
		return false;
	else return true;
}
