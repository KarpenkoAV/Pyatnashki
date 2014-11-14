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
void RanddomMass(void); //прототип функции заполнени€ массива случайными числами
int CheckButton(HWND); //прототип функции определени€ €вл€етс€ ли ресурс окна кнопкой
void SwapElements(int); //прототип функции помен€ть элемент если р€дом пуста€ €чейка
void ZeroPositions(int);//прототип функции сдвинуть пустую €чейку в любую нужную позицию
int FindElements(int);//поиск позиции числа в массиве
int Steps(int, int);//прототип функции подсчета числа шагов
int Trasser_Area(int);//прототип функции окружение точки
int Trass_Parent(int);//прототип функции поиска новой точки родител€
void Trasser_patch(int, int);//прототип функции маршрут
void Trasser_Init(void);//прототип функции инициализации массивов дл€ трассера;
void Set_ElementPosition(int,int);//прототип функции установить число в нужную позицию
void Block_Area(int, int); //прототип функции блокировки области
bool Check_Block_Position(int );//прототип функции проверки заблокирована ли данна€ позици€ в массиве блокированных элементов n_block
void Mass_Init(void);//прототип функции инициализации основных массивов;
bool Make_Line_1(void);//прототип функции сборки первого р€да
bool Make_Line_2(void);//прототип функции сборки второго р€да
bool Make_Line_End(void);//прототип функции сборки элементов последних 2-х р€дов
void WriteLog(int);
void Mass_Log(void);//прототип функции сохранени€ массивов в лог файле




struct Cell//структура €чейки открытого списка дл€ трассера
{ 
   int F,G,H,Direct,Poz; 
};




