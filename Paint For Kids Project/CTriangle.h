#ifndef TRIANG_H
#define TRIANG_H
#include "Figures/CFigure.h"
class CTriangle : public CFigure
{

private:
	Point Corner1;
	Point Corner2;
	Point Corner3;
	Point center_undo;
	string FigerName = "TRIANG";
	static int numtriangles;
public:
	CTriangle(Point, Point,Point, GfxInfo FigureGfxInfo);
	CTriangle(GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool isThisFigure(Point p) const;  // Check is this the selected figure
	virtual void PrintInfo(Output* pOut) const;	//print all figure info on the status bar
	char keyshape();
	static int getnumshapes();
	virtual string colourshape();
	virtual	void MoveFig(Point P);   // Move the triangle to another point
	virtual Point get_center();
	virtual void set_center(Point P);
	virtual void save(ofstream& Outputfile);
	virtual void Load(ifstream& infile);
};
#endif
