#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();

	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateMoveToolBar() const; //creates Move toolbar
	void CreateStatusBar() const;	//create the status bar
	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	void Cleartoolbar()const;  //Clears the toolbar

	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a rectangle
	void DrawSqr(Point P1, GfxInfo SqrGfxInfo, bool selected = false) const;  //Draw a Square
	void DrawTriang(Point P1, Point P2, Point P3, GfxInfo TriangGfxInfo, bool selected = false); //Draw a Triangle
	void DrawHexa(Point P1, GfxInfo HexaGfxInfo, bool selected = false) const;  //Draw a Hexagon
	void DrawCirc(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected = false);  //Draw a Circle
	///Make similar functions for drawing all other figure types.
	string GetColor(color c);
	void PrintMessage(string msg) const;	//Print a message on Status bar
	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	Point GetMouseCoord() const;     //retrun the coordinates of the mouse
	bool GetMouseState() const;


	~Output();
};

#endif