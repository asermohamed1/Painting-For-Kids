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
			CFigure* c = NULL;
			if (figname == "HEXAGON")
				c = new CHexa(gfxinfo);
			else if (figname == "RECT")
				c = new CRectangle(gfxinfo);
			else if (figname == "SQUARE")
				c = new CSquare(gfxinfo);
			else if (figname == "TRIANG")
				c = new CTriangle(gfxinfo);
			else if (figname == "CIRCLE")
				c = new CCircle(gfxinfo);
			if (c == NULL) //unknown figure name: the file is damaged
				break;
			c->Load(InputFile);
			if (InputFile.fail()) //missing or wrong numbers: the file is damaged
			{
				delete c;
				break;
			}
			pManager->AddFigure(c);

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

