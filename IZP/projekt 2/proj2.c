/******************************************************/
/* * *              Iteracne vypocty              * * */
/* * *						  * * */
/* * *                  Verzia:1                  * * */
/* * *						  * * */	
/* * *               Adrian Matusik               * * */
/* * *                November 2019               * * */
/******************************************************/

// potrebne kniznice + konstanty
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Ut 0.0258563      // [V]
#define I0 pow(10,-12)    // [A]
// funkcia na pocitanie Up
double diode(double Up, double U01, double R)
{
	return((I0*(exp(Up/Ut)-1))-((U01-Up)/R));
}
// binarne vyhladavanie
double bisection(double diode(double Up, double U01, double R), double a, double U0, double EPS, double R, double U01)
{
	double middle = 0;
	do
	{
		middle = (a + U0) / 2;					// ziskanie stredu intervalu
		if ((diode(a,U01,R)*diode(middle,U01,R)) > 0)		
			a = middle;					// a priradi stred intervalu a cyklus prebieha znovu
		else 
			U0 = middle;					// U0 priradi stred intervalu a cyklus prebieha znovu
	} while ((fabs(a-U0) >= EPS) && ((a+U0)/2 != middle));		// cyklus sa opakuje kym je odchylka ABS(Up) > EPS alebo kym sa nemeni hranica stredu
	return middle; 							// vrati stred intervalu = Up, akonahle bude odchylka mensia nez EPS
}
// hlavny program
int main(int argc, char *argv[])
{
	if (argc == 4)							// ak je pocet argumentov 4 == su zadane vsetky potrebne parametre (U0,R,EPS)
	{
		double U0 = 0, R = 0, EPS = 0, Up = 0, Ip = 0, U01 = 0;
		char *end;							
		U0 = strtod(argv[1], &end);  // [v]
		R = strtod(argv[2], &end);   // [Ohm]
		EPS = strtod(argv[3], &end); 
		U01 = U0;
		if ((U0 < 0) || (R <= 0) || (EPS <= 0))			// ak je napatie ale odpor zaporny alebo odchylka 0 => jedna sa o neplatne data
		{
			fprintf (stderr, "error: invalid arguments\n");
			return 9;
		}
	      	else 
		{
	 		Up = bisection(diode,0,U0,EPS,R,U01);
			fprintf(stdout, "Up=%g V\n", Up);
			Ip = I0*(exp(Up/Ut)-1);
			fprintf(stdout, "Ip=%g A\n", Ip);
		}

	}
	else								// inak vypise neplatny vstup
	{	
		fprintf(stderr, "Wrong Input!\n");
		return 2;
	}
	return 0;
}
