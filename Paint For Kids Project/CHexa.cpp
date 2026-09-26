#include "CHexa.h"
#include<cmath>
CHexa::CHexa(GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
}

CHexa::CHexa(Point center, GfxInfo FigureGfxInfo): CFigure(FigureGfxInfo)
{
	Center = center;
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

    // Maximum distance from the center to the hexagon's side (side length 100)
    const double maxXD = 100;
    const double maxYD = 86.602540378443865;    // 100 * sqrt(3) / 2
    const double slope = 0.57735026918962576;   // sqrt(3) / 3

    // Check if the point is within the hexagon bounds
    return dX <= maxXD && dY <= maxYD && dX <= maxXD - slope * dY;
}

void CHexa::PrintInfo(Output* pOut) const
{
	string Color = colourshape();
	if (Color == "WHITE")
		Color = "Non filled";

	string s = "selected Figure Info-->        Type: Hexagon      ID: " + to_string(ID) + "   Center: (" + to_string(Center.x) + "," + to_string(Center.y) + ")   Length of the side:"
		+ to_string(100)+ "   Color: "+Color;
	pOut->PrintMessage(s);

}

char CHexa::keyshape()
{
	return '@';
}

void CHexa::MoveFig(Point P)
{
	//check if figure is out of the drawing area
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
	return Center;
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

