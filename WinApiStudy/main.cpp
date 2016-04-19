//main.cpp
/************************************************************************/
/*                       
	Created time: 2016/4/19
	Created author: llc
	Function: Windows api study
*/
/************************************************************************/

#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	MessageBox(NULL, TEXT("Hello, windows api!"), TEXT("HelloMsg"), 0);
	return 0;
}