// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>



void ShowButton(HWND[], int[]);
void RanddomMass(void); //�������� ������� ���������� ������� ���������� �������
int CheckButton(HWND); //�������� ������� ����������� �������� �� ������ ���� �������
void SwapElements(int); //�������� ������� �������� ������� ���� ����� ������ ������
void ZeroPositions(int);//�������� ������� �������� ������ ������ � ����� ������ �������
int FindElements(int);//����� ������� ����� � �������
int Steps(int, int);//�������� ������� �������� ����� �����
int Trasser_Area(int);//�������� ������� ��������� �����
int Trass_Parent(int);//�������� ������� ������ ����� ����� ��������
void Trasser_patch(int, int);//�������� ������� �������
void Trasser_Init(void);//�������� ������� ������������� �������� ��� ��������;
void Set_ElementPosition(int,int);//�������� ������� ���������� ����� � ������ �������
void Block_Area(int, int); //�������� ������� ���������� �������
bool Check_Block_Position(int );//�������� ������� �������� ������������� �� ������ ������� � ������� ������������� ��������� n_block
void Mass_Init(void);//�������� ������� ������������� �������� ��������;
bool Make_Line_1(void);//�������� ������� ������ ������� ����
bool Make_Line_2(void);//�������� ������� ������ ������� ����
bool Make_Line_End(void);//�������� ������� ������ ��������� ��������� 2-� �����
void WriteLog(int);
void Mass_Log(void);//�������� ������� ���������� �������� � ��� �����




struct Cell//��������� ������ ��������� ������ ��� ��������
{ 
   int F,G,H,Direct,Poz; 
};




