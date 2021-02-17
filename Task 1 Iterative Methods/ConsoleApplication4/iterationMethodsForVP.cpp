// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <locale.h>
#include <cmath>

using namespace std;
int numOfTask;
double epsilon = pow(10, -5);
double rho = 0.4;
double r = 10;

double f(double x) {
	if (numOfTask == 1) return (10 * cos(x) - 0.1*x*x);
	else return (x*x*x - 3 * x*x*r + 4 * r*r*r*rho);
}

double derivative(double x) {
	if (numOfTask == 1) return (-10 * sin(x) - 0.2*x);
	else return (3 * x*x - 6 * x*r);
}

void bisection(double leftBorder, double rightBorder) {
	cout << "Метод бисекции\n";
	double c = 0;
	double a = leftBorder, b = rightBorder;
	int N = 0;
	cout << "	Начальное приближение: " << (a + b) / 2<<endl;
	while (fabs(b-a) >= 2 * epsilon)
	{	
		c = (a + b) / 2;
		if (f(a)*f(c) <0) b = c;
		else if (f(c)*f(b) < 0) a = c;
		N++;
		
	}
	cout << "	Количество шагов: " << N << endl;
	cout << "	Приближенное решение: " << c << endl;
	cout << "	Длина последнего отрезка: " << fabs(b - a) << endl;
	cout << "	Невязка: " << fabs(f(c)) << endl;;
}

void newton(double leftBorder, double rightBorder) {
	cout << "Метод Ньютона\n";
	double xn1, xn;
	int N = 0;
	if (derivative(rightBorder) != 0) {
		xn1 = rightBorder; xn = leftBorder;
	}

	else if (derivative(leftBorder) != 0) {
		xn1 = leftBorder; xn = rightBorder;
	}

	cout << "	Начальное приближение: " << xn1 << endl;
	while (fabs(xn - xn1) > epsilon) {
		xn1 = xn;
		xn = xn1 - f(xn1) / derivative(xn1);
		N++;
	}
	cout << "	Количество шагов: " << N << endl;
	cout << "	Приближенное решение: " << xn << endl;
	cout << "	|x_n - x_(n-1)| = " << fabs(xn - xn1) << endl;
	cout << "	Невязка: " << fabs(f(xn))<<endl;

}
void upgradedNewton(double leftBorder, double rightBorder) {
	cout << "Модифицированный метод Ньютона\n";
	double xn1, xn,x0;
	int N = 0;
	if (derivative(rightBorder) != 0) {
		xn1 = rightBorder; xn = leftBorder;
	}

	else if (derivative(leftBorder) != 0) {
		xn1 = leftBorder; xn = rightBorder;
	}
	x0 = xn1;
	cout << "	Начальное приближение: " << xn1 << endl;
	while (fabs(xn - xn1) > epsilon) {
		xn1 = xn;
		xn = xn1 - f(xn1) / derivative(x0);
		N++;
	}
	cout << "	Количество шагов: " << N << endl;
	cout << "	Приближенное решение: " << xn << endl;
	cout << "	|x_n - x_(n-1)| = " << fabs(xn - xn1) << endl;
	cout << "	Невязка: " << fabs(f(xn))<<endl;
}

void secant(double leftBorder, double rightBorder) {
	cout << "Метод секущих\n";
	double xn2,xn1,xn;
	int N = 0;
	xn1 = rightBorder; 
	xn2 = leftBorder;
	xn = xn1 - f(xn1)*(xn1 - xn2) / (f(xn1) - f(xn2));
	cout << "	Начальное приближение: " << xn2 << endl;
	while (fabs(xn - xn1) > epsilon) {
		xn2 = xn1;
		xn1 = xn;
		xn = xn1 - f(xn1)*(xn1-xn2)/(f(xn1)-f(xn2));
		N++;		
	}
	cout << "	Количество шагов: " << N << endl;
	cout << "	Приближенное решение: " << xn << endl;
	cout << "	|x_n - x_(n-1)| = " << fabs(xn - xn1) << endl;
	cout << "	Невязка: " << fabs(f(xn))<<endl;
}

int main()
{
	setlocale(LC_ALL,"Russian");
	double A, B,h;
	int amOfparts = 100;
	cout << "Введите номер задачи: ";
	cin >> numOfTask;
	cout << numOfTask << endl;
	if (numOfTask == 1) {
	cout << "Введите границы отрезка: ";
	cin >> A >> B;
	cout << "\n";
	h = (B - A) / amOfparts;
	int counter = 0;
	double leftBorder = A;
	double rightBorder = A + h;
	
		for (int i = 0; i < amOfparts; i++) {
			if (f(leftBorder)*f(rightBorder) <= 0) {
				cout << "Отрезок [" << leftBorder << "," << rightBorder << "]\n";
				bisection(leftBorder, rightBorder);
				newton(leftBorder, rightBorder);
				upgradedNewton(leftBorder, rightBorder);
				secant(leftBorder, rightBorder);
				counter++;
				cout << "\n";
			}
			leftBorder = rightBorder;
			rightBorder += h;

		}
		cout << "Количество отрезков: " << counter;
	}
	else newton(0, 2*r);
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
