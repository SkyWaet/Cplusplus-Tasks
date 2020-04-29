// Task 3.1. ReverseInterp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <locale.h>
#include <iomanip>
//#include <algorithm>
#include <windows.h>
const int nn=200;
using namespace std;

double function(double x) {
	return exp(-x) - x * x / 2;
}

double polynom(double **table, double x, int n) {
	double mult = 1;
	for (int i = 0; i < n - 1; i++)
		mult *= (x - table[i][0]);
	return mult;
}

double ** createTable(int sizeOfTable,double a, double b) {
	double h = (b - a) / (sizeOfTable-1);
	double **table = new double*[sizeOfTable];
	for (int i = 0; i < sizeOfTable; i++) {
		table[i] = new double[2];
	}
	for (int i = 0; i < sizeOfTable; i++) {
		table[i][0] = a + i * h;
		table[i][1] = function(table[i][0]);
	}
	return table;
}

double ** reverseTable(double** table, int sizeOfTable) {
	double **reversedTable = new double*[sizeOfTable];
	for (int i = 0; i < sizeOfTable; i++) {
		reversedTable[i] = new double[2];
	}
	for (int i = 0; i < sizeOfTable; i++) {
		reversedTable[i][0] = table[i][1];
		reversedTable[i][1] = table[i][0];
	}
	return reversedTable;
}

void tableSort(double **table, int sizeOfTable, double x) {
	double *elem;
	for(int i=0;i<sizeOfTable-1;i++)
		for (int j = i; j < sizeOfTable; j++) {
			if (fabs(x - table[i][0]) > fabs(x - table[j][0])) {
				elem = table[j];
				table[j] = table[i];
				table[i] = elem;
			}
		}
}

void Neuton(double **table, int sizeOfTable, double F) {
	double **neutonTable = new double*[sizeOfTable];
	for (int i = 0; i < sizeOfTable; i++) {
		neutonTable[i] = new double[sizeOfTable];
	}
	
	for (int i = 0; i <sizeOfTable; i++) {
		neutonTable[i][0] = table[i][0];
		neutonTable[i][1] = table[i][1];
	}

	for (int j = 2; j < sizeOfTable; j++) {
		for (int i = 0; i < sizeOfTable - j + 1; i++) {
			neutonTable[i][j] = (neutonTable[i + 1][j - 1] - neutonTable[i][j - 1]) / (table[i + j - 1][0] - table[i][0]);
		}
	}

	double Pn = neutonTable[0][1];
	for (int i = 2; i < sizeOfTable; i++) {
		Pn += neutonTable[0][i] * polynom(table, F, i);
	}
	cout << " Значение F: " << setprecision(15) << F<< endl;
	cout << "Искомый аргумент функции: " << setprecision(15) << Pn << endl;
	cout << " Значение f(Pn(F)) в форме Ньютона в точке " << setprecision(15) << F << ": " << setprecision(15) << function(Pn) << endl;
	cout << " Значение погрешности: " << setprecision(15) << fabs(function(Pn) - F) << endl;
	system("pause");
}

void printTable(double ** table, int sizeOfTable, int tableType) {
	if (tableType == 1) {
		cout << " " << setw(64) << setfill('=') << '=' << endl;
		cout << setfill(' ');
		cout << " | " << setw(8) << left << "№ точки" << '\t' << " | " << setw(15) << left << "x" << '\t' << " | " << setw(15) << left << "f(x)";
		cout << "\t|\t\n";
		cout << " " << setw(64) << setfill('=') << '=' << endl;
		cout << setfill(' ');
	}
	else {
		cout << " " << setw(64) << setfill('=') << '=' << endl;
		cout << setfill(' ');
		cout << " | " << setw(8) << left << "№ точки" << '\t' << " | " << setw(15) << left << "f(x)" << '\t' << " | " << setw(15) << left << "(f(x))^(-1)";
		cout << "\t|\t\n";
		cout << " " << setw(64) << setfill('=') << '=' << endl;
		cout << setfill(' ');
	}
	

	for (int i = 0; i < sizeOfTable; i++) {
		cout << " | " << setw(8) << left << i + 1;
		for (int j = 0; j < 2; j++) {
				cout << '\t' << " | " << setw(15) << setprecision(15) << left;
				if (table[i][j] || (j < 2))cout << table[i][j];
				else cout << "---";
			}
			cout << "\t|" << '\t' << '\n';
		}

		cout << " " << setw(64) << setfill('=') << '=' << endl;
	
	cout << setfill(' ');
}
void printMenu() {
	cout << "Меню" << endl;
	cout << "1.Выбрать число значений в таблице" << endl;
	cout << "2.Выбрать левую границу" << endl;
	cout << "3.Выбрать правую границу" << endl;
	cout << "4.Выбрать точку обратного интерполирования" << endl;
	cout << "5.Выполнить обратное интерполирование" << endl;
	cout << "0.Завершение работы" << endl;
	cout << "Выберите действие: ";
}

int main() {
	setlocale(LC_ALL, "Russian");
	HWND window_header = GetConsoleWindow();
	SetWindowPos(window_header, HWND_TOP, 0, 0, 1168, 768, NULL);
	int sizeOfTable;
	double a, b, F;
	double** table = createTable(1, 1, 1);
	bool isSizeSet = false;
	bool isAset = false;
	bool isBset= false;
	bool isFset = false;
	bool isTableCreated = false;
	int option = 1;
	while (option != 0) {
		if (isSizeSet)cout << "Текущее число элементов: " << sizeOfTable << endl;
		if (isAset)cout << "Текущий левая граница: " << a << endl;
		if (isBset)cout << "Текущая правая граница: " << b << endl;
		if (isFset)cout << "Текущая точка обратного интерполирования: " << F << endl;
		if (isTableCreated) printTable(table, sizeOfTable, 1);
		printMenu();
		cin >> option;

		while (option < 0 || option>5) {
			cout << "Выберите корректную опцию: ";
			cin >> option;
		}
		cout << endl;
		switch (option) {
		case 1: {
			if (isSizeSet)cout << "Текущее число элементов: " << sizeOfTable << endl;
			cout << "Введите число элементов таблицы: ";
			cin >> sizeOfTable;
			while (sizeOfTable <= 0) {
				cout << "Введите корректное значение: ";
				cin >> sizeOfTable;
			}
			isSizeSet = true;
			break;
		}
		case 2: {
			if (isAset)cout << "Текущий левая граница: " << a << endl;
			cout << "Введите левую границу: ";
			cin >> a;
			isAset = true;
			break;
		}
		case 3: {
			if (isBset)cout << "Текущая правая граница: " << b << endl;
			cout << "Введите правую границу: ";
			cin >> b;
			isBset = true;
			break;
		}
		case 4: {
			if (isFset)cout << "Текущая точка обратного интерполирования: " << F << endl;
			int choosePoint = 0;
			cout << "1.Ввести значение вручную" << endl;
			cout << "2.Выбрать значение из таблицы" << endl;
			cout << "Выберите действие: ";
			cin >> choosePoint;
			while (choosePoint < 1 || choosePoint>2) {
				cout << "Введите корректное значение";
				cin >> choosePoint;
			}
			if (choosePoint == 1) {
				cout << "Введите точку обратного интерполирования: ";
				cin >> F;
			}
			else {
				cout << "Выберите значение из таблицы: ";
				int num;
				cin >> num;
				F = table[num - 1][1];
			}
			isFset = true;
			break;
		}
		case 5: {
			if (isFset) {
				if (isTableCreated) {
					double **reversedTable = reverseTable(table, sizeOfTable);
					cout << "Обращенная таблица: " << endl;
					tableSort(reversedTable, sizeOfTable, F);
					printTable(reversedTable, sizeOfTable, 2);
					Neuton(reversedTable, sizeOfTable, F);
				}
				else {
					if (!isAset)cout << " Не задана левая граница" << endl;
					else if (!isBset)cout << " Не задана правая граница" << endl;
					else if (!isSizeSet)cout << " Не задан размер таблицы" << endl;
				}
			}
			else cout << "Не выбрана точка обратного интерполирования" << endl;
			break;
		}
		default: {
			cout << "Выбрано некорректное значение" << endl;
			break;
		}
		}
		if (isAset&&isBset&&isSizeSet) {
			table = createTable(sizeOfTable, a, b);
			isTableCreated = true;
		}
		system("cls");

	}
	
	return 0;
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
