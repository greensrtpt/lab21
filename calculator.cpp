#include <windows.h>
#include <stdio.h>

/* This is where all the input to the window goes to */
#define ID_STATIC_TEXT 1001 
#define ID_EDIT1  1
#define ID_EDIT2  2
#define ID_BTN_ADD  3
#define ID_BTN_SUB  4
#define ID_BTN_MUL  5
#define ID_BTN_DIV  6


HWND hEdit1, hEdit2;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	char buffer1[10], buffer2[10], result[50];
    double num1, num2, res;
	
	switch(Message) {
		case WM_CREATE:
			CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD,
						20, 20, 210, 20, hwnd, (HMENU)ID_STATIC_TEXT, NULL, NULL);
			
			hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
							  	20, 50, 180, 20, hwnd, (HMENU)ID_EDIT1, NULL, NULL);
			hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
							  	20, 80, 180, 20, hwnd, (HMENU)ID_EDIT2, NULL, NULL);

			CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD,
					 	20, 120, 30, 25, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
			CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD,
					 	70, 120, 30, 25, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
			CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD,
					 	120, 120, 30, 25, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
			CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD,
					 	170, 120, 30, 25, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);

			
			break;

	case WM_COMMAND:
		if (LOWORD(wParam) >= ID_BTN_ADD && LOWORD(wParam) <= ID_BTN_DIV) {
			GetWindowText(hEdit1, buffer1, 10);
			GetWindowText(hEdit2, buffer2, 10);

			if (strlen(buffer1) == 0 || strlen(buffer2) == 0) {
				MessageBox(hwnd, "Pleas input two numbers", "Error", MB_OK | MB_ICONWARNING);
				break;
			}
			
			num1 = atof(buffer1);
			num2 = atof(buffer2);
			
			switch (LOWORD(wParam)) {
				case ID_BTN_ADD: res = num1 + num2; break;
				case ID_BTN_SUB: res = num1 - num2; break;
				case ID_BTN_MUL: res = num1 * num2; break;
				case ID_BTN_DIV: 
					if(num2 == 0){
						MessageBox(hwnd, "Cannot be divided by zero", "Error",MB_OK | MB_ICONERROR);
						return 0;
					}
					res =  num1 / num2; 
					break;
			}
			
			sprintf(result, "Result: %.2f", res);
			MessageBox(hwnd, result, "Result", MB_OK);
		}
		break;

		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hwnd;
	WNDCLASSEX wc = {0}; /* A properties struct of our window */
	
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "My Calculator";
    wc.hbrBackground = CreateSolidBrush(RGB(254,1, 154)); // สี
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */
	
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	} /* A 'HANDLE', hence the H, or a pointer to our window */
	
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"My Calculator","My calculator",WS_VISIBLE|WS_OVERLAPPED | WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(!hwnd) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}