// Task5 Gauss.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cmath>

double function(double x) {
	return exp(x)*sqrt(1 - x);
}

double funcWithoutWeight(double x) {
	return exp(x);
}

double simpson(double lb, double rb) {
	double sum1 = 0;
	double sum2 = 0;
	int m = 3;
	double h = (rb - lb) / m;
	double b = lb + h;
	double a = lb;
	for (int i = 0; i < m; i++) {
		sum1 += function(a + h / 2);
		a += h;
	}
	for (int i = 0; i < m - 1; i++) {
		sum2 += function(b);
		b += h;
	}
	return h * (function(lb) + function(rb) + +4 * sum1 + 2 * sum2) / 6;
}

double integral(double lb, double rb,int i) {
	if(i==0) return 2*(pow(1-rb,5.0/2)*(10*rb-3)- pow(1 - lb, 5.0/2)*(10 * lb - 3))/35;
	else if (i == 1) return -8 * (pow(1 - rb, 5.0/2)*(5 * rb + 2) - pow(1 - lb, 5.0/2)*(5 * lb + 2))/35;
	else return -2*(pow(1 - rb, 3.0/2)*(30 * rb*rb + 3 * rb + 2) - (pow(1 - lb, 3.0/2)*(30 * lb*lb + 3 * lb + 2)))/105;
}

double interpFormula(double lb, double rb, double* points, int amOfPoints) {
	double* Ak = new double[amOfPoints];
	for (int i = 0; i < amOfPoints; i++) {
		double ans = integral(lb, rb,i);
	//	std::cout << i+1 << " " << ans << std::endl;
	//	using namespace std;
	//	cout << "A" << i << " = " << ans << endl;
		Ak[i] = ans;
	}
	double sum = 0;
	for (int i = 0; i < amOfPoints; i++) {
		sum += Ak[i] * funcWithoutWeight(points[i]);
	}
	return sum;
}

double gauss(double lb, double rb) {
	double sum = (rb + lb) / 2;
	double sub = (rb - lb) / 2;
	std::cout << "Ak = " << sub << std::endl;
	std::cout << " x1 = " << -sub / sqrt(3) + sum << " x2 = " << sub / sqrt(3) + sum << std::endl;
	return sub * (function(-sub / sqrt(3) + sum) + function(sub / sqrt(3) + sum));
}

double GaussType(double lb, double rb) {
	double m0 = -2 * (pow(1 - rb, 3.0 / 2) - pow(1 - lb, 3.0 / 2))/3;
	double m1 = -2 * (pow(1 - rb, 3.0 / 2)*(3 * rb + 2) - pow(1 - lb, 3.0 / 2)*(3 * lb + 2))/15;
	double m2 = -2 * (pow(1 - rb, 3.0 / 2)*(15 * rb * rb + 12 * rb + 8) - pow(1 - lb, 3.0 / 2)*(15 * lb * lb + 12 * lb + 8)) / 105;
	double m3 = -2 * (pow(1 - rb, 3.0 / 2)*(35 * rb * rb * rb + 30 * rb * rb + 24 * rb + 16) - pow(1 - lb, 3.0 / 2)*(5 * lb * lb * lb + 30 * lb * lb + 24 * lb + 16)) / 315;
	double a1 = (m0*m3 - m2 * m1) / (m1*m1 - m2 * m0);
	double a2 = (m2*m2 - m3 * m1) / (m1*m1 - m2 * m0);
	double discrim = a1 * a1 - 4 * a2;
	double x1 = ( - a1+sqrt(discrim)) / 2.0;
	double x2 = (-a1-sqrt(discrim)) / 2.0;
	double A1 = (m1 - x2 * m0) / (x1 - x2);
	double A2 = (m1 - x1 * m0) / (x2 - x1);
	using namespace std;
	cout << "x1 = " << x1 << " " << "x2 = " << x2 << endl;
	cout << "A1 = " << A1 << " " << "A2 = " << A2 << endl;
	double ans = A1 * funcWithoutWeight(x1) + A2 * funcWithoutWeight(x2);
	return ans;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	double accValue = 1.03008;
	double a = 0;
	double b = 1;
	char option = 'y';
	//while (option!='n') {
		using namespace std;
		cout << " Задание №5. Квадратурные формулы наибольшей АСТ. Вариант 7" << endl;
		cout << " Интегрируемая функция: e^x*sqrt(1-x)" << endl;
		/*cout << "Введите левую границу промежукта интегрирования: " << endl;
		cin >> a;
		cout << "Введите правую границу промежукта интегрирования: " << endl;
		cin >> b;*/
		std::cout << " Точное значение: " << accValue << std::endl << endl;
		std::cout << " Значение по формуле Симпсона: " << simpson(a, b) << endl;
		cout<<" Погрешность формулы Симпсона: "<<fabs(simpson(a, b) - accValue) << std::endl << endl;
		std::cout << " Значение по формуле Гаусса:" << gauss(a, b) << endl;
		cout<<" Погрешность формулы Гаусса "<< fabs(gauss(a, b) - accValue) << std::endl << endl;
		double points[3] = { 0,0.5,1 };
		std::cout << " Значение по интерполяционной КФ: " << interpFormula(a, b, points, 3) << endl;
		cout<<" Погрешность интерполяционной КФ: "<< fabs(interpFormula(a, b, points, 3) - accValue) << std::endl << endl;
		std::cout << " Значение по КФ типа Гаусса: " << GaussType(a, b) << endl;
		cout<<" Погрешность КФ типа Гаусса: " << fabs(GaussType(a, b) - accValue) << endl;
	//}
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
