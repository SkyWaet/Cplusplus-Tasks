// Task 6 CauchyProblem.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <Windows.h>
double c1;

double f(double x, double y) {
	return (-y + cos(x));
}
double accurateSolution(double x) {
	return c1*exp(-x) +( sin(x) + cos(x)) / 2;
}

double cauchyTaskSol(double x0, double y0) {
	return exp(x0)*(y0 - (sin(x0) + cos(x0)) / 2);
}

double power(double x, int deg) {
	if (x >= 0) return pow(x, deg);
	else {
		if (deg % 2 == 0) return pow(fabs(x), deg);
		else return -pow(fabs(x), deg);
	}
}

double derivative(double x0, int iter) {
	double y0 = accurateSolution(x0);
	if (iter % 4 == 0) return y0;
	else if (iter % 4 == 1) return -y0 + cos(x0);
	else if (iter % 4 == 2) return y0 - cos(x0) - sin(x0);
	else if (iter % 4 == 3) return -y0 + sin(x0);
}

int factorial(int n) {
	double res = 1;
	if (n == 0) return 1;
	else {
		for (int i = 1; i <= n; i++) {
			res *= i;
		}
		return res;
	}
}

double polynom(double **table, double x, int n) {
	double mult = 1;
	for (int i = 0; i < n - 1; i++)
		mult *= (x - table[i][0]);
	return mult;
}

double ** Taylor( double x0, double h, int N) {
	double ** table = new double*[N + 3];
	for (int i = 0; i <= N+2; i++) {
		table[i] = new double[2];
	}
	int amOfNotNull = 0;
	double slag = 0;
	double der = 0;
	double sum = 0;
	int iter = 0;
	double binom = 1;
	for (int j = 0; j <= N+2 ; j++) {
		double x = x0 + (j - 2)*h;
		while (amOfNotNull < 5) {
			der = derivative(x0, iter);
			binom = power(x - x0, iter);
			slag = der * binom / factorial(iter);
			amOfNotNull++;
			sum += slag;
			iter++;
		}
		table[j][0] = x;
		table[j][1] = sum;
		sum = 0;
		 amOfNotNull = 0;
		 iter = 0;
		 using namespace std;
		// cout << "x " << table[j][0] << " y " << table[j][1] << endl;
	}
	return table;
}

double ** Euler(double(*f)(double x,double y), double x0, double h, double N) {
	double ** table = new double*[N+1];
	for (int i = 0; i <= N; i++) {
		table[i] = new double[2];
	}
	table[0][0] = x0;
	table[0][1] = accurateSolution(x0);
	double xi=x0, yi;

	for (int i = 1; i <=N; i++) {
		table[i][0] = x0 + i * h;
		table[i][1] = table[i - 1][1] + h * f(table[i-1][0], table[i - 1][1]);
	}
	return table;
}

double ** EulerCauchy(double(*f)(double x, double y), double x0, double h, double N) {
	double ** table = new double*[N + 1];
	for (int i = 0; i <= N; i++) {
		table[i] = new double[2];
	}
	table[0][0] = x0;
	table[0][1] = accurateSolution(x0);
	double xi = x0, yi;

	for (int i = 1; i <= N; i++) {
		table[i][0] = x0 + i * h;
		yi= table[i - 1][1] + h * f(table[i - 1][0], table[i - 1][1]);
		table[i][1] = table[i - 1][1] + h * (f(table[i - 1][0], table[i - 1][1]) + f(table[i][0], yi)) / 2;
	}
	return table;
}

double ** upgradedEuler(double(*f)(double x, double y), double x0, double h, double N) {
	double ** table = new double*[N + 1];
	for (int i = 0; i <= N; i++) {
		table[i] = new double[2];
	}
	table[0][0] = x0;
	table[0][1] = accurateSolution(x0);
	double xi = x0, yi;
	double xi2;
	double yi2;

	for (int i = 1; i <= N; i++) {
		table[i][0] = x0 + i * h;
		xi2 = table[i-1][0] + h / 2;
		yi2 = table[i-1][1] + h * f(table[i-1][0], table[i-1][1])/2;
		table[i][1] = table[i - 1][1] + h * f(xi2, yi2);
	}
	return table;
}

double ** RungeKutt(double(*f)(double x, double y), double x0, double h, double N) {
	double ** table = new double*[N + 1];
	for (int i = 0; i <= N; i++) {
		table[i] = new double[2];
	}
	table[0][0] = x0;
	table[0][1] = accurateSolution(x0);
	double xi = x0, yi;
	double k1, k2, k3, k4,k;

	for (int i = 1; i <= N; i++) {
		table[i][0] = x0 + i * h;
		k1 = f(table[i - 1][0], table[i - 1][1]);
		k2 = f(table[i - 1][0] + h / 2, table[i - 1][1] + h * k1/2);
		k3= f(table[i - 1][0] + h / 2, table[i - 1][1] + h * k2/2);
		k4= f(table[i][0], table[i - 1][1] + h * k3);
		k = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		table[i][1] = table[i - 1][1] + h * k;
	}
	return table;
}

double ** createTable(double(*f)(double x),int N,double x0,double h) {
	double ** table = new double*[N + 3];
	for (int i = 0; i <= N + 2; i++) {
		table[i] = new double[2];
	}
	double xk;
	for (int i = 0; i <N + 3; i++) {
		xk = x0 + (i - 2)*h;
		table[i][0] = xk;
		table[i][1] = f(xk);
	}
	return table;
}

double integralFunc(double x, double* values,double j,double k) {
	double res = 1;
	for (int i = 0; i <= k; i++) {
		if(i!=j)res *= (x + i);
	}
	if(isnan(res/(x+j)))std::cout << x + j << std::endl;
	return res;
}

double simpson(double lb, double rb, double* values,double j,double k ) {
	double sum1 = 0;
	double sum2 = 0;
	int m = 100;
	double h = (rb - lb) / m;
	double b = lb + h;
	double a = lb;
	for (int i = 0; i < m; i++) {
		sum1 += integralFunc(a + h / 2, values,j,k);
		a += h;
	}
	for (int i = 0; i < m - 1; i++) {
		sum2 += integralFunc(b, values,j,k);
		b += h;
	}
	double ans = h * (integralFunc(lb, values, j, k) + integralFunc(rb, values, j, k) + +4 * sum1 + 2 * sum2) / 6;
	
	return ans;
}

double ** Adams(int N, double h,double x0, double **tablePart) {
	double ** table = new double*[N + 3];
	double *values = new double[N + 3];
	for (int i = 0; i <= N + 2; i++) {
		table[i] = new double[2];
	}
	int k=4;
	for (int i = 0; i <= 4; i++) {
		table[i] = tablePart[i];
		values[i] = tablePart[i][0];
	}
	double aj;
	double sum=0;
	
	double xn;
	for (int i = 5; i <= N + 2; i++) {
		aj = 0;
		int m = i-1;
		//int k = m;
		xn = x0 + (i - 2)*h;
		for (int j = 0; j <= k; j++) {
			aj = power(-1,j)*simpson(0, 1, values, j,k)/(factorial(j)*factorial(k-j));
			sum += aj*h*f(table[m-j][0],table[m-j][1]);
			
		}
		table[i][0]=xn;
		table[i][1] = table[i - 1][1] + sum;
		sum = 0;
		m++;
	//	k++;
		values[i] = xn;
	}
	return table;
}

void printTable(double ** table, int N, int begin, int type) {
	using namespace std;
	switch (type) {
		case 0: {cout << "  Таблица значений точного решения " << endl; break; }
		case 1: {cout << "  Метод разложения в ряд Тейлора  " << endl; break; }
		case 2: {cout << "  Метод Адамса " << endl; break; }
		case 3: {cout << "  Метод Эйлера " << endl; break; }
		case 4: {cout << "  Метод Эйлера - Коши " << endl; break; }
		case 5: {cout << "  Усовершенствованный метод Эйлера  " << endl; break; }
		case 6: {cout << "  Метод Рунге - Кутта  " << endl; break; }
	}
	
	cout << " " << setw(88) << setfill('=') << '=' << endl;
	cout << setfill(' ');
	cout << " | " << setw(8) << left << "№ точки" << '\t' << " | " << setw(15) << left << "x" << '\t' << " | " << setw(15) << left << "y" << '\t' << " | " << setw(15) << left<<"Погрешность";
	cout << "\t|\t\n";
	cout << " " << setw(88) << setfill('=') << '=' << endl;
	cout << setfill(' ');
	
	for (int i = begin; i <= N; i++) {
		if(type >=3)cout << " | " << setw(8) << left << i+2;
		else cout << " | " << setw(8) << left << i;
		for (int j = 0; j < 3; j++) {
			cout << '\t' << " | " << setw(15) << setprecision(15) << left;
			if (j == 2) cout << fabs(accurateSolution(table[i+2][0]) - table[i+2][1]);
			else if (table[i+2][j] || (j < 2))cout << table[i+2][j];
			else cout << "---";
		}
		cout << "\t|" << '\t' << '\n';
	}

	cout << " " << setw(88) << setfill('=') << '=' << endl;

	cout << setfill(' ');
}

void printMenu() {
	using namespace std;
	cout << " Задача №6. Решение задачи Коши. Вариант 7" << endl;
	cout << " Исходное уравнение: y'=-y-cos(x)" << endl;
	cout << " Общий вид решения: y=c1*e^x + (cos(x) + sin(x))/2" << endl;
	cout << endl << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
    int N = 10;
	double x0 = 0,y0;
	double h = 0.1;
	char option = 'y';
	bool isXChosen=false, isYChosen=false, isHchosen=false, isNChosen=false;
	while (option != 'n') {
		printMenu();
		if (isHchosen) std::cout << "Текущий шаг: " << h << std::endl;
		std::cout << " Введите шаг: ";
		std::cin >> h;
		isHchosen = true;
		if (isNChosen) std::cout << "Текущее значение N: " << N << std::endl;
		std::cout << " Введите N: ";
		std::cin >> N;
		isNChosen = true;
		if (isXChosen) std::cout << "Текущее значение х0: " << x0 << std::endl;
		std::cout << " Введите x0: ";
		std::cin >> x0;
		isXChosen = true;
		if (isYChosen) std::cout << "Текущее значение y0: " << y0 << std::endl;
		std::cout << " Введите y0: ";
		std::cin >> y0;		
		isYChosen = true;
		c1 = cauchyTaskSol(x0, y0);
		double **table = createTable(accurateSolution, N, x0, h);
		printTable(table, N, -2, 0);
		std::cout << std::endl;
		std::cout << std::endl;
		system("pause");

		double **TaylorTable = Taylor(x0, h, N - 7);
		printTable(TaylorTable, 2, -2, 1);
		std::cout << std::endl;
		std::cout << std::endl;
		system("pause");

		printTable(Adams(N + 3, h, x0, TaylorTable), N, 3, 2);
		std::cout << std::endl;
		std::cout << std::endl;
		system("pause");
		printTable(Euler(f, x0, h, N), N - 2, -1, 3);
		std::cout << std::endl;
		std::cout << std::endl;
		system("pause");
		printTable(EulerCauchy(f, x0, h, N), N - 2, -1, 4);
		std::cout << std::endl;
		std::cout << std::endl;
		system("pause");
		printTable(upgradedEuler(f, x0, h, N), N - 2, -1, 5);
		std::cout << std::endl;
		std::cout << std::endl;
		system("pause");
		printTable(RungeKutt(f, x0, h, N), N - 2, -1, 6);
		using namespace std;
		cout << endl << endl;
		cout << "Желаете ввести новые значения параметров (y/n)? ";
		cin >> option;
		while (option != 'y' && option != 'n') {
			cout << "Введите корректное значение: ";
			cin >> option;
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
