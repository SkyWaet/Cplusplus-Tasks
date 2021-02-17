// Interpolation.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <locale.h>
#include <iomanip>
#include <algorithm>
#include <windows.h>

using namespace std;
const int m = 20;

double function(double x) {
	return exp(-x) - x * x / 2;
}
double w(double x, double table[m+1], int n,int k) {
	double mult = 1;
	for (int i = 0; i <= n; i++) {
		if (i != k) mult *= (x - table[i]);
	}
	return mult;
}
double polynom(double table[], double x, int n) {
	double mult = 1;
	for (int i = 0; i < n-1; i++)
		mult *= (x-table[i]);
	return mult;
}
void printTable(double table[m+1],int amOfRows) {
	cout <<" "<< setw(64) << setfill('=')<<'='<< endl;
	cout << setfill(' ');
	cout <<" | "<< setw(8)<<left << "№ точки" <<'\t'<<" | " << setw(15) <<left<< "x" << '\t'<<" | " << setw(15) << left << "f(x)" <<"\t|\t\n";
	cout <<" "<< setw(64) << setfill('=') << '=' << endl;
	cout << setfill(' ');
	for (int i = 0; i < amOfRows; i++) {
		cout <<" | "<< setw(8)<<left <<i+1<<'\t'<<" | "<<setw(15)<<setprecision(15)<<left<< table[i] << '\t'<<" | " <<setw(15)<< setprecision(15)<<left<< function(table[i])<<"\t|"<<'\t'<<'\n';
	}
	cout <<" "<< setw(64) << setfill('=') << '=' << endl;
	cout << setfill(' ');
}
void tableSort(double table[m+1], double interPoint) {

	for (int i = 0; i < m ;i++ ) {
		for (int j = i + 1; j < m; j++)
			if (fabs(table[i] - interPoint) > fabs(table[j] - interPoint)) swap(table[i], table[j]);
		
	}
}
void Lagrange(double table[m+1], int n, double x) {
	cout << " Метод Лагранжа.\n";
	double sum = 0;
	double term = 0;
	for (int i = 0; i <= n; i++) {
		term = function(table[i])*w(x, table, n, i) / w(table[i], table, n, i);
		sum += term;
	}
	cout << " Значение f(x) в точке " << setprecision(15) << x << ": " << setprecision(15) << function(x) << endl;
	cout << " Значение Pn(x) в форме Лагранжа в точке "<<setprecision(15) << x << ": " <<setprecision(15)<< sum << endl;
	cout << " Значение погрешности: " << setprecision(15)<<fabs(function(x) - sum)<<endl;
	system("pause");
}

void Neuton(double table[m+1], int n, double x) {
	double neutonTable[m + 1][m + 1];
	for (int i = 0; i <= n; i++) {
		neutonTable[i][0] = table[i];
		neutonTable[i][1] = function(table[i]);
	}

	for (int j = 2; j <= n; j++) {
		for (int i = 0; i <= n-j+1; i++) {
			neutonTable[i][j] = (neutonTable[i + 1][j - 1] - neutonTable[i][j - 1]) / (table[i + j-1] - table[i]);
		}
	}

	double Pn = neutonTable[0][1];
	for (int i = 2; i <= n; i++) {
		Pn += neutonTable[0][i]*polynom(table,x,i);
	}
	cout << " Значение f(x) в точке " << setprecision(15) << x << ": " << setprecision(15) << function(x) << endl;
	cout << " Значение Pn(x) в форме Ньютона в точке " << setprecision(15) << x << ": " << setprecision(15) << Pn << endl;
	cout << " Значение погрешности: " << setprecision(15) << fabs(function(x) - Pn) << endl;
	system("pause");
}

void printHeader(int amount) {
	cout << " Задание №2. Алгебраическое интерполирование. Вариант 7\n";
	cout << " Число значений в таблице: " << amount<<endl;
}

void printMenu() {
	cout << endl << " Опции: "<<endl;
	cout << "  1: Выбрать точку интерполирования." << endl;
	cout << "  2: Задать степень интерполяционного полинома." << endl;
	cout << "  3: Выбрать способ интерполирования." << endl;
	cout << "  4: Завершить работу." << endl;
	cout << " Выберите одно из действий: ";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	printHeader(m+1);
	//system("mode con cols=100 lines=40");
	HWND window_header = GetConsoleWindow();
	SetWindowPos(window_header, HWND_TOP, 450, 25, 612, 768, NULL);
	double leftBorder, rightBorder;
	double interPoint;
	/*cout << "Введите число значений в таблице: ";
	cin >> n;*/
	cout << " Введите левую границу промежутка интерполирования: ";
	cin >> leftBorder;
	cout << " Введите правую границу промежутка интерполирования: ";
	cin>> rightBorder;
	double	table[m+1];
	double x = leftBorder;
	double h = (rightBorder - leftBorder) / m;
	for (int i = 0; i <= m; i++) {
		table[i] = x;
		x += h;
	}
	int n = m;
	int action = 1;
	bool isDegChosen = false;
	bool isPointChosen = false;

	while (action != 4) {
		system("cls");
		printHeader(n+1);
		if (isPointChosen)
			cout << " Точка интерполирования: " << interPoint << endl;
		if (isDegChosen)
			cout << " Степень интерполяционного полинома: " << n << endl;
		printTable(table, n+1);
		printMenu();
		cin >> action;
		while(action<1||action>4) {
			cout << " Введено некорректное значение. Попробуйте еще раз.\n";
			cout << " Выберите одно из действий: ";
			cin >> action;
		}	
		switch (action)
		{
		case 1: {
			system("cls");
			printHeader(n);
			if (isPointChosen)
				cout << " Текущая точка интерполирования: " << interPoint << endl;
			if (isDegChosen)
				cout << " Степень интерполяционного полинома: " << n << endl;
			cout << " Выбор точки интерполирования.\n";
			sort(table, table + n+1);
			printTable(table, n+1);
			cout << " Возможные варианты:\n";
			cout << " 1. Ввести значение вручную.\n";
			cout << " 2. Выбрать значение из таблицы.\n";
			cout << " Ваш выбор: ";
			int option;
			cin >> option;
			while (option < 1 || option>2) {
				cout << " Введите корректное значение: ";
				cin >> option;
			}
			if (option == 1) {
				cout << " Введите точку интерполирования: ";
				cin >> interPoint;
			}
			else if (option == 2) {
				cout << " Введите номер выбранной точки: ";
				int number;
				cin >> number ;
				interPoint = table[number-1];
			}
			cout << "Точка интерполирования успешно выбрана." << endl;
			isPointChosen = true;
			tableSort(table, interPoint);
			system("pause");
			break;
			
		}
		case 2: {
			system("cls");
			printHeader(n);
			if (isPointChosen)
				cout << " Точка интерполирования: " << interPoint << endl;
			if (isDegChosen)
				cout << " Текущая степень интерполяционного полинома: " << n << endl;
			cout << " Задание степени интерполяционного полинома.\n";
			printTable(table, n+1);
			cout << " Максимальная допустимая степень полинома - "<<m<<".\n";
			cout << " Введите степень полинома: ";
			cin >> n;
			while (n>m) {				
				cout << " Степень полинома слишком большая. Введите подходящее значение: ";
				cin >> n;
			}
			cout << " Степень полинома успешно выбрана. " << endl;
			isDegChosen = true;
			system("pause");
			break;

		}
		case 3: {
			system("cls");
			if (isDegChosen&&isPointChosen) {
				cout << " Точка интерполирования: " << interPoint << endl;
				cout << " Степень интерполяционного полинома: " << n << endl;
				cout << " Выбор метода интерполирования.\n";
				cout << " 1. Метод Лагранжа.\n";
				cout << " 2. Метод Ньютона.\n";
				cout << " Выберите метод: ";
				int method;
				cin >> method;
				while (method < 1 || method>2) {
					cout << " Введите корректное значение: ";
					cin >> method;
				}
				if (method == 1)Lagrange(table, n, interPoint);
				else Neuton(table, n, interPoint);
				isDegChosen = false;
				//isPointChosen = false;
			}
			else cout << "Ошибка: не выбраны точка интерполирования или степень полинома. Пожалуйста, повторите пункты 1-2" << endl;
			break;
		}
			default: break;
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
