#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReadIni(char *File);
void WriteIni(char* File, int *list, int n);
void NewUnit(char *title, int UnitLimits, char Default);
int newStudent(int *list, int n);
int StrCmp(const char *A, const char *B);
int SearchHeadIndex(const char *ListHeadName);
void Sort(int *list, int n, int sortBase, int Order);
int Search(int *Sourcelist, int n, int *Resultlist, int SearchUnit, const char *destin);
void GetList(int *list, int *n);
void display(int *list, int n);

