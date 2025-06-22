#include "RecordingAction.h"
#include "AddCircleAction.h"
#include"AddHexaAction.h"
#include"AddTriangleAction.h"
#include"Actions/AddRectAction.h"
#include"AddSquareAction.h"
#include"eraseAction.h"
#include"SelectAction.h"
#include"FillColorAction.h"
#include"DrwColorAction.h"
#include"MoveAction.h"
#include"UndoAction.h"
#include"RedoAction.h"
RecordingAction::RecordingAction(ApplicationManager* pApp) :Action(pApp)
{
}

void RecordingAction::ReadActionParameters()
{
	Output* output = pManager->GetOutput();
	if (pManager->check_valid_recording())
	{
		pManager->setrecord(true);
		output->PrintMessage("you just statreted recording , Note that this action will not record the operations in play mode ");
		string s;   //to print message with integer numbers
		int performed = 0;  // counter for performed actions
		while (performed < 20)
		{
			Input* input = pManager->GetInput();
			ActionType a = input->GetUserAction();
			ActionType* p = new ActionType(a);
			Point point{};

			while (a == RECORD)      //i can't do a record to the record(special case)
			{
				output->PrintMessage("that is invalid point , click a valid one");
				a = input->GetUserAction();
			}
			if (a == EXIT)          //can't be recorded (special case)
			{
				output->PrintMessage("you will close the program");
				delete p;
				p = NULL;
				pManager->ExecuteAction(a);
				break;
			}
			if (a == PLAYREC)  //we must play record after the record finish
			{
				output->PrintMessage("in valid point , click a valid one");
			}
			else if (a == STOPRECORD)    //finish record  (special case)
			{
				pManager->setrecord(false);
				delete p;
				p = NULL;
				pManager->ExecuteAction(a);
				break;
			}
			////////// actions that i don't wnat to record it//////////////
			else if ((a == SAVE) || (a == UPLOAD) || (a == DRAWING_AREA) || (a == STATUS) || (a == PLAYING_AREA) )
			{
				output->PrintMessage("this action has not recorded ,and i can't do it while recording");
			}
			else if ((a == PLAY) || (a == draw))
			{
				if (a == PLAY)
				{
					output->PrintMessage("you will switch to play mode but actions inside it will not be recorded,click any point to complete this operation");
				}
				else
				{
					output->PrintMessage("you will switch to draw mode but actions inside it will  be recorded,click any point to complete this operation");
				}
				input->GetPointClicked(point.x, point.y);

				pManager->ExecuteAction(a);

			}
			else if ((a == shape) || (a == colour) || (a == shapecolour))
			{
				pManager->ExecuteAction(a);
			}
			else if (a == Delete)    ///// to delete all actions and figures that has been done and reset the record(special case)
			{
				output->PrintMessage("you can't do clear all action while recording");
				performed = 0;  //refresh the loop by  performed operations to zero
				pManager->ExecuteAction(a);
				output->PrintMessage("your Records have been Zero and we deleted all history in the App, click any action to start your new record");
			}
			else if ((a == rED) || (a == gREEN) || (a == oRANGEE) || (a == bLACK) || (a == yELLOW) || (a == BLUE))
			{

			}
			else
			{
				//Action* act = NULL;
				switch (a)
				{
				case Select:
					pManager->ExecuteAction(a);
					break;
				case DRAW_RECT:
					pManager->ExecuteAction(a);
					break;
				case SQUARE:
					pManager->ExecuteAction(a);
					break;
				case Triangle:
					pManager->ExecuteAction(a);
					break;
				case HEXA:
					pManager->ExecuteAction(a);
					break;
				case CIRCLE:
					pManager->ExecuteAction(a);
					break;
				case ERASE:
				{
					pManager->ExecuteAction(a);
					break;
				}
				case FILLCOLOUR:
					if (pManager->ifselected())
					{
						pManager->ExecuteAction(a);
						break;
					}
					else
					{
						output->PrintMessage("i didnt record this action ,please select the figure you want first");
						break;
					}
				case PENCIL:
					if (pManager->ifselected())
					{
						pManager->ExecuteAction(a);
						break;
					}
					else
					{
						output->PrintMessage("i didnt record this action ,please select the figure you want first");
						break;
					}
				case MOVE:
					{
						pManager->ExecuteAction(a);
						break;
					}
				case UNDO:
					{
						pManager->ExecuteAction(a);
						break;
					}
				case REDO:
					{
						pManager->ExecuteAction(a);
						break;
					}

				}
					performed++;
					output->PrintMessage("we have recorded " + to_string(performed) + " operations");
					pManager->UpdateInterface();
			}

		delete p;
		p = NULL;
		}
		pManager->setrecord(false);
		output->PrintMessage("The record has been finished and your number of operations are: " + to_string(performed));
	}
	else
	{
		output->PrintMessage(" ERROR: Record action only  can be used after clearall or in the start of program");
	}
}

void RecordingAction::Execute()
{
	ReadActionParameters();
}

void RecordingAction::Execure_recording_actions()
{
	//this will not do any thing because i dont record it
}

void RecordingAction::undo()
{
}

void RecordingAction::redo()
{
}
