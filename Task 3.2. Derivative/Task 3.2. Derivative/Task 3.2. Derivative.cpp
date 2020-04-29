// Task 3.2. Derivative.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <iostream>
#include <cmath>
#include <locale.h>
#include <iomanip>
#include <Windows.h>
const int nn = 200;
using namespace std;

double function(double x) {
	return exp(4.5 * x);
}
double derivative(double x) {
	return 4.5*exp(4.5*x);
}
double secondDerivative(double x) {
	return 20.25*exp(4.5*x);
}

double centralFormula(double x, double step) {
	return (function(x + step) - function(x - step)) / (2 * step);
}
double leftCentralFormula(double x, double step) {
	return (-3*function(x) +4*function(x + step) - function(x +2* step)) / (2 * step);
}
double rightCentralFormula(double x, double step) {
	return (3 * function(x) - 4 * function(x - step) + function(x - 2 * step)) / (2 * step);
}
double secondDerivativeFormula(double x, double step) {
	return (function(x + step) - 2 * function(x) + function(x - step)) / (step*step);
}

double ** createTable(double sizeOfTable, double leftBorder,double step) {
	double **table = new double*[sizeOfTable];
	for (int i = 0; i < sizeOfTable; i++) {
		table[i] = new double[6];
	}
	for (int i = 0; i < sizeOfTable; i++) {
		table[i][0] = leftBorder + i * step;
		table[i][1] = function(table[i][0]);
	}
	return table;
}

void updateTable(double ** table, double sizeOfTable,double step) {
	for (int i = 0; i < sizeOfTable; i++) {
		if (i == 0) {
			table[i][2] = leftCentralFormula(table[i][0], step);
			table[i][4] = NULL;
			table[i][5] = NULL;
			
		}
		else if (i == sizeOfTable - 1) {
			table[i][2] = rightCentralFormula(table[i][0], step);
			table[i][4] = NULL;
			table[i][5] = NULL;
		}
		else {
			table[i][2] = centralFormula(table[i][0], step);
			table[i][4] = secondDerivativeFormula(table[i][0], step);
			table[i][5] = fabs(table[i][4] - secondDerivative(table[i][0]));
		}
		table[i][3] = fabs(table[i][2] - derivative(table[i][0]));
	}
}

void printTable(double ** table, int sizeOfTable, int amOfColumns) {
	if (amOfColumns <= 2) {
		cout << " " << setw(64) << setfill('=') << '=' << endl;
		cout << setfill(' ');
		cout << " | " << setw(8) << left << "№ точки" << '\t' << " | " << setw(15) << left << "x" << '\t' << " | " << setw(15) << left << "f(x)";
		cout << "\t|\t\n";
		cout << " " << setw(64) << setfill('=') << '=' << endl;
		cout << setfill(' ');
	}
	
	else if (amOfColumns > 2) {
		cout << " " << setw(160) << setfill('=') << '=' << endl;
		cout << setfill(' ');
		cout << " | " << setw(8) << left << "№ точки" << '\t' << " | " << setw(15) << left << "x" << '\t' << " | " << setw(15) << left << "f(x)";
		cout << '\t' << " | " << setw(15) << left << "f'(x)" << '\t' << " | " << setw(15) << left << "|f\'(x)чд - f\'(x)т|" << '\t' << " | " << setw(15) << left << "f\"(x)" << '\t' << " | " << setw(15) << left << "|f\"(x)чд - f\"(x)т|";
		cout << "\t|\t\n";
		cout << " " << setw(160) << setfill('=') << '=' << endl;
		cout << setfill(' ');
	}

	for (int i = 0; i < sizeOfTable; i++) {
		cout << " | " << setw(8) << left << i + 1 ;
		for (int j = 0; j < amOfColumns; j++) {
		cout << '\t' << " | " << setw(15) << setprecision(15) << left;
		if (table[i][j]||(j<2))cout << table[i][j];
		else cout << "---";
		}
		cout<< "\t|" << '\t' << '\n';
	}
	if (amOfColumns <= 2) {
		cout << " " << setw(64) << setfill('=') << '=' << endl;
	}
	else {
		cout << " " << setw(160) << setfill('=') << '=' << endl;
	}
	cout << setfill(' ');
}
void printMenu() {
	cout << "Меню" << endl;
	cout << "1.Выбрать число значений в таблице" << endl;
	cout << "2.Выбрать первый узел таблицы" << endl;
	cout << "3.Выбрать шаг" << endl;
	cout << "4.Вычислить производные" << endl;
	cout << "0.Завершение работы" << endl;
	cout << "Выберите действие: ";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	HWND window_header = GetConsoleWindow();
	SetWindowPos(window_header, HWND_TOP, 0, 0, 1168, 768, NULL);
	double leftBorder, sizeOfTable, step;	
	bool isNumberSet = false;
	bool isLeftBorderSet = false;
	bool isStepSet = false;
	bool isTableCreated = false;
	double **table=createTable(1,1,1);
	int option = 1;
	while (option !=0) {
		if (isNumberSet)cout << "Текущее число элементов: " << sizeOfTable<<endl;
		if (isLeftBorderSet)cout << "Текущий первый узел: " << leftBorder<<endl;
		if (isStepSet)cout << "Текущий шаг: " << step<<endl;
		if (isTableCreated) printTable(table, sizeOfTable,2);
		printMenu();
		cin >> option;
		while (option < 0 || option>4) {
			cout << "Выберите корректную опцию: ";
			cin >> option;
		}

		if (option == 1) {
			if (isNumberSet)cout << "Текущее число элементов: " << sizeOfTable << endl;
			cout << "Введите число значений в таблице: ";
			cin >> sizeOfTable;
			while (sizeOfTable <= 0) {
				cout << "Введите корректное значение: ";
				cin >> sizeOfTable;
			}
			isNumberSet = true;
		}
		else if (option == 2) {
			if (isLeftBorderSet)cout << "Текущий первый узел: " << leftBorder << endl;
			cout << "Введите первый узел: ";
			cin >> leftBorder;
			isLeftBorderSet = true;
		}
		else if (option == 3) {
			if (isStepSet)cout << "Текущий шаг: " << step << endl;
			cout << "Введите шаг: ";
			cin >> step;
			isStepSet = true;
		}
		else if (option == 4) {
			updateTable(table, sizeOfTable, step);
			printTable(table, sizeOfTable, 6);
			cout << "Введите любое значение: ";
			int c;
			cin>>c;
		}
		if (isNumberSet&&isStepSet&&isLeftBorderSet) {
			table = createTable(sizeOfTable, leftBorder, step);
			isTableCreated = true;
		}
		system("cls");
		
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
