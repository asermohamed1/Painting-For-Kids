#include "CFigure.h"
int CFigure::id = 1;
CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID = id;
	id++;
	x = false;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

int CFigure::get_id()
{
	return ID;
}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
		FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr;
}

color CFigure::return_fill_color()
{
	return (*this).FigGfxInfo.FillClr;;
}

void CFigure::null_fill_color()
{
	FigGfxInfo.isFilled = false;
}

color CFigure::return_draw_color()
{
	return (*this).FigGfxInfo.DrawClr;
}


void CFigure::setishidden(const int y)
{
	x = y;
}


bool CFigure::ishidden()
{
	return x;
}
void CFigure::setID(int ID)
{
	if (this)
		this->ID = ID;
}
void CFigure::setgfxinfo(GfxInfo GI)
{
	FigGfxInfo = GI;
}
string CFigure::GetColor(color c)
{
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
	else return "NO_COLOR";
}

color CFigure::getstring(string s)
{
	if (s == "RED")
		return RED;
	else if (s == "BLACK")
		return BLACK;
	else if (s == "ORANGE")
		return ORANGE;
	else if (s == "GREEN")
		return GREEN;
	else if (s == "YELLOW")
		return YELLOW;
	else if (s == "BLUE")
		return BLUE;
	else
		return LIGHTBLUE;
}
