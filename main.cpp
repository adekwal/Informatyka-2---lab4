#include <iostream>
#include <cstdlib>
#include <math.h>
#include "rk4.h"

//zagadnienie pocz¹tkowe:	{1} y'(t)=f(t,y);
//warunek pocz¹tkowy:		{2} y(t0)=y0;

double t0 = 0, tk = 2;//t nalezy do takiego przedzialu
double y_0 = 1;
double lambda = 10;

double f(double t, double y);//f(t,y);
double y_an(double t);

int main()
{
	double t = t0, y = y_0;
	double h = 0.01, eps_euler = 0, eps_rk4 = 0;

	FILE* dane_do_zadania;
	errno_t err = fopen_s(&dane_do_zadania, "dane_do_zadania.txt", "a+");

	FILE* wyniki_euler;
	errno_t err2 = fopen_s(&wyniki_euler, "wyniki_metoda_eulera.txt", "a+");

	FILE* wyniki_rk4;
	errno_t err3 = fopen_s(&wyniki_rk4, "wyniki_metoda_rk4.txt", "a+");

	for (int i = 0; i < 7; i++)//wszystkie h zamienione na tk/n - nowy krok calkowania
	{
		double N = pow(2, i);//n - liczba krokow jakie nalezy wykonac

		t = t0, y = y_0; fprintf(wyniki_euler, "N = %lf\n", N);

		for (int j = 0; j < N; j++)//metoda eulera
		{
			t += (tk / N);//czyli t[i+1] = t[i] + h;
			y += (tk / N) * f(t, y);//czyli y[i+1] = y[i] + h * f(t[i], y[i]);
			eps_euler = fabs(y - y_an(t)) / fabs(y_an(t));

			fprintf(wyniki_euler, "%lf\t%lf\t%lf\n", t, y, eps_euler);
		}

		t = t0, y = y_0; fprintf(wyniki_rk4, "N = %lf\n", N);

		for (int j = 0; j < N; j++)//metoda rungego-kuty
		{
			t += (tk / N);
			y = rk4(t, y, (tk / N), f);
			eps_rk4 = fabs(y - y_an(t)) / fabs(y_an(t));

			fprintf(wyniki_rk4, "%lf\t%lf\t%lf\n", t, y, eps_rk4);
		}

		fprintf(dane_do_zadania, "%lf\t%lf\t%lf\t%lf\n", N, (tk / N), eps_euler, eps_rk4);//dla ostatniego przedzialu czasowego
	}

	fclose(dane_do_zadania);
	fclose(wyniki_euler);
	fclose(wyniki_rk4);

	printf("wszystkie wyniki mozna znalezc w plikach\n");
}
double f(double t, double y)
{
	return lambda * y;
}
double y_an(double t)
{
	return y_0 * exp(lambda * (t - t0));
}