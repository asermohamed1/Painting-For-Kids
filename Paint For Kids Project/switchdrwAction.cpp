#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
#include"switchdrwAction.h"


switchdrwAction::switchdrwAction(ApplicationManager* p) :Action(p)
{

}

void switchdrwAction::Execute()
{
	pManager->SetAllUnhidden();
	pManager->UpdateInterface();
	if (pManager->getcheckvoice() == 1)
		PlaySound(TEXT("lets draw"), NULL, SND_FILENAME | SND_ASYNC);
	ReadActionParameters();
	Sleep(1000);

	pManager->PrintSelectedInfo(); //Print information about the selected figure
}

void switchdrwAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("switch to draw mode");
	pOut->Cleartoolbar();
	pOut->CreateDrawToolBar();
}

void switchdrwAction::undo()
{
}

void switchdrwAction::redo()
{
}

void switchdrwAction::Execure_recording_actions()
{
}
