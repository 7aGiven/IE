#include <exdisp.h>

#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "OleAut32.lib")

int WinMain(HINSTANCE a1, HINSTANCE a2, LPSTR lpCmdLine, int nShowCmd)
{
	IWebBrowser2* ie;
	VARIANT Flags;
	SHANDLE_PTR hWnd;
	BSTR bstr;
	if (*lpCmdLine != 0) {
		int wslen = MultiByteToWideChar(CP_ACP, 0, lpCmdLine, strlen(lpCmdLine), 0, 0);
		bstr = SysAllocStringLen(0, wslen);
		MultiByteToWideChar(CP_ACP, 0, lpCmdLine, strlen(lpCmdLine), bstr, wslen);
	}
	Flags.vt = VT_I2;
	Flags.iVal = navBrowserBar;

	CoInitialize(0);
	CoCreateInstance(CLSID_InternetExplorer, 0, CLSCTX_LOCAL_SERVER, IID_IWebBrowser2, (void**)&ie);
	if (*lpCmdLine != 0) {
		ie->put_ToolBar(false);
	}
	ie->get_HWND(&hWnd);
	ShowWindow((HWND)hWnd, nShowCmd);
	if (*lpCmdLine != 0) {
		ie->Navigate(bstr, &Flags, 0, 0, 0);
	}
	CoUninitialize();
	SysFreeString(bstr);
}
