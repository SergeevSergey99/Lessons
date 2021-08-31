// Win32Project3.cpp: определяет точку входа для приложения.
//

  #include "stdafx.h"
  #include "Win32Project3.h"
  #include <stdio.h>
  #include <conio.h>
  #include <windows.h>
  #include <gl/GL.h>
  #include <gl/GLU.h>
  #include "glaux.h"
  #include <math.h>
  #include <time.h>
  #include <iostream>
  #include <fstream>
  #include <locale.h>

  using namespace std;

  BOOL keys[256]; // Текущее состояние клавиш (кроме системных)
  GLuint base; // для шрифтов
  #define NX 120 // количество по горизонтали
  #define NZ 60 // количество вглубь
  #define CX 1.0 // размер клетки
  #define CZ 1.0
  #define vragi 5
  #define ptrp	36
  #define ptrr	11
  #define PI 3.1415926536 
  int p = 0, mgun = 0, ptr = ptrp, g, kamera = 0, garag = 0, l = 1, lm = 3, ubvrg[vragi] = { 7, 7, 5, 5, 6 },
    lvrg[vragi] = { 3, 3, 7, 7, 10 },tanketka = 1, gun = 1, language = 0, timer = 0,melose=0;
  GLuint texture[28];
  AUX_RGBImageRec *texture28, *texture27, *texture26, *texture25, *texture24, *texture23, *texture22, *texture21, *texture20, *texture19, *texture18, *texture17, *texture16, *texture15, *texture14, *texture13, *texture11, *texture1, *texture2, *texture3, *texture4, *texture5, *texture6, *texture7, *texture8, *texture9, *texture10, *texture12;
 // static int ; 
  int labir[30][30];

  typedef struct
  {
    float scale;
  } t_scene;
  static t_scene scene = { 1.0 };
  typedef struct
  {
	int down_x;
	int down_y;
	int up_x;
	int up_y;
	int move_x;
	int move_y;
	int down;
	int wheel;
  } t_mouse;
  static t_mouse mouse = { 0 };
  static float counter = 0;
  int drprosses;
  float angle = 0.0;
  float xp[ptrp], zp[ptrp], vistrel[ptrp], vr[ptrp];// угол поворота камеры вокруг оси y
  float angle2 = 0.0, ug;
  float angle3[ptrp];
  float look_x = 25.0; // расстояние до камеры
  float look_z = 25.0;
  int  ubilkame = 0, scm, scv;
  float anglev[vragi] = { 0.0, 0.0, 0.0, 0.0, 0.0 }, anglev1[vragi] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
  //float propVrag = 1.6; 
  //float radVrag = 0.5;
 // static float shoulders = 0.2;
  //int nvrg;
  typedef struct
  {
	float x, y, z;
  } t_me;
  static t_me me = { 5, 0.0, 5.0 }; // координата ног: посередине по x, 0.0 от пола
 // float nash_rost = 0.2; // высота камеры над плоскостью
  typedef struct
  {
	float x[vragi], z[vragi], y;
  } t_vrg;
  static t_vrg vrg = { 56.0, 56.0, 56.0, 56.0, 56.0, 56.0, 56.0, 56.0, 56.0, 56.0, 0.0 }; // координата ног: посередине по x, 0.0 от пола
  void ReadMas();
  LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam); // прототип функции окна
  double func(double x, double z);
  int APIENTRY WinMain( HINSTANCE hInstance, // дескриптор экземпляра приложения – уникальный идентификатор приложения для операционной системы
						HINSTANCE hPrevInstance, // не используется, оставлено для совместимости
						LPSTR lpCmdLine, // параметры в случае запуска из командной строки
						int nCmdShow ) // режим отображения окна (SW_SHOW)  
  {
	srand(unsigned(time(NULL)));
	HWND hWnd; // создание дескриптора (уникального регистрационного номера для операционной системы) окна
	WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0,
		hInstance, NULL, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL, L"My", NULL };
	RegisterClassEx(&wcex);
	hWnd = CreateWindow(L"My", L"ПОЛИГОН", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
	  CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow); // Отображение окна
	UpdateWindow(hWnd); // обновляем рабочую область заданного окна, отправляя сообщение WM_PAINT окну
	MSG msg; // переменная для принятия в нее сообщения от операционной системы
	ReadMas();
	while (GetMessage(&msg, NULL, 0, 0)) // извлекаем сообщение из очереди, созданной операционной системой
	{
	  TranslateMessage(&msg); // обрабатываем сообщения
	  DispatchMessage(&msg); // передаем сообщения обратно операционной системе
	  InvalidateRect(hWnd, NULL, FALSE); //
	  Sleep(50); // делаем паузу, чтоб не перегружать процессор
	}
	return (int)msg.wParam; // Возвращаем операционной системе код выхода из приложения
  }
__int64 GetCpuTick()
{
  LARGE_INTEGER    li;
  DWORD            l, h;
  __asm
  {
      rdtsc
       mov DWORD ptr h, edx
       mov DWORD ptr l, eax
   }
  li.HighPart = h;
  li.LowPart = l;	
  return li.QuadPart;
}
int sysGetCPUspeed(void)
{
  LONG error;
  HKEY hKey;
  DWORD data;
  DWORD dataSize;
  data = 0;
  error = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE,
  L"Hardware\\Description\\System\\CentralProcessor\\0", 0, KEY_QUERY_VALUE, &hKey);
  if (error == ERROR_SUCCESS)
  {                                     // _T
    error = ::RegQueryValueEx(hKey, L"~MHz", NULL, NULL, (LPBYTE)&data, &dataSize);
	if (error != ERROR_SUCCESS) 
	{
	}
  }
  RegCloseKey(hKey);
  return data;
}
int prosses()
{
  __int64 Frequency, TimerCount1, TimerCount2, CpuCount1, CpuCount2;
  double dr;
  if (!QueryPerformanceFrequency((LARGE_INTEGER*)&Frequency)) 
    return 0;
  QueryPerformanceCounter((LARGE_INTEGER*)&TimerCount1);
  CpuCount1 = GetCpuTick();
  Sleep(500);
  CpuCount2 = GetCpuTick();
  QueryPerformanceCounter((LARGE_INTEGER*)&TimerCount2);
  if (TimerCount1 == TimerCount2) 
	return 0;
  dr = ((double)((CpuCount2 - CpuCount1) * Frequency) /	(double)(TimerCount2 - TimerCount1));
  drprosses = (int)(dr / 1000000.0);
  if (drprosses < 3400)  drprosses = 3400 / drprosses; else drprosses = 1;
  return 0;
}

void SetWindowPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cRedShift = 16;
	pfd.cGreenBits = 8;
	pfd.cGreenShift = 8;
	pfd.cBlueBits = 8;
	pfd.cBlueShift = 0;
	pfd.cAlphaBits = 0;
	pfd.cAlphaShift = 0;
	pfd.cAccumBits = 64;
	pfd.cAccumRedBits = 16;
	pfd.cAccumGreenBits = 16;
	pfd.cAccumBlueBits = 16;
	pfd.cAccumAlphaBits = 0;
	pfd.cDepthBits = 32;
	pfd.cStencilBits = 8;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.bReserved = 0;
	pfd.dwLayerMask = 0;
	pfd.dwVisibleMask = 0;
	pfd.dwDamageMask = 0;

	SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);
}
void ReadMas()
{
	ifstream f;
	int i, j;

	f.open("lab2.txt", ios::in);
	for (i = 0; i < 30; i++)
		for (j = 0; j < 30; j++)
		{
		f >> labir[j][i];
		}
	f.close();
}


void InitFonts(HDC hdc)
{
	HFONT  font;                     // Идентификатор шрифта Windows
	base = glGenLists(256);          // массив для 256 букв
	font = CreateFont(
		4,          // высота шрифта
		5,            // ширина знакоместа
		0,            //Угол перехода
		20,            //Угол направления
		FW_BOLD,              //Ширина шрифта
		FALSE,        // Курсив
		FALSE,        // Подчеркивание
		FALSE,        // Перечеркивание
		RUSSIAN_CHARSET,       //Идентификатор кодировки
		OUT_TT_PRECIS,       // Точность вывода
		CLIP_DEFAULT_PRECIS,       //Точность отсечения
		ANTIALIASED_QUALITY,// Качество вывода
		FF_DONTCARE | DEFAULT_PITCH, // Семейство и Шаг
		NULL);
	//L"Comic Sans MS");          // Имя шрифта

	SelectObject(hdc, font);       //Выбрать шрифт, созданный нами
	wglUseFontOutlinesA(hdc, 0, 255, base, (float)0.0, (float)0.15, WGL_FONT_POLYGONS, NULL);

}
void DeleteFonts(void)                   // Удаление шрифта
{
	glDeleteLists(base, 256); // Удаление всех 256 списков отображения
}

void DrawTextGL(float x, float y, char * text)
{
	glPushAttrib(GL_LIST_BIT); // Сохраняет в стеке значения битов списка отображения
	glListBase(base);          // Устанавливает базовый символ в 0

	glPushMatrix();
	glTranslatef(x + 30, y - 1, 30);     //

	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // Создает списки отображения текста

	glPopMatrix();
	//glTranslatef(-x, -y, 0);

	glPopAttrib(); // Восстанавливает значение Display List Bits
}

void Cube(float x, float y, float z, float x1, float y1, float z1, int t1, int t2, int t3, int t4, int t5, int t6)
{
	glColor4f(0.0, 1.0, 0.0, 1.0);
	

	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
	glEnable(GL_TEXTURE_2D);		// Разрешение наложение текстуры
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, texture[t1]);
	glBegin(GL_POLYGON);//front
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y1, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y1, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y, z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[t2]);
	glBegin(GL_POLYGON);//back
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y1, z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y1, z1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y, z1);
	glEnd(); glBindTexture(GL_TEXTURE_2D, texture[t3]);
	glBegin(GL_POLYGON);//right
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x1, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x1, y1, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y1, z1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y, z1);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[t4]);
	glBegin(GL_POLYGON);//left
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y1, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y1, z1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z1);
	glEnd(); glBindTexture(GL_TEXTURE_2D, texture[t5]);
	glBegin(GL_POLYGON);//up
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y1, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y1, z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y1, z1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1, z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texture[t6]);
	glBegin(GL_POLYGON);//down
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x1, y, z1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y, z);
	glEnd();
}

void Resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (float)width / height, 1.0, 1.0 + NZ * 2);
	//	glOrtho(-15.0, 15.0, -15.0, 15.0, 15.0, -15.0);
}
void DrawMe()
{
	char txt1[64], s[10], s1[10], s2[10], s3[10], s4[10];
	static float shoulders = 0.2;
	//	static float angle1 = angle;
	glColor4f(0.0, 1.0, 0.0, 1.0);
	//glBegin(GL_LINE_LOOP);
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
	glEnable(GL_TEXTURE_2D);		// Разрешение наложение текстуры
	glEnable(GL_LIGHTING);
	
	glPushMatrix();
	glTranslatef(me.x, 0, me.z);
    glRotatef(90, 0, 1, 0);
	//angle1 = -angle;
	glRotatef(-angle * 180 / PI, 0, 1, 0);
	if (tanketka == 1)
	  Cube(-0.3, 0.0, -0.7, 0.3, 0.2, 0.7, 2, 11, 9, 9, 8, 8);
	if (tanketka == 0)
	  Cube(-0.4, 0.0, -0.8, 0.4, 0.23, 0.8, 2, 11, 9, 9, 8, 8);
	glRotatef(angle * 180 / PI, 0, 1, 0);
	glRotatef(-angle2 * 180 / PI, 0, 1, 0);
	Cube(-0.2, 0.2, -0.5, 0.2, 0.36, 0.5, 4, 7, 3,3, 5, 5);
	if (gun== 1)
	  Cube(-0.05, 0.25, 0.5, 0.05, 0.3, 0.75, 6, 6, 6, 6, 6, 6);
	if (gun == 0) 
	{
	  Cube(-0.1, 0.25, 0.5, 0.1, 0.35, 0.8, 6, 6, 6, 6, 6, 6);
	  glDisable(GL_TEXTURE_2D);
	  glDisable(GL_LIGHTING);
	  glColor3f(0, 0, 0);
	  glBegin(GL_POLYGON);//pricel
	  glVertex3f(0.5, 2.4, 2.001);
	  glVertex3f(0.5, 2.2, 2.001);
	  glVertex3f(-0.5, 2.2, 2.001);
	  glVertex3f(-0.5, 2.4, 2.001);
	  glEnd();
	  glColor3f(1, 0, 0);
	  if (timer < 100)
	  {
		  glBegin(GL_POLYGON);//pricel
		  glVertex3f(-0.5 + timer / 100.0, 2.4, 2);
		  glVertex3f(-0.5 + timer / 100.0, 2.2, 2);
		  glVertex3f(-0.5, 2.2, 2);
		  glVertex3f(-0.5, 2.4, 2);
		  glEnd();
	  }
	  if (timer >= 100)
	  {
		glBegin(GL_POLYGON);//pricel
		glVertex3f(0.5, 2.4, 2);
		glVertex3f(0.5, 2.2, 2);
		glVertex3f(-0.5, 2.2, 2);
		glVertex3f(-0.5, 2.4, 2);
		glEnd();
	  }
	}	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	if (kamera == 2)
	{
	  glRotatef(-90, 0, 1, 0);
	  glColor3f(1, 0, 0);
	  glBegin(GL_POLYGON);//pricel
	  glVertex3f(30.7, 0.29, 0.02);
	  glVertex3f(30.7, 0.29, -0.02);
	  glVertex3f(0.5, 0.29, -0.01);
	  glVertex3f(0.5, 0.29, 0.01);
	  glEnd();
	}

	glPopMatrix(); // возврат координат общий - состояние до рисования танка
	if (kamera == 2)
	{
	  float aaa;
	  
	  aaa = 1.0 - 0.04*g;
	  if (p < ptr - 1)
		glColor3f(g*0.1, aaa, 0.0);
	  if (p == ptr - 1)
		glColor3f(0.0, 0.0, 0.0);
	  glPushMatrix();
	  glTranslatef(me.x, 0, me.z);
      glScalef(0.1, 0.1, 0.1);
	  glRotatef(-angle2 * 180 / 3.1415926536, 0, 1, 0);
	  sprintf(s, "%2d", ptr - p - 1); sprintf(s1, "%3d", scm); sprintf(s2, "%3d", scv); sprintf(s3, "%3d", lm);
	  glRotatef(-90, 0.0, 1.0, 0.0);
	  glTranslatef(-39, 0.0, -34);
	  //glLoadIdentity();
	  if (ubvrg[0] == 0 && ubvrg[1] == 0 && ubvrg[2] == 0 && ubvrg[3] == 0 && ubvrg[4] == 0)
	    sprintf(s1, "you win");
	  if (scv >= melose)
		sprintf(s1, "you lose");
      //if (pause == 0){ DrawTextGL(6.0, 0.4, "pause"); }
	  DrawTextGL(0.0, 5.4, s);
	  glColor3f(1.0, 1.0, 0.0);
      DrawTextGL(0.0, 8.0, s1); 
	  DrawTextGL(0.0, 6.4, s2);
	  glColor3f(1.0, 0.0, 0.0);
	  DrawTextGL(17.0, 17.4, s3);
	  glRotatef(90, 0.0, 1.0, 0.0);
	  glPopMatrix(); // состояние до рисования танка
	}
	if (kamera == 0)
	{
	  float aaa;
	  
	  aaa = 1.0 - 0.04 * g;
	  if (p < ptr - 1)
	  	glColor3f(g*0.1, aaa, 0.0);
	  if (p == ptr - 1)
		glColor3f(0.0, 0.0, 0.0);
	  glPushMatrix();
	  glTranslatef(me.x, 0, me.z);
	  glScalef(0.1, 0.1, 0.1);
	  glRotatef(-angle2 * 180 / 3.1415926536, 0, 1, 0);
	  sprintf(s, "%2d", ptr - p - 1); 
	  sprintf(s1, "%3d", scm);
	  sprintf(s2, "%3d", scv);
	  sprintf(s3, "%3d", lm);
	  glRotatef(-90, 0.0, 1.0, 0.0);
	  glTranslatef(-39, 0.0, -28);
	  //glLoadIdentity();
      if (ubvrg[0] == 0 && ubvrg[1] == 0 && ubvrg[2] == 0 && ubvrg[3] == 0 && ubvrg[4] == 0)
		sprintf(s1, "you win");
	  if (scv >= melose)
		sprintf(s1, "you lose");
	  DrawTextGL(0.0, 5.4, s); 
	  glColor3f(1.0, 1.0, 0.0);
	  DrawTextGL(0.0, 8.0, s1); 
	  DrawTextGL(0.0, 6.4, s2);
	  glColor3f(1.0, 0.0, 0.0);
	  DrawTextGL(17.0, 17.4, s3);
	  glRotatef(90, 0.0, 1.0, 0.0);
	  glPopMatrix(); // возврат координат общий - состояние до рисования танка
	 }
	 if (kamera == 1)
	 {
	    float aaa;
		
		aaa = 1.0 - 0.04 * g;
		if (p < ptr - 1)
		  glColor3f(g*0.1, aaa, 0.0);
		if (p == ptr - 1)
		  glColor3f(0.0, 0.0, 0.0);
		  glPushMatrix();
		  glTranslatef(me.x, 0, me.z);
		  glScalef(0.1, 0.1, 0.1);
		  glRotatef(-angle * 180 / 3.1415926536, 0, 1, 0);
    	  sprintf(s, "%2d", ptr - p - 1); 
		  sprintf(s1, "%3d", scm);
		  sprintf(s2, "%3d", scv);
		  sprintf(s3, "%3d", lm);
	  	  glRotatef(-90, 0.0, 1.0, 0.0);
		  glTranslatef(-39, 0.0, -18);
		  //glLoadIdentity();
		if (ubvrg[0] == 0 && ubvrg[1] == 0 && ubvrg[2] == 0 && ubvrg[3] == 0 && ubvrg[4] == 0)
		  sprintf(s1, "you win");
		if (scv >= melose)
		  sprintf(s1, "you lose");
		DrawTextGL(0.0, 5.4, s); 
		glColor3f(1.0, 1.0, 0.0);
		DrawTextGL(0.0, 8.0, s1);
		DrawTextGL(0.0, 6.4, s2);
		glColor3f(1.0, 0.0, 0.0);
		DrawTextGL(17.0, 17.4, s3);
		glRotatef(90, 0.0, 1.0, 0.0);
		glPopMatrix(); // возврат координат общий - состояние до рисования танка
	 }
}

void DrawVrg()
{
	glColor4f(0.0, 1.0, 0.0, 1.0);
	for (int iv=0; iv < vragi; iv++)
	{
	  glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
	  glEnable(GL_TEXTURE_2D);		// Разрешение наложение текстуры
	  glEnable(GL_LIGHTING);
	  glPushMatrix();
	  glTranslatef(vrg.x[iv], 0, vrg.z[iv]);
	  glRotatef(90, 0, 1, 0);
	  glRotatef(-anglev[iv] * 180 / PI, 0, 1, 0);
	  if(lvrg[iv]==3)
		Cube(-0.3, 0.0, -0.7, 0.3, 0.2, 0.7, 15, 22, 21, 21, 20, 20);
	  if (lvrg[iv] == 7)
		Cube(-0.45, 0.0, -0.8, 0.45, 0.24, 0.8, 15, 22, 21, 21, 20, 20);
	  if (lvrg[iv] == 10)
	  {
		Cube(-0.45, 0.0, -0.7999, 0.45, 0.24, 0.8, 15, 22, 21, 21, 20, 20);
		Cube(-0.451, 0.0, -0.8, 0.451, 0.37, 0.0, 15, 22, 21, 21, 20, 20);
	  }
	  glRotatef(anglev[iv] * 180 / PI, 0, 1, 0);
	  glRotatef(-anglev1[iv] * 180 / PI, 0, 1, 0);
	  Cube(-0.2, 0.2, -0.5, 0.2, 0.36, 0.5, 17, 19, 16, 16, 18, 18);
	  Cube(-0.05, 0.25, 0.4, 0.05, 0.3, 0.75, 6, 6, 6, 6, 6, 6);
	  if (lvrg[iv] == 10)
		Cube(-0.15, 0.2, 0.5, 0.15, 0.34, 0.85, 6, 6, 6, 6, 6, 6);
	  glDisable(GL_TEXTURE_2D);
	  glDisable(GL_LIGHTING);
	  glPopMatrix();
	}
}

// Загрузка картинки и конвертирование в текстуру
GLvoid LoadGLTextures()
{
   	// 28
  texture28 = auxDIBImageLoad(L"menu2.bmp");
  glGenTextures(1, &texture[27]); //
  glBindTexture(GL_TEXTURE_2D, texture[27]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture28->sizeX, texture28->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture28->data);
	// 27
  texture27 = auxDIBImageLoad(L"bang.bmp");
  glGenTextures(1, &texture[26]); //
  glBindTexture(GL_TEXTURE_2D, texture[26]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture27->sizeX, texture27->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture27->data);
	// 26
  texture26 = auxDIBImageLoad(L"rocket1.bmp");
  glGenTextures(1, &texture[25]); //
  glBindTexture(GL_TEXTURE_2D, texture[25]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture26->sizeX, texture26->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture26->data);
	// 25
  texture25 = auxDIBImageLoad(L"rocket.bmp");
  glGenTextures(1, &texture[24]); //
  glBindTexture(GL_TEXTURE_2D, texture[24]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture25->sizeX, texture25->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture25->data);
	// 24
  texture24 = auxDIBImageLoad(L"stena1.bmp");
  glGenTextures(1, &texture[23]); //
  glBindTexture(GL_TEXTURE_2D, texture[23]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture24->sizeX, texture24->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture24->data);
	//23
  texture23 = auxDIBImageLoad(L"Vper.bmp");
  glGenTextures(1, &texture[22]); //
  glBindTexture(GL_TEXTURE_2D, texture[22]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture23->sizeX, texture23->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture23->data);
	//22
  texture22 = auxDIBImageLoad(L"Vbok.bmp");
  glGenTextures(1, &texture[21]); //
  glBindTexture(GL_TEXTURE_2D, texture[21]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture22->sizeX, texture22->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture22->data);
	//21
  texture21 = auxDIBImageLoad(L"Vverh.bmp");
  glGenTextures(1, &texture[20]); //
  glBindTexture(GL_TEXTURE_2D, texture[20]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture21->sizeX, texture21->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture21->data);
	//20
  texture20 = auxDIBImageLoad(L"Vlico.bmp");
  glGenTextures(1, &texture[19]); //
  glBindTexture(GL_TEXTURE_2D, texture[19]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture20->sizeX, texture20->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture20->data);	
	//19
  texture19 = auxDIBImageLoad(L"Vverhroof.bmp");
  glGenTextures(1, &texture[18]); //
  glBindTexture(GL_TEXTURE_2D, texture[18]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture19->sizeX, texture19->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture19->data);
	//18
  texture18 = auxDIBImageLoad(L"zadroof.bmp");
  glGenTextures(1, &texture[17]); //
  glBindTexture(GL_TEXTURE_2D, texture[17]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture18->sizeX, texture18->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture18->data);
	//17
  texture17 = auxDIBImageLoad(L"Vbokroof.bmp");
  glGenTextures(1, &texture[16]); //
  glBindTexture(GL_TEXTURE_2D, texture[16]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture17->sizeX, texture17->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture17->data);
	//16
  texture16 = auxDIBImageLoad(L"Vparket3.bmp");
  glGenTextures(1, &texture[15]); //
  glBindTexture(GL_TEXTURE_2D, texture[15]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture16->sizeX, texture16->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture16->data);	
	//15
  texture15 = auxDIBImageLoad(L"wood.bmp");
  glGenTextures(1, &texture[14]); //
  glBindTexture(GL_TEXTURE_2D, texture[14]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture15->sizeX, texture15->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture15->data);
	//14
  texture14 = auxDIBImageLoad(L"kust.bmp");
  glGenTextures(1, &texture[13]); //
  glBindTexture(GL_TEXTURE_2D, texture[13]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture14->sizeX, texture14->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture14->data);
  	//13
  texture13 = auxDIBImageLoad(L"patroni.bmp");
  glGenTextures(1, &texture[12]); //
  glBindTexture(GL_TEXTURE_2D, texture[12]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture13->sizeX, texture13->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture13->data);
	//12
  texture12 = auxDIBImageLoad(L"per.bmp");
  glGenTextures(1, &texture[11]); //
  glBindTexture(GL_TEXTURE_2D, texture[11]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture12->sizeX, texture12->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture12->data);
    //11   
  texture11 = auxDIBImageLoad(L"stena.bmp");
  glGenTextures(1, &texture[10]); //
  glBindTexture(GL_TEXTURE_2D, texture[10]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture11->sizeX, texture11->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture11->data);

    //10
  texture10 = auxDIBImageLoad(L"bok.bmp");
  glGenTextures(1, &texture[9]); //
  glBindTexture(GL_TEXTURE_2D, texture[9]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture10->sizeX, texture10->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture10->data);
	//9
  texture9 = auxDIBImageLoad(L"verh.bmp");
  glGenTextures(1, &texture[8]); //
  glBindTexture(GL_TEXTURE_2D, texture[8]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture9->sizeX, texture9->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture9->data);
	//8
  texture8 = auxDIBImageLoad(L"lico.bmp");
  glGenTextures(1, &texture[7]); //
  glBindTexture(GL_TEXTURE_2D, texture[7]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture8->sizeX, texture8->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture8->data);
	//7
  texture7 = auxDIBImageLoad(L"canon.bmp");
  glGenTextures(1, &texture[6]); //
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture7->sizeX, texture7->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture7->data);
	//6
  texture6 = auxDIBImageLoad(L"verhroof.bmp");
  glGenTextures(1, &texture[5]); //
  glBindTexture(GL_TEXTURE_2D, texture[5]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture6->sizeX, texture6->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture6->data);
	//5
  texture5 = auxDIBImageLoad(L"zadroof1.bmp");
  glGenTextures(1, &texture[4]); //
  glBindTexture(GL_TEXTURE_2D, texture[4]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture5->sizeX, texture5->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture5->data);
	//4
  texture4 = auxDIBImageLoad(L"bokroof.bmp");
  glGenTextures(1, &texture[3]); //
  glBindTexture(GL_TEXTURE_2D, texture[3]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture4->sizeX, texture4->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture4->data);
	//3
  texture3 = auxDIBImageLoad(L"parket3.bmp");
  glGenTextures(1, &texture[2]); //
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture3->sizeX, texture3->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture3->data);
    //2
  texture2 = auxDIBImageLoad(L"parket2.bmp");
  glGenTextures(1, &texture[1]); //
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 4, texture2->sizeX, texture2->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2->data);
    //1
  texture1 = auxDIBImageLoad(L"parket1.bmp"); 
  glGenTextures(1, &texture[0]); //
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // GL_NEAREST
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
}

void InitLighting()
{
  GLfloat LightAmbient[4] = { 100.0, 100.0, 100.0, 100.0 };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);
  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
  glEnable(GL_LIGHT0);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, true);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.8);
}

void Outtext()
{
  char txt[64];
  static int flag = 0;

  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
  glTranslatef(1.0, 20.0, 0.0);
  glRotatef(90.0, 1.0, 0.0, 0.0);
  glScalef(1.3, 1.3, 1.0);
  if (language == 0)
  {
    DrawTextGL(-18.0, 30.0, "Настройки. Чтобы выйти в меню нажмите Т");
	if (flag == 0)
	  {
	    DrawTextGL(-31.0, 29.0, "Сколько возрождений маленьких ботов использовать в игре? Нажмите цифру от 1 до 7");
		if (keys['1'])
		{
		  ubvrg[0] = 1;
		  ubvrg[1] = 1;
		  DrawTextGL(15.0, 29.0, "1");
        }
		if (keys['2'])
		{
		  ubvrg[0] = 2;
	      ubvrg[1] = 2;
		  DrawTextGL(15.0, 29.0, "2");
		}
		if (keys['3'])
		{
		  ubvrg[0] = 3; 
		  ubvrg[1] = 3;
		  DrawTextGL(15.0, 29.0, "3");
		}
		if (keys['4'])
		{
		  ubvrg[0] = 4; 
		  ubvrg[1] = 4;
		  DrawTextGL(15.0, 29.0, "4");
		}
		if (keys['5'])
		{
		  ubvrg[0] = 5;
		  ubvrg[1] = 5;
		  DrawTextGL(15.0, 29.0, "5");
		}
		if (keys['6'])
		{
		  ubvrg[0] = 6;
		  ubvrg[1] = 6;
		  DrawTextGL(15.0, 29.0, "6");
		}
		if (keys['7'])
		{
		  ubvrg[0] = 7;
		  ubvrg[1] = 7;
		  DrawTextGL(15.0, 29.0, "7");
		}
		if (keys[VK_SPACE])
		{
		  flag = 1;
		  keys[VK_SPACE] = false;
		}
	 }  
	 if (flag == 1)
	 {
	    DrawTextGL(-31.0, 28.0, "Сколько маленьких ботов использовать в игре? Нажмите 1 или 2");
		if (keys['1'])
		{
		  ubvrg[0] = 0; DrawTextGL(15.0, 29.0, "1");
		}
		if (keys['2'])
			DrawTextGL(15.0, 29.0, "2");
		if (keys[VK_SPACE])
		{
		  flag = 2;
		  keys[VK_SPACE] = false;
		}
	  }
	  if (flag == 2)
	  {
	    DrawTextGL(-31.0, 27.0, "Сколько возрождений средних ботов использовать в игре? Нажмите цифру от 1 до 5");
		if (keys['1'])
		{
		  ubvrg[2] = 1;
		  ubvrg[3] = 1;
		  DrawTextGL(15.0, 29.0, "1");
		}
		if (keys['2'])
		{
		  ubvrg[2] = 2;
		  ubvrg[3] = 2; 
		  DrawTextGL(15.0, 29.0, "2");
		}
		if (keys['3'])
		{
		  ubvrg[2] = 3;
		  ubvrg[3] = 3;
		  DrawTextGL(15.0, 29.0, "3");
		}
		if (keys['4'])
		{
		  ubvrg[2] = 4;
		  ubvrg[3] = 4;
		  DrawTextGL(15.0, 29.0, "4");
		}
		if (keys['5'])
		{
		  ubvrg[2] = 5;
		  ubvrg[3] = 5;
		  DrawTextGL(15.0, 29.0, "5");
		}
		if (keys[VK_SPACE])
		{
		  flag = 3;
		  keys[VK_SPACE] = false;
		}
   	  }
   	  if (flag == 3)
	  {
	    DrawTextGL(-31.0, 26.0, "Сколько средних ботов использовать в игре? Нажмите 0,1 или 2");
		if (keys['0'])
		{
		  ubvrg[2] = 0; 
		  ubvrg[3] = 0; 
		  DrawTextGL(15.0, 29.0, "0");
		}
		if (keys['1'])
		{
		  ubvrg[3] = 0;
		  DrawTextGL(15.0, 29.0, "1");
		}
	    if (keys['2'])
		{
		  DrawTextGL(15.0, 29.0, "2");
	 	}
		if (keys[VK_SPACE])
		{
		  flag = 4;
		  keys[VK_SPACE] = false;
		}
 	  }
  	  if (flag == 4)
  	  {
	    DrawTextGL(-31.0, 25.0, "Сколько возрождений большого бота использовать в игре? Нажмите цифру от 1 до 6 или 0, если он не нужен");
		if (keys['0'])
		{
		  ubvrg[4] = 0;
		  DrawTextGL(15.0, 29.0, "0");
		}
		if (keys['1'])
		{
		  ubvrg[4] = 1; 
		  DrawTextGL(15.0, 29.0, "1");
		}
		if (keys['2'])
		{
		  ubvrg[4] = 2; DrawTextGL(15.0, 29.0, "2");
		}
		if (keys['3'])
		{
	  	  ubvrg[4] = 3;
		  DrawTextGL(15.0, 29.0, "3");
		}
		if (keys['4'])
		{
		  ubvrg[4] = 4;
		  DrawTextGL(15.0, 29.0, "4");
		}
	    if (keys['5'])
		{
		  ubvrg[4] = 5; 
		  DrawTextGL(15.0, 29.0, "5");
		}
		if (keys['6'])
		{
		  ubvrg[4] = 6;
		  DrawTextGL(15.0, 29.0, "6");
		}
		if (keys[VK_SPACE])
		{
		  keys['T'] = true;
		  keys[VK_SPACE] = false;
		}
	  }
	}
	else
	{
		DrawTextGL(-18.0, 30.0, "Меню");
		DrawTextGL(-18.0, 29.0, "Управление камерой");
		DrawTextGL(-20.0, 28.0, "Кнопка 1 - это обычный вид камеры. Танк стоит перед нами.");
		DrawTextGL(-20.0, 27.0, "Kнопка 2 - это обычный вид камеры. Вид с башни танка");
		DrawTextGL(-20.0, 26.0, "и мы можем увидеть общий вид танка.");
		DrawTextGL(-20.0, 25.0, "Кнопка 3 - это приближенный вид камеры с танка.");
		DrawTextGL(-20.0, 24.0, "Kнопка 4 - это вид карты лабиринта.");
		DrawTextGL(-20.0, 23.0, "Кнопка 1 дает переход на камеру 1.Кнопка 2 дает переход на камеру 2.");
		DrawTextGL(-20.0, 22.0, "Кнопка 3 дает переход на камеру 3.Кнопка 4 дает переход на камеру 4.");
		DrawTextGL(-20.0, 21.0, "Управление танком");
		DrawTextGL(-20.0, 20.0, "Кнопка вверх - это движение вперед. ");
		DrawTextGL(-20.0, 19.0, "Кнопка вниз - это движение назад.");
		DrawTextGL(-20.0, 18.0, "Кнопка налево - это движение налево.");
		DrawTextGL(-20.0, 17.0, "Кнопка направо - это движение направо.");
		DrawTextGL(-20.0, 16.0, "Кнопки А и D - это кнопки движения башни танка.");
		DrawTextGL(-20.0, 15.0, "P - ПАУЗА . ПРОБЕЛ - СТРЕЛЬБА ");
		DrawTextGL(-20.0, 14.0, "M и N - смена характеристик танка в гараже");
		DrawTextGL(-20.0, 13.0, "Смена ландшафта (полигон/болото) - L");
		DrawTextGL(-20.0, 12.0, "Удачной игры!");
	}

	melose = ubvrg[0] + ubvrg[1] + ubvrg[2] + ubvrg[3] + ubvrg[4];
	DrawTextGL(-1.0, 1.0, txt);
	//#endif
	glRotatef(-90.0, 1.0, 0.0, 0.0);


	glPopMatrix();
}
double func(double x, double z)
{
	double y;
	//y = 0.15 * sin(time(NULL) + x / 3.0f) + 0.15 * sin(time(NULL) + z / 1.0);
	y = 0.15 * sin(counter + x / 3.0f) + 0.15 * sin(counter + z / 1.0);
	return y;
}
void KeyInfo()
{// персонаж
	int sx = 1;
	int sz = 1;
	float x[4], z[4];
	if (keys[VK_UP])
	{
		if (tanketka == 1){
			me.x += 0.15 * cos(angle) * drprosses;
			me.z += 0.15 * sin(angle) * drprosses;
		}
		if (tanketka == 0){
			me.x += 0.05 * cos(angle) *  drprosses;
			me.z += 0.05 * sin(angle) *  drprosses;
		}
		 x[0] = cos(angle + 0.2) + me.x;
		z[0] = sin(angle + 0.2) + me.z;
		 x[1] = cos(angle - 0.2) + me.x;
		z[1] = sin(angle - 0.2) + me.z;
		 x[2] = -cos(angle + 0.2) + me.x;
		z[2] = -sin(angle + 0.2) + me.z;
		 x[3] = -cos(angle - 0.2) + me.x;
		z[3] = -sin(angle - 0.2) + me.z;

		// столбы
		int a = 0, i, m, j, n;
		for (int r = 0; r < 4; r++)
		    {
      i = x[0] / 2;
      m = x[1] / 2;
      j = z[0] / 2;
      n = z[1] / 2;
					if (a == 0)
            if ((labir[i][j] == 1) || (labir[i][j] == 4 || labir[m][n] == 1) || (labir[m][n] == 4))
						{
            sx = 2 * i;
							sz = 2 * j;
							if (
								(x[r] > 0 + sx) &&
								(x[r] < sx + 2.0) &&
								(z[r]> 0 + sz) &&
								(z[r] < sz + 2.0)
								)

							{
								if (tanketka == 1){
									me.x -= 0.15 * cos(angle) *  drprosses;
									me.z -= 0.15 * sin(angle) *  drprosses;
								}
								if (tanketka == 0){
									me.x -= 0.05 * cos(angle) * drprosses;
									me.z -= 0.05 * sin(angle) *  drprosses;
								}
								a = 1;
							}
					}
				}
	}
	if (keys[VK_DOWN])
	{
		if (tanketka == 1){
			me.x -= 0.17 * cos(angle) *drprosses;
			me.z -= 0.17 * sin(angle) * drprosses;
		}
		if (tanketka == 0){
			me.x -= 0.07 * cos(angle) *  drprosses;
			me.z -= 0.07 * sin(angle) *  drprosses;
		}
		x[0] = cos(angle + 0.2) + me.x;
		z[0] = sin(angle + 0.2) + me.z;
		x[1] = cos(angle - 0.2) + me.x;
		z[1] = sin(angle - 0.2) + me.z;
		x[2] = -cos(angle + 0.2) + me.x;
		z[2] = -sin(angle + 0.2) + me.z;
		x[3] = -cos(angle - 0.2) + me.x;
		z[3] = -sin(angle - 0.2) + me.z;
    int a = 0, i, m, j, n;
		for (int r = 0; r < 4; r++)
		{

      i = x[2] / 2;
      m = x[3] / 2;
      j = z[2] / 2;
      n = z[3] / 2;
					if (a == 0)
            if ((labir[i][j] == 1) || (labir[i][j] == 4 || labir[m][n] == 1) || (labir[m][n] == 4))
						{
							sx = 2 * i;
							sz = 2 * j;
							if (
								(x[r] > 0 + sx) &&
								(x[r] < sx + 2.0) &&
								(z[r]> 0 + sz) &&
								(z[r] < sz + 2.0)
								)

							{
								if (tanketka == 1){
									me.x += 0.17 * cos(angle) *  drprosses;
									me.z += 0.17 * sin(angle) *  drprosses;
								}
								if (tanketka == 0){
									me.x += 0.07 * cos(angle) *  drprosses;
									me.z += 0.07 * sin(angle) * drprosses;
								}
								a = 1;
							}
						}
				}

	}

	// поворот
	if (keys[VK_LEFT])
	{
		if (tanketka == 1){ angle -= 0.07 *  drprosses; angle2 -= 0.07 * drprosses; }
		if (tanketka == 0){ angle -= 0.03 * drprosses; angle2 -= 0.03 *  drprosses; }
		if (angle < 0.0)
			angle += 6.28;
		if (angle2 < 0.0)
			angle2 += 6.28;


	}
	if (keys[VK_RIGHT])
	{
		if (tanketka == 1){ angle += 0.07 *  drprosses; angle2 += 0.07 *  drprosses; }
		if (tanketka == 0){ angle += 0.03 * drprosses; angle2 += 0.03 *  drprosses; }
		if (angle > 6.28)
			angle -= 6.28;


		if (angle2 > 6.28)
			angle2 -= 6.28;


	}
	if (keys['A'])
	{
		angle2 -= 0.01 *  drprosses;
		if (angle2 < 0.0)
			angle2 += 6.28;
	}
	if (keys['D'])
	{
		angle2 += 0.01 *  drprosses;
		if (angle2 > 6.28)
			angle2 -= 6.28;
	}

	// движение камеры по вертикали
	//if (keys['W']) me.y += 1.0; 
	//	if (keys['S']) me.y -= 1.0;


	if (keys['L'])
	{
		l = 1 - l;
		keys['L'] = false;
	}
	if (garag == 1)	if (keys['M'])
	{
		gun = 1 - gun;
		if (gun == 0)ptr = ptrr;
		if (gun == 1)ptr = ptrp;
		p = 0;
		keys['M'] = false;
	}
	if (garag == 1)	if (keys['N'])
	{
		tanketka = 1 - tanketka;
	
		if (tanketka == 1)lm = 3;
		if (tanketka == 0)lm = 7;

		keys['N'] = false;
	}



	if (keys['1'])
	{
		kamera = 0;
	}
	if (keys['2'])
	{
		kamera = 1;
	}
	if (keys['3'])
	{
		kamera = 2;
	}
	if (keys['4'])
	{
		kamera = 3;
	}
	if (keys['0'])
	{
		kamera = 4;
		language = 0;
	}
	if (keys['5'])
	{
		kamera = 5;
		language = 1;
	}

	if (gun == 1)	if (keys[VK_SPACE])
	{
		if (p < ptr - 1)
		{
			xp[p] = me.x;
			zp[p] = me.z;
			vistrel[p] = 1;
			angle3[p] = angle2;
			p = p + 1;
		}
		keys[VK_SPACE] = false;
	}
	if (gun == 0)if (timer >= 100)	if (keys[VK_SPACE])
	{
		if (p < ptr - 1)
		{
			xp[p] = me.x;
			zp[p] = me.z;
			vistrel[p] = 1;
			angle3[p] = angle2;
			p = p + 1;
			timer = 0;
		}
		keys[VK_SPACE] = false;
	}
}
void Draw(HDC hDC)
{
	static int du[vragi] = { 0, 0, 0, 0, 0 }, dl[vragi] = { 0, 0, 0, 0, 0 }, dr[vragi] = { 0, 0, 0, 0, 0 }, dd[vragi] = { 0, 0, 0, 0, 0 }, pause = 0,
			r[vragi] = { 3, 3, 3, 3, 3 }, vx, vz, smotr = 80,
		ubilka[vragi] = { 0, 0, 0, 0, 0 }, sx = 1, sz = 1, 
		dviz[vragi] = { 1, 1, 1, 1, 1 }, lv[vragi] = { 3, 3, 7, 7, 10 }, vragvistr[vragi] = { 0, 0, 0, 0, 0 };
	static float  dx[vragi] = { 0, 0, 0, 0, 0 }, dz[vragi] = { 0, 0, 0, 0, 0 },
		ugle[vragi] = { 0.03, 0.03, 0.03, 0.03, 0.03 }, dvrag[vragi] = { 0, 0, 0, 0, 0 }, tr[vragi], ugle1[vragi], ugle2[vragi],
		vptrx[vragi], vptrz[vragi], povorot[vragi], xpvrg[vragi], zpvrg[vragi];
	
	if (keys[VK_ESCAPE])
	{
		PostQuitMessage(0);
	}
	if (pause == 0){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка
		glClearColor(0.0, 0.0, 0.2, 0.0); // цвет очистки экрана

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(30.0, smotr, 30.0,

			// смотрим в точку на плоскости лабиринта: мы + сдвиг по x и z
			30.0, 0.0, 30.0,

			0.0, 0.0, 30.0);
		glEnable(GL_ALPHA_TEST); // включаем режим тестирования прозрачности
		glEnable(GL_BLEND); // Разрешение прозрачности
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
glColor3f(0.0,0.0,0.0);
		glBegin(GL_POLYGON);
	 glVertex3f(-30, 9, 90);
	 glVertex3f(90, 9, 90);
      glVertex3f(90, 9, 0);
	 glVertex3f(-30, 9, 0);
		glEnd();
		Outtext();
		glDisable(GL_ALPHA_TEST); // выключаем режим тестирования прозрачности
		glDisable(GL_BLEND); // запрещение прозрачности
glEnable(GL_TEXTURE_2D); // Разрешение наложение текстуры
		glEnable(GL_LIGHTING);
		glBindTexture(GL_TEXTURE_2D, texture[27]);

		//вывод заставки
		glBegin(GL_QUADS); // начало рисования прямоугольника, z == const
		glTexCoord2f(1.0f, 0.0f); 
		        glVertex3f( -10, 10, 0 );
		glTexCoord2f(0.0f, 0.0f); 
	     	    glVertex3f( 0.5 * 130, 10, 0 );
		glTexCoord2f(-0.6f, 1.0f);
		        glVertex3f( 0.5 * 130, 10, 60 );
		glTexCoord2f(0.0f, 1.0f); 
		        glVertex3f( -10, 10, 60 );
        glEnd(); 
		//конец вывода заставки

		/*glBegin(GL_POLYGON);	glTexCoord2f(0.0f, 0.0f); glVertex3f(-15, 10, 60);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(75, 10, 60);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(75, 10, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-15, 10, 0);//1,7300884955752212389380530973451
	glEnd();*/	
		
	
		if (keys['S'])
		{
			pause = 1 - pause;
			keys['S'] = false;
		}	
			
		if (keys['Q'])
		{
			if (smotr ==80)
			smotr = -66;
			else  smotr = 80;
			language = 1;
			keys['Q'] = false;
		}
		if (keys['T'])
		{
			if (smotr == 80)
				smotr = -66;
			else  smotr = 80;
			language = 0;
			keys['T'] = false;
		}
	}
	if (keys['P']){
		
		pause = 1 - pause; 
		keys['P'] = false;}
	if (pause == 1){
		glEnd(); glEnable(GL_TEXTURE_2D); // Разрешение наложение текстуры
		glEnable(GL_LIGHTING); 
		const float a = 1.5707 / 1.5;  // 60 град
		const float b = 1.5707 / 3.0;   // 30 град
		const float k = 0.5;
		float u = 4.0;

		counter += 0.01;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка
		glClearColor(0.0, 0.0, 0.2, 0.0); // цвет очистки экрана

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if (kamera == 0){
			gluLookAt(me.x, 1.2, me.z,

				// смотрим в точку на плоскости лабиринта: мы + сдвиг по x и z
				me.x + look_x * cos(angle2), 0.0, me.z + look_z * sin(angle2),

				0.0, 1.0, 0.0); // вертикаль (верх - по оси y); эту часть обычно не надо менять

			// делаем шаг "назад", чтобы видеть себя, свой "затылок" - то есть отодвигаем сцену вперед
			glTranslatef(2.0 * cos(angle2), 0.0, 2.0 * sin(angle2));
		}
		if (kamera == 1){
			gluLookAt(me.x, 1.2, me.z,

				// смотрим в точку на плоскости лабиринта: мы + сдвиг по x и z
				me.x + look_x * cos(angle), 0.0, me.z + look_z * sin(angle),

				0.0, 1.0, 0.0); // вертикаль (верх - по оси y); эту часть обычно не надо менять

			// делаем шаг "назад", чтобы видеть себя, свой "затылок" - то есть отодвигаем сцену вперед
			glTranslatef(3.0 * cos(angle), 0.0, 3.0 * sin(angle));
		}
		if (kamera == 2){
			gluLookAt(me.x, 1.2, me.z,

				// смотрим в точку на плоскости лабиринта: мы + сдвиг по x и z
				me.x + look_x * cos(angle2), 0.0, me.z + look_z * sin(angle2),

				0.0, 1.0, 0.0); // вертикаль (верх - по оси y); эту часть обычно не надо менять

			// делаем шаг "назад", чтобы видеть себя, свой "затылок" - то есть отодвигаем сцену вперед
			glTranslatef(1.5 * cos(angle2), 0.0, 1.5 * sin(angle2));
		}
		if (kamera == 3){
			gluLookAt(30.0, 80.0, 30.0,

				// смотрим в точку на плоскости лабиринта: мы + сдвиг по x и z
				30.0, 0.0, 30.0,

				0.0, 0.0, -30.0); // вертикаль (верх - по оси y); эту часть обычно не надо менять
		}
		if (kamera == 4){
			gluLookAt(30.0, -80.0, 30.0,

				// смотрим в точку на плоскости лабиринта: мы + сдвиг по x и z
				30.0, 0.0, 30.0,

				.0, 0.0, 30.0); // вертикаль (верх - по оси y); эту часть обычно не надо менять


			// делаем шаг "назад", чтобы видеть себя, свой "затылок" - то есть отодвигаем сцену вперед
			//	glTranslatef(1.0 * cos(angle2), 0.0, 1.0 * sin(angle2));
		}
		if (kamera == 5){
			gluLookAt(30.0, -80.0, 30.0,

				// смотрим в точку на плоскости лабиринта: мы + сдвиг по x и z
				30.0, 0.0, 30.0,

				.0, 0.0, 30.0); // вертикаль (верх - по оси y); эту часть обычно не надо менять


			// делаем шаг "назад", чтобы видеть себя, свой "затылок" - то есть отодвигаем сцену вперед
			//	glTranslatef(1.0 * cos(angle2), 0.0, 1.0 * sin(angle2));

		}
		/*
		gluLookAt(0.0, 2.0, 0.0,

		1.0, 1.0, 1.0,

		0.0, 1.0, 0.0); */ // вертикаль (верх - по оси y); эту часть обычно не надо менять

		
		for (int i = 0; i < NX; i++)
			for (int j = 0; j < NZ; j++)
			{
			if (l == 0){
				glColor3f((float)(i + 1) / NX, (float)(j + 1) / NZ, 0.5);
				if ((i % 2 + j % 2 == 1)) glBindTexture(GL_TEXTURE_2D, texture[1]);
				else glBindTexture(GL_TEXTURE_2D, texture[1]);
				glBegin(GL_QUADS); // начало рисования прямоугольника, z == const
				glTexCoord2f(0.0f, 0.0f); glVertex3f(i*CX-30, func(i, j), j*CZ);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(i*CX - 30 + CX, func(i + 1, j), j*CZ);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(i*CX + CX - 30, func(i + 1, j + 1), j*CZ + CZ);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(i*CX - 30, func(i, j + 1), j*CZ + CZ);
				glEnd();
			}
			if (l == 1){
				glColor3f((float)(i + 1) / NX, (float)(j + 1) / NZ, 0.5);
				if ((i % 2 + j % 2 == 1)) glBindTexture(GL_TEXTURE_2D, texture[0]);
				else glBindTexture(GL_TEXTURE_2D, texture[0]);
				glBegin(GL_QUADS); // начало рисования прямоугольника, z == const
				glTexCoord2f(0.0f, 0.0f); glVertex3f(i*CX - 30, 0.0, j*CZ);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(i*CX + CX - 30, 0.0, j*CZ);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(i*CX + CX - 30, 0.0, j*CZ + CZ);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(i*CX - 30, 0.0, j*CZ + CZ);
				glEnd();
			}
			}

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);

		for (int i = 0; i < 30; i++)
			for (int j = 0; j < 30; j++)
			{
			if (labir[i][j] == 1){

				glColor3f(0.0, 0.0, 1.0);
				glLineWidth(3);

				Cube(i * 2, 0.0, j * 2, i * 2 + 2.0, 3.0, j * 2 + 2.0, 14, 14, 14, 14, 14, 14);

			}
			if (labir[i][j] == 2){
				glColor3f(100.0, 100.0, 100.0);
				glLineWidth(3);
				glBindTexture(GL_TEXTURE_2D, texture[12]);
				glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
				glEnable(GL_TEXTURE_2D); // Разрешение наложение текстуры
				glEnable(GL_LIGHTING);

				glBegin(GL_QUADS); // то же рисование пола, но без текстуры
				glTexCoord2f(0.0f, 0.0f); glVertex3f(i * 2 + 2.0, 0.0001, j * 2);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(i * 2 + 2.0, 0.0001, j * 2 + 2.0);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(i * 2, 0.0001, j * 2 + 2.0);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(i * 2, 0.0001, j * 2);
				glEnd();

			}
			if (labir[i][j] == 3){
				glColor3f(0.0, 0.0, 1.0);
				glLineWidth(3);
				Cube(i * 2, 0.0, j * 2, i * 2 + 2.0, 3.0, j * 2 + 2.0, 13, 13, 13, 13, 13, 13);

			}
			if (labir[i][j] == 4){

				glColor3f(0.0, 0.0, 1.0);
				glLineWidth(3);
				if (l == 1)	Cube(i * 2, 0.0, j * 2, i * 2 + 2.0, 3.0, j * 2 + 2.0, 10, 10, 10, 10, 10, 10);
				if (l == 0)	Cube(i * 2, 0.0, j * 2, i * 2 + 2.0, 3.0, j * 2 + 2.0, 23, 23, 23, 23, 23, 23);

			}
			}


		glEnable(GL_ALPHA_TEST); // включаем режим тестирования прозрачности
		glEnable(GL_BLEND); // Разрешение прозрачности
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
		KeyInfo();
		DrawMe(); 
		Outtext();
		garag = 0;
		DrawVrg();
		if (timer < 500) 
		  timer++;
		for (int iv = 0; iv < vragi; iv++)
		{
			if (ubvrg[iv] <= 0) { dviz[iv] = 0; vrg.x[iv] = -150; vrg.z[iv] = -150; }
			if (ubvrg[iv] == 0)lv[iv] = 0;
			if (vragvistr[iv] == 0)
			{
			  for (ugle[iv] = anglev1[iv] - 0.6; ugle[iv] < anglev1[iv] + 0.6; ugle[iv] = ugle[iv] + 0.03){
					vptrx[iv] = vrg.x[iv];
					vptrz[iv] = vrg.z[iv];
					for (tr[iv] = 0; tr[iv] < 60; tr[iv] = tr[iv] + 0.15)
					{
						vptrx[iv] += 0.15 * cos(ugle[iv]);
						vptrz[iv] += 0.15 * sin(ugle[iv]);
						for (int i = 0; i < 30; i++)
						{
							for (int j = 0; j < 30; j++)
							{
								if ((labir[i][j] == 1) || (labir[i][j] == 3) || (labir[i][j] == 4))
								{
									sx = 2 * i;
									sz = 2 * j;

									if ((vptrx[iv] > 0 + sx) &&
										(vptrx[iv] < sx + 2.0) &&
										(vptrz[iv]> 0 + sz) &&
										(vptrz[iv] < sz + 2.0))tr[iv] = 70;
								}
							}
						}
						if ((vptrx[iv] >  me.x - 0.2) &&
							(vptrx[iv] < me.x + 0.2) &&
							(vptrz[iv]> me.z - 0.2) &&
							(vptrz[iv] < me.z + 0.2)

							){
							vragvistr[iv] = 1; tr[iv] = 70; ugle1[iv] = ugle[iv]; ugle[iv] = anglev1[iv] + 1.6; ugle2[iv] = anglev[iv];
						}
					}
				}


				while
					((r[iv] != du[iv]) && (r[iv] != dd[iv]) && (r[iv] != dl[iv]) && (r[iv] != dr[iv]) )
				{
					vx = (int)(vrg.x[iv] / 2);
					vz = (int)(vrg.z[iv] / 2);
					if (labir[vx][vz + 1] == 0)
					  dr[iv] = 1;
					if (labir[vx + 1][vz] == 0)
					  dd[iv] = 3;
					if (labir[vx][vz - 1] == 0)
					  dl[iv] = 2;
					if (labir[vx - 1][vz] == 0)
					  du[iv] = 4;
					if ((dvrag[iv] == 40) || ((r[iv] != du[iv]) && (r[iv] != dd[iv]) && (r[iv] != dl[iv]) && (r[iv] != dr[iv])))
					{
						r[iv] = (int)(rand() * 4.0 / RAND_MAX) + 1;
					}
				}
				if (dvrag[iv] == 40)
				dvrag[iv] = 0;
				dvrag[iv] = dvrag[iv] + 1;
				if (r[iv] == 1)
				  if (lvrg[iv] == 3)
				  {
					dz[iv] = 0.15; 
					dx[iv] = 0.0; 
					anglev[iv] = 0.5 * PI;
					anglev1[iv] = anglev[iv]; 
				  }
				if (r[iv] == 2)
				  if (lvrg[iv] == 3)
				  { 
					dz[iv] = -0.15; 
					dx[iv] = 0.0; 
					anglev[iv] = 1.5* PI; 
					anglev1[iv] = anglev[iv]; }
				if (r[iv] == 3)if (lvrg[iv] == 3){ dz[iv] = 0.0; dx[iv] = 0.15; anglev[iv] = 2 * PI; anglev1[iv] = anglev[iv]; }
				if (r[iv] == 4)if (lvrg[iv] == 3){ dz[iv] = 0.0; dx[iv] = -0.15; anglev[iv] = PI; anglev1[iv] = anglev[iv]; }
				
				if (r[iv] == 1)if (lvrg[iv] != 3){ dz[iv] = 0.13; dx[iv] = 0.0; anglev[iv] = 0.5* PI; anglev1[iv] = anglev[iv]; }
				if (r[iv] == 2)if (lvrg[iv] != 3){ dz[iv] = -0.13; dx[iv] = 0.0; anglev[iv] = 1.5* PI; anglev1[iv] = anglev[iv]; }
				if (r[iv] == 3)if (lvrg[iv] != 3){ dz[iv] = 0.0; dx[iv] = 0.13; anglev[iv] = 2 * PI; anglev1[iv] = anglev[iv]; }
				if (r[iv] == 4)if (lvrg[iv] != 3){ dz[iv] = 0.0; dx[iv] = -0.13; anglev[iv] = PI; anglev1[iv] = anglev[iv]; }
				if (dviz[iv] == 1)  vrg.x[iv] += dx[iv]*drprosses;
				if (dviz[iv] == 1)  vrg.z[iv] += dz[iv] * drprosses;
			dr[iv] = 0;
			dl[iv] = 0;
			dd[iv] = 0;
			du[iv] = 0;
			}
			if (vragvistr[iv] == 1){
				xpvrg[iv] = vrg.x[iv];
				zpvrg[iv] = vrg.z[iv];
				povorot[iv] = 0.045;
				if (ugle1[iv] < anglev1[iv])povorot[iv] = -0.045;
				anglev[iv] = ugle2[iv];
				if (ugle1[iv] != anglev1[iv])anglev1[iv] = anglev1[iv] + povorot[iv];
				if ((ugle1[iv] - 0.02 <= anglev1[iv]) && (ugle1[iv] + 0.02 >= anglev1[iv]))vragvistr[iv] = 2;

			}
			if (vragvistr[iv] == 2){
				xpvrg[iv] += 1.0 * cos(ugle1[iv]), zpvrg[iv] += 1.0 * sin(ugle1[iv]);

				glColor3f(1, 0.0, 0.0);
				glBegin(GL_POLYGON);//patron
				glVertex3f(xpvrg[iv] - cos(ugle1[iv] + 1.5707)*0.05, 0.3, zpvrg[iv] - sin(ugle1[iv] + 1.5707)*0.05);
				glVertex3f(xpvrg[iv] + cos(ugle1[iv] + 1.5707)*0.05, 0.3, zpvrg[iv] + sin(ugle1[iv] + 1.5707)*0.05);
				glVertex3f(xpvrg[iv] + cos(ugle1[iv] + 1.5707)*0.05, 0.2 + 0.15, zpvrg[iv] + sin(ugle1[iv] + 1.5707)*0.05);
				glVertex3f(xpvrg[iv] - cos(ugle1[iv] + 1.5707)*0.05, 0.2 + 0.15, zpvrg[iv] - sin(ugle1[iv] + 1.5707)*0.05);
				glEnd();
				glBegin(GL_POLYGON);//patron
				glVertex3f(xpvrg[iv] - cos(ugle1[iv] + 0.07), 0.35, zpvrg[iv] - sin(ugle1[iv] + 0.07));
				glVertex3f(xpvrg[iv] + cos(ugle1[iv] + 0.07), 0.35, zpvrg[iv] + sin(ugle1[iv] + 0.07));
				glVertex3f(xpvrg[iv] + cos(ugle1[iv] + 1.5707)*0.05, 0.2 + 0.15, zpvrg[iv] + sin(ugle1[iv] + 1.5707)*0.05);
				glVertex3f(xpvrg[iv] - cos(ugle1[iv] + 1.5707)*0.05, 0.2 + 0.15, zpvrg[iv] - sin(ugle1[iv] + 1.5707)*0.05);
				glEnd();
				if ((xpvrg[iv] > 60.0) || (xpvrg[iv] < 0.0) || (zpvrg[iv]<0.0) || (zpvrg[iv]>60.0))vragvistr[iv] = 0;
				if ((xpvrg[iv] > me.x - 0.4) &&
					(xpvrg[iv] < me.x + 0.4) &&
					(zpvrg[iv]> me.z - 0.4) &&
					(zpvrg[iv] < me.z + 0.4)

					){
					if(lvrg[iv]==3)lm = lm - 1;
					if (lvrg[iv] == 7)lm = lm - 2;
					if (lvrg[iv] == 10)lm = lm - 5;
					glBegin(GL_POLYGON);//patron
					glVertex3f(xpvrg[iv] + 1.7, 1.35, zpvrg[iv] + 1.7);
					glVertex3f(xpvrg[iv] + 1.0, 1.35, zpvrg[iv] - 1.2);
					glVertex3f(xpvrg[iv] - 2.2, 0.2 + 0.15, zpvrg[iv] - 1.2);
					glVertex3f(xpvrg[iv] - 0.8, 0.2 + 0.15, zpvrg[iv] + 1.7);
					glEnd();
					glBegin(GL_POLYGON);//patron
					glVertex3f(xpvrg[iv] + 1.7, 2 * 1.35, zpvrg[iv] + 1.7);
					glVertex3f(xpvrg[iv] + 1.0, 2 * 1.35, zpvrg[iv] - 1.2);
					glVertex3f(xpvrg[iv] - 2.2, 0.2 + 0.15 - 0.2, zpvrg[iv] - 1.2);
					glVertex3f(xpvrg[iv] - 0.8, 0.2 + 0.15 - 0.2, zpvrg[iv] + 1.7);
					glEnd();
					glBegin(GL_POLYGON);//patron
					glVertex3f(xpvrg[iv] + 1.7, 2 * 1.35, zpvrg[iv] + 1.7);
					glVertex3f(xpvrg[iv] + 1.0, 2 * 1.35, zpvrg[iv] - 1.2);
					glVertex3f(xpvrg[iv] - 2.2,  0.35 - 0.2, zpvrg[iv] - 1.2);
					glVertex3f(xpvrg[iv] - 0.8,  0.35 - 0.2, zpvrg[iv] + 1.7);
					glEnd();
					glBegin(GL_POLYGON);//patron
					glVertex3f(xpvrg[iv] + 1.7, 2 * 1.35, zpvrg[iv] + 1.7);
					glVertex3f(xpvrg[iv] + 1.0, 0.0, zpvrg[iv] - 1.2);
					glVertex3f(xpvrg[iv] - 2.2, 0.35 - 0.2, zpvrg[iv] - 1.2);
					glVertex3f(xpvrg[iv] - 0.8, 2 * 1.3, zpvrg[iv] + 1.7);
					glEnd();
					xpvrg[iv] = -150.0;
					zpvrg[iv] = -150.0;
					if (lm <= 0){
						ubilkame = (int)(rand() * 4.0 / RAND_MAX);
						if (ubilkame == 0)me.x = 15, me.z = 5;
						if (ubilkame == 1)me.x = 45, me.z = 55;
						if (ubilkame == 2)me.x = 15, me.z = 55;
						if (ubilkame == 3)me.x = 45, me.z = 5;

						scv = scv + 1;
						if (tanketka == 1)lm = 3;
						if (tanketka == 0)lm = 7;
					}
				}
			}
		}
		//if (anglev!=ug)anglev=anglev+0.03
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 30; j++)
			{
				if (labir[i][j] == 2)
				{
					sx = 2 * i;
					sz = 2 * j;

					if ((me.x > 0 + sx) &&
						(me.x < sx + 2.0) &&
						(me.z> 0 + sz) &&
						(me.z < sz + 2.0))
					{
						p = 0; garag = 1;
					}
					for (int j = 0; j < ptr; j++)
						vr[g] = 0;

				}
			}
		}
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_COLOR);


		glDisable(GL_ALPHA_TEST); // выключаем режим тестирования прозрачности
		glDisable(GL_BLEND); // запрещение прозрачности

		float aaa;
		//	DrawMe();
		for (g = 0; g < p; g++)
		{
			if (vistrel[g] == 1)
			  xp[g] += 1.0 * cos(angle3[g]), zp[g] += 1.0 * sin(angle3[g]);
			aaa = 1.0 - 0.04*g;
			glColor3f(g*0.1, aaa, 0.0);

			glBegin(GL_POLYGON);//patron
			glVertex3f(xp[g] - cos(angle3[g] + 1.5707)*0.05, 0.3, zp[g] - sin(angle3[g] + 1.5707)*0.05);
			glVertex3f(xp[g] + cos(angle3[g] + 1.5707)*0.05, 0.3, zp[g] + sin(angle3[g] + 1.5707)*0.05);
			glVertex3f(xp[g] + cos(angle3[g] + 1.5707)*0.05, 0.35, zp[g] + sin(angle3[g] + 1.5707)*0.05);
			glVertex3f(xp[g] - cos(angle3[g] + 1.5707)*0.05,0.35, zp[g] - sin(angle3[g] + 1.5707)*0.05);
			glEnd();
			glBegin(GL_POLYGON);//patron
			glVertex3f(xp[g] - cos(angle3[g] + 0.07), 0.35, zp[g] - sin(angle3[g] + 0.07));
			glVertex3f(xp[g] + cos(angle3[g] + 0.07), 0.35, zp[g] + sin(angle3[g] + 0.07));
			glVertex3f(xp[g] + cos(angle3[g] + 1.5707)*0.05, 0.35, zp[g] + sin(angle3[g] + 1.5707)*0.05);
			glVertex3f(xp[g] - cos(angle3[g] + 1.5707)*0.05,  0.35, zp[g] - sin(angle3[g] + 1.5707)*0.05);
			glEnd();

			for (int i = 0; i < 30; i++)
				for (int j = 0; j < 30; j++)
				{
				  for (int iv = 0; iv < vragi; iv++)
				    {
					  if ((xp[g] >  vrg.x[iv] - 1.5) &&
						  (xp[g] < vrg.x[iv] + 1.5) &&
						  (zp[g]> vrg.z[iv] - 1.5) &&
						  (zp[g] < vrg.z[iv] + 1.5)){
					  if (vr[g] < 10)
					  {
						if (gun == 0)
					    { 
						  lv[iv] = lv[iv] - 3; Cube(xp[g] + 1.7, 0.0, zp[g] + 1.7, xp[g] - 2.2, 2.95, zp[g] - 1.2, 26, 26, 26, 26, 26, 26);
						}
						if (gun == 1)
						{
						  lv[iv] = lv[iv] - 1; Cube(xp[g] + 0.7, 1.0, zp[g] + 0.7, xp[g] - 1.2, 1.95, zp[g] - 0.2, 26, 26, 26, 26, 26, 26);
						}
						xp[g] = 150.0;
						zp[g] = 150.0;		
						if (((iv == 1 || 2) && (ubvrg[iv]>=1)) || ((iv == 3 || 4) && (ubvrg[iv]>=1)) || ((iv == 5) && (ubvrg[iv] >=1)))
						{
						  if (lv[iv] <= 0)
						  {
						    ubvrg[iv]--;
							ubilka[iv] = (int)(rand() * 4.0 / RAND_MAX);
							if (ubilka[iv] == 0)
							  vrg.x[iv] = 15, vrg.z[iv] = 5;
							if (ubilka[iv] == 1)
							  vrg.x[iv] = 45, vrg.z[iv] = 55;
							if (ubilka[iv] == 2)
							  vrg.x[iv] = 15, vrg.z[iv] = 55;
							if (ubilka[iv] == 3)
							  vrg.x[iv] = 45, vrg.z[iv] = 5;
							lv[iv] = lvrg[i];
							scm = scm + 1;
						   }
						   if (ubvrg[iv] <= 0) { dviz[iv] = 0; vrg.x[iv] = -150; vrg.z[iv] = -150; }
								
							}
						}

					}
				}
				if ((labir[i][j] == 1) || (labir[i][j] == 4))
				{
					sx = 2 * i;
					sz = 2 * j;
					if (
						(xp[g] > 0 + sx) &&
						(xp[g] < sx + 2.0) &&
						(zp[g]> 0 + sz) &&
						(zp[g] < sz + 2.0)
						)

					{
						if (vr[g] < 10){

							if (gun == 0){// lv = lv - 3; 
								Cube(xp[g] + 1.7, 0.0, zp[g] + 1.7, xp[g] - 2.2,  2.95, zp[g] - 1.2, 26, 26, 26, 26, 26, 26);
							}
							if (gun == 1){
								Cube(xp[g] + 0.7, 1.0, zp[g] + 0.7, xp[g] - 1.2, 1.95, zp[g] - 0.2, 26, 26, 26, 26, 26, 26);

							}
							vistrel[g] = 0;
							vr[g] = vr[g] + 1;
							if (labir[i][j] == 1)labir[i][j] = 0;
							xp[g] = 150.0;
							zp[g] = 150.0;

						}
					}
				}
				}
		}
	}
		SwapBuffers(wglGetCurrentDC()); // переключить буфер
	}
	LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam) // дескриптор окна, сообщение, два параметра сообщения
	{
		static HDC hdc;
		static HGLRC hGLRC;
		if (Message == WM_CREATE) // при создании окна создаем кнопки
		{
			prosses();
			hdc = GetDC(hwnd); // получить дескриптор окна
			SetWindowPixelFormat(hdc); // установить для него настройки
			hGLRC = wglCreateContext(hdc); // создать контекст OpenGL
			wglMakeCurrent(hdc, hGLRC); // сделать этот контекст OpenGL текущим
			glEnable(GL_DEPTH_TEST); // включаем режим тестирования глубины

			// включение освещения
			InitLighting();
			glEnable(GL_LIGHTING);
			// Загрузка шрифта
			InitFonts(hdc);
			// Загрузка текстур
			LoadGLTextures();
		}
		if (Message == WM_SIZE)
		{
			Resize(LOWORD(lparam), HIWORD(lparam));
		}
		if (Message == WM_PAINT)
		{

			Draw(hdc); // прикладная функция - рисование кадра
		}
		if (Message == WM_KEYDOWN)
		{
			keys[wparam] = true;
			// вперед и назад
		}
		if (Message == WM_KEYUP)
		{
			keys[wparam] = false;
		}
		if (Message == WM_LBUTTONDOWN)
		{
			mouse.down_x = LOWORD(lparam);
			mouse.down_y = HIWORD(lparam);
			mouse.down = 1;
		}
		if (Message == WM_MOUSEMOVE)
		{
			mouse.move_x = LOWORD(lparam);
			mouse.move_y = HIWORD(lparam);
			if (mouse.down == 1)
			{

				mouse.down_x = mouse.move_x;
				mouse.down_y = mouse.move_y;
			}
		}
		if (Message == WM_LBUTTONUP)
		{
			mouse.up_x = LOWORD(lparam);
			mouse.up_y = HIWORD(lparam);
			mouse.down = 0;
		}

		if (Message == WM_DESTROY) // если операционная система требует завершить работу (приняла нажатие Alt-f4, кнопки в заголовке и т.д.)
		{
			PostQuitMessage(0); // Сообщить операционной системе о нашем желании закрыть приложение
		}
		return DefWindowProc(hwnd, Message, wparam, lparam); // перед выходом вызвать стандартный обработчик не проработанных нами сообщений
	}