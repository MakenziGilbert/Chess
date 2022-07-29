#include "Chess.h"
#include "framework.h"
// Глобальные переменные:
HINSTANCE hInst;                        // текущий экземпляр
LPCTSTR szTitle = "Шахматы";            // Текст строки заголовка
LPCTSTR szWindowClass = "skorbatiuk";   // имя класса главного окна
POINT p1 = { 0, 0 };
POINT p2 = { 0, 0 };
POINT mousePos;
Position ps1, ps2;
ChessBoard cb;
ChessBoard temp;
HBITMAP hBoard;
HBITMAP hwChess;
HBITMAP hbChess;
bool flag = false;
bool multiplayer = false;
bool white;
bool typeMove = false;
bool findMouse = false;
double sizeCellx = 57.5;
double sizeCelly = 57.5;
char ip[] = "255.255.255.255";
ofstream fout;
ifstream fin;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CreateSession(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    ConnectionSession(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Failed(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHESS));
    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCE(IDC_CHESS);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 475, 515, nullptr, nullptr, hInstance, nullptr);

    hBoard = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
    hwChess = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
    hbChess = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_NEWGAME:
            cb = temp;
            InvalidateRect(hWnd, NULL, true);
            break;
        case IDM_CREATE_SESSION:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_CREATE_SESSION), hWnd, CreateSession);
            break;
        case IDM_CONNECTION_SESSION:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_CONNECTION_SESSION), hWnd, ConnectionSession);
            break;
        case IDM_SAVE1:
            fout.open("save_1.txt");

            if (!fout.is_open())
            {
                MessageBox(hWnd, "Ошибка сохранения!", "Ошибка!", MB_ICONWARNING || MB_OK);
            }

            fout << cb;

            fout.close();
            break;
        case IDM_SAVE2:
            fout.open("save_2.txt");

            if (!fout.is_open())
            {
                MessageBox(hWnd, "Ошибка сохранения!", "Ошибка!", MB_ICONWARNING || MB_OK);
            }

            fout << cb;

            fout.close();
            break;
        case IDM_SAVE3:
            fout.open("save_3.txt");

            if (!fout.is_open())
            {
                MessageBox(hWnd, "Ошибка сохранения!", "Ошибка!", MB_ICONWARNING || MB_OK);
            }

            fout << cb;

            fout.close();
            break;
        case IDM_LOAD1:
            fin.open("save_1.txt");

            if (!fin.is_open())
            {
                MessageBox(hWnd, "Ошибка загрузки!", "Ошибка!", MB_ICONWARNING || MB_OK);
            }

            fin >> cb;

            fin.close();
            InvalidateRect(hWnd, NULL, true);
            break;
        case IDM_LOAD2:
            fin.open("save_2.txt");

            if (!fin.is_open())
            {
                MessageBox(hWnd, "Ошибка загрузки!", "Ошибка!", MB_ICONWARNING || MB_OK);
            }

            fin >> cb;

            fin.close();
            InvalidateRect(hWnd, NULL, true);
            break;
        case IDM_LOAD3:
            fin.open("save_3.txt");

            if (!fin.is_open())
            {
                MessageBox(hWnd, "Ошибка загрузки!", "Ошибка!", MB_ICONWARNING || MB_OK);
            }

            fin >> cb;

            fin.close();
            InvalidateRect(hWnd, NULL, true);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_MOUSEMOVE:
        if (findMouse)
        {
            GetCursorPos(&mousePos);//получения координат фигуры
            ScreenToClient(hWnd, &mousePos);
            InvalidateRect(hWnd, NULL, true);
        }
        break;
    case WM_LBUTTONDOWN:
    {
        findMouse = true;
        GetCursorPos(&p1);//получения координат фигуры
        ScreenToClient(hWnd, &p1);
    }
    break;
    case WM_LBUTTONUP:
    {
        findMouse = false;
        GetCursorPos(&p2);//получения координат места ходу
        ScreenToClient(hWnd, &p2);

        ps1.x = p1.x / sizeCellx;//получение номеру клетки
        ps2.x = p2.x / sizeCellx;
        ps1.y = p1.y / sizeCelly;
        ps2.y = p2.y / sizeCelly;

        if (ps1.x != ps2.x || ps1.y != ps2.y)
        {
            cb.Move(ps1, ps2);//движение фигуры
            if (cb.win == 1)//проверка н то что игра не законцена
            {
                 DialogBox(hInst, MAKEINTRESOURCE(IDD_WHITE), hWnd, Failed);
            }
            else if (cb.win == 2)
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_BLACK), hWnd, Failed);
            }
        }
        else
        {
            typeMove = true;
        }

        InvalidateRect(hWnd, NULL, true);
    }
    break;
    case  WM_RBUTTONUP:
    {
        if (typeMove)
        {
            GetCursorPos(&p2);//получения координат места ходу
            ScreenToClient(hWnd, &p2);

            ps2.x = p2.x / sizeCellx;
            ps2.y = p2.y / sizeCelly;

            cb.Move(ps1, ps2);//движение фигуры
            if (cb.win == 1)//проверка н то что игра не законцена
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_WHITE), hWnd, Failed);
            }
            else if (cb.win == 2)
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_BLACK), hWnd, Failed);
            }

            typeMove = false;

            InvalidateRect(hWnd, NULL, true);
        }
    }
    case WM_PAINT:
    {
        BITMAP Bitmapp;
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT Rect;
        GetClientRect(hWnd, &Rect);

        sizeCellx = (Rect.right - Rect.left) / 8.;
        sizeCelly = (Rect.bottom - Rect.top) / 8.;

        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP hBM = CreateCompatibleBitmap(hdc, Rect.right, Rect.bottom);
        SelectObject(memDC, hBM);

        
        HDC hCompatibleDC = CreateCompatibleDC(memDC);
       
        GetObject(hBoard, sizeof(BITMAP), &Bitmapp);
        HANDLE hOldBitmap = SelectObject(hCompatibleDC, hBoard);
        StretchBlt(memDC, 0, 0, Rect.right, Rect.bottom, hCompatibleDC, 0, 0, Bitmapp.bmWidth, Bitmapp.bmHeight, SRCCOPY);

        SelectObject(hCompatibleDC, hOldBitmap);
        DeleteDC(hCompatibleDC);

        hCompatibleDC = CreateCompatibleDC(memDC);

        POINT p;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
            {
                p.x = i * sizeCellx;
                p.y = j * sizeCelly;

                COLORREF col = GetPixel(memDC, p.x + sizeCellx / 2, p.y + sizeCelly / 2);
               if (col != COLORREF(0x000000))
                {
                    GetObject(hwChess, sizeof(BITMAP), &Bitmapp);
                    SelectObject(hCompatibleDC, hwChess);
                }
                else
                {
                    GetObject(hbChess, sizeof(BITMAP), &Bitmapp);
                    SelectObject(hCompatibleDC, hbChess);
                }

                if (cb.board[j][i][0] == 'w')
                {
                    switch (cb.board[j][i][1])
                    {
                    case 'K':

                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 0, 0, 330, 350, SRCCOPY);
                        break;
                    case 'Q':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 330, 0, 330, 350, SRCCOPY);
                        break;
                    case 'O':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 670, 0, 330, 350, SRCCOPY);
                        break;
                    case 'N':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 1000, 0, 330, 350, SRCCOPY);
                        break;
                    case 'T':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 1340, 0, 330, 350, SRCCOPY);
                        break;
                    case 'P':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 1670, 0, 330, 350, SRCCOPY);
                        break;
                    }
                }
                else
                {
                    switch (cb.board[j][i][1])
                    {
                    case 'K':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 0, 350, 330, 350, SRCCOPY);
                        break;
                    case 'Q':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 330, 350, 330, 350, SRCCOPY);
                        break;
                    case 'O':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 670, 350, 330, 350, SRCCOPY);
                        break;
                    case 'N':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 1000, 350, 330, 350, SRCCOPY);
                        break;
                    case 'T':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 1340, 350, 330, 350, SRCCOPY);
                        break;
                    case 'P':
                        StretchBlt(memDC, p.x, p.y, sizeCellx, sizeCelly, hCompatibleDC, 1670, 350, 330, 350, SRCCOPY);
                        break;
                    }
                }
            }
        
        if (typeMove)
        {
            POINT select;
            SelectObject(memDC, CreatePen(PS_SOLID, 4, RGB(245, 220, 0)));
            select.x = p1.x / sizeCellx;
            select.y = p1.y / sizeCelly;
            select.x *= sizeCellx;
            select.y *= sizeCelly;
            
            MoveToEx(memDC, select.x, select.y, NULL);
            LineTo(memDC, select.x + sizeCellx, select.y);
            LineTo(memDC, select.x + sizeCellx, select.y + sizeCelly);
            LineTo(memDC, select.x, select.y + sizeCelly);
            LineTo(memDC, select.x, select.y);
        }

        if (findMouse)
        {
            p.x = p1.x / sizeCellx;
            p.y = p1.y / sizeCelly;

            COLORREF col = GetPixel(memDC, mousePos.x, mousePos.y);
            if (col != COLORREF(0x000000))
            {
                GetObject(hwChess, sizeof(BITMAP), &Bitmapp);
                SelectObject(hCompatibleDC, hwChess);
            }
            else
            {
                GetObject(hbChess, sizeof(BITMAP), &Bitmapp);
                SelectObject(hCompatibleDC, hbChess);
            }

            if (cb.board[p.y][p.x][0] == 'w')
            {
                switch (cb.board[p.y][p.x][1])
                {
                case 'K':

                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 0, 0, 330, 350, SRCCOPY);
                    break;
                case 'Q':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 330, 0, 330, 350, SRCCOPY);
                    break;
                case 'O':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 670, 0, 330, 350, SRCCOPY);
                    break;
                case 'N':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 1000, 0, 330, 350, SRCCOPY);
                    break;
                case 'T':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 1340, 0, 330, 350, SRCCOPY);
                    break;
                case 'P':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 1670, 0, 330, 350, SRCCOPY);
                    break;
                }
            }
            else
            {
                switch (cb.board[p.y][p.x][1])
                {
                case 'K':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 0, 350, 330, 350, SRCCOPY);
                    break;
                case 'Q':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 330, 350, 330, 350, SRCCOPY);
                    break;
                case 'O':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 670, 350, 330, 350, SRCCOPY);
                    break;
                case 'N':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 1000, 350, 330, 350, SRCCOPY);
                    break;
                case 'T':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 1340, 350, 330, 350, SRCCOPY);
                    break;
                case 'P':
                    StretchBlt(memDC, mousePos.x - sizeCellx / 2, mousePos.y - sizeCelly / 2, sizeCellx, sizeCelly, hCompatibleDC, 1670, 350, 330, 350, SRCCOPY);
                    break;
                }
            }
        }


        BitBlt(hdc, 0, 0, Rect.right, Rect.bottom, memDC, 0, 0, SRCCOPY);

        SelectObject(hCompatibleDC, hOldBitmap);
        DeleteDC(hCompatibleDC);
        DeleteObject(hBM);
        DeleteDC(memDC);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_ERASEBKGND:
        return (LRESULT)1; 
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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

INT_PTR CALLBACK CreateSession(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (wParam)
        {
        case IDOK:
        {
            multiplayer = true;
            GetDlgItemText(hDlg, IDC_EDIT1, ip, 16);
            static Server server(ip);
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK ConnectionSession(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (wParam)
        {
        case IDOK:
        {
            GetDlgItemText(hDlg, IDC_EDIT1, ip, 16);
            static Client client(ip);
            multiplayer = true;
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Failed(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    ChessBoard temp;
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDNEW:
            cb = temp;
            EndDialog(hDlg, LOWORD(wParam));
            break;
        case IDEXIT:
            EndDialog(hDlg, LOWORD(wParam));
            PostQuitMessage(0);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}