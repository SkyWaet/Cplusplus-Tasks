// Task 5 Integrals.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <locale.h>
#include <iomanip>
#include <Windows.h>
#include <queue>
using namespace std;

struct polynom {
	int deg;
	double* coeff;
};

double f(double x, polynom otpional) {
	return exp(x);
}

double F(double a, double b, polynom optional) {
	return exp(b)-exp(a);
}

double p(double x, polynom params) {
	double result = 0;
	for (int i = 0; i <= params.deg; i++) {
		if (x < 0) {
			if (i % 2 == 0) result += pow(fabs(x), i)*params.coeff[i];
			else result -= pow(fabs(x), i)*params.coeff[i];
		}
		else result += pow(x, i)*params.coeff[i];
		
	}
	return result;
}

double P(double a, double b, polynom params) {
	double result = 0;
	for (int i = 0; i <= params.deg; i++) {
		result += params.coeff[i]*(pow(b, i+1)-pow(a,i+1))/(i+1);
	}
	return result;
}

void printPolynom(polynom pol) {
	for (int i = pol.deg; i >= 0; i--) {
		if (pol.coeff[i] == 0) continue;
		if (i != pol.deg) cout << "+ ";
		if (pol.coeff[i] != 1)cout << pol.coeff[i];
		if(i!=0) cout<< "t";
		if(i>=1)cout<<"^"<<i;
		if(i==0&& pol.coeff[i] == 1)cout << pol.coeff[i];
		
	}
}

polynom createPolynom() {
	cout << "Введите степень полинома: ";
	int deg;
	cin >> deg;
	polynom pol;
	pol.deg = deg;
	pol.coeff = new double[pol.deg + 1];
	for (int i = deg; i >= 0; i--) {
		cout << "Введите " << i << "-ый коэффициент полинома: ";
		cin >> pol.coeff[i];
	}
	printPolynom(pol);
	cout << endl;
	return pol;
}



double leftRectangles(double lb, double rb, int m, polynom params, double(*func)(double x, polynom otpional)) {
	double result = 0;
	double a = lb;
	double h = (rb - lb) / m;
	for (int i = 0; i < m ; i++) {
		result += func(a, params);
		a += h;
	}
	return result * h;
}

double rightRectangles(double lb, double rb, int m, polynom params, double(*func)(double x, polynom otpional)) {
	double result = 0;
	double h = (rb - lb) / m;
	double b = lb+h;
	for (int i = 0; i < m; i++) {
		result += func(b, params);
		b += h;
	}
	return result * h;
}

double middleRectangles(double lb, double rb, int m, polynom params, double(*func)(double x, polynom otpional)) {
	double result = 0;
	double h = (rb - lb) / m;
	double b = lb;
	for (int i = 0; i < m; i++) {
		result += func(b+h/2, params);
		b += h;
	}
	return result * h;
}
double trapeze(double lb, double rb, int m, polynom params, double(*func)(double x, polynom otpional)) {
	double result = 0;
	double h = (rb - lb) / m;
	double b = lb+h;
	for (int i = 0; i < m-1; i++) {
		result += func(b, params);
		b += h;
	}
	return h*(func(lb,params)+func(rb,params)+2*result)/2;
}

double simpson(double lb, double rb, int m, polynom params, double(*func)(double x, polynom otpional)) {
	double sum1 = 0;
	double sum2 = 0;
	double h = (rb - lb) / m;
	double b = lb + h;
	double a = lb;
	for (int i = 0; i < m ; i++) {
		sum1 += func(a+h/2, params);
		a += h;
	}
	for (int i = 0; i < m - 1; i++) {
		sum2 += func(b, params);
		b += h;
	}
	return h * (func(lb, params) + func(rb, params) + 4*sum1 + 2 * sum2) / 6;
}

polynom derive(polynom pol) {
	polynom derivedPol;
	derivedPol.deg = pol.deg - 1;
	if (pol.deg > 0) {
		derivedPol.coeff = new double[pol.deg+1];
		for (int i = 1; i <= pol.deg; i++) {
			derivedPol.coeff[i - 1] = pol.coeff[i] * i;
		}
		derivedPol.deg = pol.deg - 1;
		//cout << derivedPol.deg << endl;
	}
	else {
		derivedPol.deg = 0;
		derivedPol.coeff = new double[derivedPol.deg+1];
		derivedPol.coeff[0] = 0;
	}
	return derivedPol;
}

double findMax(double lb,double rb, polynom pol) {
	polynom derivedPol = derive(pol);
	double c = 0;
	
	double amOfParts = 100;
	double a = lb, b = rb;
	double h = (b - a) / amOfParts;
	double epsilon = h/100;
	b = a + h;
	queue<double> candidates;
	candidates.push(lb);
	candidates.push(rb);
	for (int i = 0; i < amOfParts; i++) {
		if (p(a,derivedPol)*p(b,derivedPol) <= 0) {
			int N = 0;
			//cout << "Начальное приближение: " << (a + b) / 2 << endl;
			while (fabs(b - a) >= 2 * epsilon)
			{
				c = (a + b) / 2;
				if (p(a, derivedPol)*p(c, derivedPol) <= 0) b = c;
				else if (p(c, derivedPol)*p(b, derivedPol) < 0) a = c;
				N++;
				
			}
			//cout << "-1: " << p(-1, derivedPol);
			//cout << "Roots" << c<<" ";
			if ((p(c - 10*epsilon, derivedPol) > 0) && (p(c + 10*epsilon, derivedPol) < 0)) candidates.push(c);			
		}
		a = b;
		b = a + h;
	}
	double max = 0;
	double maxElem;
	while (!candidates.empty()) {
		double elem = candidates.front();
		if (fabs(p(elem, pol)) > max) {
			max = fabs(p(elem, pol));
			maxElem = elem;
		}
		candidates.pop();
	}
	return max;
}
double error(double A,double B,int m, int method, int fNum,polynom pol) {
	double Md;
	double h = (B - A) / m;
	if (fNum == 1) {
		Md = exp(B);
	}
	else {
		if (method ==1 ||method ==2) Md = findMax(A, B, derive(pol));
		else if (method == 3 || method == 4) Md = findMax(A, B, derive(derive(pol)));
		else {
			Md = findMax(A, B, derive(derive(derive(derive(pol)))));
		}
	}
	
	if (method == 1||method == 2) {
		return 0.5*Md*(B - A)*h;
	}
	else if (method == 3) {
		return Md * (B - A)*h*h / 24;
	}
	else if (method == 4) {
		return Md * (B - A)*h*h / 12;
	}
	else {
		return Md * (B - A)*h*h*h*h / 2880;
	}
}

void printHeader() {
	cout << " Задача 4. Вычисление интегралов по квадратурным формулам. Вариант 7." << endl<<endl;
	//cout << " Функция: e^(-x) - x^2/2" << endl << endl;;
}

void printMenu() {
	cout << "Меню" << endl;
	cout << "1.Выбрать отрезок интегрирования" << endl;
	cout << "2.Выбрать число промежутков" << endl;
	cout << "3.Выбрать функцию" << endl;
	cout << "4.Выбрать метод интегрирования" << endl;
	cout << "5.Проинтегрировать функцию" << endl;
	cout << "0.Выход" << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double A = -1,B=10,m=100;
	double leftBorder, rightBorder;
	polynom pol;
	pol.deg = 1;
	pol.coeff = new double[2];
	//pol = createPolynom();
	//cout << "Derivative "<<endl;
	//printPolynom(derive(pol));
	//cout << endl;
	//printPolynom(pol);
	//cout << endl;
//	cout << "Max "<<findMax(A, B, pol) << endl;
	//cout << p(10, pol) << endl;
	/*printPolynom(derive(pol));
	pol.deg = 10;
	pol.coeff = new double[pol.deg];
	pol.coeff[0] = 1;*/
	
	int option=1,method,functionNumber;
	double(*function)(double x, polynom params)=f;
	double(*prim)(double a, double b, polynom optional)=F;
	bool isIntChosen = false;
	bool isMChosen = false;
	bool isFunctionChosen = false;
	bool isMethodChosen = false;

	while (option != 0)
	{
		printHeader();
		if (isIntChosen)cout << "Текущий интервал: [" << A << "," << B << "]" << endl;
		if (isMChosen)cout << "Текущее число разбиений: "<<m << endl;
		if (isMChosen&&isIntChosen) cout << "Текущий шаг: " << (B - A) / m << endl;
		if (isFunctionChosen) {
			if(functionNumber==1) cout << "Текущая функция: e^x" << endl;
			else { 
				cout << "Текущая функция: ";
				printPolynom(pol);
				cout << endl;
			}
		}
		if (isMethodChosen) {
			cout << "Текущий метод: ";
			switch (method) {
			case 1: {
				cout << "Левые прямоугольники" << endl;
				break;

			}
			case 2: {
				cout << "Правые прямоугольники" << endl;
				break;

			}
			case 3: {
				cout << "Центральные прямоугольники" << endl;
				break;

			}
			case 4: {
				cout << "Трапеции" << endl;
				break;

			}
			case 5: {
				cout << "Симпсон" << endl;
				break;

			}
			}

		}
		cout << endl;
		printMenu();
		cout << "Выберите действие: ";
		cin >> option;
		switch (option) {
		case 1: {
			cout << "Введите границы промежутка через пробел: ";
			cin >> A >> B;
			isIntChosen = true;
			break;

		}
		case 2: {
			cout << "Введите число промежутков: ";
			cin >> m;
			isMChosen = true;
			break;

		}
		case 3: {
			cout << "1.e^x" << endl;
			cout << "2. Многочлен" << endl;
			cout << "Выберите функцию: ";
			cin >> functionNumber;
			isFunctionChosen = true;
			if (functionNumber == 2) {
				pol = createPolynom();
				function = p;
				prim = P;
			}
			else {
				function = f;
				prim = F;
			}
			break;

		}
		case 4: {
			cout << "1.Левые прямоугольники" << endl;
			cout << "2.Правые прямоугольники" << endl;
			cout << "3.Центральные прямоугольники" << endl;
			cout << "4.Трапеции" << endl;
			cout << "5. Симпсон" << endl;
			cout << "Выберите метод интегрирования: " << endl;
			cin >> method;
			isMethodChosen = true;

			break;

		}
		case 5: {
			if (isMChosen&&isIntChosen&&isFunctionChosen&&isMethodChosen) {
				double answer;
				switch (method) {
				case 1: {
					answer = leftRectangles(A, B, m, pol, function);
					break;

				}
				case 2: {
					answer = rightRectangles(A, B, m, pol, function);
					break;

				}
				case 3: {
					answer = middleRectangles(A, B, m, pol, function);
					break;

				}
				case 4: {
					answer = trapeze(A, B, m, pol, function);
					break;

				}
				case 5: {
					answer = simpson(A, B, m, pol, function);
					break;

					}
				}
				double exactValue = prim(A, B, pol);
				cout << endl;
				cout << "Приближенное значение интеграла: " << answer << endl;
				cout << "Точное значение: " << exactValue << endl;
				cout << "Абсолютная фактическая погрешность: " << fabs(exactValue - answer)<<endl;
				cout << "Теоретическая погрешность: " << error(A, B, m, method, functionNumber, pol)<<endl;
				system("pause");
			}
			break;

		}
		}
		
		system("cls");
	}

	
/*	cout << P(A, B, pol)<<endl;
	cout << fabs(leftRectangles(A, B, m, pol, p)- P(A, B, pol)) << endl;
	cout << rightRectangles(A, B, m, pol, p) << endl;
	cout << middleRectangles(A, B, m, pol, p) << endl;
	cout << trapeze(A, B, m, pol, p) << endl;
	cout << simpson(A, B, m, pol, p) << endl;*/
	
	system("pause");
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
