// double_buffering_2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "double_buffering_2.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DOUBLEBUFFERING2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DOUBLEBUFFERING2));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DOUBLEBUFFERING2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DOUBLEBUFFERING2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
#define step 10
#define r 50
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC memDC;
    static HBITMAP hBit;

    static POINT ptCircle;
    static RECT rtClient;
    static int direction = VK_RIGHT;
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 50, NULL);
        break;
    case WM_SIZE: 
    {
        GetClientRect(hWnd, &rtClient);
        ptCircle.x = rtClient.right / 2;
        ptCircle.y = rtClient.bottom / 2;
        HDC hdc = GetDC(hWnd);
        if (hBit)
            DeleteObject(hBit);
        hBit = CreateCompatibleBitmap(hdc, rtClient.right, rtClient.bottom);
        if (memDC)
            DeleteDC(memDC);
        memDC = CreateCompatibleDC(hdc);
        ReleaseDC(hWnd, hdc);
        SelectObject(memDC, hBit);
    }
    break;
    case WM_KEYDOWN:
        switch (wParam) 
        {
        case VK_LEFT:
            direction = VK_LEFT;
            break;
        case VK_RIGHT:
            direction = VK_RIGHT;
            break;
        case VK_UP:
            direction = VK_UP;
            break;
        case VK_DOWN:
            direction = VK_DOWN;
            break;
        }
        break;
    case WM_TIMER:
        switch (direction) 
        {
        case VK_LEFT:
            ptCircle.x -= step;
            break;
        case VK_RIGHT:
            ptCircle.x += step;
            break;
        case VK_UP:
            ptCircle.y -= step;
            break;
        case VK_DOWN:
            ptCircle.y += step;
            break;
        }
        if (ptCircle.x - r <= 0) {
            ptCircle.x = r;
            direction = VK_RIGHT;
        }
        if (ptCircle.x + r >= rtClient.right) {
            ptCircle.x = rtClient.right - r;
            direction = VK_LEFT;
        }
        if (ptCircle.y - r <= 0) {
            ptCircle.y = r;
            direction = VK_DOWN;
        }
        if (ptCircle.y + r >= rtClient.bottom) {
            ptCircle.y = rtClient.bottom - r;
            direction = VK_UP;
        }
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_ERASEBKGND:
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            FillRect(memDC, &rtClient, (HBRUSH)(COLOR_WINDOW + 2));
            HPEN hPen, hOldPen;
            HBRUSH hBrush, hOldBrush;

            hPen = CreatePen(PS_INSIDEFRAME, 10, RGB(255, 0, 0));
            hBrush = CreateSolidBrush(RGB(0, 0, 255));
            hOldPen = (HPEN)SelectObject(memDC, hPen);
            hOldBrush = (HBRUSH)SelectObject(memDC, hBrush);

            Ellipse(memDC, ptCircle.x - r, ptCircle.y - r, ptCircle.x + r, ptCircle.y + r);
            SelectObject(memDC, hOldPen);
            SelectObject(memDC, hOldBrush);
            DeleteObject(hPen);
            DeleteObject(hBrush);

            BitBlt(hdc, 0, 0, rtClient.right, rtClient.bottom, memDC, 0, 0, SRCCOPY);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
