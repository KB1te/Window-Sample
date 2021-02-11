#include <Windows.h>
#include <CommCtrl.h>

LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
) {
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd) {

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"KB1te";
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);
	HWND hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, wc.lpszClassName, L"KB1te" ,WS_OVERLAPPED, 800, 600, 800, 600, NULL, NULL, hInstance, NULL);
	MSG Msg;
	HWND pgb = CreateWindow(PROGRESS_CLASS, L"", WS_VISIBLE | WS_OVERLAPPED | WS_CHILD, 100, 100, 515,50, hwnd, NULL, hInstance,NULL);
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);
	SendMessage(pgb, PBM_SETSTEP, 10, 0);
	while (SendMessage(pgb, PBM_GETPOS, 0, 0) != 100) {
		SendMessage(pgb, PBM_STEPIT, 0, 0);
		Sleep(10);
	}
	MessageBoxA(NULL, "Yea!", "test", MB_ICONINFORMATION);
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}
