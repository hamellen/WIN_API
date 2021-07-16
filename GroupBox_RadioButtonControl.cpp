// GroupBox_RadioButtonControl.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "GroupBox_RadioButtonControl.h"

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
    LoadStringW(hInstance, IDC_GROUPBOXRADIOBUTTONCONTROL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GROUPBOXRADIOBUTTONCONTROL));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GROUPBOXRADIOBUTTONCONTROL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GROUPBOXRADIOBUTTONCONTROL);
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
#define IDC_NULL_PEN 1001
#define IDC_BLACK_PEN 1002
#define IDC_RED_PEN 1003
#define IDC_BLUE_PEN 1004
enum{IDC_NULL_BRUSH=2001,IDC_WHITE_BRUSH,IDC_BLACK_BRUSH,IDC_BLUE_BRUSH};
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hR[8];
    static POINT pts[2] = { {20,250},{300,400} };
    static int penType = IDC_BLACK_PEN;
    static int brushType = IDC_BLACK_BRUSH;
    switch (message)
    {
    case WM_CREATE:
        CreateWindowW(TEXT("BUTTON"), TEXT("Pen Color"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 10, 10, 120, 200, hWnd, (HMENU)IDC_STATIC, hInst, nullptr);
        hR[0] = CreateWindowW(TEXT("BUTTON"), TEXT("NULL Pen"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 20, 40, 100, 40, hWnd, (HMENU)IDC_NULL_PEN, hInst, nullptr);
        hR[1] = CreateWindowW(TEXT("BUTTON"), TEXT("BLACK"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 80, 100, 40, hWnd, (HMENU)IDC_BLACK_PEN, hInst, nullptr);
        hR[2] = CreateWindowW(TEXT("BUTTON"), TEXT("RED"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 120, 100, 40, hWnd, (HMENU)IDC_RED_PEN, hInst, nullptr);
        hR[3] = CreateWindowW(TEXT("BUTTON"), TEXT("BLUE"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 160, 100, 40, hWnd, (HMENU)IDC_BLUE_PEN, hInst, nullptr);
        SendMessage(hR[1], BM_SETCHECK, BST_CHECKED, 0);
        CreateWindowW(TEXT("BUTTON"), TEXT("Brush Color"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 140, 10, 120, 200, hWnd, (HMENU)IDC_STATIC, hInst, nullptr);
        hR[4] = CreateWindowW(TEXT("BUTTON"), TEXT("NULL Brush"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 40, 100, 40, hWnd, (HMENU)IDC_NULL_BRUSH, hInst, nullptr);
        hR[5] = CreateWindowW(TEXT("BUTTON"), TEXT("WHITE"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON , 150, 80, 100, 40, hWnd, (HMENU)IDC_WHITE_BRUSH, hInst, nullptr);
        hR[6] = CreateWindowW(TEXT("BUTTON"), TEXT("BLACK"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 120, 100, 40, hWnd, (HMENU)IDC_BLACK_BRUSH, hInst, nullptr);
        hR[7] = CreateWindowW(TEXT("BUTTON"), TEXT("BLUE"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 160, 100, 40, hWnd, (HMENU)IDC_BLUE_BRUSH, hInst, nullptr);
        SendMessage(hR[5], BM_SETCHECK, BST_CHECKED, 0);
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDC_NULL_PEN:
                penType = IDC_NULL_PEN;
                break;
            case IDC_BLACK_PEN:
                penType = IDC_BLACK_PEN;
                break;
            case IDC_RED_PEN:
                penType = IDC_RED_PEN;
                break;
            case IDC_BLUE_PEN:
                penType = IDC_BLUE_PEN;
                break;
            case IDC_NULL_BRUSH:
                brushType = IDC_NULL_BRUSH;
                break;
            case IDC_WHITE_BRUSH:
                brushType = IDC_WHITE_BRUSH;
                break;
            case IDC_BLACK_BRUSH:
                brushType = IDC_BLACK_BRUSH;
                break;
            case IDC_BLUE_BRUSH:
                brushType = IDC_BLACK_BRUSH;
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            HPEN hPen;
            HBRUSH hBrush;
            switch (penType) 
            {
            case IDC_NULL_PEN:
                hPen = (HPEN)GetStockObject(NULL_PEN);
                break;
            case IDC_RED_PEN:
                hPen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
                break;
            case IDC_BLUE_PEN:
                hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
                break;
            default:
                hPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
                break;
            }
            switch(brushType) 
            {
            case IDC_NULL_BRUSH:
                hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
                break;
            case IDC_WHITE_BRUSH:
                hBrush = CreateSolidBrush(RGB(255, 255, 255));
                break;
            case IDC_BLUE_BRUSH:
                hBrush = CreateSolidBrush(RGB(0, 0, 225));
                break;
            default:
                hBrush = CreateSolidBrush(RGB(0, 0, 0));
                break;
            }

            HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

            Rectangle(hdc, pts[0].x, pts[0].y, pts[1].x, pts[1].y);

            SelectObject(hdc, oldPen);
            DeleteObject(hPen);
            SelectObject(hdc, oldBrush);
            DeleteObject(hBrush);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
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
