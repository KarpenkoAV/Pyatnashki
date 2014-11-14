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


static HWND hBut[16],hBt; //������ ������

static int mas[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0}; //������ ����� 0-15 (��� ������� ������ ���������)
static int n_block[16];//������ ������������� ���������
static int map_15[16]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,};//������ ��������� � ������������� ���������
static int close_list[16];//������ �������� ��� ����������� ���������
static int mass_a[4];//������ ��������� �������� [0]=�����,[1]=������,[2]=������,[3]=����� (���� ����� ��� ����� ��� �����������, �� �������� -1, ���� ���� �� ����� ������)
int Min_F =100;//����������� ��������� �������� F

static int trassa[16];//������ ����� ��������
static Cell open_list[16];//������ �������� ��� ����������� ���������
char log_str[256] ="";
int Delay_time =400;//�������� ��




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
	int wmId, wmEvent,a,nBt,p1;//��������������


	static HDC hDc;
	
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		 WriteLog(0);
		sprintf(log_str,"Start Programm ********************************************************************************\n"); //� ��� ����
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
	
	case WM_SHOWWINDOW://��� ������ ���� ��������� ���������� �������
		//RanddomMass();
		ShowButton(hBut,mas);	
	break;


	case WM_COMMAND:
		wmId    = LOWORD(wParam); //��������� �������������� ������� � ������� �� ��������
		wmEvent = HIWORD(wParam);//��������� ������� ������� � ������� ������������ ������
		switch (wmId)
		{
			case ID_MAIN_NEW://��������� ������� ������ ���� "New" ��������� ����
				sprintf(log_str,"-------------------------Start ID_MAIN_NEW -----------------------\n"); //� ��� ����
                WriteLog(1);
				RanddomMass();
				Mass_Init();
				Trasser_Init();
				ShowButton(hBut,mas);
				Mass_Log();
				sprintf(log_str,"----------------------------End ID_MAIN_NEW -----------------------\n"); //� ��� ����
                WriteLog(1);
			break;

			case ID_MAIN_GO://��������� ������� ������ ���� "Go!!!" ��������� ���� 
			sprintf(log_str,"Start ID_MAIN_GO ----------------------------------------------------\n"); //� ��� ����
            Trasser_Init();
			WriteLog(1);
			if(Make_Line_1())// ������� 1-� ���
			{
				Trasser_Init();
				if(Make_Line_2())// ������� 2-� ���
				{
					Trasser_Init();
					if(Make_Line_End())//��������� 2 ����
						{
							MessageBoxA (NULL,(LPCSTR)"�����������!", (LPCSTR)"���� ����������!", MB_OK|MB_ICONINFORMATION);
							sprintf(log_str,"\n------------>>>>  SUCSESS !!!!!! <<<<<<<<<---------------------\n"); //� ��� ����
							WriteLog(1);
						}
						else //��������� 2 ����
						{
							MessageBoxA (NULL,(LPCSTR)"������������ ����������", (LPCSTR)"��������� ������", MB_OK|MB_ICONWARNING);
							sprintf(log_str,"\n------------>>>> not decided situation <<<<<<<<<---------------------\n"); //� ��� ����
							WriteLog(1);
						}
				}
				else // ������� 2-� ���
						{
							MessageBoxA (NULL,(LPCSTR)"����", (LPCSTR)"������ ��� 2 !",MB_OK|MB_ICONERROR);
							sprintf(log_str,"\n------------>>>>  ERROR !!!!!! <<<<<<<<<---------------------\n"); //� ��� ����
							WriteLog(1);
						}
			}
			else // ������� 1-� ���
						{
							MessageBoxA (NULL,(LPCSTR)"����", (LPCSTR)"������ ��� 1 !",MB_OK|MB_ICONERROR);
							sprintf(log_str,"\n------------>>>>  ERROR !!!!!! <<<<<<<<<---------------------\n"); //� ��� ����
							WriteLog(1);
						}
			Mass_Log();//�������� � ��� ��������� ��������
							
			sprintf(log_str,"End ID_MAIN_GO ----------------------------------------------------\n"); //� ��� ����
            WriteLog(1);
			break;

			case ID_MAIN_TEST://��������� ������� ������ ���� "test!!!" ��������� ���� 
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
				if(nBt!=-1) //��������� ������� ������ ������?
					{
						SwapElements(nBt);	//�������� ������� ������ �������� � ������ �������
					}
	        break;
		}
	  // break;
	break;
	case WM_CLOSE:
		//EndDialog(hDlg,LOWORD(wParam));
		DestroyWindow(hDlg);
		sprintf(log_str,"Finish Programm ********************************************************************************\n"); //� ��� ����
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
sprintf(log_str,"Start CheckButton \n"); //� ��� ����
WriteLog(1);
	int  N_But = -1;

	for(int i=0;i<16;i++)
	{
	  if(hResurs==hBut[i])
		  N_But = i;
	}
sprintf(log_str,"Finish CheckButton \n"); //� ��� ����
WriteLog(1);
	return  N_But;
}

void SwapElements(int num) //������� ����� ������� ��������� ���� ������ ������ �����
{
	sprintf(log_str,"Start SwapElements num=%d \n",num); //� ��� ����
WriteLog(1);

int zero;
for(int _i=0;_i<16;_i++)
	{
		if(mas[_i]==0)
			zero = _i;
	}

if(num==zero+1||num==zero-1||num==zero-4||num==zero+4)//���� ����� � ��������� �� ������ num ��������� ������ 
	{
		mas[zero]=mas[num];//���������� �������� �������� � ������ ��� ��� 0
		mas[num]=0;			//���������� 0 � ������ ��� ��� �������
	}
ShowButton(hBut,mas);

sprintf(log_str,"Finish SwapElements \n"); //� ��� ����
WriteLog(1);
return;
}

void RanddomMass(void) //������� ���������� ������� ���������� �������
{
sprintf(log_str,"Start RanddomMass \n"); //� ��� ����
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
sprintf(log_str,"Finish RanddomMass \n"); //� ��� ����
WriteLog(1);
return;
}

void ZeroPositions(int n) //������� �������� ������ ������ � ����� ������ �������
{
sprintf(log_str,"!!!--------Start ZeroPositions %d\n",n); //� ��� ����
WriteLog(1);

	 int p_zero=FindElements(0);//������� ����� "0" � �������
	 int _i;
	 /*static int patch[16];*/
		 
	 if(p_zero==n)//���� ���� ��� � ������ ������� �� �������
		 return;

	   Trasser_patch(p_zero,n);//������� ������� �� ��������� 0 � ��������� �����

	 for (_i=0;_i<16;_i++)//������� ����� ��������
	 {
		 if(trassa[_i]!=-1)//���� ���� ����� (����� �� ������ -1)

		 {
			SwapElements(trassa[_i]);//������ 0 � ��������� ��������
			Sleep(Delay_time);//��������
		 }
	 }
Trasser_Init();
sprintf(log_str,"!!!--------Finish ZeroPositions %d\n",n); //� ��� ����
WriteLog(1);	
return;
}

int FindElements(int D) //������� ����� ������� �����
{
	sprintf(log_str,"####### Start FindElements    %d\n",D); //� ��� ����
WriteLog(1);
	int poz;
for(int _i=0;_i<16;_i++)
	{
		if(mas[_i]==D)
			poz = _i;
	}
sprintf(log_str,"####### Finish FindElements    %d\n",D); //� ��� ����
WriteLog(1);
return poz;
}

void Trasser_patch(int start, int finish)//������� ������ �� ����� � � ����� � (�������� �*)***********************************************
{
sprintf(log_str,"<---->Start Trasser A=%d  B=%d\n",start,finish); //� ��� ����
WriteLog(1);
	int rod = start; //��������� �������� - ��������� �����
	int old_rod = start;//���������� �������� - ��������� �����
	int count_rod =0;
	int _i;
	int direct =0; //��������� ����������� ����������� �� ������ �����
	int count_point=0;//������� ����� ��������
	int count_err=0;//������� ������������ ��� ������;
	int n_step; //���-�� ����������� � ������ ����� �� ���������

	open_list[start].Poz =start; //������� ��������
	open_list[start].G =0;//G = ��������� ������������ �� ��������� ����� A � ������ ������, ������ ���������� ���� � ���� ������.
						  //(����� ������� ��� ��������� ������������ �� 1 ������� =10)
	open_list[start].H =Steps(start,finish)*10;//H = ��������� ��������� ������������ �� ������ ������ �� �������, �� ���� ����� B. ��� ������ �������� ������������� ��������.
											   //��������� H ��������� � ������� ���������� �������������� ���������� � ����� �, 
											   //�������� ������ �� ����������� � ���������, ��������� ��� ����������� �� ����. 	
	open_list[start].F = open_list[start].G + open_list[start].H; //��������� F ��� ������ ������ ����������� ������� ������������� G � H.
	//open_list[start].Dst = abs(finish-start); //�������� ����� ��������� ������ � ��������

	for(_i=0;_i<16;_i++)//���������� � �������� ������ ��������� �� ������ ���������� 
	{
		if(n_block[_i]==_i)//���� ������� ������ ���������� �������� ����� ������� (-1 ������ �� ����������)
		close_list[_i]=_i;//��������� ��� � �������� ������
	}

	open_list[finish].Poz =finish;//������� � �������� ������ �������� �����
	open_list[finish].H =-1;//������������� �������� �����, ����� �� ����� ����� � ����

	while(open_list[finish].H!=0) //������ ������� ���� �� �������� �������� ����� �.� ��� H=0 �� ��������� � ���. �����
	{
		direct =Trasser_Area(rod);//��������� ����� mass_a ��������� ������������ ����� � ���������� ����� ����������� �� ������������ �����
		close_list[rod] =rod; //������� ��������� ����� � �������� ������
		
		for(_i=0;_i<4;_i++)//��������� open_list ������ �� ������� ��������� ��������
		{
			n_step =10;//������������� �������� �������� �� 1 ���
			int _ar = mass_a[_i];//��������� ������� ��������� � open_list  (� ���� ������� [0] -����� ������ [1]-����� ����� [2]-����� ������ [3]-����� �����)
				if( _ar!=-1)//���� ������� = -1 �� �������� ����� � ����� ���� ������� ��� ���� ��� ������������� � close_list
				{
					open_list[_ar].Poz =_ar; //������� ��������
			
					for(int _c=0;_c<16;_c++) //��������� ��� ��������� ����� �������� � ������� ������� ����� �� ��� ������
					{
						if(trassa[_c]!=-1)
							n_step=n_step+10;//��������� ��������� ������������ �� ����� ������ =10 � ����� �� �����������
					}
					open_list[_ar].G =n_step; //������� ��������� ����������� �� ��������� � ��� ������
					open_list[_ar].H =((Steps(_ar,finish))*10);//������� ��������� ����������� �� ������ ������ � ��������
					open_list[_ar].F = open_list[_ar].G + open_list[_ar].H;//��������� F=G+H;
					open_list[_ar].Direct = direct;//���������� ���-�� ����������� ����������� �� ������������ �����;
				}
		}
		old_rod = rod;
        rod = Trass_Parent(rod);//�������� �������� 

		if(count_point<16&&old_rod!=rod)//���� ������� ������ �� ��������� ������ ������� �������� � ������ � ����� �������� �� ���������
		{
			trassa[count_point]=rod;//���������� ����� �������� � ������
			count_point=count_point+1;//����������� ������� ����� ��������
			Min_F=100;
		}
		if(old_rod==rod)//����  ������ � ����� �������� ��������� ����� �� ������������
		   count_rod=count_rod+1;
		if(count_rod==10)
		{	
			sprintf(log_str,"<!!!!!!!!>Trable Parent=%d  Trasser A=%d  B=%d\n",rod,start,finish); //� ��� ����
            WriteLog(1);
			Mass_Log();//��������� �������
			//Trasser_Init();//���������� �������
			//sprintf(log_str,"<\n--------Restart Mass--------���� Trasser---\n"); //� ��� ����
   //         WriteLog(1);
			//Mass_Log();//��������� �������
			//MessageBoxA (NULL,(LPCSTR)"����� �� ��������", (LPCSTR)"���� Trasser", MB_OK|MB_ICONERROR);
		    break;
		}

		if(count_err==100)//���� �������� ������
		{
			MessageBoxA (NULL,(LPCSTR)"������������", (LPCSTR)"���� Trasser", MB_OK|MB_ICONERROR);
			break;
		}
		if(count_point>=16)//���� �������� ������
		{
			MessageBoxA (NULL,(LPCSTR)"������������ trassa", (LPCSTR)"���� Trasser", MB_OK|MB_ICONERROR);
			break;
		}
	}//End while

sprintf(log_str,"<----> End Trasser A=%d  B=%d\n",start,finish); //� ��� ����
WriteLog(1);
return;
}

int Trass_Parent(int parent) //������� ��������� ����� ����� �������� *************************************************************
{
sprintf(log_str,"+++++Start Trasser_Parent =%d \n",parent); //� ��� ����
WriteLog(1);
	int _i,el;

	//int Min_dist = 16;//����� �������� � ����������� F (������������� ��� �������)


	for(_i=0;_i<4;_i++)
	{
		el = mass_a[_i];
		if(el!=-1)
		{
				 sprintf(log_str,"<--------------------open_list___---------------->open_list poz=%d  Direct=%d   F =%d  G =%d H=%d \n",open_list[el].Poz,open_list[el].Direct,open_list[el].F,open_list[el].G,open_list[el].H); //� ��� ����
                 WriteLog(1);
			if (Min_F >=open_list[el].F)
			{
			/*	 if(Min_H >=open_list[el].H)
					Min_H = open_list[el].H;*/

				 if(open_list[el].Direct!=0)//��������� ���������� � ��������
				{
			       Min_F =  open_list[el].F;
				   parent =  open_list[el].Poz; 
				  
				}
			}
		}
	}
	sprintf(log_str,"+++++End Trasser_Parent =%d \n",parent); //� ��� ����
    WriteLog(1);
	return  parent;
}

bool Check_Block_Position(int p)//�������� ������������� �� ������ ������� � ������� ������������� ��������� n_block
{
	bool result=false;//�� ����������
	for(int _i=0;_i<16;_i++)
	{
		if(p==_i&&p==close_list[_i])//��������� �������� � �������� ������ (���� ������������ �� ������ ������� �������� ���� ������=�)
		result=true;//����������
	}
return result;
}

int Trasser_Area(static int aa)
{
sprintf(log_str,">>>>>>>>>>>>>>>>>>>>>>>Start Trasser_Area =%d \n",aa); //� ��� ����
WriteLog(1);
	int d=0;//���-�� ����������� �� ���� �����
	int _r;
	if((aa-1)/4==(aa/4))//���� �� ����� ����� ������� �� ��� �� ������
	{
		if(!Check_Block_Position(aa-1))//���� ������� ����� �� ����������
	       mass_a[0]=aa-1; //���������� �� �� ����������
		else 
		   mass_a[0]=-1;  //�� ����������, �� ����������
	}
	else
    mass_a[0] =-1;//�������� ����� ��� �� �� ����� �������� 

	if((aa+1)<=15&&(aa+1)/4==aa/4)//���� �� ����� ������ ������� �� ��� �� ������
	{
		if(!Check_Block_Position(aa+1))//���� ������� ������ �� ����������
		  mass_a[1]=aa+1; //���������� �� �� ����������
		else
		  mass_a[1]=-1;	 //�� ����������, �� ����������		  	
	}
	else
    mass_a[1] =-1;//�������� ������ ��� �� �� ������ �������� 
	
	if((aa-4)>=0)//���� �� ��� ���� ��������� ������� ����
	{
		if(!Check_Block_Position(aa-4))//���� ������� ������ �� ����������
			mass_a[2]=aa-4;//���������� �� �� ����������
		else
			mass_a[2]=-1;	 //�� ����������, �� ����������	
	}
	else
    mass_a[2] =-1;//�������� ������ ��� �� �� ������� �������� 

	if((aa+4)<=15)//���� �� ��� ���� ��������� ������� ����
	{
		if(!Check_Block_Position(aa+4))//���� ������� ����� �� ����������
			mass_a[3]=aa+4;//���������� �� �� ����������
		else
			mass_a[3]=-1;	 //�� ����������, �� ����������	
	}
	else
    mass_a[3] =-1;//�������� ����� ��� �� �� ������ �������� 

	for(_r=0;_r<4;_r++)//������� ����� �����������
	{
     if(mass_a[_r]!=-1)
		 d=d+1;
	}
	sprintf(log_str,"<<<<<<<<<<<<<<<<<<<End Trasser_Area Direct=%d \n",d); //� ��� ����
    WriteLog(1);
	return d;
}

int Steps(int a1, int a2)//������� ����� ����� � �� ����� ����� � ������
{
	sprintf(log_str,"____Start Steps a1=%d a2=%d \n",a1,a2); //� ��� ����
    WriteLog(1);
	int step=0, tmp;
	int count_err=0; //������� ������������ ��� ������
	if (a2<a1)
	{
		tmp=a2;
		a2=a1;
		a1 =tmp;
	}
		while(a1!=a2)
		{
			if(a2>a1&&a1/4!=a2/4) //���� �2 ������ �1 � ��� � ������ �������
			{
				a1=a1+4;//��������� �� ������ ������
				step=step+1;//������ ���
			}
			if(a2>a1&&a1/4==a2/4) //���� �2 ������ �1 � ��� � ����� ������
			{
				a1=a1+1;//��������� �� ������ ������
				step=step+1;//������ ���
			}
			if(a2<a1)
			{
				a1=a1-1;
				step=step+1;
			}

			if(count_err==1000)//���� �������� ������
			{
			MessageBoxA (NULL,(LPCSTR)"������������", (LPCSTR)"���� Steps", MB_OK|MB_ICONERROR);
			break;
			}
			count_err=count_err+1;
		}
	sprintf(log_str,"____End Steps step=%d \n",step); //� ��� ����
    WriteLog(1);
return step;
}

void Trasser_Init(void) //������������� �������� ��� ��������
{
    sprintf(log_str,"******Start Trasser_Init \n"); //� ��� ����
    WriteLog(1);
 for(int _i=0;_i<16;_i++)//������������� �������� (-1)
	{
	close_list[_i]=-1;
	if(map_15[_i]==_i)//���� � ������� ���� ��������� ��� ���� ������� �� ��������� ��� � � �������� ����
		close_list[_i]=_i;//��������� ������� �� ������� ������ � ������ �������� ��� ����������� ���������

	if(n_block[_i]==_i)//���� � ������� ���������� ��� ���� ������� �� ��������� ��� � �������� ����
		close_list[_i]=_i;//��������� ������� �� ������� ���������� � ������ �������� ��� ����������� ���������
	
	trassa[_i] =-1;//������ ����� ��������
				//�������� ������ �������� ������ �����
	open_list[_i].F =0;
	open_list[_i].G =0;
	open_list[_i].H =0;
	open_list[_i].Poz =0;
	}
    Min_F =100;
 //mass_a{0};//������ ��������� ��������
	sprintf(log_str,"*******End Trasser_Init \n"); //� ��� ����
    WriteLog(1);
return;
}

void Mass_Init(void) //������������� �������� ��������
{
sprintf(log_str,"*******Start Mass_Init \n"); //� ��� ����
WriteLog(1);
 for(int _i=0;_i<16;_i++)//������������� �������� (-1)
	{
	map_15[_i] =-1; //������ ������ ���������
	n_block[_i]=-1; //������ ������������� ���������
	}
sprintf(log_str,"********End Mass_Init \n"); //� ��� ����
WriteLog(1);
return;
}

void Set_ElementPosition(int number,int ni) //��������� ����� � ������ �������
{
sprintf(log_str,">>>>Start Set_ElementPosition Element=%d on position =%d \n", number,ni); //� ��� ����
WriteLog(1);

int poz_munber;
int n_column = ni%4;//��������� ����� ������� ��� �������
int n_line = ni/4;//��������� ����� ������ ��� �������
int  el_column;//����� ������� ��� ��������
int  el_line;//����� ������ ��� ��������
int count_err=0; //������� ������������ ��� ������
poz_munber =  FindElements(number);

if (ni==poz_munber)//���� ������� �� ����� �� �������
	return;

while(ni!=poz_munber)//��������� ���� �� �������� ������ �������
{
  el_column = poz_munber%4;//��������� ����� ������� ��� ��������
  el_line   = poz_munber/4;//��������� ����� ������ ��� ��������

	if(el_column<n_column)//���� ������� �������� ����� �� ������ �������
	{
			close_list[poz_munber]=poz_munber;//��������� ��� ����� ����� ����������������� �������
			ZeroPositions(int(poz_munber+1));//������������� ������ ������ ������
			SwapElements(poz_munber); //������ ������� � ������ �������
			Sleep(Delay_time);//��������
			close_list[poz_munber]=-1;//������� ���������� ����� ����� ���������������� �������
	}
	
	if(el_column>n_column)//���� ������� �������� ������ �� ������ �������
	{
		close_list[poz_munber]=poz_munber;//��������� ��� ����� ����� ����������������� �������
		ZeroPositions(int(poz_munber-1));//������������� ������ ������ �����
		SwapElements(poz_munber); //������ ������� � ������ �������
		Sleep(Delay_time);//��������
		close_list[poz_munber]=-1;//������� ���������� ����� ����� ���������������� �������
	}

	if((el_column==n_column)&&(el_line>n_line))//���� ������� ��������� � ������� �� ��� ������� ���� ������ ������
	{
		close_list[poz_munber]=poz_munber;//��������� ��� ����� ����� ����������������� �������
		ZeroPositions(int(poz_munber-4));//������������� ������ ������ ������
		SwapElements(poz_munber); //������ ������� � ������ �������
		Sleep(Delay_time);//��������
		close_list[poz_munber]=-1;//������� ���������� ����� ����� ���������������� �������
	}
	if((el_column==n_column)&&(el_line<n_line))//���� ������� ��������� � ������� �� ��� ������� ���� ������ ������
	{
		close_list[poz_munber]=poz_munber;//��������� ��� ����� ����� ����������������� �������
		ZeroPositions(int(poz_munber+4));//������������� ������ ������ �����
		SwapElements(poz_munber); //������ ������� � ������ �������
		Sleep(Delay_time);//��������
		close_list[poz_munber]=-1;//������� ���������� ����� ����� ���������������� �������
	}

	if(count_err==1000)//���� �������� ������
	{
		MessageBoxA (NULL,(LPCSTR)"������������", (LPCSTR)"���� Set_ElementPosition", MB_OK|MB_ICONERROR);
		break;
	}
	Trasser_Init();//������������� �������� �����������
	poz_munber =  FindElements(number);
	count_err=count_err+1;
}
sprintf(log_str,"<<<<<Finish Set_ElementPosition Element=%d on position =%d \n", number,ni); //� ��� ����
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

void Mass_Log(void)//���������� �������� � ��� �����
{
	int _i;
	sprintf(log_str,"------->mas------------------------------------\n"); //� ��� ����
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=%d   ",_i,mas[_i]); //� ��� ����
		WriteLog(1);
	}
	sprintf(log_str,"\n------->n_block-------------------------------\n"); //� ��� ����
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=%d   ",_i,n_block[_i]); //� ��� ����
		WriteLog(1);
	}
	sprintf(log_str,"\n------->map15----------------------------------\n"); //� ��� ����
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=%d   ",_i, map_15[_i]); //� ��� ����
		WriteLog(1);
	}
	sprintf(log_str,"\n------->trassa----------------------------------\n"); //� ��� ����
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=%d   ",_i,trassa[_i]); //� ��� ����
		WriteLog(1);
	}
	sprintf(log_str,"\n------->close_list------------------------------\n"); //� ��� ����
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=%d   ",_i,close_list[_i]); //� ��� ����
		WriteLog(1);
	}
	sprintf(log_str,"\n------->open_list-------------------------------\n"); //� ��� ����
		WriteLog(1);
	for(_i=0;_i<16;_i++)
	{
		sprintf(log_str,"[%d]=(Direct=%d, F=%d, G=%d, H=%d)   ",_i,open_list[_i].Direct, open_list[_i].F,open_list[_i].G,open_list[_i].H ); //� ��� ����
		WriteLog(1);
	}
	return;
}

bool Make_Line_1(void)
{
	static int coun_er=0;
	static bool result = false;
	Trasser_Init();//������������� ��������
	if(mas[0]==1 && mas[1]==2 && mas[2]==3 && mas[3]==4)//���� 1,2,3,4  �� ����� ������ �� ��� �������
	{
		map_15[0]=0;map_15[1]=1;map_15[2]=2;map_15[3]=3;//��������� ���� ��� �� ������
        return true; //������������ ��� �������!!!!
	}
			//������ 1-�� ���� **************************************************************************************
						
				Set_ElementPosition(1,0);
				if(mas[0]==1)
					map_15[0]=0; //��������� ������ 0 (� ������ 1)
				Trasser_Init();
				Set_ElementPosition(2,1);
				if(mas[1]==2)
					map_15[1]=1; //��������� ������ 1 (� ������ 2)
				Trasser_Init();
				if(mas[0]==1&&mas[1]==2)//���� ������ � ����� ������ �� �����
				{
					
L1:					if(mas[2]==4)//���� ����� 4 �������� ���� ����������� �� ������� 2 ����� �������� �� � ��� 11, ���� ����� �� �������, �� ��� ������������� � ���� � �� ���������� ����� ������
					Trasser_Init();
					Set_ElementPosition(4,11);	

					Set_ElementPosition(3,3);
					if(mas[3]==3)//���� ������ 3 �� �����
						map_15[3]=3; //��������� ������ 3 (� ������ 3)
					Trasser_Init();
				
					Set_ElementPosition(4,7);//������ 4 � ������ 7
					if(mas[7]==4)
						map_15[7]=7; //��������� ������ 7 (� ������ 4)
					Trasser_Init();

					if((mas[3]==3)&&(mas[7]==4))
					{
						ZeroPositions(2);//������ ������ ������ �� ������ 2
						map_15[3]=-1; //������� ���������� � ������ 3 (� ������ 3)
						map_15[7]=-1; //������� ���������� � ������ 7 (� ������ 4)
						Trasser_Init();
						SwapElements(3);//������  3 � ������ 2
						Sleep(Delay_time);//��������
						SwapElements(7);//������  4 � ������ 3
						Sleep(Delay_time);//��������
						if((mas[2]==3)&&(mas[3]==4))//���� 3 � 4 � ����� �������
							{
							map_15[2]=2; //��������� ������ 2 (� ������ 3)
							map_15[3]=3; //��������� ������ 3 (� ������ 4)
							Trasser_Init();
							}
						else
							{
							map_15[2]=-1; //������������ ������ 2 (� ������ 3)
							map_15[3]=-1; //������������ ������ 3 (� ������ 4)
							Trasser_Init();
							goto L1;
							}
						
					}
				}
				Trasser_Init();
				result=true;
			sprintf(log_str,"\n------------>>>>  1-st row is built ! <<<<<<<<<---------------------\n"); //� ��� ����
            WriteLog(1);
			
return result;
}

bool Make_Line_2(void)
{
	static int coun_er=0;//������� ������������
	static bool result=false;
L0:	if(mas[4]==5 && mas[5]==6 && mas[6]==7 && mas[7]==8)//���� �������� 5,6,7,8 �� ����� ������
	{
		map_15[4]=4;map_15[5]=5;map_15[6]=6;map_15[7]=7;//��������� ���� ���, �� ������
        return true; //������������ ��� �������!!!!
	}
	     Trasser_Init();//������������� ��������
		//������ 2-�� ���� *******************************************************
	   //      
			 //while(mas[4]!=5 && mas[5]!=6 && mas[6]!=7 && mas[7]!=8)//��������� ���� �������� 5,6,7,8 �� ����� �� ����� ������
			 //{
L2:			Set_ElementPosition(5,4);
				if(mas[4]==5)
					map_15[4]=4; //��������� ������ 4 (� ������ 5)
				Trasser_Init();
				Set_ElementPosition(6,5);
				if(mas[5]==6)
					map_15[5]=5;//��������� ������ 5 (� ������ 6)
				Trasser_Init();
				if(mas[4]==5 && mas[5]==6)//���� ����� 5 � 6 �� ����� �� �����
				{
L3:	 			Set_ElementPosition(7,7);
					if(mas[7]==7)
					   map_15[7]=7;//��������� ������ 7 (� ������ 7)
					Trasser_Init();
					if(mas[6]==8)//���� ����� 8 �������� ���� ����������� �� ������� 6 ����� �������� �� � ��� 8, ���� ����� �� �������, �� ��� ������������� � ���� � �� ���������� ����� ������
					{
						map_15[6]=-1;
						map_15[7]=-1;
						Trasser_Init();
						Set_ElementPosition(8,14);
						goto L3;//������� �� ���������������� ����� 7 � ������ 7
					}
									
					Set_ElementPosition(8,11);//������ 8 � ������ 11
					if(mas[11]==8)
					 map_15[11]=11;//��������� ������ 11 (� ������ 8)
					Trasser_Init();
						ZeroPositions(6);//������ ������ ������ �� ������ 6 //����� ����� ������ ������� �������� ������
						map_15[7]=-1; //������� ���������� � ������ 7 (� ������ 7)
						map_15[11]=-1; //������� ���������� � ������ 11 (� ������ 8)
						Trasser_Init();
						SwapElements(7);//������  7 � ������ 6
						Sleep(Delay_time);//��������
						SwapElements(11);//������  8 � ������ 7
						Sleep(Delay_time);//��������
						if((mas[6]==7)&&(mas[7]==8))//���� 7 � 8 � ����� �������
							{
							map_15[6]=6; //��������� ������ 6 (� ������ 7)
							map_15[7]=7; //��������� ������ 7 (� ������ 8)	
							}
						Trasser_Init();
				}
				if(mas[4]==5&& mas[5]==6&& mas[6]==7&& mas[7]==8)// ���� ��� �������� �� �����
					result =true;
				else
				{
					Mass_Log();//������ ��������� �������� � ���
					map_15[4]=-1;map_15[5]=-1;map_15[6]=-1;map_15[7]=-1;//������� ���������� � ��������� ������
					Trasser_Init();
					goto L2;//������� �� ������ ������
				}

				coun_er=coun_er+1;//����������� ������� ������
				if(coun_er>=10)
				{	
					if(coun_er>=100)//���� ��������� �������� �� �����
					{
						Mass_Log();//������ ��������� �������� � ���
						MessageBoxA (NULL,(LPCSTR)"������������ ������ 2", (LPCSTR)"���� Make_Line_2", MB_OK|MB_ICONERROR);
						result =false;
					}
					goto L0;//�������� ������ �����
				}
			//}//end while
			sprintf(log_str,"\n------------>>>>  2-st row is built ! <<<<<<<<<---------------------\n"); //� ��� ����
            WriteLog(1);
			
return result;
}

bool Make_Line_End(void)//������� ������ ���������
{
		bool result=false;
	
  		//map_15[8]=-1; map_15[12]=-1;map_15[9]=-1; map_15[10]=-1;map_15[11]=-1; map_15[13]=-1;map_15[14]=-1; map_15[15]=-1; //������� ���������� � �������
		
		int count_err1=0;//������� ������������
		int count_err2=0;//������� ������������
		//������ ��������� ������� *******************************************************
L4:		 if(mas[8]==9&&mas[9]==10&&mas[10]==11&&mas[11]==12&&mas[12]==13&&mas[13]==14&&mas[14]==15)// ���� � ��������� ����� 8-15 � ������� 9-15 �.� �� �� ����� ������
			return true; //���� ��� ����� �� ������  ������������ 
		 if(mas[8]==9&&mas[9]==10&&mas[10]==11&&mas[11]==12&&mas[12]==13&&mas[13]==15&&mas[14]==14)// ���� � ��������� ����� 8-15 � ������� 9-15 �.� �� �� ����� ������
			return false; //���������� ����������	
		 Trasser_Init();
		
		if(!(mas[8]==9&&mas[12]==13))// ���� � ��������� ����� 9 � 13 � ������� 8 � 12 �.� �� �� ����� ������
		{
				   if(!(mas[15]==9&&(mas[10]==13||mas[11]==13)))//�������� �� ������������� �����������
				   {
					   Set_ElementPosition(9,15);//������ 9 � ������ 15 (������ ������ ����)
					   map_15[15]=15; // ���������  ������ 15 (� ������ 9)
					   Trasser_Init();
					   if(mas[15]==9&&(mas[10]==13||mas[11]==13))//�������� �� ������������� ����������� ����� ���������������� 9 � ������ 15
							goto L4;
					   Set_ElementPosition(13,8);//������ 13 � ������ 8 (����� 9)
					   map_15[8]=8; // ���������  ������ 8 (� ������ 13)
					   Trasser_Init();
					   Set_ElementPosition(9,9);//������ 9 � ������ 9 (����� 10)
					   map_15[15]=-1; // ������������  ������ 15 
					   map_15[8]=-1; // ������������  ������ 8 (� ������ 13)
					   Trasser_Init();
					   ZeroPositions(12);
					   SwapElements(8);
					   Sleep(Delay_time);//��������
					   SwapElements(9);
					   Sleep(Delay_time);//��������
					   map_15[8]=8; //��������� ������ 8 (� ������ 9)
					   map_15[12]=12; //��������� ������ 12 (� ������ 13)
					   Trasser_Init();
				   }

				   else
				   {
					map_15[15]=-1; //������������ ������ 15 (� ������ 9)
				    Trasser_Init();
					Set_ElementPosition(13,8);//������ 13 � ������ 8 (����� 9)
					map_15[8]=8; //��������� ������ 8 (� ������ 13)
					Set_ElementPosition(9,9);//������ 9 � ������ 9 (����� 10)
					map_15[9]=9; // ���������  ������ 15 (� ������ 9)
					ZeroPositions(12);
					map_15[8]=-1;map_15[9]=-1;
					Trasser_Init();
					   SwapElements(8);
					   Sleep(Delay_time);//��������
					   SwapElements(9);
					   Sleep(Delay_time);//��������
					map_15[8]=8; //��������� ������ 8 (� ������ 9)
				    map_15[12]=12; //��������� ������ 12 (� ������ 13)
				    Trasser_Init();
				   }
		}// ����� ���� � ��������� ����� 9 � 13 � ������� 8 � 12 �.� �� �� ����� ������	
		 if(!(mas[8]==9&&mas[12]==13)) //���� ������ �� ������ �� ���� ����� �� ������ ��� �����
			  goto L4;
				//������������ ������ 9,10,11,13,14,15
					
L5:					Set_ElementPosition(10,13);//������ 10 � ������ 13 (����� ����� 14) �������� "10" ������� �� ����� "14"
				    Set_ElementPosition(10,15);//������ 10 � ������ 15 ����� �� � ������ ������ ����, ����� ��������� ���������� ������������������
					Set_ElementPosition(11,15);//������ 11 � ������ 15 (��� ��� ����� ����� 10) 
					Set_ElementPosition(10,15);//������ 10 � ������ 15 (� ������ ������ ����)
					Set_ElementPosition(11,14);//������ 11 � ������ 14 (����� ����� 15)
					Set_ElementPosition(10,11);//��������� 10 � ������ 11 
				
					Set_ElementPosition(11,15);//��� 10 ������ 11 � ������ 15 
				
					Set_ElementPosition(12,14);//12 ������ � ������ 14
					
					SwapElements(11);
					Sleep(Delay_time);//��������
					SwapElements(15);
					Sleep(Delay_time);//��������
					SwapElements(14);
					Sleep(Delay_time);//��������
					SwapElements(13);
					Sleep(Delay_time);//��������
					SwapElements(9);
					Sleep(Delay_time);//��������
					SwapElements(10);
					Sleep(Delay_time);//��������
					SwapElements(11);
					Sleep(Delay_time);//��������
					SwapElements(15);
				    Sleep(Delay_time);//��������
					count_err2=count_err2+1;
					if (count_err2>4)
					{
						//MessageBoxA (NULL,(LPCSTR)"������������ ������ ������� 9,10,11,13,14,15", (LPCSTR)"���� Make_Line_End", MB_OK|MB_ICONERROR);	
					 //   goto L4; //������� ������������ ������ 9,10,11,13,14,15
						return false; //������ ��� ���������� ��������
					}
				if(!(mas[8]==9&&mas[9]==10&&mas[10]==11&&mas[11]==12&&mas[12]==13))
					goto L5;

					//if(mas[14]==15||mas[13]==15)//���� � ����� ���������� 14,15 ��� 15,14 �� ��� �������
					  if(mas[8]==9&&mas[9]==10&&mas[10]==11&&mas[11]==12&&mas[12]==13&&mas[13]==14&&mas[14]==15)// ���� � ��������� ����� 8-15 � ������� 9-15 �.� �� �� ����� ������
					result=true; //���� ��� OK ���������� ������	
					  else
					result=false; //���������� ����������	
					
return result;
}