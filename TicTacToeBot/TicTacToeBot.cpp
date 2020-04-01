
#include <iostream>

using namespace std;

const int ROW = 3;//строки
const int COL = 3;//столбцы
char ticTacToe[ROW][COL];
int botPriority[18] = { 1, 1, 0, 0, 2, 2, 0, 2, 2, 0, 0, 1, 1, 0, 1, 2, 2, 1 };


int row, col, k, o, p, q, rowBot, colBot;
bool winX, winO, flag;
char gameOver;

void Print();
bool Check(char symbol);
void Step(char symbol);
void Bot(char symbol, char aSymbol);
void Interfere(char symbol, char aSymbol);

int main()
{
	setlocale(LC_ALL, "rus");
	do
	{
		winX = false;
		winO = false;
		//Заполнение пробелами
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				ticTacToe[i][j] = ' ';
			}
		}
		Print();
		for (int i = 1; i <= 9; i++)
		{
			if (i % 2 != 0)//Выбор игрока
			{
				cout << "Ход крестика" << endl;
				Bot('X', 'O');
				Print();
			}
			else
			{
				cout << "Ход нолика" << endl;
				Step('O');
				Print();
			}
			//Если ход больше 5, то проверяем на выигрыш
			if (i >= 5)
			{
				winX = Check('X');
				if (winX)
				{
					break;
				}
				winO = Check('O');
				if (winO)
				{
					break;
				}
			}
		}
		//Проверка, чья победа
		if (winX) 
		{
			cout << "Крестик победил!" << endl;
		}
		else if (winO)
		{
			cout << "Нолик победил!" << endl;
		}
		else
		{
			cout << "Ничья" << endl;
		}
		cout << "Сыграем еще раз? "; cin >> gameOver; cout << endl;
	} while (gameOver == 'Y' || gameOver == 'y');
	cout << "Выход" << endl;
}
//Вывод
void Print()
{
	system("cls");
	cout << "   1 2 3" << endl;
	cout << "  -------" << endl;
	for (int n = 0; n < ROW; n++)
	{
		cout << n + 1 << " |";
		for (int m = 0; m < COL; m++)
		{
			cout << ticTacToe[n][m] << '|';
		}
		cout << endl << "  -------" << endl;
	}
}
//Бот
void Bot(char symbol, char aSymbol)
{
	flag = false;
	Interfere(symbol, aSymbol);
	if (rowBot != -1)//проверка на строки
	{
		for (int m = 0; m < COL; m++)
		{
			if (ticTacToe[rowBot][m] == ' ')
			{
				ticTacToe[rowBot][m] = symbol;
				flag = true;
				break;
			}
			if (m == 3)
			{
				flag = true;
				break;
			}
		}
	}
	else if (colBot != -1)//проверка на столбцы
	{
		for (int m = 0; m < ROW; m++)
		{
			if (ticTacToe[m][colBot] == ' ')
			{
				ticTacToe[m][colBot] = symbol;
				flag = true;
				break;
			}
			if (m == 3)
			{
				flag = true;
				break;
			}
		}
	}
	if (flag == false)
	{
		//если проверка не проходит
		o = 0;
		p = 0;
		q = 0;
		do
		{
			p = botPriority[o];
			o++;
			q = botPriority[o];
			o++;
			if (ticTacToe[p][q] == ' ')
			{
				ticTacToe[p][q] = symbol;
				break;
			}
			if (o >= 18)
			{
				break;
			}
		} while (true);
	}
}
//Ход
void Step(char symbol)
{
	cout << "Введите координату строку(row)(1-3): "; cin >> row; row--;
	cout << "Введите координату столбец(col)(1-3): "; cin >> col; col--;
	while (ticTacToe[row][col] != ' ' || row > ROW - 1 || col > COL - 1 || row < 0 || col < 0)
	{
		cout << "Вы ввели неверные координаты" << endl;
		cout << "Повторите ввод" << endl;
		cout << "Введите координату строку(row)(1-3): "; cin >> row; row--;
		cout << "Введите координату столбец(col)(1-3): "; cin >> col; col--;
	}
	ticTacToe[row][col] = symbol;
}
//проверка на победу
bool Check(char symbol)
{
	//по строкам
	for (int j = 0; j < ROW; j++)
	{
		for (k = 0; k < COL; k++)
		{
			if (ticTacToe[j][k] != symbol)
			{
				break;
			}
		}
		if (k == 3)
		{
			return true;
		}
	}
	//по столбцам
	for (int j = 0; j < ROW; j++)
	{
		for (k = 0; k < COL; k++)
		{
			if (ticTacToe[k][j] != symbol)
			{
				break;
			}
		}
		if (k == 3)
		{
			return true;
		}
	}
	//диагональ прямая
	for (k = 0; k < ROW; k++)
	{
		if (ticTacToe[k][k] != symbol)
		{
			break;
		}
	}
	if (k == 3)
	{
		return true;
	}
	//диагональ обратная
	for (k = 0; k < ROW; k++)
	{
		if (ticTacToe[ROW - k - 1][k] != symbol)
		{
			break;
		}
	}
	if (k == 3)
	{
		return true;
	}
	return false;
}
//проверка на возможность помешать выигрышу
void Interfere(char symbol, char aSymbol)
{
	rowBot = -1;
	colBot = -1;
	//по строкам
	o = 0;
	for (int j = 0; j < ROW; j++)
	{
		o = 0;
		for (k = 0; k < COL; k++)
		{
			if (ticTacToe[j][k] == aSymbol)
			{
				o++;
			}
		}
		if (o == 2)
		{
			rowBot = j;
			break;
		}
	}
	//по столбцам
	o = 0;
	for (int j = 0; j < ROW; j++)
	{
		o = 0;
		for (k = 0; k < COL; k++)
		{
			if (ticTacToe[k][j] == aSymbol)
			{
				o++;
			}
		}
		if (o == 2)
		{
			colBot = j;
			break;
		}
	}
}