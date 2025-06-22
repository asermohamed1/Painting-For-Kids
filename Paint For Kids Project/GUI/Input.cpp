#include "Input.h"
#include "Output.h"


Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int& x, int& y) const
{
	pWind->FlushMouseQueue();
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}


//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			if (ClickedItemOrder == 9)
			{


			}
			switch (ClickedItemOrder)
			{
			case ITM_SELECT: return Select;
			case ITM_TRI: return Triangle;
			case ITM_RECT: return DRAW_RECT;
			case ITM_SQUARE: return SQUARE;
			case ITM_HEXA: return HEXA;
			case ITM_CIRCLE: return CIRCLE;
			case ITM_FILLCOLOUR: return FILLCOLOUR;
			case ITM_PENCIL: return PENCIL;
			case ITM_RED: return rED;
			case ITM_GREEN: return gREEN;
			case ITM_YELLOW: return yELLOW;
			case ITM_ORANGE: return oRANGEE;
			case ITM_BLUE: return bLUE;
			case ITM_BLACK: return bLACK;
			case ITM_UNDO: return UNDO;
			case ITM_REDO: return REDO;
			case ITM_RECORD: return RECORD;
			case ITM_STOPRECORD: return STOPRECORD;
			case ITM_PLAYREC: return PLAYREC;
			case ITM_VOICE: return VOICE;
			case ITM_MUTE: return MUTE;
			case ITM_MOVE: return MOVE;
			case ITM_PLAY: return PLAY;
			case ITM_UPLOAD: return UPLOAD;
			case ITM_SAVE: return SAVE;
			case ITM_ERASE: return ERASE;
			case ITM_DELETE:return Delete;
			case ITM_EXIT: return EXIT;


			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			if (ClickedItemOrder == 9)
			{


			}
			switch (ClickedItemOrder)
			{
				case PLAY_ITM_COLOUR: return colour;
				case PLAY_ITM_SHAPE: return shape;
				case PLAY_ITM_SHAPECOLOUR: return shapecolour;
				case PLAY_ITM_DRAW: return draw;
				case PLAY_ITM_restart:return restart;
				case PLAY_ITM_EXIT: return EXIT;
				default:return EMPTY;
			}
		}

		else if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return PLAYING_AREA;
		}
		else
			return STATUS;//just for now. This should be updated

		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action	

	}

}


/////////////////////////////////

Input::~Input()
{
}
