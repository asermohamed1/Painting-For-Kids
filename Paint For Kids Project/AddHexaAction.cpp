#include "AddHexaAction.h"
#include "ApplicationManager.h"
#include "CHexa.h"
#include "GUI/Input.h"
#include "GUI/Output.h"

AddHexaAction::AddHexaAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddHexaAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Hexagon: Click the center at Drawing Area");
	if (pManager->getcheckvoice() == 1)
		PlaySound(TEXT("lets draw hexagonal"), NULL, SND_FILENAME | SND_ASYNC);
	//Read the center of the Hexagon
	do
	{
		pIn->GetPointClicked(Center.x, Center.y);
		if (!isvalid(Center))
			pOut->PrintMessage("Invalid point .... Click another point");
	} while (!isvalid(Center));



	HexaGfxInfo.isFilled = fill;	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexaGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexaGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Check validation of the center point
bool AddHexaAction::isvalid(Point P) {
	if (P.y<UI.ToolBarHeight || P.y>(UI.height - UI.StatusBarHeight) || (P.y + ((float(sqrt(3)) / 2) * 100)) > (UI.height - UI.StatusBarHeight)
		|| P.y - ((float(sqrt(3)) / 2) * 100)<UI.ToolBarHeight || P.x - 100 < 0 || P.x + 100 > UI.width-15) {
		return false;
	}
	else return true;
}

//Execute the action
void AddHexaAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a Hexagon with the parameters read from the user
	CHexa* R = new CHexa(Center, HexaGfxInfo);
	Hexa = R;
	//Add the Hexagon to the list of figures
	pManager->AddFigure(R);
	pManager->PrintSelectedInfo(); //Print information about the selected figure

}

void AddHexaAction::Execure_recording_actions()
{
	//Create a Hexagon with the parameters read from the user
	CHexa* R = new CHexa(Center, HexaGfxInfo);
	Hexa = R;
	//Add the Hexagon to the list of figures
	pManager->AddFigure(R);
	pManager->PrintSelectedInfo();
}

void AddHexaAction::undo()
{
	pManager->decrease_undo_array();
}

void AddHexaAction::redo()
{
	//Add the Hexagon to the list of figures
	pManager->AddFigure(Hexa);
	pManager->PrintSelectedInfo();
}
