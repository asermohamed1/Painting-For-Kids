#include "Clearall.h"

Clearall::Clearall(ApplicationManager* pApp):Action(pApp)
{
}

void Clearall::ReadActionParameters()
{
	Point p{};
	Output* out = pManager->GetOutput();
	Input* in = pManager->GetInput();
	out->PrintMessage("we will clear all the drwaing area , click any point to confirm");
	in->GetPointClicked(p.x, p.y);
}

void Clearall::Execute()
{
	ReadActionParameters();
	pManager->clearall();  //calling clear all function
	fill = false;
	UI.DrawColor = BLUE;	//reset Drawing color
	UI.FillColor = WHITE;	//reset Filling color
}

void Clearall::undo()
{
}

void Clearall::redo()
{
}

void Clearall::Execure_recording_actions()
{
}
