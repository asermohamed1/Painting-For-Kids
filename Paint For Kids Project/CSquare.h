#pragma once
#include "Figures/CFigure.h"
class CSquare : public CFigure
{
private :
	Point Center;
	string FigerName = "SQUARE";
public:
	CSquare(Point, GfxInfo FigureGfxInfo);
	CSquare(GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool isThisFigure(Point p) const;  // Check is this the selected figure
	virtual void PrintInfo(Output* pOut) const;	//print all figure info on the status bar
	char keyshape();
	virtual	void MoveFig(Point P); // Move the square to another point
	virtual Point get_center();
	virtual void save(ofstream& Outputfile);
	virtual void Load(ifstream& infile);
};

