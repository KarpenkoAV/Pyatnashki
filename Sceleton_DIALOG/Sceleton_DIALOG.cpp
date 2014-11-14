// Sceleton_DIALOG.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Sceleton_DIALOG.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


// Forward declarations of functions included in this code module:
//ATOM				MyRegisterClass(HINSTANCE hInstance);
//BOOL				InitInstance(HINSTANCE, int);
//LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	DFunc(HWND, UINT, WPARAM, LPARAM);


static HWND hBut[16],hBt; //массив кнопок

static int mas[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0}; //массив чисел 0-15 (при отладке удобно заполнять)
static int n_block[16];//массив блокированных элементов
static int map_15[16]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,};//массив собранных и блокированных элементов
static int close_list[16];//массив закрытых при трассировке элементов
static int mass_a[4];//массив окружения элемента [0]=слева,[1]=справа,[2]=сверху,[3]=снизу (если рядом нет ячеек или блокированы, то содержит -1, если есть то номер ячейки)
int Min_F =100;//минимальная стоимость маршрута F

static int trassa[16];//массив точек маршрута
static Cell open_list[16];//массив открытых при трассировке элементов
char log_str[256] ="";
int Delay_time =400;//задержка мс




int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	//HACCEL hAccelTable;

	// Initialize global strings
/*	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SCELETON_DIALOG, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SCELETON_DIALOG));
*/
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP,DFunc);
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
//		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
//		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//
//	wcex.style			= CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc	= WndProc;
//	wcex.cbClsExtra		= 0;
//	wcex.cbWndExtra		= 0;
//	wcex.hInstance		= hInstance;
//	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SCELETON_DIALOG));
//	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
//	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SCELETON_DIALOG);
//	wcex.lpszClassName	= szWindowClass;
//	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//	return RegisterClassEx(&wcex);
//}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   HWND hWnd;
//
//   hInst = hInstance; // Store instance handle in our global variable
//
//   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	int wmId, wmEvent;
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	switch (message)
//	{
//	case WM_COMMAND:
//		wmId    = LOWORD(wParam);
//		wmEvent = HIWORD(wParam);
//		// Parse the menu selections:
//		switch (wmId)
//		{
//		case IDM_DIALOG:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd,DFunc);
//		break;
//		case IDM_ABOUT:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//		break;
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		// TODO: Add any drawing code here...
//		EndPaint(hWnd, &ps);
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}

// Message handler for about box.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//		{
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		break;
//	}
//	return (INT_PTR)FALSE;
//}
// Message handler for MyDialog.
INT_PTR CALLBACK DFunc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent,a,nBt,p1;//идентификаторы


	static HDC hDc;
	
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		 WriteLog(0);
		sprintf(log_str,"Start Programm ********************************************************************************\n"); //в лог файл
        WriteLog(1);

		hDc = GetDC(hDlg);
		for(a=0;a<16;a++)
		{
		hBut[a] = GetDlgItem(hDlg,1000+a);
		}
		srand(time(NULL));
		Mass_Init();
		Trasser_Init();
		Mass_Log();
	return (INT_PTR)TRUE;
	
	case WM_SHOWWINDOW://при выводе окна заполнить случайными числами
		//RanddomMass();
		ShowButton(hBut,mas);	
	break;


	case WM_COMMAND:
		wmId    = LOWORD(wParam); //Получение идентификатора ресурса с которым мы работаем
		wmEvent = HIWORD(wParam);//Получение события ресурса с которым производится работа
		switch (wmId)
		{
			case ID_MAIN_NEW://обработка нажатия кнопки меню "New" диалового окна
				sprintf(log_str,"-------------------------Start ID_MAIN_NEW -----------------------\n"); //в лог файл
                WriteLog(1);
				RanddomMass();
				Mass_Init();
				Trasser_Init();
				ShowButton(hBut,mas);
				Mass_Log();
				sprintf(log_str,"----------------------------End ID_MAIN_NEW -----------------------\n"); //в лог файл
                WriteLog(1);
			break;

			case ID_MAIN_GO://обработка нажатия кнопки меню "Go!!!" диалового окна 
			sprintf(log_str,"Start ID_MAIN_GO ----------------------------------------------------\n"); //в лог файл
            Trasser_Init();
			WriteLog(1);
			if(Make_Line_1())// Собрать 1-й ряд
			{
				Trasser_Init();
				if(Make_Line_2())// Собрать 2-й ряд
				{
					Trasser_Init();
					if(Make_Line_End())//остальные 2 ряда
						{
							MessageBoxA (NULL,(LPCSTR)"ПОЗДРАВЛЯЕМ!", (LPCSTR)"Цель достигнута!", MB_OK|MB_ICONINFORMATION);
							sprintf(log_str,"\n------------>>>>  SUCSESS !!!!!! <<<<<<<<<---------------------\n"); //в лог файл
							WriteLog(1);
						}
						else //остальные 2 ряда
						{
							MessageBoxA (NULL,(LPCSTR)"Несобираемая комбинация", (LPCSTR)"Окончание сборки", MB_OK|MB_ICONWARNING);
							sprintf(log_str,"\n------------>>>> not decided situation <<<<<<<<<---------------------\n"); //в лог файл
							WriteLog(1);
						}
				}
				else // Собрать 2-й ряд
						{
							MessageBoxA (NULL,(LPCSTR)"ГЛЮК", (LPCSTR)"Ошибка ряд 2 !",MB_OK|MB_ICONERROR);
							sprintf(log_str,"\n------------>>>>  ERROR !!!!!! <<<<<<<<<---------------------\n"); //в лог файл
							WriteLog(1);
						}
			}
			else // Собрать 1-й ряд
						{
							MessageBoxA (NULL,(LPCSTR)"ГЛЮК", (LPCSTR)"Ошибка ряд 1 !",MB_OK|MB_ICONERROR);
							sprintf(log_str,"\n------------>>>>  ERROR !!!!!! <<<<<<<<<---------------------\n"); //в лог файл
							WriteLog(1);
						}
			Mass_Log();//записать в лог состояния массивов
							
			sprintf(log_str,"End ID_MAIN_GO ----------------------------------------------------\n"); //в лог файл
            WriteLog(1);
			break;

			case ID_MAIN_TEST://обработка нажатия кнопки меню "test!!!" диалового окна 
			     WriteLog(0);
				 Mass_Log();
				 /*ZeroPositions(15);
				 SwapElements(15);*/
				 map_15[0]=0; map_15[1]=1;map_15[2]=2;map_15[3]=3;//map_15[4]=4;map_15[5]=5;map_15[6]=6;map_15[7]=7;//map_15[8]=8;map_15[12]=12;//map_15[13]=13;
				 Trasser_Init();
				 /*Set_ElementPosition(4,11);
				 Mass_Log();
				 Set_ElementPosition(3,3);*/
				// Make_Line_1();
				 Make_Line_2();
				 Make_Line_End();
			break;

			default:
				nBt = CheckButton(GetDlgItem(hDlg,wmId));
				if(nBt!=-1) //проверяем нажатый ресурс кнопка?
					{
						SwapElements(nBt);	//вызываем функцию обмена элемента с пустой ячейкой
					}
	        break;
		}
	  // break;
	break;
	case WM_CLOSE:
		//EndDialog(hDlg,LOWORD(wParam));
		DestroyWindow(hDlg);
		sprintf(log_str,"Finish Programm ********************************************************************************\n"); //в лог файл
        WriteLog(1);
	break;
	case WM_DESTROY:
		EndDialog(hDlg,LOWORD(wParam));
		PostQuitMessage(0);
    break;
	}
	return (INT_PTR)FALSE;
}

int CheckButton(HWND hResurs)
{
sprintf(log_str,"Start CheckButton \n"); //в лог файл
WriteLog(1);
	int  N_But = -1;

	for(int i=0;i<16;i++)
	{
	  if(hResurs==hBut[i])
		  N_But = i;
	}
sprintf(log_str,"Finish CheckButton \n"); //в лог файл
WriteLog(1);
	return  N_But;
}

void SwapElements(int num) //функция обмен местами элементов если пустая ячейка рядом
{
	sprintf(log_str,"Start SwapElements num=%d \n",num); //в лог файл
WriteLog(1);

int zero;
for(int _i=0;_i<16;_i++)
	{
		if(mas[_i]==0)
			zero = _i;
	}

if(num==zero+1||num==zero-1||num==zero-4||num==zero+4)//если рядом с элементом по адресу num находится пробел 
	{
		mas[zero]=mas[num];//записываем значение элемента в ячейку где был 0
		mas[num]=0;			//записываем 0 в ячейку где был элемент
	}
ShowButton(hBut,mas);

sprintf(log_str,"Finish SwapElements \n"); //в лог файл
WriteLog(1);
return;
}

void RanddomMass(void) //функция заполнения массива случайными числами
{
sprintf(log_str,"Start RanddomMass \n"); //в лог файл
WriteLog(1);

int i,j,element; 
bool flag = true;
for(i=0;i<16;i++)
			{
				while(flag)
				{
					flag=false;
					element = rand()%16;
					for(j=0;j<i;j++)
					{
						if(mas[j]==element)
						{
							flag=true;
							break;
						}
					}
				
				}
			  mas[i]=element;
			  flag=true;
			}
sprintf(log_str,"Finish RanddomMass \n"); //в лог файл
WriteLog(1);
return;
}

void ZeroPositions(int n) //функция сдвинуть пустую ячейку в любую нужную позицию
{
sprintf(log_str,"!!!--------Start ZeroPositions %d\n",n); //в лог файл
WriteLog(1);

	 int p_zero=FindElements(0);//находим адрес "0" в таблице
	 int _i;
	 /*static int patch[16];*/
		 
	 if(p_zero==n)//если ноль уже в нужной позиции то возврат
		 return;

	   Trasser_patch(p_zero,n);//создаем маршрут от положения 0 к указанной точке

	 for (_i=0;_i<16;_i++)//перебор точек маршрута
	 {
		 if(trassa[_i]!=-1)//если есть точка (число не равное -1)

		 {
			SwapElements(trassa[_i]);//меняем 0 с элементом маршрута
			Sleep(Delay_time);//задержка
		 }
	 }
Trasser_Init();
sprintf(log_str,"!!!--------Finish ZeroPositions %d\n",n); //в лог файл
WriteLog(1);	
return;
}

int FindElements(int D) //функция поиск позиции числа
{
	sprintf(log_str,"####### Start FindElements    %d\n",D); //в лог файл
WriteLog(1);
	int poz;
for(int _i=0;_i<16;_i++)
	{
		if(mas[_i]==D)
			poz = _i;
	}
sprintf(log_str,"####### Finish FindElements    %d\n",D); //в лог файл
WriteLog(1);
return poz;
}

void Trasser_patch(int start, int finish)//создаем машрут из точки А в точку В (алгоритм А*)***********************************************
{
sprintf(log_str,"<---->Start Trasser A=%d  B=%d\n",start,finish); //в лог файл
WriteLog(1);
	int rod = start; //начальный родитель - стартовая точка
	int old_rod = start;//предыдущий родитель - стартовая точка
	int count_rod =0;
	int _i;
	int direct =0; //количесво разрешенных направлений из данной точки
	int count_point=0;//счетчик точек маршрута
	int count_err=0;//счетчик зацикливания для ошибок;
	int n_step; //кол-во перемещений в данную точку из стартовой

	open_list[start].Poz =start; //позиция элемента
	open_list[start].G =0;//G = стоимость передвижения из стартовой точки A к данной клетке, следуя найденному пути к этой клетке.
						  //(будем считать что стоимость передвижения на 1 позицию =10)
	open_list[start].H =Steps(start,finish)*10;//H = примерная стоимость передвижения от данной клетки до целевой, то есть точки B. Она обычно является эвристической функцией.
											   //Стоимость H посчитана с помощью вычисления Манхеттенского расстояния к точке В, 
											   //двигаясь только по горизонтали и вертикали, игнорируя все препятствия на пути. 	
	open_list[start].F = open_list[start].G + open_list[start].H; //Стоимость F для каждой клетки вычисляется простым суммированием G и H.
	//open_list[start].Dst = abs(finish-start); //разность между начальной точкой и конечной

	for(_i=0;_i<16;_i++)//добавление в закрытый список элементов из списка блокировки 
	{
		if(n_block[_i]==_i)//если позиция списка блокировки содержит номер позиции (-1 значит не блокирован)
		close_list[_i]=_i;//добавляем его в закрытый список
	}

	open_list[finish].Poz =finish;//добавим в открытый список конечную точку
	open_list[finish].H =-1;//инициализация финишной точки, чтобы мы могли войти в цикл

	while(open_list[finish].H!=0) //строим маршрут пока не достигли конечной точки т.е при H=0 мы находимся в кон. точке
	{
		direct =Trasser_Area(rod);//формируем масив mass_a окружения родительской точки и определяем число направлений из родительской точки
		close_list[rod] =rod; //заносим стартовую точку в закрытый список
		
		for(_i=0;_i<4;_i++)//заполняем open_list исходя из массива окружения родителя
		{
			n_step =10;//инициализация стомости перехода на 1 шаг
			int _ar = mass_a[_i];//сохраняем элемент окружения в open_list  (в этом массиве [0] -точка справа [1]-точка слева [2]-точка сверху [3]-точка снизу)
				if( _ar!=-1)//если элемент = -1 то соседней точки с какой либо стороны нет либо она заблокирована в close_list
				{
					open_list[_ar].Poz =_ar; //позиция элемента
			
					for(int _c=0;_c<16;_c++) //сканируем уже созданную часть маршрута и считаем сколько ячеек мы уже прошли
					{
						if(trassa[_c]!=-1)
							n_step=n_step+10;//определим стоимость передвижения из одной ячейки =10 и будем ее накапливать
					}
					open_list[_ar].G =n_step; //заносим стоимость перемещения из стартовой в эту ячейку
					open_list[_ar].H =((Steps(_ar,finish))*10);//заносим стоимость перемещения из данной ячейки в конечную
					open_list[_ar].F = open_list[_ar].G + open_list[_ar].H;//вычисляем F=G+H;
					open_list[_ar].Direct = direct;//записываем кол-во разрешенных направлений из родительской точки;
				}
		}
		old_rod = rod;
        rod = Trass_Parent(rod);//получаем родителя 

		if(count_point<16&&old_rod!=rod)//если счетчик циклов не превышает размер массива маршрута и старый и новый родители не совпадают
		{
			trassa[count_point]=rod;//записываем точку маршрута в массив
			count_point=count_point+1;//увеличиваем счетчик точек маршрута
			Min_F=100;
		}
		if(old_rod==rod)//если  старый и новый родители совпадают будем их подсчитывать
		   count_rod=count_rod+1;
		if(count_rod==10)
		{	
			sprintf(log_str,"<!!!!!!!!>Trable Parent=%d  Trasser A=%d  B=%d\n",rod,start,finish); //в лог файл
            WriteLog(1);
			Mass_Log();//сохраняем массивы
			//Trasser_Init();//сбрасываем массивы
			//sprintf(log_str,"<\n--------Restart Mass--------Блок Trasser---\n"); //в лог файл
   //         WriteLog(1);
			//Mass_Log();//сохраняем массивы
			//MessageBoxA (NULL,(LPCSTR)"Тупик по родителю", (LPCSTR)"Блок Trasser", MB_OK|MB_ICONERROR);
		    break;
		}

		if(count_err==100)//блок контроля ошибок
		{
			MessageBoxA (NULL,(LPCSTR)"Зацикливание", (LPCSTR)"Блок Trasser", MB_OK|MB_ICONERROR);
			break;
		}
		if(count_point>=16)//блок контроля ошибок
		{
			MessageBoxA (NULL,(LPCSTR)"Переполнение trassa", (LPCSTR)"Блок Trasser", MB_OK|MB_ICONERROR);
			break;
		}
	}//End while

sprintf(log_str,"<----> End Trasser A=%d  B=%d\n",start,finish); //в лог файл
WriteLog(1);
return;
}

int Trass_Parent(int parent) //функция установки новой точки родителя *************************************************************
{
sprintf(log_str,"+++++Start Trasser_Parent =%d \n",parent); //в лог файл
WriteLog(1);
	int _i,el;

	//int Min_dist = 16;//номер элемента с минимальным F (инициализация вне области)


	for(_i=0;_i<4;_i++)
	{
		el = mass_a[_i];
		if(el!=-1)
		{
				 sprintf(log_str,"<--------------------open_list___---------------->open_list poz=%d  Direct=%d   F =%d  G =%d H=%d \n",open_list[el].Poz,open_list[el].Direct,open_list[el].F,open_list[el].G,open_list[el].H); //в лог файл
                 WriteLog(1);
			if (Min_F >=open_list[el].F)
			{
			/*	 if(Min_H >=open_list[el].H)
					Min_H = open_list[el].H;*/

				 if(open_list[el].Direct!=0)//исключаем напрвления с тупиками
				{
			       Min_F =  open_list[el].F;
				   parent =  open_list[el].Poz; 
				  
				}
			}
		}
	}
	sprintf(log_str,"+++++End Trasser_Parent =%d \n",parent); //в лог файл
    WriteLog(1);
	return  parent;
}

bool Check_Block_Position(int p)//проверка заблокирована ли данная позиция в массиве блокированных элементов n_block
{
	bool result=false;//не блокирован
	for(int _i=0;_i<16;_i++)
	{
		if(p==_i&&p==close_list[_i])//проверяем значение в закрытом списке (если заблокирован то элемен массива содержит этот индекс=р)
		result=true;//блокирован
	}
return result;
}

int Trasser_Area(static int aa)
{
sprintf(log_str,">>>>>>>>>>>>>>>>>>>>>>>Start Trasser_Area =%d \n",aa); //в лог файл
WriteLog(1);
	int d=0;//кол-во направлений из этой точки
	int _r;
	if((aa-1)/4==(aa/4))//есть ли рядом слева элемент на той же строке
	{
		if(!Check_Block_Position(aa-1))//если элемент слева не блокирован
	       mass_a[0]=aa-1; //записываем он не блокирован
		else 
		   mass_a[0]=-1;  //не записываем, он блокирован
	}
	else
    mass_a[0] =-1;//елемента слева нет он за левой границей 

	if((aa+1)<=15&&(aa+1)/4==aa/4)//есть ли рядом справа элемент на той же строке
	{
		if(!Check_Block_Position(aa+1))//если элемент справа не блокирован
		  mass_a[1]=aa+1; //записываем он не блокирован
		else
		  mass_a[1]=-1;	 //не записываем, он блокирован		  	
	}
	else
    mass_a[1] =-1;//елемента справа нет он за правой границей 
	
	if((aa-4)>=0)//есть ли над этим элементом элемент выше
	{
		if(!Check_Block_Position(aa-4))//если элемент сверху не блокирован
			mass_a[2]=aa-4;//записываем он не блокирован
		else
			mass_a[2]=-1;	 //не записываем, он блокирован	
	}
	else
    mass_a[2] =-1;//елемента сверху нет он за верхней границей 

	if((aa+4)<=15)//есть ли над этим элементом элемент ниже
	{
		if(!Check_Block_Position(aa+4))//если элемент снизу не блокирован
			mass_a[3]=aa+4;//записываем он не блокирован
		else
			mass_a[3]=-1;	 //не записываем, он блокирован	
	}
	else
    mass_a[3] =-1;//елемента снизу нет он за нижней границей 

	for(_r=0;_r<4;_r++)//подсчет числа направлений
	{
     if(mass_a[_r]!=-1)
		 d=d+1;
	}
	sprintf(log_str,"<<<<<<<<<<<<<<<<<<<End Trasser_Area Direct=%d \n",d); //в лог файл
    WriteLog(1);
	return d;
}

int Steps(int a1, int a2)//подсчет числа шагов к от одной точки к другой
{
	sprintf(log_str,"____Start Steps a1=%d a2=%d \n",a1,a2); //в лог файл
    WriteLog(1);
	int step=0, tmp;
	int count_err=0; //счетчик зацикливания для ошибок
	if (a2<a1)
	{
		tmp=a2;
		a2=a1;
		a1 =tmp;
	}
		while(a1!=a2)
		{
			if(a2>a1&&a1/4!=a2/4) //если а2 больше а1 и они в разных строках
			{
				a1=a1+4;//переходим на другую строку
				step=step+1;//делаем шаг
			}
			if(a2>a1&&a1/4==a2/4) //если а2 больше а1 и они в одной строке
			{
				a1=a1+1;//переходим на другую ячейку
				step=step+1;//делаем шаг
			}
			if(a2<a1)
			{
				a1=a1-1;
				step=step+1;
			}

			if(count_err==1000)//блок контроля ошибок
			{
			MessageBoxA (NULL,(LPCSTR)"Зацикливание", (LPCSTR)"Блок Steps", MB_OK|MB_ICONERROR);
			break;
			}
			count_err=count_err+1;
		}
	sprintf(log_str,"____End Steps step=%d \n",step); //в лог файл
    WriteLog(1);
return step;
}

void Trasser_Init(void) //инициализация массивов для трассера
{
    sprintf(log_str,"******Start Trasser_Init \n"); //в лог файл
    WriteLog(1);
 for(int _i=0;_i<16;_i++)//инициализация массивов (-1)
	{
	close_list[_i]=-1;
	if(map_15[_i]==_i)//если в массиве собр элементов уже есть элемент то переносим его в в закрытый лист
		close_list[_i]=_i;//переносим элемент из массива сборки в массив закрытых при трассировке элементов

	if(n_block[_i]==_i)//если в массиве блокировок уже есть элемент то переносим его в закрытый лист
		close_list[_i]=_i;//переносим элемент из массива блокировки в массив закрытых при трассировке элементов
	
	trassa[_i] =-1;//массив точек маршрута
				//обнуляем массив открытый список точек
	open_list[_i].F =0;
	open_list[_i].G =0;
	open_list[_i].H =0;
	open_list[_i].Poz =0;
	}
    Min_F =100;
 //mass_a{0};//массив окружения элемента
	sprintf(log_str,"*******End Trasser_Init \n"); //в лог файл
    WriteLog(1);
return;
}

void Mass_Init(void) //инициализация основных массивов
{
sprintf(log_str,"*******Start Mass_Init \n"); //в лог файл
WriteLog(1);
 for(int _i=0;_i<16;_i++)//инициализация массивов (-1)
	{
	map_15[_i] =-1; //массив сборки элементов
	n_block[_i]=-1; //массив блокированных элементов
	}
sprintf(log_str,"********End Mass_Init \n"); //в лог файл
WriteLog(1);
return;
}

void Set_ElementPosition(int number,int ni) //Поставить число в нужную позицию
{
sprintf(log_str,">>>>Start Set_ElementPosition Element=%d on position =%d \n", number,ni); //в лог файл
WriteLog(1);

int poz_munber;
int n_column = ni%4;//вычисляем номер колонки для позиции
int n_line = ni/4;//вычисляем номер строки для позиции
int  el_column;//номер колонки для элемента
int  el_line;//номер строки для элемента
int count_err=0; //счетчик зацикливания для ошибок
poz_munber =  FindElements(number);

if (ni==poz_munber)//если элемент на месте то возврат
	return;

while(ni!=poz_munber)//выполняем пока не достигли нужной позиции
{
  el_column = poz_munber%4;//вычисляем номер колонки для элемента
  el_line   = poz_munber/4;//вычисляем номер строки для элемента

	if(el_column<n_column)//если позиция элемента слева от нужной колонки
	{
			close_list[poz_munber]=poz_munber;//блокируем эту точку перед позиционированием пробела
			ZeroPositions(int(poz_munber+1));//устанавливаем пустую клетку справа
			SwapElements(poz_munber); //меняем местами с пустой клеткой
			Sleep(Delay_time);//задержка
			close_list[poz_munber]=-1;//снимаем блокировку точки после позиционирования пробела
	}
	
	if(el_column>n_column)//если позиция элемента справа от нужной колонки
	{
		close_list[poz_munber]=poz_munber;//блокируем эту точку перед позиционированием пробела
		ZeroPositions(int(poz_munber-1));//устанавливаем пустую клетку слева
		SwapElements(poz_munber); //меняем местами с пустой клеткой
		Sleep(Delay_time);//задержка
		close_list[poz_munber]=-1;//снимаем блокировку точки после позиционирования пробела
	}

	if((el_column==n_column)&&(el_line>n_line))//если элемент находится в колонке но его позиция ниже нужной строки
	{
		close_list[poz_munber]=poz_munber;//блокируем эту точку перед позиционированием пробела
		ZeroPositions(int(poz_munber-4));//устанавливаем пустую клетку сверху
		SwapElements(poz_munber); //меняем местами с пустой клеткой
		Sleep(Delay_time);//задержка
		close_list[poz_munber]=-1;//снимаем блокировку точки после позиционирования пробела
	}
	if((el_column==n_column)&&(el_line<n_line))//если элемент находится в колонке но его позиция выше нужной строки
	{
		close_list[poz_munber]=poz_munber;//блокируем эту точку перед позиционированием пробела
		ZeroPositions(int(poz_munber+4));//устанавливаем пустую клетку снизу
		SwapElements(poz_munber); //меняем местами с пустой клеткой
		Sleep(Delay_time);//задержка
		close_list[poz_munber]=-1;//снимаем блокировку точки после позиционирования пробела
	}

	if(count_err==1000)//блок контроля ошибок
	{
		MessageBoxA (NULL,(LPCSTR)"Зацикливание", (LPCSTR)"Блок Set_ElementPosition", MB_OK|MB_ICONERROR);
		break;
	}
	Trasser_Init();//инициализация массивов трассировки
	poz_munber =  FindElements(number);
	count_err=count_err+1;
}
sprintf(log_str,"<<<<<Finish Set_ElementPosition Element=%d on position =%d \n", number,ni); //в лог файл
WriteLog(1);
	return;
}

void WriteLog(int r)
{
	FILE *file;
char* file_name = "log_15.log";
char load_string[50] = "none";
if(r==0)
{
file = fopen( file_name, "w" ); 
fputs( "", file );
}
if(r==1)
{
file = fopen( file_name, "a" ); 
fputs( log_str, file );
}

fclose( file );

return;
}

void Mass_Log(void)//сохранение массивов в лог файле
{
	int _i;
	sprintf(log_str,"------->mas------------------------------------\n"); //в лог файл
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=%d   ",_i,mas[_i]); //в лог файл
		WriteLog(1);
	}
	sprintf(log_str,"\n------->n_block-------------------------------\n"); //в лог файл
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=%d   ",_i,n_block[_i]); //в лог файл
		WriteLog(1);
	}
	sprintf(log_str,"\n------->map15----------------------------------\n"); //в лог файл
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=%d   ",_i, map_15[_i]); //в лог файл
		WriteLog(1);
	}
	sprintf(log_str,"\n------->trassa----------------------------------\n"); //в лог файл
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=%d   ",_i,trassa[_i]); //в лог файл
		WriteLog(1);
	}
	sprintf(log_str,"\n------->close_list------------------------------\n"); //в лог файл
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=%d   ",_i,close_list[_i]); //в лог файл
		WriteLog(1);
	}
	sprintf(log_str,"\n------->open_list-------------------------------\n"); //в лог файл
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=(Direct=%d, F=%d, G=%d, H=%d)   ",_i,open_list[_i].Direct, open_list[_i].F,open_list[_i].G,open_list[_i].H ); //в лог файл
		WriteLog(1);
	}
	return;
}

bool Make_Line_1(void)
{
	static int coun_er=0;
	static bool result = false;
	Trasser_Init();//инициализация массивов
	if(mas[0]==1 && mas[1]==2 && mas[2]==3 && mas[3]==4)//если 1,2,3,4  на свойх местах то нам повезло
	{
		map_15[0]=0;map_15[1]=1;map_15[2]=2;map_15[3]=3;//блокируем весь ряд он сложен
        return true; //возвращаемся нам повезло!!!!
	}
			//сборка 1-го ряда **************************************************************************************
						
				Set_ElementPosition(1,0);
				if(mas[0]==1)
					map_15[0]=0; //блокируем ячейку 0 (с цифрой 1)
				Trasser_Init();
				Set_ElementPosition(2,1);
				if(mas[1]==2)
					map_15[1]=1; //блокируем ячейку 1 (с цифрой 2)
				Trasser_Init();
				if(mas[0]==1&&mas[1]==2)//Если первая и вторя ячейка на месте
				{
					
L1:					if(mas[2]==4)//Если цифра 4 случайно была установлена на позицию 2 тогда сдвигаем ее в поз 11, если этого не сделать, то она заблокируется в ряду и ее невозможно будет вынуть
					Trasser_Init();
					Set_ElementPosition(4,11);	

					Set_ElementPosition(3,3);
					if(mas[3]==3)//Если ячейка 3 на месте
						map_15[3]=3; //блокируем ячейку 3 (с цифрой 3)
					Trasser_Init();
				
					Set_ElementPosition(4,7);//ставим 4 в ячейку 7
					if(mas[7]==4)
						map_15[7]=7; //блокируем ячейку 7 (с цифрой 4)
					Trasser_Init();

					if((mas[3]==3)&&(mas[7]==4))
					{
						ZeroPositions(2);//ставим пустую ячейку на ячейку 2
						map_15[3]=-1; //снимаем блокировку с ячейки 3 (с цифрой 3)
						map_15[7]=-1; //снимаем блокировку с ячейки 7 (с цифрой 4)
						Trasser_Init();
						SwapElements(3);//ставим  3 в ячейку 2
						Sleep(Delay_time);//задержка
						SwapElements(7);//ставим  4 в ячейку 3
						Sleep(Delay_time);//задержка
						if((mas[2]==3)&&(mas[3]==4))//если 3 и 4 в своих ячейках
							{
							map_15[2]=2; //блокируем ячейку 2 (с цифрой 3)
							map_15[3]=3; //блокируем ячейку 3 (с цифрой 4)
							Trasser_Init();
							}
						else
							{
							map_15[2]=-1; //разблокируем ячейку 2 (с цифрой 3)
							map_15[3]=-1; //разблокируем ячейку 3 (с цифрой 4)
							Trasser_Init();
							goto L1;
							}
						
					}
				}
				Trasser_Init();
				result=true;
			sprintf(log_str,"\n------------>>>>  1-st row is built ! <<<<<<<<<---------------------\n"); //в лог файл
            WriteLog(1);
			
return result;
}

bool Make_Line_2(void)
{
	static int coun_er=0;//счетчик зацикливания
	static bool result=false;
L0:	if(mas[4]==5 && mas[5]==6 && mas[6]==7 && mas[7]==8)//если элементы 5,6,7,8 на свойх местах
	{
		map_15[4]=4;map_15[5]=5;map_15[6]=6;map_15[7]=7;//блокируем весь ряд, он сложен
        return true; //возвращаемся нам повезло!!!!
	}
	     Trasser_Init();//инициализация массивов
		//сборка 2-го ряда *******************************************************
	   //      
			 //while(mas[4]!=5 && mas[5]!=6 && mas[6]!=7 && mas[7]!=8)//выполняем пока элементы 5,6,7,8 не будут на свойх местах
			 //{
L2:			Set_ElementPosition(5,4);
				if(mas[4]==5)
					map_15[4]=4; //блокируем ячейку 4 (с цифрой 5)
				Trasser_Init();
				Set_ElementPosition(6,5);
				if(mas[5]==6)
					map_15[5]=5;//блокируем ячейку 5 (с цифрой 6)
				Trasser_Init();
				if(mas[4]==5 && mas[5]==6)//Если цифра 5 и 6 на месте то далее
				{
L3:	 			Set_ElementPosition(7,7);
					if(mas[7]==7)
					   map_15[7]=7;//блокируем ячейку 7 (с цифрой 7)
					Trasser_Init();
					if(mas[6]==8)//Если цифра 8 случайно была установлена на позицию 6 тогда сдвигаем ее в поз 8, если этого не сделать, то она заблокируется в ряду и ее невозможно будет вынуть
					{
						map_15[6]=-1;
						map_15[7]=-1;
						Trasser_Init();
						Set_ElementPosition(8,14);
						goto L3;//переход на позиционирование цифры 7 в ячейку 7
					}
									
					Set_ElementPosition(8,11);//ставим 8 в ячейку 11
					if(mas[11]==8)
					 map_15[11]=11;//блокируем ячейку 11 (с цифрой 8)
					Trasser_Init();
						ZeroPositions(6);//ставим пустую ячейку на ячейку 6 //потом будем менять местами соседние ячейки
						map_15[7]=-1; //снимаем блокировку с ячейки 7 (с цифрой 7)
						map_15[11]=-1; //снимаем блокировку с ячейки 11 (с цифрой 8)
						Trasser_Init();
						SwapElements(7);//ставим  7 в ячейку 6
						Sleep(Delay_time);//задержка
						SwapElements(11);//ставим  8 в ячейку 7
						Sleep(Delay_time);//задержка
						if((mas[6]==7)&&(mas[7]==8))//если 7 и 8 в своих ячейках
							{
							map_15[6]=6; //блокируем ячейку 6 (с цифрой 7)
							map_15[7]=7; //блокируем ячейку 7 (с цифрой 8)	
							}
						Trasser_Init();
				}
				if(mas[4]==5&& mas[5]==6&& mas[6]==7&& mas[7]==8)// если все элементы на месте
					result =true;
				else
				{
					Mass_Log();//запись состояния массивов в лог
					map_15[4]=-1;map_15[5]=-1;map_15[6]=-1;map_15[7]=-1;//снимаем блокировку с элементов строки
					Trasser_Init();
					goto L2;//переход на начало сборки
				}

				coun_er=coun_er+1;//увеличиваем счетчик ошибок
				if(coun_er>=10)
				{	
					if(coun_er>=100)//если серьезная проблема то выход
					{
						Mass_Log();//запись состояния массивов в лог
						MessageBoxA (NULL,(LPCSTR)"Зацикливание строка 2", (LPCSTR)"Блок Make_Line_2", MB_OK|MB_ICONERROR);
						result =false;
					}
					goto L0;//пытаемся пройти снова
				}
			//}//end while
			sprintf(log_str,"\n------------>>>>  2-st row is built ! <<<<<<<<<---------------------\n"); //в лог файл
            WriteLog(1);
			
return result;
}

bool Make_Line_End(void)//Функция сборки элементов
{
		bool result=false;
	
  		//map_15[8]=-1; map_15[12]=-1;map_15[9]=-1; map_15[10]=-1;map_15[11]=-1; map_15[13]=-1;map_15[14]=-1; map_15[15]=-1; //снимаем блокировку с области
		
		int count_err1=0;//счетчик зацикливания
		int count_err2=0;//счетчик зацикливания
		//сборка остальных позиций *******************************************************
L4:		 if(mas[8]==9&&mas[9]==10&&mas[10]==11&&mas[11]==12&&mas[12]==13&&mas[13]==14&&mas[14]==15)// Если в раскладке числа 8-15 в ячейках 9-15 т.е не на своих местах
			return true; //если все цифры на местах  возвращаемся 
		 if(mas[8]==9&&mas[9]==10&&mas[10]==11&&mas[11]==12&&mas[12]==13&&mas[13]==15&&mas[14]==14)// Если в раскладке числа 8-15 в ячейках 9-15 т.е не на своих местах
			return false; //нерешаемая комбинация	
		 Trasser_Init();
		
		if(!(mas[8]==9&&mas[12]==13))// Если в раскладке числа 9 и 13 в ячейках 8 и 12 т.е не на своих местах
		{
				   if(!(mas[15]==9&&(mas[10]==13||mas[11]==13)))//проверка на блокированную расстановку
				   {
					   Set_ElementPosition(9,15);//ставим 9 в ячейку 15 (правый нижний угол)
					   map_15[15]=15; // блокируем  ячейку 15 (с цифрой 9)
					   Trasser_Init();
					   if(mas[15]==9&&(mas[10]==13||mas[11]==13))//проверка на блокированную расстановку после позиционирования 9 в ячейку 15
							goto L4;
					   Set_ElementPosition(13,8);//ставим 13 в ячейку 8 (место 9)
					   map_15[8]=8; // блокируем  ячейку 8 (с цифрой 13)
					   Trasser_Init();
					   Set_ElementPosition(9,9);//ставим 9 в ячейку 9 (место 10)
					   map_15[15]=-1; // разблокируем  ячейку 15 
					   map_15[8]=-1; // разблокируем  ячейку 8 (с цифрой 13)
					   Trasser_Init();
					   ZeroPositions(12);
					   SwapElements(8);
					   Sleep(Delay_time);//задержка
					   SwapElements(9);
					   Sleep(Delay_time);//задержка
					   map_15[8]=8; //блокируем ячейку 8 (с цифрой 9)
					   map_15[12]=12; //блокируем ячейку 12 (с цифрой 13)
					   Trasser_Init();
				   }

				   else
				   {
					map_15[15]=-1; //разблокируем ячейку 15 (с цифрой 9)
				    Trasser_Init();
					Set_ElementPosition(13,8);//ставим 13 в ячейку 8 (место 9)
					map_15[8]=8; //блокируем ячейку 8 (с цифрой 13)
					Set_ElementPosition(9,9);//ставим 9 в ячейку 9 (место 10)
					map_15[9]=9; // блокируем  ячейку 15 (с цифрой 9)
					ZeroPositions(12);
					map_15[8]=-1;map_15[9]=-1;
					Trasser_Init();
					   SwapElements(8);
					   Sleep(Delay_time);//задержка
					   SwapElements(9);
					   Sleep(Delay_time);//задержка
					map_15[8]=8; //блокируем ячейку 8 (с цифрой 9)
				    map_15[12]=12; //блокируем ячейку 12 (с цифрой 13)
				    Trasser_Init();
				   }
		}// Конец Если в раскладке числа 9 и 13 в ячейках 8 и 12 т.е не на своих местах	
		 if(!(mas[8]==9&&mas[12]==13)) //если ячейки не попали на свои места то делаем все снова
			  goto L4;
				//обрабатываем ячейки 9,10,11,13,14,15
					
L5:					Set_ElementPosition(10,13);//ставим 10 в ячейку 13 (место числа 14) Загоняем "10" сначала на место "14"
				    Set_ElementPosition(10,15);//ставим 10 в ячейку 15 затем ее в правый нижний угол, чтобы выстроить правильную последовательность
					Set_ElementPosition(11,15);//ставим 11 в ячейку 15 (там где стоит число 10) 
					Set_ElementPosition(10,15);//ставим 10 в ячейку 15 (в правый нижний угол)
					Set_ElementPosition(11,14);//ставим 11 в ячейку 14 (место числа 15)
					Set_ElementPosition(10,11);//поднимаем 10 в ячейку 11 
				
					Set_ElementPosition(11,15);//под 10 ставим 11 в ячейку 15 
				
					Set_ElementPosition(12,14);//12 ставим в ячейку 14
					
					SwapElements(11);
					Sleep(Delay_time);//задержка
					SwapElements(15);
					Sleep(Delay_time);//задержка
					SwapElements(14);
					Sleep(Delay_time);//задержка
					SwapElements(13);
					Sleep(Delay_time);//задержка
					SwapElements(9);
					Sleep(Delay_time);//задержка
					SwapElements(10);
					Sleep(Delay_time);//задержка
					SwapElements(11);
					Sleep(Delay_time);//задержка
					SwapElements(15);
				    Sleep(Delay_time);//задержка
					count_err2=count_err2+1;
					if (count_err2>4)
					{
						//MessageBoxA (NULL,(LPCSTR)"Зацикливание ячейки массива 9,10,11,13,14,15", (LPCSTR)"Блок Make_Line_End", MB_OK|MB_ICONERROR);	
					 //   goto L4; //переход обрабатываем ячейки 9,10,11,13,14,15
						return false; //значит это нерешаемая ситуация
					}
				if(!(mas[8]==9&&mas[9]==10&&mas[10]==11&&mas[11]==12&&mas[12]==13))
					goto L5;

					//if(mas[14]==15||mas[13]==15)//если в конце комбинация 14,15 или 15,14 то все сложено
					  if(mas[8]==9&&mas[9]==10&&mas[10]==11&&mas[11]==12&&mas[12]==13&&mas[13]==14&&mas[14]==15)// Если в раскладке числа 8-15 в ячейках 9-15 т.е не на своих местах
					result=true; //если все OK возвращаем истина	
					  else
					result=false; //нерешаемая комбинация	
					
return result;
}