#include "SelectAction.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include "Figures/CFigure.h"

SelectAction::SelectAction(ApplicationManager* pApp) :Action(pApp)
{}

void SelectAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Get the point which select the figure
	pOut->PrintMessage("Select Icon:...Please select only one Figure");
	pIn->GetPointClicked(point.x, point.y);
	pOut->ClearStatusBar();
}

//Execute the action
void SelectAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();



	if (pManager->GetFigure(point)!=NULL) {        //Check if the point selected belongs to a figure or not
	///	if (pManager->CheckSelection(point))        // Check if the figure selcted before or not
		if (pManager->getSelectedFigure() == pManager->GetFigure(point) && pManager->getSelectedFigure() != NULL)  // Check if the figure selcted before or not
		{
			pManager->UnSelectFig();     // if selected before  ---> this will be Unselected			
		}
		else {                            // if Unselected before 
			pManager->UnSelectFig();  //the selected before it will unselected 

			pManager->SetSelectedFig(point);     // make the figure selected
			
		}
	
	}
		pManager->UpdateInterface();
	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void SelectAction::Execure_recording_actions()
{
	if (pManager->GetFigure(point) != NULL) {        //Check if the point selected belongs to a figure or not
		///	if (pManager->CheckSelection(point))        // Check if the figure selcted before or not
		if (pManager->getSelectedFigure() == pManager->GetFigure(point) && pManager->getSelectedFigure() != NULL)  // Check if the figure selcted before or not
		{
			pManager->UnSelectFig();     // if selected before  ---> this will be Unselected			
		}
		else {                            // if Unselected before 
			pManager->UnSelectFig();  //the selected before it will unselected 

			pManager->SetSelectedFig(point);     // make the figure selected

		}

	}
	pManager->UpdateInterface();

	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void SelectAction::undo()
{
}

void SelectAction::redo()
{
}
