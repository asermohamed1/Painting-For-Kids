#include "LoadAction.h"
loadaction::loadaction(ApplicationManager* pApp) : Action(pApp)
{
	gfxinfo.DrawClr = BLUE;
	gfxinfo.isFilled = false;
}

void loadaction::ReadActionParameters()
{
	filename = pManager->GetInput()->GetSrting(pManager->GetOutput());
}

void loadaction::Execute()
{

	pManager->GetOutput()->PrintMessage("enter the file name that u want to load from : ");
	ReadActionParameters();
	if (filename == "") //the user pressed ESC
	{
		pManager->GetOutput()->PrintMessage("Load has been cancelled");
		return;
	}
	InputFile.open(filename + ".txt");
	if (InputFile.is_open())
	{
		pManager->clearall();
		InputFile >> drawclr >> fillclr;
		InputFile >> num;
		//restore the current draw and fill colors
		if (drawclr != "NO_COLOR")
			UI.DrawColor = CFigure::getstring(drawclr);
		if (fillclr != "NO_COLOR")
			UI.FillColor = CFigure::getstring(fillclr);
		fill = !(UI.FillColor == WHITE);
		for (int i = 0; i < num && (InputFile >> figname); i++)
		{
			if (figname == "HEXAGON")
			{
				CFigure* c = new CHexa(gfxinfo);
				c->Load(InputFile);
				pManager->AddFigure(c);
			}
			else if (figname == "RECT")
			{
				CFigure* c = new CRectangle(gfxinfo);
				c->Load(InputFile);
				pManager->AddFigure(c);
			}
			else if (figname == "SQUARE")
			{
				CFigure* c = new CSquare(gfxinfo);
				c->Load(InputFile);
				pManager->AddFigure(c);
			}
			else if (figname == "TRIANG")
			{
				CFigure* c = new CTriangle(gfxinfo);
				c->Load(InputFile);
				pManager->AddFigure(c);
			}
			else if (figname == "CIRCLE")
			{
				CFigure* c = new CCircle(gfxinfo);
				c->Load(InputFile);
				pManager->AddFigure(c);
			}

		}
	}
	else
	{
		pManager->GetOutput()->PrintMessage("THERE IS NO FILE WITH THIS NAME"); return;
	}
	pManager->GetOutput()->PrintMessage("File (" + filename + ") has been Loaded Successfully");
	InputFile.close();
}

void loadaction::undo()
{
}

void loadaction::redo()
{
}

void loadaction::Execure_recording_actions()
{
}

