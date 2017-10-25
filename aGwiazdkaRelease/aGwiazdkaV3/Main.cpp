#include "stdafx.h"
#include "MyLibrary.h"
#include "Colors.h"

int **board = new int*[10]; //Deklaracja planszy 10x10 [0 - p. wolne, 1 - przeszkoda, 2 - p. startowe, 3 - p. docelowe, 4 - p. wykluczone]
int **cost = new int*[10]; //Deklaracja tablicy 10x10 zawierającej koszty ruchu
int **parent = new int*[10]; //Deklaracja tablicy 10x10 zawierającej optymalny kierunek ruchu
int **closed = new int*[10]; // Deklaracja tablicy 10x10 wyeksplorowanych pól.
int **dis = new int*[10]; //Deklaracja tablicy 10x10 zawierającej informacje o odleglosci od celu
int ***returned = new int**[10]; //Deklaracja tablicy 2x10x10 zawierającej dwie możliwe drogi. Ma za zadanie zwrócić tą optymanlną.

int howMuch = 0; //Zlicza liczbę kosztu ruchu

int main()
{
	//board
	for (int i = 0; i <= 9; i++)
		board[i] = new int[10]{ 0 };

	//returned
	for (int i = 0; i <= 9; i++)
	{
		returned[i] = new int*[10];
		for (int j = 0; j <= 9; j++)
			returned[i][j] = new int[10]{ 0 };
	}

	int osX1 = (-1); // pierwsza wspolrzedna punktu startowego
	int osY1 = (-1); //druga wspolrzedna punktu startowego
	int osX2 = (-1); // pierwsza wspolrzedna punktu docelowego
	int osY2 = (-1); //druga wspolrzedna punktu docelowego

	NewBoards();
	GenerateBoard();
	//Test();

	do
	{
		while (osX1 < 0 || osX1 > 9)
		{
			REFRESH;
			cout << SELEDIN << "\nWybierz pole startowe:\n\n";
			cout << SELEDIN << "Os pozioma: ";
			cin >> osX1;
		}
		while (osY1 < 0 || osY1 > 9)
		{
			REFRESH;
			cout << SELEDIN << "\nWybierz pole startowe:\n\n";
			cout << SELEDIN << "Os pozioma: " << osX1 << "\n";
			cout << SELEDIN << "Os pionowa: ";
			cin >> osY1;
		}
	} while (CheckBoard(&osX1, &osY1) == false);
	board[osY1][osX1] = 2;
	do
	{
		while (osX2 < 0 || osX2 > 9)
		{
			REFRESH;
			cout << SELEDIN << "\nWybierz pole docelowe:\n\n";
			cout << SELEDIN << "Os pozioma: ";
			cin >> osX2;
		}
		while (osY2 < 0 || osY2 > 9)
		{
			REFRESH;
			cout << SELEDIN << "\nWybierz pole docelowe:\n\n";
			cout << SELEDIN << "Os pozioma: " << osX2 << "\n";
			cout << SELEDIN << "Os pionowa: ";
			cin >> osY2;
		}
	} while (CheckBoard(&osX2, &osY2) == false);
	board[osY2][osX2] = 3;

	for (int i = 0; i < 3; i++)
		if (!Algoritm(osX1, osY1, osX2, osY2, i))
			return 0;


	REFRESH;
	int count[3] = { 0, 0, 0 };
	int chosen = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			for (int u = 0; u < 10; u++)
			{
				if (returned[i][j][u] == 4)
					count[i]++;
			}
		}
	}
	if (count[1] <= count[0] && count[1] <= count[2])
		chosen = 1;
	if (count[2] <= count[0] && count[2] <= count[1])
		chosen = 2;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (returned[chosen][i][j] == 4)
				board[i][j] = returned[chosen][i][j];
		}
	}

	REFRESH;
	cout << WHITE << "\n\n";
	system("pause");
	return 0;
}

int Exponentiation(int x, int y)
{
	int z = x;
	for (int i = 1; i < y; i++)
		x = x * z;
	return x;
}

int Operation(int posX, int posY, int endX, int endY, int q)
{
	if (q == 0)
	{
		int a = (posX - endX);
		int b = (posY - endY);
		if (a < 0)
			a = a - (2 * a);
		if (b < 0)
			b = b - (2 * b);
		return a + b;
	}
	if (q == 1)
	{
		int a = endX + endY - posX - posY;
		if (a < 0)
			a = a - (2 * a);
		return a;
	}
	else
		return sqrt(Exponentiation((posX - endX), 2) + Exponentiation((posY - endY), 2));
}

bool CheckBoard(int *checkX, int *checkY)
{
	if (board[*checkY][*checkX] == 1)
	{
		*checkX = (-1);
		*checkY = (-1);
		cout << RED << "\nNie mozna ustawic punktu na przeszkodzie!\n\n";
		system("pause");
		return false;
	}
	return true;
}

bool ChooseDirection(int *posX, int *posY, int endX, int endY)
{
	int min = 100;
	int currentX = *posX;
	int currentY = *posY;
	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			if (dis[i][j] < min && closed[i][j] != 1)
			{
				min = dis[i][j];
				*posX = j;
				*posY = i;
			}
		}
	}
	if (cost[*posY][*posX] != 0)
		howMuch = cost[*posY][*posX];
	else
		howMuch++;
	closed[*posY][*posX] = 1;
	if (*posX == currentX && *posY == currentY)
		return false;
	if (*posX == 7 && *posY == 4)
	{
		int u = 2;
	}
	return true;
}

void Test()
{
	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			board[i][j] = 0;
			closed[i][j] = 0;
		}
	}
	/*board[0][0] = closed[0][0] = 1;
	board[1][0] = closed[1][0] = 1;
	board[2][0] = closed[2][0] = 1;
	board[3][0] = closed[3][0] = 1;
	board[0][6] = closed[0][6] = 1;
	board[0][7] = closed[0][7] = 1;
	board[0][8] = closed[0][8] = 1;
	board[0][9] = closed[0][9] = 1;
	board[1][7] = closed[1][7] = 1;
	board[1][9] = closed[1][9] = 1;
	board[2][6] = closed[2][6] = 1;
	board[3][6] = closed[3][6] = 1;
	board[3][7] = closed[3][7] = 1;
	board[4][2] = closed[4][2] = 1;
	board[4][3] = closed[4][3] = 1;
	board[5][4] = closed[5][4] = 1;
	board[5][5] = closed[5][5] = 1;
	board[5][6] = closed[5][6] = 1;
	board[6][2] = closed[6][2] = 1;
	board[7][1] = closed[7][1] = 1;
	board[7][3] = closed[7][3] = 1;
	board[8][0] = closed[8][0] = 1;
	board[8][9] = closed[8][9] = 1;
	board[9][6] = closed[9][6] = 1;
	board[9][8] = closed[9][8] = 1;
	board[9][9] = closed[9][9] = 1;*/

	board[8][0] = closed[8][0] = 1;
	board[4][0] = closed[4][0] = 1;
	board[4][1] = closed[4][1] = 1;
	board[4][2] = closed[4][2] = 1;
	board[5][2] = closed[5][2] = 1;
	board[5][5] = closed[5][5] = 1;
	board[5][6] = closed[5][6] = 1;
	board[5][8] = closed[5][8] = 1;
	board[4][5] = closed[4][5] = 1;
	board[3][5] = closed[3][5] = 1;
	board[1][5] = closed[1][5] = 1;
	board[3][6] = closed[3][6] = 1;
	board[1][7] = closed[1][7] = 1;
	board[0][8] = closed[0][8] = 1;
	board[2][9] = closed[2][9] = 1;
}

void NewBoards()
{
	//cost
	for (int i = 0; i <= 9; i++)
		cost[i] = new int[10]{ 0 };

	//parent
	for (int i = 0; i <= 9; i++)
		parent[i] = new int[10]{ 0 };

	for (int i = 0; i <= 9; i++)
		closed[i] = new int[10]{ 0 };

	//dis
	for (int i = 0; i <= 9; i++)
		dis[i] = new int[10]{ 0 };
	for (int i = 0; i <= 9; i++)
	{
		for (int j = 0; j <= 9; j++)
			dis[i][j] = 100;
	}
}

void GenerateBoard()
{
	RAND;
	int q; //zmienna przyjmujaca wartosc losowania przy ustawianiu przeszkod na planszy
	int pool = rand() % 25 + 10; //pula przeszkód na planszy
	bool done = false; //okresla, czy generowanie planszy zostalo ukonczone

	while (!done)
	{
		for (int i = 0; i <= 9; i++)
		{
			for (int j = 0; j <= 9; j++)
			{
				if (pool > 0)
				{
					q = rand() % 5;
					if (q == 0)
					{
						board[i][j] = 1;
						closed[i][j] = 1;
						pool--;
					}
				}
				else
				{
					done = true;
					break;
				}
			}
		}
	}
}

void DrawBoard()
{
	cout << GREY << "  0123456789\n\n";
	for (int i = 0; i <= 9; i++)
	{
		cout << GREY << i << " ";
		for (int j = 0; j <= 9; j++)
		{
			if (board[i][j] == 0)
				cout << WHITE << "#";
			if (board[i][j] == 1)
				cout << YELLOW << "#";
			if (board[i][j] == 2)
				cout << GREEN << "#";
			if (board[i][j] == 3)
				cout << BLUE << "#";
			if (board[i][j] == 4)
				cout << SELEDIN << "#";
		}
		cout << "\n";
	}
}

void Refresh()
{
	system("cls");
	DrawBoard();
}

void CheckDistances(int posX, int posY, int endX, int endY, int q)
{
	if (posY > 0)
	{
		if (closed[posY - 1][posX] != 1)
		{
			if (howMuch + 1 < cost[posY - 1][posX] || cost[posY - 1][posX] == 0)
			{
				parent[posY - 1][posX] = 1;
				cost[posY - 1][posX] = howMuch + 1;
			}
			dis[posY - 1][posX] = Operation(posX, posY - 1, endX, endY, q);
		}
	}
	if (posX < 10)
	{
		if (closed[posY][posX + 1] != 1)
		{
			if (howMuch + 1 < cost[posY][posX + 1] || cost[posY][posX + 1] == 0)
			{
				parent[posY][posX + 1] = 2;
				cost[posY][posX + 1] = howMuch + 1;
			}
			dis[posY][posX + 1] = Operation(posX + 1, posY, endX, endY, q);
		}
	}
	if (posY < 9)
	{
		if (closed[posY + 1][posX] != 1)
		{
			if (howMuch + 1 < cost[posY + 1][posX] || cost[posY + 1][posX] == 0)
			{
				parent[posY + 1][posX] = 3;
				cost[posY + 1][posX] = howMuch + 1;
			}
			dis[posY + 1][posX] = Operation(posX, posY + 1, endX, endY, q);
		}
	}
	if (posX > 0)
	{
		if (closed[posY][posX - 1] != 1)
		{
			if (howMuch + 1 < cost[posY][posX - 1] || cost[posY][posX - 1] == 0)
			{
				parent[posY][posX - 1] = 4;
				cost[posY][posX - 1] = howMuch + 1;
			}
			dis[posY][posX - 1] = Operation(posX - 1, posY, endX, endY, q);
		}
	}
}

void Finish(int osX1, int osY1, int osX2, int osY2, int q)
{
	int currentX = osX2;
	int currentY = osY2;
	bool done;
	while (currentX != osX1 || currentY != osY1)
	{
		done = false;
		if (!done && parent[currentY][currentX] == 1)
		{
			currentY++;
			done = true;
		}
		if (!done && parent[currentY][currentX] == 2)
		{
			currentX--;
			done = true;
		}
		if (!done && parent[currentY][currentX] == 3)
		{
			currentY--;
			done = true;
		}
		if (!done && parent[currentY][currentX] == 4)
		{
			currentX++;
			done = true;
		}
		if (currentX != osX1 || currentY != osY1)
		{
			returned[q][currentY][currentX] = 4;
		}
	}
}

bool Algoritm(int osX1, int osY1, int osX2, int osY2, int q)
{
	int posX = osX1;
	int posY = osY1;
	int count = 0;
	closed[posY][posX] = 1;
	dis[posY][posX] = Operation(posX, posY, osX2, osY2, q);
	while (posX != osX2 || posY != osY2)
	{
		CheckDistances(posX, posY, osX2, osY2, q);
		if (!ChooseDirection(&posX, &posY, osX2, osY2))
		{
			cout << SELEDIN << "\n\nNiestety, trasa pomiedzy dwoma wybranymi punktami jest nieosiagalna.\n\n";
			system("pause");
			return false;
		}
	}
	Finish(osX1, osY1, osX2, osY2, q);
	NewBoards();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (board[i][j] == 1)
				closed[i][j] = board[i][j];
		}
	}
	return true;
}
