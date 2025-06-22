#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy = 5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 44;

	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor =WHITE;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames


	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\SELECT.jpg";
	MenuItemImages[ITM_TRI] = "images\\MenuItems\\TRI.jpg";
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\RECT.jpg";
	MenuItemImages[ITM_SQUARE] = "images\\MenuItems\\seq2.jpg";
	MenuItemImages[ITM_HEXA] = "images\\MenuItems\\hexx.jpg";
	MenuItemImages[ITM_CIRCLE] = "images\\MenuItems\\Circle.jpg";
	MenuItemImages[ITM_FILLCOLOUR] = "images\\MenuItems\\edit 3.jpg";
	MenuItemImages[ITM_PENCIL] = "images\\MenuItems\\pencil.jpg";
	MenuItemImages[ITM_RED] = "images\\MenuItems\\red.jpg";
	MenuItemImages[ITM_ORANGE] = "images\\MenuItems\\orange.jpg";
	MenuItemImages[ITM_YELLOW] = "images\\MenuItems\\yellow.jpg";
	MenuItemImages[ITM_GREEN] = "images\\MenuItems\\green.jpg";
	MenuItemImages[ITM_BLUE] = "images\\MenuItems\\blue.jpg";
	MenuItemImages[ITM_BLACK] = "images\\MenuItems\\black.jpg";
	MenuItemImages[ITM_UNDO] = "images\\MenuItems\\undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\MenuItems\\redo.jpg";
	MenuItemImages[ITM_RECORD] = "images\\MenuItems\\record.jpg";
	MenuItemImages[ITM_STOPRECORD] = "images\\MenuItems\\stop record.jpg";
	MenuItemImages[ITM_PLAYREC] = "images\\MenuItems\\play record.jpg";
	MenuItemImages[ITM_VOICE] = "images\\MenuItems\\voice.jpg";
	MenuItemImages[ITM_MUTE] = "images\\MenuItems\\muted.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\move.jpg";
	MenuItemImages[ITM_PLAY] = "images\\MenuItems\\play.jpg";
	MenuItemImages[ITM_UPLOAD] = "images\\MenuItems\\upload.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\save.jpg";
	MenuItemImages[ITM_ERASE] = "images\\MenuItems\\erase.jpg";
	MenuItemImages[ITM_DELETE] = "images\\MenuItems\\delete.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";




	//TODO: Prepare images for each menu item and add it to the list
	// 
	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[PLAY_ITM_COLOUR] = "images\\MenuItems\\colour.jpg";
	MenuItemImages[PLAY_ITM_SHAPE] = "images\\MenuItems\\shape.jpg";
	MenuItemImages[PLAY_ITM_SHAPECOLOUR] = "images\\MenuItems\\shapecolour.jpg";
	MenuItemImages[PLAY_ITM_DRAW] = "images\\MenuItems\\draw.jpg";
	MenuItemImages[PLAY_ITM_restart] = "images\\MenuItems\\restart.jpg";
	MenuItemImages[PLAY_ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";







	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * (UI.MenuItemWidth), 0, (UI.MenuItemWidth), UI.ToolBarHeight);//YOU USE HERE UI.WIDTH+7 TAKE CARE










	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
	///TODO: write code to create Play mode menu
}
void Output::CreateMoveToolBar() const
{
	//Draw the images of Move Type 
	UI.InterfaceMode= MODE_DRAW;
	
	pWind->DrawImage("images\\MenuItems\\moveToolBar.jpg", (ITM_MOVE -.5)* UI.MenuItemWidth, UI.ToolBarHeight , UI.MenuItemWidth, UI.MenuItemWidth); //Draw the image of move by click
	pWind->DrawImage("images\\MenuItems\\move by drag.jpg", (ITM_MOVE + .5) * UI.MenuItemWidth, UI.ToolBarHeight, UI.MenuItemWidth, UI.MenuItemWidth); //Draw the image of move by Dragging
	
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
void Output::Cleartoolbar() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

string Output::GetColor(color c)
{
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
	else
		return "NO_COLOR";
}

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.25), msg);
}

//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

Point Output::GetMouseCoord() const
{
	Point p;
	pWind->GetMouseCoord(p.x, p.y);
	return p;
}

bool Output::GetMouseState() const
{
	int z, w;
	if(pWind->GetButtonState(LEFT_BUTTON,z,w)==BUTTON_DOWN) return true;
	return false;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}
void Output::DrawSqr(Point P1, GfxInfo SqrGfxInfo, bool selected) const {

	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = SqrGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (SqrGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SqrGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x - 100, P1.y - 100, P1.x + 100, P1.y + 100, style);

}

void Output::DrawTriang(Point P1, Point P2, Point P3, GfxInfo TriangGfxInfo, bool selected) {


	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = TriangGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (TriangGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriangGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);

}
void Output::DrawHexa(Point P1, GfxInfo RectGfxInfo, bool selected) const {

	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;
	int arr_x[6] = { P1.x + 100,P1.x + 50,P1.x - 50,P1.x - 100,P1.x - 50,P1.x + 50 };
	int arr_y[6] = { P1.y,P1.y - ((float(sqrt(3)) / 2) * 100),P1.y - ((float(sqrt(3)) / 2) * 100),P1.y ,P1.y + ((float(sqrt(3)) / 2) * 100),P1.y + ((float(sqrt(3)) / 2) * 100) };

	pWind->DrawPolygon(arr_x, arr_y, 6, style);

}

void Output::DrawCirc(Point P1, Point P2, GfxInfo CircleGfxInfo, bool selected)
{

	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = CircleGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (CircleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int radius = sqrt((P1.x - P2.x) * (P1.x - P2.x) + (P1.y - P2.y) * (P1.y - P2.y));

	pWind->DrawCircle(P1.x, P1.y, radius, style);
}


//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

