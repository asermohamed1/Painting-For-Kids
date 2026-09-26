#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	Select,
	DRAW_RECT,
	Triangle,
	SQUARE,
	HEXA,
	CIRCLE,
	FILLCOLOUR,
	PENCIL,
	rED,
	gREEN,
	yELLOW,
	oRANGEE,
	bLUE,
	bLACK,
	UNDO,
	REDO,
	RECORD,
	STOPRECORD,
	PLAYREC,
	VOICE,
	MUTE,
	MOVE,
	PLAY,
	//SWITCH,
	UPLOAD,
	SAVE,
	ERASE,
	Delete,
	EXIT,			//Exit
	EMPTY,	//A click on empty place in the toolbar
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	///TODO: Add the other action types of the two modes
	colour,
	shape,
	shapecolour,
	draw,
	restart,
	stopplay,
	PLAYING_AREA,
	///TODO: Add the other action types of the two modes
};

struct Point	//To be used for figures points
{
	int x, y;
};

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr; 	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif