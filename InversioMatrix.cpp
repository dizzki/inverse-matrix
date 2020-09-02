// InversioMatrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
using namespace std;

//Решение СЛАУ методом итераций
double* iter(double** a, double* y, int n)
{
	double* res = new double[n];
	int i, j;


	for (i = 0; i < n; i++)
	{
		res[i] = y[i] / a[i][i];
	}

	double eps = 0.0001;
	double* Xn = new double[n];

	do {
		for (i = 0; i < n; i++) {
			Xn[i] = y[i] / a[i][i];
			for (j = 0; j < n; j++) {
				if (i == j)
					continue;
				else {
					Xn[i] -= a[i][j] / a[i][i] * res[j];
				}
			}
		}

		bool flag = true;
		for (i = 0; i < n - 1; i++) {
			if (abs(Xn[i] - res[i]) > eps) {
				flag = false;
				break;
			}
		}

		for (i = 0; i < n; i++) {
			res[i] = Xn[i];
		}

		if (flag)
			break;
	} while (1);

	return res;
}

//Нахождение обратной матрицы
double** InvMatr(double** a, int n)
{
	double** res;
	double* y = new double[n];
	double* itr;
	int i, j, k;

	res = new double* [n];
	for (i = 0; i < n; i++)
	{
		res[i] = new double[n];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				y[j] = 1;
			}
			else
			{
				y[j] = 0;
			}
		}
		itr = iter(a, y, n);
		for (k = 0; k < n; k++)
		{
			res[k][i] = itr[k];
		}
	}

	return res;
}

//Умножение матриц
double** prodMatr(double** a, double** b, int n)
{
	double** res;
	double sum=0;
	res = new double* [n];
	int i, j;
	res = new double* [n];
	for (i = 0; i < n; i++)
	{
		res[i] = new double[n];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			res[i][j] = 0;
			for (int k = 0; k < n; k++)
				res[i][j] += a[i][k] * b[k][j];
		}
	}

	return res;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double** a;
	double** x;
	double** c;
	ifstream Infile;
	int n, i, j;
	cout << "Введите размерность матрицы: ";
	cin >> n;
	Infile.open("inArray5.txt");

	a = new double* [n];
	for (i = 0; i < n; i++)
	{
		a[i] = new double[n];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			Infile >> a[i][j];
		}
	}
	Infile.close();

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << a[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	x = InvMatr(a, n);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << x[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	c = prodMatr(a, x, n);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << c[i][j] << "\t";
		}
		cout << endl;
	}

	return 0;
}


