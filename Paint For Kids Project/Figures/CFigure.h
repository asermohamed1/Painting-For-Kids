#ifndef CFIGURE_H
#define CFIGURE_H
#include<fstream>
#include "..\defs.h"
#include "..\GUI\Output.h"

//Base class for all figures
class CFigure
{
protected:
	 int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	static int id;
	/// Add more parameters if needed.
	bool x;//to check if shape is hidden or not
public:
	CFigure(GfxInfo FigureGfxInfo);
	void setID(int ID);
	void setgfxinfo(GfxInfo GI);
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	int get_id();
	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	virtual bool isThisFigure(Point p) const = 0; //Check is this the selected figure
	              ///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	
	virtual char keyshape() = 0;
	virtual string colourshape() = 0;
	void setishidden(const int);
	bool ishidden();
	// move the figure
	virtual	void MoveFig(Point P) = 0; // Move the figure to another point
	virtual color return_fill_color();
	virtual void null_fill_color();
	virtual color return_draw_color();
	virtual Point get_center() = 0;
	virtual void set_center(Point P) = 0;
	virtual void save(ofstream& Outputfile) = 0;
	virtual void Load(ifstream& infile) = 0;
	string GetColor(color c);
	color getstring(string s);
	virtual void PrintInfo(Output* pOut) const =0 ;	//print all figure info on the status bar
};

#endif