// stdafx.cpp : source file that includes just the standard includes
// Sceleton_DIALOG.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


void ShowButton(HWND hB[], int mm[])
{
	char s[256]="";
	for(int i=0;i<16;i++)
	if(mm[i])
	{
		sprintf(s,"%d",mm[i]);
		SetWindowTextA(hB[i],s);
	}
	else
		SetWindowTextA(hB[i],"");
	
	return;
}



