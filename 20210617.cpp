// 20210617.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "20210617.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];              // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];           // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);//명령 처리 함수
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,//메인함수
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY20210617, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY20210617));

    MSG msg;

    // 기본 메시지 루프입니다:,메세지 처리
    while (GetMessage(&msg, nullptr, 0, 0))//메세지 가져오기
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);//메세지 번역
            DispatchMessage(&msg);//메세지를 원도우 프로시저로 보내기
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)//윈도우 클래스 등록
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//가로세로 길이 변경,마우스 더블클릭 여부
    wcex.lpfnWndProc    = WndProc;//메세지 처리할 프로시저 이름 설정
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, IDI_APPLICATION);//원도우 아이콘 설정
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);//커서 설정
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MY20210617);//메뉴 설정
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);//원도우 아이콘 설정

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,//윈도우 생성
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);//원도우 화면에 출력
   UpdateWindow(hWnd);//클라이언트 영역 갱신

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
#define maxstring 128
#define r 50
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)//메세지를 처리하는 핵심 함수
{
    static HPEN hBluePen;//펜 생성
    static POINT ptStart, ptEnd;//직선 시작지점,끝나는 지점 좌표
    static POINT ptMouse;//마우스 위지정보
    static  BOOL bDraw = FALSE;//마우스 누름정보 
    static WCHAR str[maxstring + 1];
    static WCHAR str2[maxstring + 1];
    int n;
    switch (message)
    {
    case WM_CREATE:
        hBluePen = CreatePen(PS_DASH, 1, RGB(0, 0, 255));//펜생성
        break;
    case WM_LBUTTONDOWN:
        ptStart.x = LOWORD(lParam);//마우스  x 위치
        ptStart.y = HIWORD(lParam);//마우스 y 위치
        ptEnd = ptStart;
        break;
    case WM_LBUTTONUP://마우스왼쪽의 누름이 사라지는 순간 출력설정
        bDraw = TRUE;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_MOUSEMOVE:
        if (wParam && MK_LBUTTON)//마우스 왼쪽 관련 
        {
            HDC hdc = GetDC(hWnd);
            int OldMode = SetROP2(hdc, R2_NOTXORPEN);//레스터연산모드

            HPEN hOldPen = (HPEN)SelectObject(hdc, hBluePen);
            MoveToEx(hdc, ptStart.x, ptStart.y, NULL);//(0,0)에서 직선시작지점으로 좌표이동
            LineTo(hdc, ptEnd.x, ptEnd.y);//처음좌표에서 마지막좌표까지의 직선출력

            ptEnd.x = LOWORD(lParam);//마지막 x좌표
            ptEnd.y = HIWORD(lParam);//마지막 y좌표
            MoveToEx(hdc, ptStart.x, ptStart.y, NULL);//(0,0)에서 직선시작지점으로 좌표이동
            LineTo(hdc, ptEnd.x, ptEnd.y);//처음좌표에서 마지막좌표까지의 직선출력

            SelectObject(hdc, hOldPen);
            SetROP2(hdc, OldMode);
            ReleaseDC(hWnd, hdc);
        }
        break;
    case WM_KEYDOWN://키다운 호출
        n = lstrlen(str);
        if (n < maxstring&&IsCharAlphaNumeric(wParam))
            str[n] = (WCHAR)wParam;
        if (n > 0 && wParam == 8)
            str[n - 1] = 0;

        //InvalidateRect(hWnd, NULL, TRUE);//타원 이동흔적 제거.FALSE면 타원의 이동흔적이 남는다. 
        break;
    case WM_CHAR://문자 호출
        n = lstrlen(str2);
        if (wParam == 8 && n > 0)
            str2[n - 1] = 0;
        else
            str2[n] = (WCHAR)wParam;
        
        InvalidateRect(hWnd, NULL, TRUE);
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
    case WM_PAINT://윈도우 클라이언트 영역에서 일어나는 모든일 총괄 함수,hdc 꼭 포홤시키기 
        {
            PAINTSTRUCT ps;//그리기 정보를 가지고 있는 구조체
            HDC hdc = BeginPaint(hWnd, &ps);//DC 얻기 함수
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            if (bDraw)//영역무력화 호출시 발동 
            {
                MoveToEx(hdc, ptStart.x, ptStart.y, NULL);//초기좌표
                LineTo(hdc, ptEnd.x, ptEnd.y);//마지막 좌표까지의 선긋기


            }
                
            EndPaint(hWnd, &ps);//DC 반환 함수
        }
        break;
    case WM_DESTROY://원도우 종료 메세지
        DeleteObject(hBluePen);//펜오브젝트삭제
        PostQuitMessage(0);
        break;
    default://case에 의해 처리되지 않은 메세지 처리 
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)//대화상자에서 발생하는 메세지 처리
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
