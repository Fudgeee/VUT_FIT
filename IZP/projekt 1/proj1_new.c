/******************************************************/
/* * *               Práca s textom               * * */
/* * *						  * * */
/* * *                  Verzia:1                  * * */
/* * *						  * * */	
/* * *               Adrián Matušík               * * */
/* * *                November 2019               * * */
/******************************************************/ 

// potrebne kniznice
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX 101
// vymazanie medzier zo stringu
char *remove_space (char *str)
{	
	int x = 0, i = 0;
	while (str[i] != '\0')                                // po znakoch kontroluje ci nieje koniec stringu
	{
		if (str[i] != ' ')                            // ak sa dany znak nerovna medzere, znak vlozi na index x++ 
			str[x++] = str[i];		      // ide na dalsi znak
		i++;
	}
	str[x] = '\0';
	return str;                                           // vracia string bez medzier
}
// docita(odtrhne) cast stringu nad 100 znakov
void docitaj (char *str)
{
	while (str[strlen(str)-1] != '\n')                           // kym sa 101. znak nerovna enteru
	{	
		if ((str[strlen(str)-1]) == EOF)                     // ak predposledny znak nieje koniec suboru
			str[strlen(str)-1] = '\n';                   // tak mu priradi enter
		else
			str[strlen(str)-1] = fgetc(stdin);           // inak berie dalsi znak
	}
}
// overuje ci je dany charakter v stringu ciselneho charakteru
int je_cislo (char *str)
{
	char znak;
	int pocet_neciselnych_znakov = 0, dlzka_retazca = (strlen(str));
	for (int i = 0; (i < dlzka_retazca-1); i++)                              // prechadza string po znakoch
	{
		znak = str[i];
		if (isdigit(znak) == 0)                                          // ak sa dany znak = 0, cize nie je ciselneho charakteru
			pocet_neciselnych_znakov++;                              // zvysi hodnotu pocitadla
	}
	return pocet_neciselnych_znakov;                                         // vrati hodnotu pocitadla(pocet znakov neciselneho charakteru)
}
// zmeni vsetky male pismena na velke
char *uppercase (char *str)
{
	int dlzka_mena = strlen(str);
	char str1[MAX];
	for (int i = 0; (i < dlzka_mena); i++)                     // prechadza string po znakoch
	{
		if ((str[i] > 96) && (str[i] < 123))               // ak je dany znak male pismeno (a-z)
			str1[i] = toupper(str[i]);                 // tak uppercasne dany znak a priradi ho do pomocneho stringu
		else
			str1[i] = str[i];                          // inak dany znak len priradi do pomocneho
	}
	strcpy(str, str1);                                         // skopiruje upraveny pomocny string str1 do povodneho
	return str;                                                // vrati uppercasnuty string
}
// premena pismen na cisla (ciselne stringy)
char *change_name (char *str)
{
	int dlzka_mena = strlen(str);
	char pismeno, str1[MAX];
	for (int i = 0; (i < dlzka_mena); i++)                        // prechadza string po znakoch
	{
		pismeno = str[i];
		switch(pismeno)                                       // switch meni znaky (A-Z,+) na ciselne znaky
		{
			case 'A': pismeno = '2'; break;
			case 'B': pismeno = '2'; break;
			case 'C': pismeno = '2'; break;
			case 'D': pismeno = '3'; break;
			case 'E': pismeno = '3'; break;
			case 'F': pismeno = '3'; break;
			case 'G': pismeno = '4'; break;
			case 'H': pismeno = '4'; break;
			case 'I': pismeno = '4'; break;
			case 'J': pismeno = '5'; break;
			case 'K': pismeno = '5'; break;
			case 'L': pismeno = '5'; break;
			case 'M': pismeno = '6'; break;
			case 'N': pismeno = '6'; break;
			case 'O': pismeno = '6'; break;
			case 'P': pismeno = '7'; break;
			case 'Q': pismeno = '7'; break;
			case 'R': pismeno = '7'; break;
			case 'S': pismeno = '7'; break;
			case 'T': pismeno = '8'; break;
			case 'U': pismeno = '8'; break;
			case 'V': pismeno = '8'; break;
			case 'W': pismeno = '9'; break;
			case 'X': pismeno = '9'; break;
			case 'Y': pismeno = '9'; break;
			case 'Z': pismeno = '9'; break;
			case '+': pismeno = '0'; break;
			default: break;
		}
		str1[i] = pismeno;                                    // do pomocneho stringu ukladam znaky ktore uz presli switchom (zmenili sa na ciselne znaky)
	}
	strcpy(str, str1);                                            // skopiruje upraveny pomocny string str1 do povodneho
	return str;                                                   // vrati upraveny string ktory presiel switchom (ma zmenene pismena na cisla)
}
// vypis
void vypis (int control, int pocet_znakov, char *meno, int pocet_cislic, char *cislo) 
{
	if (control > 0)                                                                               // control = pocet neciselnych znakov
												       // ak sa v stringu nachadza nejaky znak neciselneho charakteru
		fprintf(stdout, "%.*s, Invalid Number!\n", pocet_znakov-1, meno);                      // vypise meno kontaktu a neplatne cislo
	else
		fprintf(stdout, "%.*s, %.*s", pocet_znakov-1, meno, pocet_cislic, cislo);              // inak vypise meno a cislo kontaktu
}
// hlavny program
int main(int argc, char *argv[])
{
	char meno[MAX], cislo[MAX];
	if (argc == 1)                                                                         	        	    // pocet argumentov = 1, nieje zadane
       										                                    // ziadne cislo na hladanie => vypis celeho zoznamu
	{
		int pocet_znakov = 0, pocet_cislic = 0, control_vysledok = 0;                                       // control_vysledok = pocitadlo znakov nenuloveho charakteru
		while (fgets(meno, MAX+1, stdin) != NULL)                                                           // pokial naslo dalsi string (nie je koniec suboru)
		{
			pocet_znakov = (strlen(meno));
			if (((meno[pocet_znakov-1]) != '\n') || ((meno[pocet_znakov-1]) == EOF))                    // ak predposledny znak stringu (kedze posledny je \0)
                                        	                                                                    // nie je enter alebo je koniec suboru
			{								                    	    // cize meno je dlhsie ako 100 znakov
				docitaj(meno);                                                                      // odtrhne zvysne znaky za 100. znakom
				cislo[0] = '\0';                                                                    // vycisti string cislo
				fgets(cislo, MAX+1, stdin); 							    // nacita dalsi riadok = cislo
				control_vysledok = je_cislo(cislo);                                                 // priradi pocet neciselnych znakov z funkcie
				if ((cislo) == NULL)
					printf("\n");
				pocet_cislic = (strlen(cislo));
				if (((cislo[pocet_cislic-1]) != '\n') || ((cislo[pocet_cislic-1]) == EOF))          // ak je cislo dlhsie ako 100 znakov
				{
					docitaj(cislo);                                                             // odtrhne znysne znaky za 100. znakom
					vypis(control_vysledok, pocet_znakov, meno, pocet_cislic, cislo);           // vypise kontakt podla vysledku z funkcie vypis =>
				}									  	    // => berie v uvahu pocet znakov neciselneho charakteru
				else										    // v pripade ze cislo malo menej ako 100 znakov, vypise kontakt
					vypis(control_vysledok, pocet_znakov, meno, pocet_cislic, cislo);	    // podla poctu znakov neciselneho charakteru	
			}
			else 											    // v pripade ze meno malo menej ako 100 znakov 
			{
				cislo[0] = '\0';								    // vycisti string cislo
				fgets(cislo, MAX+1, stdin);							    // nacita dalsi riadok = cislo
				control_vysledok = je_cislo(cislo);						    // priradi pocet neciselnych znakov z funkcie
				pocet_cislic = (strlen(cislo));
				if (((cislo[pocet_cislic-1]) != '\n') || ((cislo[pocet_cislic-1]) == EOF))	    // ak cislo ma viac ako 100 znakov
				{
					docitaj(cislo);								    // odtrhne znaky za 100. znakom
					vypis(control_vysledok, pocet_znakov, meno, pocet_cislic, cislo);	    // vypise kontakt podla vysledku
				}       	                                                                    // kontroly poctu neciselnych znakov z cisla
				else 
					vypis(control_vysledok, pocet_znakov, meno, pocet_cislic, cislo);	    // ak malo cislo menej ako 100 znakov, riesi uz len
			}											    // pocet neciselnych znakov z cisla => vypis kontaktu
		}
	}
	else if (argc == 2)								 // zadany 1 argument, (CISLO = hladana postupnost znakov)
	{
		int x = 0, dlzka_arg = (strlen(argv[1]));
		char str[dlzka_arg];
		strcpy(str, argv[1]);
		x = je_cislo(str);							 // kontrola, ci je argument len z cisel
		if (x > 0)
		{
			fprintf(stderr, "Invalid Input!\n");				 // ak argument pozostava z inych znakov ako cisel tak vypise chybny vstup
			return 1;
		}
		if (x == 0)								 // ak argument pozostava len z cisel
		{
			int pocet_zn = 0, pocet_cis = 0;
			char meno1[MAX];
			bool found = false;
			while (fgets(meno, MAX+1, stdin) != NULL)                                                   // pokial naslo dalsi string (nie je koniec suboru)
			{
				pocet_zn = (strlen(meno));
				if (((meno[pocet_zn-1]) != '\n') || ((meno[pocet_zn-1]) == EOF))		    // ak predposledny znak stringu (kedze posledny je \0)
                                                	                                                            // nie je enter alebo je koniec suboru
				{										    // cize meno je dlhsie ako 100 znakov
					docitaj(meno);                                                              // odtrhne zvysne znaky za 100. znakom
					cislo[0] = '\0';							    // vycisti string cislo
					fgets(cislo, MAX+1, stdin);						    // nacita dalsi riadok = cislo		
					if ((cislo) == NULL)							    // skontroluje ci cislo existuje
						printf("\n");
					pocet_cis = (strlen(cislo));
					if (((cislo[pocet_cis-1]) != '\n') || ((cislo[pocet_cis-1]) == EOF))        // ak cislo ma viac ako 100 znakov
					{
						docitaj(cislo);							    // odtrhne zvysne znaky za 100. znakom
					}
				}
				else 										    // v pripade ze meno malo menej ako 100 znakov
				{
					cislo[0] = '\0';							    // vycisti string cislo
					fgets(cislo, MAX+1, stdin);						    // nacita dalsi riadok = cislo
					if ((cislo) == NULL)							    // skontroluje ci cislo existuje
						printf("\n");	
					pocet_cis = (strlen(cislo));
					if (((cislo[pocet_cis-1]) != '\n') || ((cislo[pocet_cis-1]) == EOF))	    // ak ma cislo viac ako 100 znakov
					{
						docitaj(cislo);							    // odtrhne znaky za 100. znakom
					}
				}
				int p = 0, dlzka_meno = ((strlen(meno)));					    // p = pocet znakov neciselneho charakteru
				strcpy(meno1, meno);								    
				uppercase(meno1);								    // uppercasne male pismena v mene
				remove_space(meno1);								    // vymaze medzery v mene
				remove_space(cislo);								    // vymaze medzery v cisle
				char  *find, *findc, prelozene_meno[MAX];					    // find = zhoda v mene podla hladaneho cisla
														    // findc = zhoda v cisle podla hladaneho cisla
				change_name(meno1);								    // zmeni meno na string zlozeny z cisel
				strcpy(prelozene_meno, meno1);
				p = je_cislo(cislo);								    // do p priradi pocet znakov neciselneho charakteru
				find = strstr(prelozene_meno,str);						    
				findc = strstr(cislo, str);
				if ((find != 0)	|| (findc != 0))						    // ak naslo zhodu v cisle alebo v mene(alebo v oboch)
				{										    // vypise kontakty ktore sa zhoduju
					vypis(p, dlzka_meno, meno, pocet_cis, cislo);
					found = true;								    // pocitadlu priradi hodnotu true
				}
			}
			if (found == false)									    // found = false, pretoze nenaslo ani jednu zhodu
														    // v celom telefonnom zozname
				fprintf(stdout, "Not found\n");						    // vypise ze nic nenaslo
		}
			
	}		
	else if (argc > 2)	                                                                                    // pocet argumentov viac ako 2 => neplatny vstup
	{
		fprintf(stderr, "Too many arguments!\n");
		return 1;
	}
	return 0;
}
