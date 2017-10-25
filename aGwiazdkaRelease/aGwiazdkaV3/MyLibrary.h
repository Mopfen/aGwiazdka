#pragma once

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <conio.h>

using namespace std;

HANDLE hOut;

#define RAND srand(time(NULL))
#define REFRESH Refresh()

#define YELLOW color::yellow
#define WHITE color::white
#define GREY color::grey
#define GREEN color::green
#define SELEDIN color::seledin
#define RED color::red
#define BLUE color::blue

int Exponentiation(int, int);
bool CheckBoard(int*, int*);
bool ChooseDirection(int *, int*, int, int);
int Operation(int, int, int, int, int);
void Test();
void NewBoards();
void GenerateBoard();
void DrawBoard();
void Refresh();
void CheckDistances(int, int, int, int, int);
void Finish(int, int, int, int, int);
bool Algoritm(int, int, int, int, int);
