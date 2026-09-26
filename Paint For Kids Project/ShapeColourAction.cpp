#include "ShapeColourAction.h"
#include"ApplicationManager.h"
#include <random>
ShapeColourAction::ShapeColourAction(ApplicationManager* p) :Action(p)
{
    CountF = 0;
    CountT = 0;
    random_number = 0;
    counter = 0;
}

void ShapeColourAction::ReadActionParameters()
{
    //Get a Pointer to the Input / Output Interfaces
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();
}

void ShapeColourAction::Execute()
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
    else if (!(pManager->isanyfill()))
    {
        pOut->PrintMessage("NO FILL COLOUR SHAPES");
    }
    else
    {
        do
        {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distribution(0, (pManager->GetFigCount() - 1));
            random_number = distribution(gen);
        } while (pManager->Getshape(random_number) == 0 || (pManager->Getshape(random_number)->colourshape() == "WHITE"));
        keyShape = pManager->Getshape(random_number)->keyshape();
        Colour = (pManager->Getshape(random_number))->colourshape();
        switch (keyShape)
        {
        case '!':
        { pOut->PrintMessage("PICK ALL " + Colour + " CIRCLE SHAPES");
        break;
        }
        case '@':
        { pOut->PrintMessage("PICK ALL " + Colour + " HEXAGONAL SHAPES");
        break;
        }

        case '#':
        { pOut->PrintMessage("PICK ALL " + Colour + " SQUARE SHAPES");
        break;
        }

        case '*':
        { pOut->PrintMessage("PICK ALL " + Colour + " TRIANGLE SHAPES");
        break;
        }
        case '$':
        { pOut->PrintMessage("PICK ALL " + Colour + " RECTANGLE SHAPES");
        break;
        }
        }
        counter = pManager->numsamecolourshape(keyShape, Colour);
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
                if (fig->keyshape() == keyShape && fig->colourshape() == Colour)
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
            else if (check == restart || check == shapecolour)
            {
                pManager->SetAllUnhidden();
                pManager->UpdateInterface();
                pOut->ClearStatusBar();
                pManager->ExecuteAction(shapecolour);
                break;
            }
            else if (check == shape || check == colour || check == draw)
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



void ShapeColourAction::undo()
{
}

void ShapeColourAction::redo()
{
}

void ShapeColourAction::Execure_recording_actions()
{
}