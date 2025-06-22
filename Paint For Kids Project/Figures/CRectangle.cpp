#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	center.x = (Corner1.x + Corner2.x) / 2.0;
	center.y = (Corner1.y + Corner2.y) / 2.0;
}
CRectangle::CRectangle(GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
}


void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

bool CRectangle::isThisFigure(Point p) const
{
	if (Corner1.y < Corner2.y&&Corner1.x<Corner2.x) {

		if (p.y >= Corner1.y && p.y <= Corner2.y && p.x >= Corner1.x && p.x <= Corner2.x)
			return true;
		else return false;
	}
	else if (Corner1.y < Corner2.y && Corner1.x > Corner2.x) {

		if (p.y >= Corner1.y && p.y <= Corner2.y && p.x <= Corner1.x && p.x >= Corner2.x)
			return true;
		else return false;

	}
	else if (Corner1.y > Corner2.y && Corner1.x < Corner2.x) {

		if (p.y <= Corner1.y && p.y >= Corner2.y && p.x >= Corner1.x && p.x <= Corner2.x)
			return true;
		else return false;
	}
	else {

		if (p.y >= Corner2.y && p.y <= Corner1.y && p.x >= Corner2.x && p.x <= Corner1.x)
			return true;
		else return false;
	}
}

void CRectangle::PrintInfo(Output* pOut) const
{
	int width, length;
	if(abs(Corner1.x - Corner2.x) > abs(Corner1.y - Corner2.y))   //Check which is bigger to determine the length & the width
	{
		length = abs(Corner1.x - Corner2.x);
		width = abs(Corner1.y - Corner2.y);
	}
	else {
		length = abs(Corner1.y - Corner2.y);
		width = abs(Corner1.x - Corner2.x);
	}
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
	string s = "selected Figure Info-->      Type: Rectangle       ID: " + to_string(ID) + "   Center: (" + to_string((Corner1.x+Corner2.x)/2) + "," + to_string((Corner1.y + Corner2.y) / 2) + ")     Length:"
		+ to_string(length)+"     Whidth: "+to_string(width)+"   Color: "+Color;
	pOut->PrintMessage(s);

}

char CRectangle::keyshape()
{
	return'$';
}

string CRectangle::colourshape()
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

void CRectangle::MoveFig(Point P)
{
	Point center;
	center.x = (Corner1.x + Corner2.x) / 2.0;
	center.y = (Corner1.y + Corner2.y) / 2.0;
	set_center(center);
	//check if figure out of the drawing area

	if (Corner1.x > Corner2.x && Corner1.y < Corner2.y) {

		if (P.x + (Corner1.x - center.x) > UI.width - 15)       // UI.width-15 --> because of UI.Width is not enough
		{
			P.x = UI.width - 15 - (Corner1.x - center.x);
		}
		if (P.x - (Corner1.x - center.x) < 0)
		{
			P.x = (Corner1.x - center.x);
		}
		if (P.y - (Corner2.y - center.y) < UI.ToolBarHeight)
		{
			P.y = (Corner2.y - center.y) + UI.ToolBarHeight ;
		}
		if (P.y + (Corner2.y - center.y) > UI.height-UI.StatusBarHeight)
		{
			P.y = UI.height - UI.StatusBarHeight -(Corner2.y - center.y);
		}
		Corner1.x = P.x + (Corner1.x - center.x);
		Corner1.y = P.y + (Corner1.y - center.y);
		Corner2.x = P.x + (Corner2.x - center.x);
		Corner2.y = P.y + (Corner2.y - center.y);

	}
	if (Corner1.x < Corner2.x && Corner1.y < Corner2.y) {

		if (P.x + (Corner2.x - center.x) > UI.width - 15)
		{
			P.x = UI.width - 15 - (Corner2.x - center.x);
		}
		if (P.x - (Corner2.x - center.x) < 0)
		{
			P.x = (Corner2.x - center.x);
		}
		if (P.y - (Corner2.y - center.y) < UI.ToolBarHeight)
		{
			P.y = (Corner2.y - center.y) + UI.ToolBarHeight ;
		}
		if (P.y + (Corner2.y - center.y) > UI.height-UI.StatusBarHeight)
		{
			P.y = UI.height - UI.StatusBarHeight -(Corner2.y - center.y);
		}
		Corner1.x = P.x + (Corner1.x - center.x);
		Corner1.y = P.y + (Corner1.y - center.y);
		Corner2.x = P.x + (Corner2.x - center.x);
		Corner2.y = P.y + (Corner2.y - center.y);

	}
	if (Corner1.x < Corner2.x && Corner1.y > Corner2.y) {

		if (P.x + (Corner2.x - center.x) > UI.width - 15)
		{
			P.x = UI.width - 15 - (Corner2.x - center.x);
		}
		if (P.x - (Corner2.x - center.x) < 0)
		{
			P.x = (Corner2.x - center.x);
		}
		if (P.y - (Corner1.y - center.y) < UI.ToolBarHeight)
		{
			P.y = (Corner1.y - center.y) + UI.ToolBarHeight;
		}
		if (P.y + (Corner1.y - center.y) > UI.height - UI.StatusBarHeight)
		{
			P.y = UI.height - UI.StatusBarHeight - (Corner1.y - center.y);
		}
		Corner1.x = P.x + (Corner1.x - center.x);
		Corner1.y = P.y + (Corner1.y - center.y);
		Corner2.x = P.x + (Corner2.x - center.x);
		Corner2.y = P.y + (Corner2.y - center.y);

	}
	if (Corner1.x > Corner2.x && Corner1.y > Corner2.y) {

		if (P.x + (Corner1.x - center.x) > UI.width - 15)
		{
			P.x = UI.width - 15 - (Corner1.x - center.x);
		}
		if (P.x - (Corner1.x - center.x) < 0)
		{
			P.x = (Corner1.x - center.x);
		}
		if (P.y - (Corner1.y - center.y) < UI.ToolBarHeight)
		{
			P.y = (Corner1.y - center.y) + UI.ToolBarHeight;
		}
		if (P.y + (Corner1.y - center.y) > UI.height - UI.StatusBarHeight)
		{
			P.y = UI.height - UI.StatusBarHeight - (Corner1.y - center.y);
		}
		Corner1.x = P.x + (Corner1.x - center.x);
		Corner1.y = P.y + (Corner1.y - center.y);
		Corner2.x = P.x + (Corner2.x - center.x);
		Corner2.y = P.y + (Corner2.y - center.y);

	}
}

Point CRectangle::get_center()
{
	return center;
}

void CRectangle::set_center(Point P)
{
	center = P;
}
void CRectangle::save(ofstream& Outputfile)
{
	Outputfile << FigerName << " " << ID << " " << Corner1.x << " " << Corner1.y << " " << Corner2.x << " " << Corner2.y << " " << GetColor(FigGfxInfo.DrawClr) << " " << GetColor(FigGfxInfo.FillClr) << " " << FigGfxInfo.isFilled << endl;

}
void CRectangle::Load(ifstream& infile)
{
	int id;
	bool isfilled;
	string drawclr;
	string fillclr;
	GfxInfo gfx;
	infile >> id >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> drawclr >> fillclr >> isfilled;
	setID(id);
	gfx.DrawClr = getstring(drawclr);
	gfx.FillClr = getstring(fillclr);
	gfx.isFilled = isfilled;
	SetSelected(false);
	setgfxinfo(gfx);
}