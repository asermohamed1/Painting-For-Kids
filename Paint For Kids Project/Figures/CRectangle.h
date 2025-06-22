#ifndef CRectangle_H
#define CRectangle_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
	Point center;
	string FigerName = "RECT";
public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	CRectangle(GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool isThisFigure(Point p) const;  // Check is this the selected figure
	virtual void PrintInfo(Output* pOut) const;	//print all figure info on the status bar
	char keyshape();
	virtual string colourshape();
	virtual	void MoveFig(Point P); // Move the rectangle to another point
	virtual Point get_center();
	virtual void set_center(Point P);
	virtual void save(ofstream& Outputfile);
	virtual void Load(ifstream& infile);
};

#endif