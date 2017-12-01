#include "EGraphics.h"
#include "EWindow.h"
#include "EMeshUtil.h"
#include "EUtil.h"
#include "EGame.h"
#include "res/resource.h"

using namespace E3D;

int WINAPI WinMain(
	HINSTANCE hInstance,		//当前实例的句柄
	HINSTANCE hPrevInstance,//当前实例的句柄
	LPSTR lpCmdLine,		//命令行
	int nCmdShow			//显示状态
)
{
	InitLog("E3D.Log");

	Log("Init Graphics...");
	EGraphics::initGraphics(hInstance);
	Log("Graphics Load Successed!");

	EGameWindow::GWindow = new EGameWindow("E3D[3DTankWar]", hInstance);
	EGameWindow::GWindow->showWindow(true);

	//设置游戏的小图标
	HWND hwnd = EGameWindow::GWindow->getHWnd();
	LONG iconID = (LONG)LoadIcon(::GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON_TANKWAR));
	::SetClassLong(hwnd, GCL_HICON, iconID);

	EGame* game = new EGame;
	EGameWindow::GWindow->setCanvasListener(game);
	EGameWindow::GWindow->addInputListener(game);
	EGameWindow::GWindow->startLoop();

	Log("Shutdown Graphics...");
	EGraphics::shutdownGraphics();

	CloseLog();

	return;
}
