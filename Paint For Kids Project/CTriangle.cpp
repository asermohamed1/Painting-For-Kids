#include "CTriangle.h"
#include <cmath>
CTriangle::CTriangle(GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
}
CTriangle::CTriangle(Point P1, Point P2,Point P3, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Corner1 = P1;	Corner2 = P2;	Corner3 = P3;
}

void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawTriang to draw a triangle on the screen	

	pOut->DrawTriang(Corner1, Corner2, Corner3, FigGfxInfo, Selected);
}

bool CTriangle::isThisFigure(Point p) const
{
	//twice the signed area of each small triangle (exact integer math, no float comparison)
	long long d1 = (long long)(p.x - Corner2.x) * (Corner1.y - Corner2.y) - (long long)(Corner1.x - Corner2.x) * (p.y - Corner2.y);
	long long d2 = (long long)(p.x - Corner3.x) * (Corner2.y - Corner3.y) - (long long)(Corner2.x - Corner3.x) * (p.y - Corner3.y);
	long long d3 = (long long)(p.x - Corner1.x) * (Corner3.y - Corner1.y) - (long long)(Corner3.x - Corner1.x) * (p.y - Corner1.y);
	bool hasNeg = d1 < 0 || d2 < 0 || d3 < 0;
	bool hasPos = d1 > 0 || d2 > 0 || d3 > 0;
	return !(hasNeg && hasPos);	//inside or on the border when all have the same sign
}

void CTriangle::PrintInfo(Output* pOut) const
{
	string Color = colourshape();
	if (Color == "WHITE")
		Color = "Non filled";
	string s = "selected Figure Info-->   Type : Triangle    ID: " + to_string(ID) + "  Center: (" + to_string((Corner1.x + Corner2.x + Corner3.x) / 3) + "," + to_string((Corner1.y + Corner2.y + Corner3.y) / 3)
		+ ")     Corner1: (" + to_string(Corner1.x) + "," + to_string(Corner1.y) + ")     Corner2: (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + ")     Corner3: (" + to_string(Corner3.x) + "," + to_string(Corner3.y) + ")"+"   Color: "+Color;
	pOut->PrintMessage(s);


}
 
char CTriangle::keyshape()
{
	return '*';
}

void CTriangle::MoveFig(Point P)
{
	Point center = get_center();
	//corner offsets from the center
	int left = min(min(Corner1.x, Corner2.x), Corner3.x) - center.x;
	int right = max(max(Corner1.x, Corner2.x), Corner3.x) - center.x;
	int top = min(min(Corner1.y, Corner2.y), Corner3.y) - center.y;
	int bottom = max(max(Corner1.y, Corner2.y), Corner3.y) - center.y;

	//keep the triangle inside the drawing area
	if (P.x + right > UI.width - 15)
		P.x = UI.width - 15 - right;
	if (P.x + left < 0)
		P.x = -left;
	if (P.y + top < UI.ToolBarHeight)
		P.y = UI.ToolBarHeight - top;
	if (P.y + bottom > UI.height - UI.StatusBarHeight)
		P.y = UI.height - UI.StatusBarHeight - 2 - bottom;

	int dx = P.x - center.x, dy = P.y - center.y;
	Corner1.x += dx;	Corner2.x += dx;	Corner3.x += dx;
	Corner1.y += dy;	Corner2.y += dy;	Corner3.y += dy;
}

Point CTriangle::get_center()
{
	Point c;
	c.x = (Corner1.x + Corner2.x + Corner3.x) / 3;
	c.y = (Corner1.y + Corner2.y + Corner3.y) / 3;
	return c;
}

void CTriangle::save(ofstream& Outputfile)
{
	Outputfile << FigerName << " " << ID << " " << Corner1.x << " " << Corner1.y << " " << Corner2.x << " " << Corner2.y << " " << Corner3.x << " " << Corner3.y << " " << GetColor(FigGfxInfo.DrawClr) << " " << GetColor(FigGfxInfo.FillClr) << " " << FigGfxInfo.isFilled << endl;

}
void CTriangle::Load(ifstream& infile)
{
	int id;
	bool isfilled;
	string drawclr;
	string fillclr;
	GfxInfo gfx;
	infile >> id >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> Corner3.x >> Corner3.y >> drawclr >> fillclr >> isfilled;
	setID(id);
	gfx.DrawClr = getstring(drawclr);
	gfx.FillClr = getstring(fillclr);
	gfx.isFilled = isfilled;
	SetSelected(false);
	setgfxinfo(gfx);
}
