#include "CTriangle.h"
#include <cmath>
CTriangle::CTriangle(GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
}
CTriangle::CTriangle(Point P1, Point P2,Point P3, GfxInfo FigureGfxInfo) : CFigure(FigureGfxInfo)
{
	Corner1 = P1;	Corner2 = P2;	Corner3 = P3;
	numtriangles++;
	center_undo.x = (Corner1.x + Corner2.x + Corner3.x) / 3.0;
	center_undo.y = (Corner1.y + Corner2.y + Corner3.y) / 3.0;
}

void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DrawTriang to draw a triangle on the screen	

	pOut->DrawTriang(Corner1, Corner2, Corner3, FigGfxInfo, Selected);
}

bool CTriangle::isThisFigure(Point p) const
{
	float A  = abs(Corner1.x*(Corner2.y-Corner3.y)+Corner2.x*(Corner3.y-Corner1.y)+Corner3.x*(Corner1.y-Corner2.y))/2.0;  //Area of all triangle
	float A1 = abs(p.x * (Corner1.y - Corner2.y) + Corner1.x * (Corner2.y - p.y) + Corner2.x * (p.y - Corner1.y)) / 2.0;  //Area of the first small triangle
	float A2 = abs(p.x * (Corner2.y - Corner3.y) + Corner2.x * (Corner3.y - p.y) + Corner3.x * (p.y - Corner2.y)) / 2.0;  //Area of the second small triangle
	float A3 = abs(p.x * (Corner3.y - Corner1.y) + Corner3.x * (Corner1.y - p.y) + Corner1.x * (p.y - Corner3.y)) / 2.0;  //Area of the third small triangle
	if (A == A1 + A2 + A3) return true; //check is the sum of small areaa = the big area or not
	else return false;
}

void CTriangle::PrintInfo(Output* pOut) const
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
	string s = "selected Figure Info-->   Type : Triangle    ID: " + to_string(ID) + "  Center: (" + to_string((Corner1.x + Corner2.x + Corner3.x) / 3) + "," + to_string((Corner1.y + Corner2.y + Corner3.y) / 3)
		+ ")     Corner1: (" + to_string(Corner1.x) + "," + to_string(Corner1.y) + ")     Corner2: (" + to_string(Corner2.x) + "," + to_string(Corner2.y) + ")     Corner3: (" + to_string(Corner3.x) + "," + to_string(Corner3.y) + ")"+"   Color: "+Color;
	pOut->PrintMessage(s);


}
 
char CTriangle::keyshape()
{
	return '*';
}
int CTriangle::numtriangles = 0;


int CTriangle::getnumshapes()
{
	return numtriangles;
}

string CTriangle::colourshape()
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

void CTriangle::MoveFig(Point P)
{
	//check if figure out of the drawing area

	Point Center;
	Center.x = (Corner1.x + Corner2.x + Corner3.x) / 3.0;
	Center.y = (Corner1.y + Corner2.y + Corner3.y) / 3.0;
	set_center(Center);
	Corner1.x += (P.x - Center.x);
	Corner2.x += (P.x - Center.x);
	Corner3.x += (P.x - Center.x);
	Corner1.y += (P.y - Center.y);
	Corner2.y += (P.y - Center.y);
	Corner3.y += (P.y - Center.y);
	Center = P;
	if (Corner1.x > UI.width - 15) {
		P.x = P.x - (Corner1.x - (UI.width - 15));
		Corner1.x += (P.x - Center.x);
		Corner2.x += (P.x - Center.x);
		Corner3.x += (P.x - Center.x);
		Center = P;
	}
	if (Corner1.x <0) {
		P.x = P.x + (-Corner1.x);
		Corner1.x += (P.x - Center.x);
		Corner2.x += (P.x - Center.x);
		Corner3.x += (P.x - Center.x);
		Center = P;
	}
	if (Corner2.x > UI.width - 15) {
		P.x = P.x - (Corner2.x - (UI.width - 15));
		Corner1.x += (P.x - Center.x);
		Corner2.x += (P.x - Center.x);
		Corner3.x += (P.x - Center.x);
		Center = P;
	}
	if (Corner2.x <0) {
		P.x = P.x + (-Corner2.x);
		Corner1.x += (P.x - Center.x);
		Corner2.x += (P.x - Center.x);
		Corner3.x += (P.x - Center.x);
		Center = P;
	}
	if (Corner3.x > UI.width - 15) {
		P.x = P.x - (Corner3.x - (UI.width - 15));
		Corner1.x += (P.x - Center.x);
		Corner2.x += (P.x - Center.x);
		Corner3.x += (P.x - Center.x);
		Center = P;
	}
	if (Corner3.x <0) {
		P.x = P.x + (-Corner3.x);
		Corner1.x += (P.x - Center.x);
		Corner2.x += (P.x - Center.x);
		Corner3.x += (P.x - Center.x);
		Center = P;
	}
	if (Corner1.y < UI.ToolBarHeight) {
		P.y = P.y + ( UI.ToolBarHeight- Corner1.y );
		Corner1.y += (P.y - Center.y);
		Corner2.y += (P.y - Center.y);
		Corner3.y += (P.y - Center.y);
		Center = P;
	}
	if (Corner1.y > UI.height-UI.StatusBarHeight) {
		P.y = P.y - (Corner1.y -( UI.height - UI.StatusBarHeight-2));
		Corner1.y += (P.y - Center.y);
		Corner2.y += (P.y - Center.y);
		Corner3.y += (P.y - Center.y);
		Center = P;
	}if (Corner2.y < UI.ToolBarHeight) {
		P.y = P.y + (UI.ToolBarHeight - Corner2.y);
		Corner1.y += (P.y - Center.y);
		Corner2.y += (P.y - Center.y);
		Corner3.y += (P.y - Center.y);
		Center = P;
	}
	if (Corner2.y > UI.height - UI.StatusBarHeight) {
		P.y = P.y - (Corner2.y - (UI.height - UI.StatusBarHeight-2));
		Corner1.y += (P.y - Center.y);
		Corner2.y += (P.y - Center.y);
		Corner3.y += (P.y - Center.y);
		Center = P;
	}
	if (Corner3.y < UI.ToolBarHeight) {
		P.y = P.y + (UI.ToolBarHeight - Corner3.y);
		Corner1.y += (P.y - Center.y);
		Corner2.y += (P.y - Center.y);
		Corner3.y += (P.y - Center.y);
		Center = P;
	}
	if (Corner3.y > UI.height - UI.StatusBarHeight) {
		P.y = P.y - (Corner3.y - (UI.height - UI.StatusBarHeight-2));
		Corner1.y += (P.y - Center.y);
		Corner2.y += (P.y - Center.y);
		Corner3.y += (P.y - Center.y);
		Center = P;
	}




}

Point CTriangle::get_center()
{
	return center_undo;
}

void CTriangle::set_center(Point P)
{
	center_undo = P;
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
