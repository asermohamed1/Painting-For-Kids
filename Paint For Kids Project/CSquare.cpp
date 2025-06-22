#include "CSquare.h"
CSquare::CSquare(GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
}
CSquare::CSquare(Point center, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	
	Center = center;
	center_undo = center;
}
void CSquare::Draw(Output* pOut) const
{
	//Call Output::DrawSqr to draw a ssquare on the screen	
	pOut->DrawSqr( Center, FigGfxInfo, Selected);
}

bool CSquare::isThisFigure(Point p) const
{
	if ((p.y >= Center.y - 100) && (p.y <= Center.y + 100) && (p.x <= Center.x + 100) && (p.x >= Center.x - 100))
		return true;
	else return false;
}

void CSquare::PrintInfo(Output* pOut) const
{
	string Color;
	{	color c;
	c = (*this).FigGfxInfo.FillClr;
	if (c == RED)
		Color = "RED";
	else if (c == BLACK)
		Color = "BLACK";
	else if (c == ORANGE)
		Color = "ORANGE";
	else if (c == GREEN)
		Color = "GREEN";
	else if (c == YELLOW)
		Color = "YELLOW";
	else if (c == BLUE)
		Color = "BLUE";
	else if (c == WHITE)
		Color = "Non filled";
	}
	string s = "selected Figure Info-->      Type: Square         ID: " + to_string(ID) + "   Center: (" + to_string(Center.x) + "," + to_string(Center.y) + ")     Length:"
		+ to_string(100)+"   Color: "+Color;
	pOut->PrintMessage(s);


}

char CSquare::keyshape()
{ 
	return '#';
}

string CSquare::colourshape()
{
	{	color c;
		c = (*this).FigGfxInfo.FillClr;
		if (c == RED)
			return "RED";
		else if (c == BLACK)
			return "BLACK";
		else if (c == ORANGE)
			return "ORANGE";
		else if (c == GREEN)
			return "GREEN";
		else if (c == YELLOW)
			return "YELLOW";
		else if (c == BLUE)
			return"BLUE";
		else if (c == WHITE)
			return "WHITE";
	}
}

void CSquare::MoveFig(Point P)
{
	//check if figure out of the drawing area
	set_center(Center);
	if (P.x + 100 > UI.width - 15)       // UI.width-15 --> because of UI.Width is not enough
	{
		P.x = UI.width - 15 - 100;
	}
	if (P.x - 100 < 0)
	{
		P.x = 100;
	}
	if (P.y + 100 > UI.height - UI.StatusBarHeight)
	{
		P.y = UI.height - UI.StatusBarHeight - 100;
	}
	if (P.y - 100 < UI.ToolBarHeight )
	{
		P.y = UI.ToolBarHeight  + 100;

	}
	Center = P;
}

Point CSquare::get_center()
{
	return center_undo;
}

void CSquare::set_center(Point p)
{
	center_undo = p;
}
void CSquare::save(ofstream& Outputfile)
{
	Outputfile << FigerName << " " << ID << " " << Center.x << " " << Center.y << " " << GetColor(FigGfxInfo.DrawClr) << " " << GetColor(FigGfxInfo.FillClr) << " " << FigGfxInfo.isFilled << endl;

}

void CSquare::Load(ifstream& infile)
{
	int id;
	bool isfilled;
	string drawclr;
	string fillclr;
	GfxInfo gfx;
	infile >> id >> Center.x >> Center.y >> drawclr >> fillclr >> isfilled;
	setID(id);
	gfx.DrawClr = getstring(drawclr);
	gfx.FillClr = getstring(fillclr);
	gfx.isFilled = isfilled;
	SetSelected(false);
	setgfxinfo(gfx);
}
