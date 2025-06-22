#include "ApplicationManager.h"
#include <fstream>
#include "CCircle.h"
#include "CHexa.h"
#include "Figures/CRectangle.h"
#include "CSquare.h"
#include "CTriangle.h"
using namespace std;
class loadaction :public Action
{
private:
	string filename;
	string drawclr;
	string figname;
	string fillclr;
	int num;
	ifstream InputFile;
	GfxInfo gfxinfo;
public:

	loadaction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void undo();
	virtual void redo();
	virtual void Execure_recording_actions();
};
