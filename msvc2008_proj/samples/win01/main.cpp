#include "win/Framewindow.h"
#include "lang/String.h"

class MyWindow : public win::FrameWindow
{
public:
	void handleKeyDown(int key) 
	{
		lang::String msg;
		msg = "You pressed " + lang::String::valueOf(key) + "key";
		char buf[128];
		msg.getBytes(&buf[0], 128, "ASCII-7");
		MessageBox(0, buf, "info", MB_OK | MB_TOPMOST);
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR lpCmdLine, int nShowCmd)
{
	MyWindow myWindow;
	myWindow.create("mywindow", "catmother win sample", 640, 480, false, hInstance);
	while(true)
	{
		if (!myWindow.flushWindowMessages())
			break;
	}
	myWindow.destroy();
}