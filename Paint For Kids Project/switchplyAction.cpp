#include"switchplyAction.h"
#include "ApplicationManager.h"
#include "GUI/Input.h"
#include "GUI/Output.h"
switchplyAction::switchplyAction(ApplicationManager* p):Action(p)
{

}

void switchplyAction::Execute()
{     
	ReadActionParameters();
	if (pManager->getcheckvoice() == 1)
		PlaySound(TEXT("lets play"), NULL, SND_FILENAME | SND_ASYNC);
}

 void switchplyAction::ReadActionParameters()
{
	 Output* pOut = pManager->GetOutput();
	 pOut->PrintMessage("switch to play mode");
	 pManager->setArryFig(pManager->GetFigCount());
	 pOut->Cleartoolbar();
	 pOut->CreatePlayToolBar();
}

 void switchplyAction::undo()
 {
 }

 void switchplyAction::redo()
 {
 }

 void switchplyAction::Execure_recording_actions()
 {
 }
