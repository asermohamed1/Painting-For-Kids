#include "colourAction.h"
#include "ApplicationManager.h"
#include <random>
#include<cmath>
#include<cstring>
colourAction::colourAction(ApplicationManager* p) :Action(p)
{
    CountF = 0;
    CountT = 0;
    counter = 0;
    random_number = 0;

}

void colourAction::ReadActionParameters()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();

}

void colourAction::Execute()
{
    pManager->SetAllUnhidden();
    pManager->UpdateInterface();
    Input* pIn = pManager->GetInput();
    Output* pOut = pManager->GetOutput();

    if (pManager->GetFigCount() == 0)
    {
        pOut->PrintMessage("THERE ARE NO SHAPES TO PICK");
    }
    else  if (pManager->GetFigCount() == 1)
    {
        pOut->PrintMessage("DRAW MORE SHAPES");
    }
    else if (!(pManager->isanyfill()))
    {
        pOut->PrintMessage("NO FILL COLOUR SHAPES");
    }

    else
    {
        random_number = 0;
        do
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distribution(0, (pManager->GetFigCount() - 1));
            random_number = distribution(gen);
        } while ((pManager->Getshape(random_number)->colourshape() == "WHITE") || (pManager->Getshape(random_number)) == 0);
        Colour = (pManager->Getshape(random_number))->colourshape();
        pOut->PrintMessage("PICK ALL " + Colour + " SHAPES");
        counter = (pManager->numsamecolour(Colour));
        do
        {
            pIn->GetPointClicked(p1.x, p1.y);
            if (pManager->GetFigure(p1) != 0)
            {
                if ((pManager->GetFigure(p1))->colourshape() == Colour)
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
                        (pManager->GetFigure(p1))->setishidden(1);
                        if (pManager->getcheckvoice())
                        {
                            PlaySound(TEXT("good jj.wav"), NULL, SND_FILENAME | SND_ASYNC);
                        }
                    }
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
                else if (((pManager->GetFigure(p1))->colourshape() != Colour && !(pManager->GetFigure(p1)->ishidden())))
                {
                    pOut->ClearDrawArea();
                    (pManager->GetFigure(p1))->setishidden(1);
                    pManager->UpdateInterface();
                    pOut->PrintMessage(" FOCUS AND TRY AGAIN .... ");
                    Sleep(500);
                    if (pManager->getcheckvoice())
                    {
                        PlaySound(TEXT("eh da.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    }
                    CountF++;
                }
                check = pManager->GetUserAction();
                if (check == restart)
                {
                    pManager->SetAllUnhidden();
                    pManager->UpdateInterface();
                    pOut->ClearStatusBar();
                    pManager->ExecuteAction(colour);
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
                else if (check == shape)
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

void colourAction::undo()
{
}

void colourAction::redo()
{
}

void colourAction::Execure_recording_actions()
{
}

