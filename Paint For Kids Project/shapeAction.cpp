#include "ApplicationManager.h"
#include"shapeAction.h"
#include<cmath>//this for func sleep
shapeAction::shapeAction(ApplicationManager* p) :Action(p)
{
    CountF = 0;
    CountT = 0;
    counter = 0;
}

void shapeAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();
}

void shapeAction::Execute()
{
    pManager->SetAllUnhidden();
    pManager->UpdateInterface();
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    if (pManager->GetFigCount() == 0) {
        pOut->PrintMessage("THERE ARE NO SHAPES TO PICK");
    }
    else  if (pManager->GetFigCount() == 1)
    {
        pOut->PrintMessage("DRAW MORE SHAPES");
    }
    else
    {

        CFigure* target = pManager->GetRandomFigure(false); //the kid picks all figures of this type
        keyShape = target->keyshape();
        switch (keyShape)
        {
        case '!':
        { pOut->PrintMessage("PICK ALL CIRCLE SHAPES");

        break;
        }
        case '@':
        { pOut->PrintMessage("PICK ALL HEXAGONAL SHAPES");

        break;
        }

        case '#':
        { pOut->PrintMessage("PICK  ALL SQUARE SHAPES");

        break;
        }

        case '*':
        { pOut->PrintMessage("PICK ALL  TRIANGLE SHAPES");

        break;
        }
        case '$':
        { pOut->PrintMessage("PICK ALL RECTANGLE SHAPES");

        break;
        }

        }
        counter = (pManager->numgivenkeyshape(keyShape));
        while (true)
        {
            check = pIn->GetUserAction(p1); //one click: a figure in the playing area or a toolbar icon
            if (check == PLAYING_AREA)
            {
                CFigure* fig = pManager->GetFigure(p1); //hidden (already picked) figures are not returned
                if (fig == NULL)
                    continue;
                pOut->ClearDrawArea();
                fig->setishidden(1);
                pManager->UpdateInterface();
                if (fig->keyshape() == keyShape)
                {
                    pOut->PrintMessage(" GOOD JOB.....  ");
                    if (pManager->getcheckvoice())
                    {
                        PlaySound(TEXT("good jj.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    }
                    Sleep(500);
                    CountT++;
                    counter--;
                    if (counter == 0)
                    {
                        if (pManager->getcheckvoice())
                        {
                            PlaySound(TEXT("allah.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        }
                        pOut->PrintMessage("YOU ARE A CLEVER KID...YOU WIN");
                        Sleep(1000);
                        pOut->PrintMessage("NUMBER OF CORRECT PICKS IS " + to_string(CountT));
                        Sleep(1000);
                        pOut->PrintMessage("NUMBER OF WRONG PICKS IS " + to_string(CountF));
                        break;
                    }
                }
                else
                {
                    pOut->PrintMessage(" FOCUS AND TRY AGAIN .... ");
                    if (pManager->getcheckvoice())
                    {
                        PlaySound(TEXT("eh da.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    }
                    Sleep(500);
                    CountF++;
                }
            }
            else if (check == restart || check == shape)
            {
                pManager->SetAllUnhidden();
                pManager->UpdateInterface();
                pOut->ClearStatusBar();
                pManager->ExecuteAction(shape);
                break;
            }
            else if (check == colour || check == shapecolour || check == draw)
            {
                pOut->PrintMessage("NUMBER OF CORRECT PICKS IS " + to_string(CountT) + "");
                Sleep(1000);
                pOut->PrintMessage("NUMBER OF WRONG PICKS IS " + to_string(CountF) + "");
                Sleep(1000);
                pManager->SetAllUnhidden();
                pManager->UpdateInterface();
                pOut->ClearStatusBar();
                pManager->ExecuteAction(check);
                break;
            }
            else if (check == EXIT)
            {
                pManager->ExecuteAction(EXIT);
                break;
            }
        }
    }
     
}

void shapeAction::undo()
{
}

void shapeAction::redo()
{
}

void shapeAction::Execure_recording_actions()
{
}

  

   



