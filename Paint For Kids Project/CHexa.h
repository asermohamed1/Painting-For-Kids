#ifndef HEXA_H
#define HEXA_H
#include "Figures/CFigure.h"
class CHexa : public CFigure
{
private:
	Point Center;
	Point center_undo;
	string FigerName = "HEXAGON";
public:
	CHexa(Point, GfxInfo FigureGfxInfo);
	CHexa(GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool isThisFigure(Point p) const ;  // Check is this the selected figure
	virtual void PrintInfo(Output* pOut) const;	//print all figure info on the status bar
	char keyshape();
	virtual string colourshape();
	virtual	void MoveFig(Point P); // Move the hexagon to another point
	virtual Point get_center();
	virtual void set_center(Point P);
	virtual void save(ofstream& Outputfile);
	virtual void Load(ifstream& infile);
};
#endif
