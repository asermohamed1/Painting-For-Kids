#include "ApplicationManager.h"
#include"shapeAction.h"
#include <random>//for generate random number
#include<cmath>//this for func sleep
shapeAction::shapeAction(ApplicationManager* p) :Action(p)
{
    CountF = 0;
    CountT = 0;
    random_number = 0;
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

        do
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distribution(0, (pManager->GetFigCount() - 1));
            random_number = distribution(gen);
        } while (pManager->Getshape(random_number) == 0);
        keyShape = pManager->Getshape(random_number)->keyshape();
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
        do
        {
            pIn->GetPointClicked(p1.x, p1.y);
            if (pManager->GetFigure(p1) != 0)
            {
                if ((pManager->GetFigure(p1))->keyshape() == keyShape)
                {
                    pick = (pManager->GetFigure(p1))->ishidden();
                    if (pick == 0)
                    {
                        pOut->ClearDrawArea();
                        (pManager->GetFigure(p1))->setishidden(1);
                        pManager->UpdateInterface();
                        pOut->PrintMessage(" GOOD JOB.....  ");
                        Sleep(500);
                        CountT++;
                        counter--;
                        if (pManager->getcheckvoice())
                        {
                            PlaySound(TEXT("good jj.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        }
                    }

                    if (counter == 0)
                    {
                        if (pManager->getcheckvoice())
                        {
                            PlaySound(TEXT("allah"), NULL, SND_FILENAME | SND_ASYNC);
                        }
                        pOut->PrintMessage("YOU ARE A CLEVER KID...YOU WIN");
                        Sleep(1000);
                        pOut->PrintMessage("NUMBER OF CORRECT PICKS IS " + to_string(CountT));
                        Sleep(1000);
                        pOut->PrintMessage("NUMBER OF WRONG PICKS IS " + to_string(CountF));
                        break;
                    }
                }
                else if ((pManager->GetFigure(p1))->keyshape() != keyShape && !(pManager->GetFigure(p1)->ishidden()))
                {
                    pOut->ClearDrawArea();
                    (pManager->GetFigure(p1))->setishidden(1);
                    pManager->UpdateInterface();
                    pOut->PrintMessage(" FOCUS AND TRY AGAIN .... ");
                    Sleep(500);
                    CountF++;
                    if (pManager->getcheckvoice() == 1)
                    {
                        PlaySound(TEXT("eh da.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    }
                }
                check = pManager->GetUserAction();
                if (check == restart)
                {
                    pManager->SetAllUnhidden();
                    pManager->UpdateInterface();
                    pOut->ClearStatusBar();
                    pManager->ExecuteAction(shape);
                    break;
                }
                else if (check == colour)
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
                else if (check == draw)
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

                else if (check == shapecolour)
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
            }
        } while (1);
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

  

   



