// message and window function.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "message and window function.h"

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
    LoadStringW(hInstance, IDC_MESSAGEANDWINDOWFUNCTION, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MESSAGEANDWINDOWFUNCTION));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MESSAGEANDWINDOWFUNCTION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MESSAGEANDWINDOWFUNCTION);
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
      CW_USEDEFAULT,0,400,400, nullptr, nullptr, hInstance, nullptr);

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
#define _USE_MATH_DEFINES
#include <math.h>
#define r 100
#define RADIAN(X) ((X)*M_PI/180) 
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    SYSTEMTIME st;//시스템 시간 선언
    POINT pt;
    double theta;

    static RECT rtClient;//영역 변수 선언
    static WCHAR szTime[128];//문자열 선언
    static POINT Circlept;
    static double sec, minute, hour;
    static HPEN hPen[3];
    switch (message)
    {

    case WM_CREATE:
        hPen[0] = CreatePen(PS_SOLID, 8, RGB(0, 0, 255));
        hPen[1] = CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
        hPen[2] = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        SetTimer(hWnd, 1, 1000, NULL);//타이머 설정
        SendMessage(hWnd, WM_TIMER, 1, 0);
        break;
    case WM_SIZE:
        GetClientRect(hWnd, &rtClient);//영역 로딩
        Circlept.x = rtClient.right / 2;
        Circlept.y = rtClient.bottom / 2;
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
    case WM_TIMER:
        GetLocalTime(&st);//시간 설정
        wsprintf(szTime, TEXT("%d-%d-%d : %d:%d:%d"),st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);//시간 출력 문자열
        sec = st.wSecond;
        minute = st.wMinute + st.wSecond / 60.0;
        hour = st.wHour + minute / 60.0;
        InvalidateRect(hWnd, NULL, TRUE);//영역 무력화 
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            DrawText(hdc, szTime, -1, &rtClient, DT_CENTER);//시간출력
            Ellipse(hdc, Circlept.x - r, Circlept.y - r, Circlept.x + r, Circlept.y + r);//왼쪽,위,오른쪽,아래

            for (int i = 1; i <= 12; i++) {
                theta = (i - 3) * 30;
                pt.x = (int)(r * cos(RADIAN(theta)) + Circlept.x + 0.5);
                pt.y = (int)(r * sin(RADIAN(theta)) + Circlept.y + 0.5);

                WCHAR str[10];
                wsprintf(str, TEXT("%d"),i);
                RECT rt;
                SetRect(&rt, pt.x - 10, pt.y - 10, pt.x + 10, pt.y + 10);
                DrawText(hdc, str, -1, &rt, DT_CENTER);
            }
            //2시침
            theta = (hour * 30 - 90);
            pt.x = (int)((r - 20) * cos(RADIAN(theta)) + Circlept.x + 0.5);
            pt.y = (int)((r - 20) * sin(RADIAN(theta)) + Circlept.y + 0.5);
            HPEN hOldPen = (HPEN)SelectObject(hdc, hPen[0]);
            MoveToEx(hdc, Circlept.x, Circlept.y, NULL);
            LineTo(hdc, pt.x, pt.y);
            //3분침
            theta = (minute * 6 - 90);
            pt.x = (int)((r - 10) * cos(RADIAN(theta)) + Circlept.x + 0.5);
            pt.y = (int)((r - 10) * sin(RADIAN(theta)) + Circlept.y + 0.5);
            SelectObject(hdc, hPen[1]);
            MoveToEx(hdc, Circlept.x, Circlept.y, NULL);
            LineTo(hdc, pt.x, pt.y);
            //4초침
            theta = (sec * 6 - 90);
            pt.x = (int)((r - 5) * cos(RADIAN(theta)) + Circlept.x + 0.5);
            pt.y = (int)((r - 5) * sin(RADIAN(theta)) + Circlept.y + 0.5);
            SelectObject(hdc, hPen[2]);
            MoveToEx(hdc, Circlept.x, Circlept.y, NULL);
            LineTo(hdc, pt.x, pt.y);
            SelectObject(hdc, hOldPen);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        for (int i = 0; i < 3; i++)
            DeleteObject(hPen[i]);
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
