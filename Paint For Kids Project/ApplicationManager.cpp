#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "AddSquareAction.h"
#include"AddTriangleAction.h"
#include"AddHexaAction.h"
#include"AddCircleAction.h"
#include "SelectAction.h"
#include"switchplyAction.h"
#include"switchdrwAction.h"
#include"shapeAction.h"
#include"eraseAction.h"
#include"RecordingAction.h"
#include"Clearall.h"
#include"PlayRecordingAction.h"
#include "FillColorAction.h"
#include "DrwColorAction.h"
#include"colourAction.h"
#include <cmath>
#include <random>
#include"VoiceAction.h"
#include"MuteAction.h"
#include "MoveAction.h"
#include"UndoAction.h"
#include"RedoAction.h"
#include"StopRecord.h"
#include"ShapeColourAction.h"
#include"ExitAction.h"
#include"SaveAction.h"
#include"LoadAction.h"
bool Action::fill = false;

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	checkvoice = 0;//default will not play any voice
	FigCount = 0;
	actioncount = 0;// intialize the numbers of actions that has been done
	number_undo = 0;
	
	number_redo = 0;
	record = false;
	exitRequested = false;
	SelectedFig = NULL;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
	{
		FigList[i] = NULL;
	}
	//Create an array of actiontype pointers and set them to NULL	
	for (int i = 0; i < MaxActionCount; i++)
	{
		actions[i] = NULL;
	}
	for (int i = 0; i < 5; i++)
	{
		redo_undo_arr[i] = NULL;
	}
	for (int i = 0; i < 5; i++)
	{
		redo_arr[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	    case Select:
		    pAct = new SelectAction(this);
		    break;
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;
		case SQUARE:
			pAct = new AddSquareAction(this);
			break;
		case Triangle:
			pAct = new AddTriangleAction(this);
			break;
		case HEXA:
			pAct = new AddHexaAction(this);
			break;
		case CIRCLE:
			pAct = new AddCircleAction(this);
			break;
		case PLAY:
			{
			pAct = new switchplyAction(this);
			break;
			}
		case SAVE:
			pAct = new SaveAction(this);
			break;
		case UPLOAD:
			pAct = new loadaction(this);
			break;
		case shape:
		{ pAct = new shapeAction(this);
		      break;
		}
		case colour:
		{
			pAct = new colourAction(this);
			break;
		}
		case shapecolour:
		{
			pAct = new ShapeColourAction(this);
			break;
		}
		case draw:
		{
			pAct = new switchdrwAction(this);
			break;
		}
		case ERASE:
		{
			pAct = new eraseAction(this);
			break;
		}
		case RECORD:
		{
			pAct = new RecordingAction(this);
			break;
		}
		case STOPRECORD:
		{
			pAct = new StopRecordAction(this);
			break;
		}
		case Delete:
		{
			pAct = new Clearall(this);
			break;
		}
		case PLAYREC:
		{
			pAct = new PlayRecordingAction(this);
			break;
		}
		case FILLCOLOUR:
		{
			pAct = new FillColorAction(this);
			break;
		}	
		case PENCIL:
		{
			pAct = new DrwColorAction(this);
			break;
		}
		case VOICE:
		{
			pAct = new VoiceAction(this);
			break;
		}
		case MUTE:
		{ pAct = new MuteAction(this);
			break;
		}
		case MOVE:
		{
			pAct = new MoveAction(this);
			break;
		}
		case UNDO:
		{
			pAct = new UndoAction(this);
			break;
		}
		case REDO:
		{
			pAct = new RedoAction(this);
			break;
		}
		case EXIT:
		{
			pAct = new ExitAction(this);
			break;
		}
			
		case DRAWING_AREA:
			return;
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		//Actions that change figures go to the undo list
		//(actions on the selected figure only when there is a selected figure)
		bool undoable = ActType == DRAW_RECT || ActType == CIRCLE || ActType == SQUARE || ActType == HEXA || ActType == Triangle
			|| ((ActType == ERASE || ActType == FILLCOLOUR || ActType == PENCIL || ActType == MOVE) && ifselected());
		if (undoable)
		{
			add_action(pAct);
			ClearRedo();
		}
		pAct->Execute();//Execute
		bool recorded = false;
		if (isrecorded()&&((ActType == DRAW_RECT || ActType == CIRCLE || ActType == SQUARE || ActType == HEXA || ActType == Triangle || ActType == ERASE || ActType == FILLCOLOUR || ActType == PENCIL || ActType == MOVE||ActType==Select||ActType==UNDO||ActType==REDO)))
		{
			recorded = Addaction(pAct);
		}
		//the action is not kept in any list so it is not needed anymore
		if (!undoable && !recorded)
		{
			delete  pAct;
			pAct = NULL;
		}
	}
	
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(Point p) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	for (int i = FigCount-1; i >=0; i--)
	{
		if (FigList[i] != NULL && !FigList[i]->ishidden() && FigList[i]->isThisFigure(p)) return FigList[i];
	}

	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	return NULL;
}

void ApplicationManager::SetSelectedFig(Point p)
{
	SelectedFig = GetFigure(p);
	if (SelectedFig != NULL)
		SelectedFig->SetSelected(true);
}
void ApplicationManager::UnSelectFig()
{
	if (SelectedFig != NULL) 
	{
		SelectedFig->SetSelected(false);
		SelectedFig = NULL;
	}
}
void ApplicationManager::PrintSelectedInfo() const
{
	if (SelectedFig!=NULL)
		SelectedFig->PrintInfo(pOut);
}
int ApplicationManager::GetFigCount()
{
	return FigCount;
}

CFigure* ApplicationManager::GetRandomFigure(bool filledOnly)
{
	//one generator for the whole program (creating a random_device every time is slow)
	static mt19937 gen(random_device{}());
	int count = 0;
	for (int i = 0; i < FigCount; i++)
		if (FigList[i] != NULL && (!filledOnly || FigList[i]->colourshape() != "WHITE"))
			count++;
	if (count == 0)
		return NULL;
	//pick one of the matching figures directly (no retrying)
	int k = uniform_int_distribution<>(0, count - 1)(gen);
	for (int i = 0; i < FigCount; i++)
		if (FigList[i] != NULL && (!filledOnly || FigList[i]->colourshape() != "WHITE"))
			if (k-- == 0)
				return FigList[i];
	return NULL;
}




int ApplicationManager::numgivenkeyshape(char c)
{
	int count = 0;       // in this loop i want to know number of shapes in figlist that choosen random from play mode have same type
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] != NULL)
			if (FigList[i]->keyshape() == c)
				count++;
	}
	return count;

}

int ApplicationManager::numsamecolour(string colour)
{
	int c = 0;       // in this loop i want to know number of shapes in figlist that choosen random from play mode have same colour
	for (int i = 0; i < FigCount; i++)
		if (FigList[i] != NULL)//check to handle error
			if (FigList[i]->colourshape() == colour)
				c++;
	return c;
}

int ApplicationManager::numsamecolourshape(char s, string cl)//this return number of same type and colour shape of random shape that generate in pick by shape and colour by take colour and type of random shape
{
	int c = 0;//counter
	for (int i = 0; i < FigCount; i++)
		if (FigList[i] != NULL)//check to handle error
			if (FigList[i]->keyshape() == s && FigList[i]->colourshape() == cl)
				c++;
	return c;
}

void ApplicationManager::SetAllUnhidden()//set all shapes unhidden to draw it again
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] != 0)
			FigList[i]->setishidden(0);
	}
}

bool ApplicationManager::Addaction(Action* action)
{
	if (actioncount < MaxActionCount)
	{
		actions[actioncount++] = action;  //increasing number of actions in array
		return true;
	}
	return false;
}

void ApplicationManager::clearall()
{
	for (int i = 0; i < FigCount; i++) //delete all figures and set them to NULL
	{
		if (FigList[i]!=NULL)
		{
			delete FigList[i];
			FigList[i] = NULL;
		}
	}
	ClearUndoRedo(); //must be done before the recorded actions are deleted
	for (int i = 0; i < actioncount; i++) //delete all actions and set them to NULL
	{
		if (actions[i] != NULL)
		{
			delete actions[i];
			actions[i] = NULL;
		}
	}
	UnSelectFig();  // to delete selection for any figure 
	actioncount = 0;                    //the actions beame zero
    FigCount=0;                         //the figures beame zero
	pOut->ClearDrawArea();
	pOut->PrintMessage("The clear all has been done");
}

void ApplicationManager::displayAction()
{
	if (actioncount == 0)//if i didnt record any action
	{
		pOut->PrintMessage("You didnt record any thing to play it");
	}
	else
	{
		ClearUndoRedo();
		for (int i = 0; i < FigCount; i++) //delete all figures and set them to NULL
		{
			if (FigList[i] != NULL)
			{
				delete FigList[i];
				FigList[i] = NULL;
			}
		}
		UnSelectFig();  // to delete selection for any figure 
		FigCount = 0;                         //the figures beame zero
		pOut->ClearDrawArea();
		Sleep(1000);
		for (int i = 0; i < actioncount; i++)    // display the actions recorded
		{
			if (actions[i] != NULL)
			{
				actions[i]->Execure_recording_actions(); //execute the recording action without reading paramters
				if (SelectAction* select = dynamic_cast<SelectAction*>(actions[i]))
				{
				}
				else if (UndoAction* undo = dynamic_cast<UndoAction*>(actions[i]))
				{
				}
				else if (RedoAction* redo = dynamic_cast<RedoAction*>(actions[i]))
				{}
				else
				{
					add_action(actions[i]);
				}

				UpdateInterface();
			}
			Sleep(1000);           //make a one second sleep between every two operations
		}
		pOut->PrintMessage("The play had been finished and we make " + to_string(actioncount) + " Opeartions");
	}
}

bool ApplicationManager::ifselected() const
{
	if (SelectedFig != NULL) return true;
	return false;
}



bool ApplicationManager::isanyfill()
{
	for (int i = 0; i < FigCount; i++)
		if (FigList[i] != NULL && FigList[i]->colourshape() != "WHITE")
			return true;
	return false;
}

void ApplicationManager::setcheckvoice(const int x)
{
	if (x == 0)
	{
		checkvoice = 0;
		pOut->PrintMessage("this will make voice mute");
	}
	else
	{
		checkvoice = 1;
		pOut->PrintMessage("this will make voice enable");
	}
}

int ApplicationManager::getcheckvoice()
{
	return checkvoice;
}



 CFigure* ApplicationManager::getSelectedFigure() const
{
	return   SelectedFig;
}


 void ApplicationManager::setrecord(bool b)
 {
	 record = b;
 }

 bool ApplicationManager::isrecorded()
 {
	 return record;
 }

 void ApplicationManager::add_action(Action* act)
 {
	 if (number_undo >= 5)
	 {
		 //the oldest action leaves the undo list, free it unless it is still kept in the recorded actions
		 if (!is_recorded_action(redo_undo_arr[0]))
		 {
			 delete redo_undo_arr[0];
		 }
		 redo_undo_arr[0] = NULL;
		 for (int i = 0; i < 4; i++)
		 {
			 redo_undo_arr[i] = redo_undo_arr[i + 1];
		 }
		 redo_undo_arr[4] = act;
	 }
	 else
	 {
		 redo_undo_arr[number_undo] = act;
		 number_undo++;
	 }

 }

 

 bool ApplicationManager::is_recorded_action(Action* act) const
 {
	 for (int i = 0; i < actioncount; i++)
	 {
		 if (actions[i] == act)
			 return true;
	 }
	 return false;
 }

 void ApplicationManager::ClearRedo()
 {
	 for (int i = 0; i < number_redo; i++)
	 {
		 if (redo_arr[i] != NULL && !is_recorded_action(redo_arr[i]))
			 delete redo_arr[i];
		 redo_arr[i] = NULL;
	 }
	 number_redo = 0;
 }

 void ApplicationManager::ClearUndoRedo()
 {
	 for (int i = 0; i < number_undo; i++)
	 {
		 if (redo_undo_arr[i] != NULL && !is_recorded_action(redo_undo_arr[i]))
			 delete redo_undo_arr[i];
		 redo_undo_arr[i] = NULL;
	 }
	 number_undo = 0;
	 ClearRedo();
 }

 void ApplicationManager::decrease_undo_arr()
 {
	 if (number_undo != 0)
	 {
		 redo_arr[number_redo++] = redo_undo_arr[number_undo  - 1];
		 (redo_undo_arr[number_undo  - 1])->undo();
		 redo_undo_arr[number_undo - 1] = NULL;
		 number_undo--;
	 }
	 else
	 {
		 pOut->PrintMessage("you cant do undo action ");
	 }
	 UpdateInterface();
 }

 

void ApplicationManager::deleteSelectedFig()
{
	if (SelectedFig == NULL)
		return;
	//the figure is not freed because the erase action keeps it for undo
	delete_fig(SelectedFig);
	pOut->ClearDrawArea();
}


void ApplicationManager::redo_display()
{
	if (number_redo != 0)
	{
		if (number_redo <= 5)
		{
			redo_arr[number_redo - 1]->redo();
			redo_undo_arr[number_undo] = redo_arr[number_redo - 1];
			number_undo++;
			redo_arr[number_redo - 1]=NULL;
			number_redo--;
			UpdateInterface();
		}
		else
		{
			pOut->PrintMessage("the redo actions have been finished");
		}
	}
	else
	{
		pOut->PrintMessage("you didnt do any undo action");
	}
}




bool ApplicationManager::check_valid_recording()
{
	int count_action = 0;         //for checking if all actions are null like we start our program or after clear all function
	int count_figure = 0;       //for checking if all figures are null like we start our program or after clear all function
	for (int i = 0; i < MaxActionCount; i++)
	{
		if (actions[i] == NULL)
			count_action++;// increasing numbers of actions of NULL
	}
	for (int i = 0; i < MaxFigCount; i++)
	{
		if (FigList[i] == NULL)
			count_figure++; // increasing number of fig_list of NULL
	}
	if (count_figure == MaxFigCount && count_action == MaxActionCount)       //if all are NULL we will do the record
	{
		return true;
	}
	else { return false; }
}

void ApplicationManager::SaveAll(ofstream& Outputfile)
{
	for (int i = 0; i < FigCount; i++)
		if (FigList[i] != NULL)
			FigList[i]->save(Outputfile);
}

void ApplicationManager::RequestExit()
{
	exitRequested = true;
}

bool ApplicationManager::IsExitRequested() const
{
	return exitRequested;
}

void ApplicationManager::delete_fig(CFigure* fig)
{
	if (fig == NULL)
		return;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] == fig)
		{
			fig->SetSelected(false);
			if (SelectedFig == fig)
				SelectedFig = NULL;
			// Shift elements in the array to close the gap after deletion
			for (int j = i; j < FigCount - 1; j++)
			{
				FigList[j] = FigList[j + 1];
			}
			FigList[FigCount - 1] = NULL;
			FigCount--;
			break;
		}
	}
}




//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] != NULL)
			if (!(FigList[i]->ishidden()))
				FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
			else
				continue;
	}
}



////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	clearall();
	if(pIn!=NULL)delete pIn; //only for error handling
	if(pOut!=NULL)delete pOut; // only for error handling
	
}
