// test.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "test.h"
#include <iostream>
#include <string>
#include <strstream>
#include <vector>
#include <atlconv.h>  


using namespace std;
#define MAX_LOADSTRING 100

typedef struct{

	int x;
	int y;
} point;


int N;
int pre_N;
int from_x;
int from_y;
int xStep;
int yStep;
int x=2,y=2;
vector <int> is_use;
vector <int> w2p;

static RECT pre_Rect;
static RECT cur_Rect;
// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK set_hs(HWND , UINT , WPARAM , LPARAM );

HWND hwnd_main;
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	fclose(stdout);
	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   hwnd_main = hWnd;
   if (!hWnd)
   {
      return FALSE;
   }

   N = 20;
   is_use.resize(N*N);

   AllocConsole();                                          // 开辟控制台
  // SetConsoleTitle(_T("Debug Output"));      // 设置控制台窗口标题
   freopen("CONOUT$","w+t",stdout); 

   cout << "wo ca" << endl;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


void pd(){


	for(int i=0;i<w2p.size();i++){
	
		int x = w2p[i];
		int h=x/N;
		int w=x%N;

		//cout << "x--" <<  x << endl;
		if(x+N*4<N*N&&is_use[x+N]&&is_use[x+N*2]&&is_use[x+N*3]&&is_use[x+N*4]){
			cout << "You Win" << endl;
			return ;
		}

		if(x+4<N*N&&is_use[x+1]&&is_use[x+2]&&is_use[x+3]&&is_use[x+4]){
			cout << "You Win" << endl;
			return ;
		}

		if(x+N*4+4<N*N&&is_use[x+N+1]&&is_use[x+N*2+2]&&is_use[x+N*3+3]&&is_use[x+N*4+4]){
			cout << "You Win" << endl;
			return ;
		}
		if(x+N*4-1<N*N&&is_use[x+N-1]&&is_use[x+N*2-2]&&is_use[x+N*3-3]&&is_use[x+N*4-4]){
			cout << "You Win" << endl;
			return ;
		}
	}

}


//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	int color =  RGB(0, 0, 0);
	HBRUSH brush = CreateSolidBrush(color);
	strstream ss;
	string s;
	int n;

	switch (message)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &pre_Rect);
	case WM_SIZE:
		pre_Rect.right = LOWORD(lParam);
		pre_Rect.bottom = HIWORD(lParam);
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			fclose(stdout);
			DestroyWindow(hWnd);
			break;
		case IDM_SET:
			cout << "set hs" << endl;
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SET_HSBOX), hWnd, set_hs);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		xStep = pre_Rect.right / (N + 4);
		yStep = pre_Rect.bottom / (N + 4);

		cur_Rect.top = pre_Rect.top + xStep * 1;
		cur_Rect.bottom = cur_Rect.top + (N-1) * xStep;
		//cout << pre_Rect.right << "--" << pre_Rect.bottom << endl;
		from_x = 2*xStep;
		from_y = 2*yStep;
		for(int i=2;i<N+2;i++){
			MoveToEx(ps.hdc,xStep*i,yStep*2,0);
			LineTo(ps.hdc, xStep*i,pre_Rect.top+yStep*(N+1));
			MoveToEx(ps.hdc,xStep*2,yStep*i,0);
			LineTo(ps.hdc, pre_Rect.left+xStep*(N+1),yStep*i);
		}


		for(int i=0;i<w2p.size();i++){
			x = w2p[i] / N;
			y = w2p[i] % N;
			x = (x+2)*xStep;
			y = (y+2)*yStep;
			SelectObject(hdc, brush);
			Ellipse(hdc, x-5, y-5, x+5, y+5);
			DeleteObject(brush);
		}

		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		pd();
		break;
	case WM_LBUTTONDOWN:

		x = float (LOWORD(lParam) - from_x) / (float) xStep + 0.5;
		y = float (HIWORD(lParam) - from_y) / (float) yStep + 0.5;


		if(x*N+y>=N*N||x*N+y<0){
			break;
		}
		if(is_use[x*N+y]==0){
			is_use[x*N+y] = 1;
			w2p.push_back(x*N+y);
		}
		RedrawWindow(hWnd,NULL,NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);  

		break;
	case WM_DESTROY:
		fclose(stdout);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void change_isuse_w2p(){


	for(int i=0;i<w2p.size();i++){

		int x = w2p[i]/pre_N;
		int y = w2p[i]%pre_N;

		if(x*N+y<0||x*N+y>=N*N){
			cout << "覆盖已有内容." << endl;
			return;
		}
	}

	if(pre_N == N){

		return;
	}
	vector<int> w2p_(w2p.begin(),w2p.end());
	is_use.resize(N*N);

	w2p.clear();
	for(int i=0;i<w2p_.size();i++){

		int x = w2p_[i]/pre_N;
		int y = w2p_[i]%pre_N;

		if(x*N+y<0||x*N+y>=N*N){
			cout << "覆盖已有内容." << endl;
			return;
		}
		is_use[x*N+y] = 1;
		w2p.push_back(x*N+y);
	}
}

INT_PTR CALLBACK set_hs(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam){

	UNREFERENCED_PARAMETER(lParam);

	HWND hwnd_hs = GetDlgItem(hDlg,IDE_HS);
	char buffer[10];
	string str;
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:

		if(LOWORD(wParam) == IDCANCEL){

			cout << "cancle" << endl;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			int len = GetWindowTextLength(hwnd_hs) ;
			GetWindowText(hwnd_hs, LPWSTR(buffer), len+1);
			int i=0;
			while(str.size()<len){
				if(i%2==0&&(buffer[i]>='0'&&buffer[i]<='9')){
					str.push_back(buffer[i]);
				}
				i++;
			}
		
			pre_N = N;
			N = atoi(str.c_str());
			change_isuse_w2p();
			RedrawWindow(hwnd_main,NULL,NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);  
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;

}


// “关于”框的消息处理程序。
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
