#ifndef CCIRCLE_H
#define CCIRCLE_H
#include "Figures/CFigure.h"
class CCircle : public CFigure
{
private:
	Point Center;
	Point point;
	Point center_undo;
	string FigerName = "CIRCLE";
public:
	CCircle(Point, Point, GfxInfo FigureGfxInfo);
	CCircle(GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool isThisFigure(Point p) const;  // Check is this the selected figure
	virtual void PrintInfo(Output* pOut) const;	//print all figure info on the status bar
	char keyshape();
	virtual string colourshape();
	virtual	void MoveFig(Point P) ; // Move the circle to another point
	virtual Point get_center();
	virtual void set_center(Point P);
	virtual void save(ofstream& Outputfile);
	virtual void Load(ifstream& infile);
};
#endif
