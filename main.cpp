#include <windows.h>

#include <cmath>

#define ROUND(a) ((int) (a + 0.5))

/* set window handle */

static HWND sHwnd;

static COLORREF redColor=RGB(255,0,0);

static COLORREF blueColor=RGB(0,0,255);

static COLORREF greenColor=RGB(0,255,0);


void SetWindowHandle(HWND hwnd){

sHwnd=hwnd;

}

/* SetPixel */

void setPixel(int x,int y,COLORREF& color=redColor){

if(sHwnd==NULL){

MessageBox(NULL,"sHwnd was not initialized !","Error",MB_OK|MB_ICONERROR);

exit(0);

}

HDC hdc=GetDC(sHwnd);

SetPixel(hdc,x,y,color);

ReleaseDC(sHwnd,hdc);

return;

// NEVERREACH //

}


void drawLineDDA(int xa, int ya, int xb, int yb){

int dx = xb - xa, dy = yb - ya, steps, k;

float xIncrement, yIncrement, x = xa, y = ya;

if(abs(dx) > abs(dy)) steps = abs(dx);

else steps = abs(dy);

xIncrement = dx / (float) steps;

yIncrement = dy / (float) steps;

setPixel(ROUND(x), ROUND(y));

for(int k = 0; k < steps; k++){

x += xIncrement;

y += yIncrement;

setPixel(x, y);

}

}

/* Window Procedure WndProc */

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam){

switch(message){

case WM_PAINT:

SetWindowHandle(hwnd);


//1st line
//one
drawLineDDA(100, 20, 10, 160);
drawLineDDA(10, 160, 100, 160);

//two
drawLineDDA(120, 20, 170, 160);
drawLineDDA(170, 160, 240, 160);

//three
drawLineDDA(250, 20, 250, 160);
drawLineDDA(250, 160, 350, 160);

//four
drawLineDDA(400, 20, 360, 160);
drawLineDDA(360, 160, 460, 160);
drawLineDDA(460, 160, 400, 20);

//five
drawLineDDA(470, 20, 470, 160);
drawLineDDA(470, 160, 550, 160);
drawLineDDA(470, 20, 550, 160);

//House
//top
drawLineDDA(770, 20, 570, 160);
drawLineDDA(570, 160, 970, 160);
drawLineDDA(970, 160, 770, 20);

//middle start
drawLineDDA(590, 160, 590, 420);
//window 1
drawLineDDA(610, 250, 610, 350);
drawLineDDA(680, 250, 680, 350);
drawLineDDA(610, 350, 680, 350);
drawLineDDA(610, 250, 680, 250);
//window 2
drawLineDDA(930, 250, 930, 350);
drawLineDDA(930, 350, 860, 350);
drawLineDDA(860, 250, 860, 350);
drawLineDDA(860, 250, 930, 250);
//door
drawLineDDA(730, 420, 730, 250);
drawLineDDA(810, 420, 810, 250);
drawLineDDA(730, 250, 810, 250);

drawLineDDA(950, 160, 950, 420);
//middle end

//bottom
//drawLineDDA(590, 420, 950, 420);
drawLineDDA(570, 420, 970, 420);
drawLineDDA(570, 420, 570, 450);
drawLineDDA(970, 420, 970, 450);
drawLineDDA(570, 450, 970, 450);

//2nd line
//one
drawLineDDA(10, 180, 100, 180);
drawLineDDA(10, 180, 10, 280);
drawLineDDA(10, 280, 100, 280);
drawLineDDA(100, 280, 100, 180);

//two
drawLineDDA(120, 230, 175, 180);
drawLineDDA(120, 230, 175, 280);
drawLineDDA(175, 280, 230, 230);
drawLineDDA(230, 230, 175, 180);



break;

case WM_CLOSE: // FAIL THROUGH to call DefWindowProc

break;

case WM_DESTROY:

PostQuitMessage(0);

return 0;

default:

break; // FAIL to call DefWindowProc //

}

return DefWindowProc(hwnd,message,wParam,lParam);

}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow){

static TCHAR szAppName[] = TEXT("Straight Line");

WNDCLASS wndclass;

wndclass.style         = CS_HREDRAW|CS_VREDRAW ;

wndclass.lpfnWndProc   = WndProc ;

wndclass.cbClsExtra    = 0 ;

wndclass.cbWndExtra    = 0 ;

wndclass.hInstance     = hInstance ;

wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;

wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;

wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;

wndclass.lpszMenuName  = NULL ;

wndclass.lpszClassName = szAppName ;

// Register the window //

if(!RegisterClass(&wndclass)){

MessageBox(NULL,"Registering the class failled","Error",MB_OK|MB_ICONERROR);

exit(0);

}

// CreateWindow //

HWND hwnd=CreateWindow(szAppName,"DDA - Programming Techniques",

WS_OVERLAPPEDWINDOW,

CW_USEDEFAULT,

CW_USEDEFAULT,

CW_USEDEFAULT,

CW_USEDEFAULT,

NULL,

NULL,

hInstance,

NULL);

if(!hwnd){

MessageBox(NULL,"Window Creation Failed!","Error",MB_OK);

exit(0);

}

// ShowWindow and UpdateWindow //

ShowWindow(hwnd,iCmdShow);

UpdateWindow(hwnd);

// Message Loop //

MSG msg;

while(GetMessage(&msg,NULL,0,0)){

TranslateMessage(&msg);

DispatchMessage(&msg);

}

/* return no error to the operating system */

return 0;

}

