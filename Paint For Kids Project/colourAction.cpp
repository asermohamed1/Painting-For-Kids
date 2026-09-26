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
        } while ((pManager->Getshape(random_number)) == 0 || (pManager->Getshape(random_number)->colourshape() == "WHITE"));
        Colour = (pManager->Getshape(random_number))->colourshape();
        pOut->PrintMessage("PICK ALL " + Colour + " SHAPES");
        counter = (pManager->numsamecolour(Colour));
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
                if (fig->colourshape() == Colour)
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
            else if (check == restart || check == colour)
            {
                pManager->SetAllUnhidden();
                pManager->UpdateInterface();
                pOut->ClearStatusBar();
                pManager->ExecuteAction(colour);
                break;
            }
            else if (check == shape || check == shapecolour || check == draw)
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

void colourAction::undo()
{
}

void colourAction::redo()
{
}

void colourAction::Execure_recording_actions()
{
}

