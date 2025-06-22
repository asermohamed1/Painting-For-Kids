#include "CHexa.h"
#include<cmath>
CHexa::CHexa(GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
}

CHexa::CHexa(Point center, GfxInfo FigureGfxInfo): CFigure(FigureGfxInfo)
{
	Center = center;
	center_undo = center;
}

void CHexa::Draw(Output* pOut) const
{
   
	//Call Output::DrawHexa to draw a Hexagon on the screen	
	pOut->DrawHexa(Center, FigGfxInfo, Selected);
}

bool CHexa::isThisFigure(Point p) const
{
    // Calculate the distance between the point and the hexagon's center
    double dX = abs(p.x - Center.x);
    double dY = abs(p.y - Center.y);

    // Calculate the maximum distance from the center to the hexagon's side
    double maxXD = 100;
    double maxYD = 100* sqrt(3) / 2;

    // Check if the point is within the hexagon bounds
    if (dX <= maxXD) {
        if (dY <= maxYD) {
          if(dX<=100-(sqrt(3.0)/3.0)*dY)
                return true;
        }
    }
    return false;
}

void CHexa::PrintInfo(Output* pOut) const
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

	string s = "selected Figure Info-->        Type: Hexagon      ID: " + to_string(ID) + "   Center: (" + to_string(Center.x) + "," + to_string(Center.y) + ")   Length of the side:"
		+ to_string(100)+ "   Color: "+Color;
	pOut->PrintMessage(s);

}

char CHexa::keyshape()
{
	return '@';
}

string CHexa::colourshape()
{         
	{color c;
		c = (*this).FigGfxInfo.FillClr;
			 if (c == GREEN)
				return "GREEN";
		else if (c == RED)
			return "RED";
		else if (c == BLACK)
			return "BLACK";
		else if (c == ORANGE)
			return "ORANGE";
		
		else if (c == YELLOW)
			return "YELLOW";
		else if (c == BLUE)
			return"BLUE";
		else if ( c == WHITE)
				 return "WHITE";
	}
}

void CHexa::MoveFig(Point P)
{
	//check if figure is out of the drawing area
	set_center(Center);
	if (P.x + 100 > UI.width - 15)       // UI.width-15 --> because of UI.Width is not enough
	{
		P.x = UI.width - 15 - 100;
	}
	if (P.x - 100 < 0)
	{
		P.x = 100;
	}
	if (P.y - ((sqrt(3.0)/2.0)*100) < (UI.ToolBarHeight ))
	{
		P.y = UI.ToolBarHeight  + (sqrt(3.0) / 2.0) * 100;
	}
	if (P.y + (sqrt(3.0) / 2.0) * 100 > (UI.height - UI.StatusBarHeight))
	{
		P.y = UI.height - UI.StatusBarHeight - (sqrt(3.0) / 2.0) * 100;
	}
	Center = P;
}

Point CHexa::get_center()
{
	return center_undo;
}

void CHexa::set_center(Point P)
{
	center_undo = P;
}

void CHexa::save(ofstream& Outputfile)
{
	Outputfile << FigerName << " " << ID << " " << Center.x << " " << Center.y << " " << GetColor(FigGfxInfo.DrawClr) << " " << GetColor(FigGfxInfo.FillClr) << " " << FigGfxInfo.isFilled << endl;
}
void CHexa::Load(ifstream& infile)
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

