#include <windows.h>
#include <stdio.h>

const char g_szClassName[] = "myCalculator";
HWND hEdit1, hEdit2, hButtonAdd, hButtonSub, hButtonMul, hButtonDiv;

void Calculate(char op) {
    char buffer1[100], buffer2[100];
    GetWindowText(hEdit1, buffer1, 100);
    GetWindowText(hEdit2, buffer2, 100);
    
    double num1 = atof(buffer1);
    double num2 = atof(buffer2);
    double result;
    
    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = (num2 != 0) ? num1 / num2 : 0; break;
    }
    
    char resultStr[100];
    sprintf(resultStr, "%.2f", result);
    MessageBox(NULL, resultStr, "Result", MB_OK | MB_ICONINFORMATION);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            CreateWindow("STATIC", "Enter Number 1:", WS_CHILD | WS_VISIBLE,
                         20, 20, 200, 20, hwnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  20, 40, 200, 25, hwnd, NULL, NULL, NULL);
            CreateWindow("STATIC", "Enter Number 2:", WS_CHILD | WS_VISIBLE,
                         20, 70, 200, 20, hwnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  20, 90, 200, 25, hwnd, NULL, NULL, NULL);
            
            hButtonAdd = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                      20, 130, 45, 30, hwnd, (HMENU)1, NULL, NULL);
            hButtonSub = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                      75, 130, 45, 30, hwnd, (HMENU)2, NULL, NULL);
            hButtonMul = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                      130, 130, 45, 30, hwnd, (HMENU)3, NULL, NULL);
            hButtonDiv = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                      185, 130, 45, 30, hwnd, (HMENU)4, NULL, NULL);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1: Calculate('+'); break;
                case 2: Calculate('-'); break;
                case 3: Calculate('*'); break;
                case 4: Calculate('/'); break;
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW), CreateSolidBrush(RGB(0, 0, 255)), NULL, g_szClassName, LoadIcon(NULL, IDI_APPLICATION) };
    RegisterClassEx(&wc);
    
    HWND hwnd = CreateWindowEx(0, g_szClassName, "My Calculator", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                               CW_USEDEFAULT, CW_USEDEFAULT, 250, 220, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}