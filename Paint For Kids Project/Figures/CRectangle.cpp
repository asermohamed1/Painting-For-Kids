#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
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
	return p.x >= min(Corner1.x, Corner2.x) && p.x <= max(Corner1.x, Corner2.x)
		&& p.y >= min(Corner1.y, Corner2.y) && p.y <= max(Corner1.y, Corner2.y);
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
	string Color = colourshape();
	if (Color == "WHITE")
		Color = "Non filled";
	string s = "selected Figure Info-->      Type: Rectangle       ID: " + to_string(ID) + "   Center: (" + to_string((Corner1.x+Corner2.x)/2) + "," + to_string((Corner1.y + Corner2.y) / 2) + ")     Length:"
		+ to_string(length)+"     Whidth: "+to_string(width)+"   Color: "+Color;
	pOut->PrintMessage(s);

}

char CRectangle::keyshape()
{
	return'$';
}

void CRectangle::MoveFig(Point P)
{
	Point center = get_center();
	//corner offsets from the center
	int left = min(Corner1.x, Corner2.x) - center.x, right = max(Corner1.x, Corner2.x) - center.x;
	int top = min(Corner1.y, Corner2.y) - center.y, bottom = max(Corner1.y, Corner2.y) - center.y;

	//keep the rectangle inside the drawing area
	if (P.x + right > UI.width - 15)       // UI.width-15 --> because of UI.Width is not enough
		P.x = UI.width - 15 - right;
	if (P.x + left < 0)
		P.x = -left;
	if (P.y + top < UI.ToolBarHeight)
		P.y = UI.ToolBarHeight - top;
	if (P.y + bottom > UI.height - UI.StatusBarHeight)
		P.y = UI.height - UI.StatusBarHeight - bottom;

	Corner1.x += P.x - center.x;
	Corner1.y += P.y - center.y;
	Corner2.x += P.x - center.x;
	Corner2.y += P.y - center.y;
}

Point CRectangle::get_center()
{
	Point c;
	c.x = (Corner1.x + Corner2.x) / 2;
	c.y = (Corner1.y + Corner2.y) / 2;
	return c;
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