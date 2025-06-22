#include "SaveAction.h"
SaveAction::SaveAction(ApplicationManager* pApp) :Action(pApp)
{}
void SaveAction::ReadActionParameters()
{
	FileName = pManager->GetInput()->GetSrting(pManager->GetOutput());//get the name of file from user
}
void SaveAction::Execute()
{
	pManager->GetOutput()->PrintMessage("Enter the File Name : ");
	ReadActionParameters();
	Outputfile.open(FileName + ".txt");
	//read the current draw color and fill color
	Outputfile << pManager->GetOutput()->GetColor(pManager->GetOutput()->getCrntDrawColor()) << " " << pManager->GetOutput()->GetColor(pManager->GetOutput()->getCrntFillColor()) << endl;

	Outputfile << pManager->GetFigCount() << endl;//read number of figures
	pManager->SaveAll(Outputfile);
	pManager->GetOutput()->PrintMessage("File Named : (" + FileName + ") has been saved");
	Outputfile.close();
}

void SaveAction::undo()
{
}

void SaveAction::redo()
{
}

void SaveAction::Execure_recording_actions()
{
}