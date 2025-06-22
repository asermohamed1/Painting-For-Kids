#include "CCircle.h"

CCircle::CCircle(GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
}
CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	Center = P1;
	point = P2;
	center_undo = Center;
}


void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawCirc to draw a Circle on the screen	
	pOut->DrawCirc(Center, point, FigGfxInfo, Selected);
}

bool CCircle::isThisFigure(Point p) const
{
	float radius=  sqrt((Center.x - point.x) * (Center.x - point.x) + (Center.y - point.y) * (Center.y - point.y));
	float d= sqrt((Center.x - p.x) * (Center.x - p.x) + (Center.y - p.y) * (Center.y - p.y));

	if (d<=radius)
		return true;
	else return false;
}

void CCircle::PrintInfo(Output* pOut) const
{ 
	string Color;
	{	color c;
	c = (*this).FigGfxInfo.FillClr;
	if (c == RED)
		Color= "RED";
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

	int  radius = sqrt((Center.x - point.x) * (Center.x - point.x) + (Center.y - point.y) * (Center.y - point.y)); //Determines the Radius of the Circle
	string s = "selected Figure Info-->     Type: Circle      ID: " + to_string(ID) + "   Center: (" + to_string(Center.x) + "," + to_string(Center.y) + ")   radius:"
		+to_string(radius)+ "    color: "+ Color;
	pOut->PrintMessage(s);

}

char CCircle::keyshape()
{
	return '!';
}

string CCircle::colourshape()
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
		else if(c==WHITE)
			return "WHITE";
	}
}

void CCircle::MoveFig(Point P)
{
	set_center(Center);
	float  radius = sqrt((Center.x - point.x) * (Center.x - point.x) + (Center.y - point.y) * (Center.y - point.y));
	
	//check if figure is out of the drawing area
	if (P.x + radius > UI.width- 15)      // UI.width-15 --> because of UI.Width is not enough
	{
		P.x = UI.width - 15 - radius;
	}
	if (P.y - radius < (UI.ToolBarHeight))
	{
		P.y = UI.ToolBarHeight+ radius;
	}
	
	if (P.y + radius > (UI.height-UI.StatusBarHeight))
	{
		P.y = (UI.height-UI.StatusBarHeight)- radius-1;
	}
	if (P.x - radius < 0)
	{
		P.x = radius;
	}
	Center.x = P.x;
	Center.y = P.y;
	point.x = Center.x + radius;
	point.y = Center.y;
	
}

Point CCircle::get_center()
{
	return center_undo;
}

void CCircle::set_center(Point P)
{
	center_undo = P;
}
void CCircle::save(ofstream& Outputfile)
{
	Outputfile << FigerName << " " << ID << " " << Center.x << " " << Center.y << " " << point.x << " " << point.y << " " << GetColor(FigGfxInfo.DrawClr) << " " << GetColor(FigGfxInfo.FillClr) << " " << FigGfxInfo.isFilled << endl;
}
void CCircle::Load(ifstream& infile)
{
	int id;
	bool isfilled;
	string drawclr;
	string fillclr;
	GfxInfo gfx;
	infile >> id >> Center.x >> Center.y >> point.x >> point.y >> drawclr >> fillclr >> isfilled;
	setID(id);
	gfx.DrawClr = getstring(drawclr);
	gfx.FillClr = getstring(fillclr);
	gfx.isFilled = isfilled;
	SetSelected(false);
	setgfxinfo(gfx);
}