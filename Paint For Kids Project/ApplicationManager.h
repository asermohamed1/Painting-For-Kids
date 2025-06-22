#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H
#include <fstream>
#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include <cmath>
#include"Actions/Action.h"
//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200,MaxActionCount=20, };	//Max no of figures

private:
	int checkvoice;//check if kid want an voice for some action or not 
	int FigCount;		//Actual number of figures
	int actioncount;    //Actual number of actions
	int number_undo ;
	
	int number_redo;
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure* ArryFig[MaxFigCount];
	CFigure* SelectedFig; //Pointer to the selected figure
	bool record;
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	Action* actions[MaxActionCount]; //List of all actions that recorded (Array of pointers)
	Action* redo_undo_arr[5];  
	Action* redo_arr[5];
public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure *GetFigure(Point p) const; //Search for a figure given a point inside the figure
	bool CheckSelection(Point p) const;     //Check the figure is selected or not
	void SetSelectedFig(Point p);     // set the figure to be selected
	void UnSelectFig();               // unselect figure
	void PrintSelectedInfo() const;         // print message of the  selected figure
	int GetFigCount();   //Get  FigCount to set ID of the Figures
	CFigure* Getshape(int);     // -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
	void deleteSelectedFig();   //delete the selected figure
	int GetNUMfig(Point);
	int numgivenkeyshape(char);
	int numsamecolour(string);
	int numsamecolourshape(char, string);
	void SetAllUnhidden();
	void Addaction(Action*);  //Add actions that have been recorded
	void clearall();              // clear all history and figures
	void displayAction();         // play last record
	bool ifselected() const;
	void ChngSelectedCLR(char);// Update the Fill & Drawing color of the selected figure
	bool isanyfill();
	void setcheckvoice(const int);
	int getcheckvoice();
	void setArryFig(int);
	CFigure* getSelectedFigure() const; // Get Pointer to the selected figure
	void MoveSelectedFig(Point P); //move the selected figure
	void setrecord(bool);   //set start or end record
	bool isrecorded();      //check record
	void add_action(Action*); //add action to undo array
	void decrease_undo_arr(); //display undo
	CFigure* get_figure_with_id(int); 
	CFigure* return_final_figure();
	void redo_display(); //redo display
	void decrease_undo_array(); //decrease array of undo to undo a figure
	void delete_fig(CFigure* fig); //delete figure
	bool check_valid_recording();
	void SaveAll(ofstream& Outputfile); // loop to save all figures
};

#endif