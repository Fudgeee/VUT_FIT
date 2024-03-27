/******************************************************/
/* * *        Praca s datovymi strukturami        * * */
/* * *						  * * */
/* * *                  Verzia:1                  * * */
/* * *						  * * */	
/* * *               Adrian Matusik               * * */
/* * *                December 2019               * * */
/******************************************************/

// potrebne kniznice a konstanty
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
const char *HELPMSG =
	"\n                  Program Priechod Bludiskom\n\n"
	"Program hlada cestu von z bludiska zadaneho v textovom subore.\n"
	"Vystupom je vypis suradnic policok bludiska cez ktore vedie\n"
	"cesta od vchodu do bludiska k vychodu.\n"
	"Podoby parametrov spustenia programu:\n"
	"--help: vypisuje napovedu.\n"
	"--test subor.txt: skontroluje ci sa v subor.txt nachadza riadna\n"
	"definicia mapy bludiska.\n"
	"V pripade ze pocet definicii policok zodpoveda rozmerom bludiska danym\n"
	"dvomi ciselnymi hodnotami na zaciatku suboru, v subore sa nachadzaju\n"
	"iba celociselne udaje a susediace policka maju rovnaky typ zdielanej \n"
	"hranice vypise Valid, ak je porusena niektora z tychto podmienok\n"
	"vypise Invalid.\n"
	"--rpath R C subor.txt: vypisuje suradnice policok mapy zo subor.txt\n"
	"od vchodu na suradniciach R C k vychodu podla pravidla pravej ruky.\n"
	"--lpath R C subor.txt: hlada cestu von z bludiska podla pravidla lavej ruky.\n";

enum direction {LEFT, RIGHT, UP, DOWN};
// struktura mapy
typedef struct
{
	int rows;
	int cols;
	unsigned char *cells;
} Map;
// funkcia nacitavajuca mapu zo suboru
int nacitaj(Map *map)
{
	int i = 0, j = 0;
	FILE *subor;
	if ((subor = fopen("subor.txt", "r+")) == NULL)						// otvori subor, overi ci nieje prazdny
		fprintf(stderr, "File is empty!\n");
	else
	{	
		fscanf(subor, "%d", &map->rows);							// nacita prve dve hodnoty -> pocet riadkov, pocet stlpcov
		fscanf(subor, "%d", &map->cols);
	}
	map->cells = malloc (map->rows * map->cols * sizeof(unsigned char*));			// allokuje miesto v pamati podla nacitanych rozmerov 
	for (i = 0; (i < map->rows); i++)
	{
		for (j = 0; (j < map->cols); j++)	
		{
			if (!(fscanf(subor, "%hhu", &map->cells[i * map->cols + j])) != 0)	// nacitava jednotlive bunky do matice s tym ze pokial niektora 
			{									// obsahuje ine ako ciselne znaky vypise error
				fprintf(stderr, "Invalid\n");
				return 8;
			}
		}
	}
	fclose(subor);										// zatvori subor
	return 0;
}
// funkcia zistujuca hranice trojuholnikov
bool isborder(Map *map, int r, int c, int border)
{
	switch (border)
	{
		case LEFT:			
			if (((map->cells[r * map->cols + c]) >> 0) & 1)		// ak je hranica zlava vrati TRUE (na prvom bite je jednotka)
				return true;
			break;
		case RIGHT:
			if (((map->cells[r * map->cols + c]) >> 1) & 1)		// ak je hranica sprava vrati TRUE (na druhom bite je jendotka)
				return true;
			break;
		case UP:
		case DOWN:
			if (((map->cells[r * map->cols + c]) >> 2) & 1)		// ak je hranica zhora/zdola vrati TRUE (na tretom bite je jednotka)
				return true;
			break;	
	}
	return false;								// inak ak neni hranica na kontrolovanej strane trojuholnika ->vrati FALSE
}
// funkcia overujuca platnost mapy
int validity(Map *map)
{
	int i,j;
	for (i = 0; (i <= map->rows-1); i++)					// prechadza po jednotlivych bunkach v mape
		for (j = 0; (j < map->cols-1); j++)						
		{
			if (isborder(map, i, j, RIGHT) != isborder(map, i, j+1, LEFT)) 		// ak vpravo je hranica a vlavo nie vrati hodnotu 1
				return 1;
			if ((i % 2) != (j % 2))							// na parnom riadku a neparnom stlpci alebo naopak
				if ((i < map->rows-1) && isborder(map, i, j, DOWN) != isborder(map, i+1, j, UP))	// kontroluje ak je dolna hranica a riadok pod tym chyba
					return 1;									// horna hranica vrati hodnotu 1
			if (map->cells[i *map->cols + j] > 7)					// ak je obsah niektorej bunky vacsi ako 7 vrati hodnotu 1
				return 1;
		} 
	return 0;
}
// funkcia
int start_border(Map *map, int r, int c, int leftright)			// LEFT = 0, RIGHT = 1, DOWN = 2
{
	if (leftright == 0)						// start_border pre Rpath
	{
		if ((c == 0) && ((r % 2) == 0))				// nastavi pociatocnu hranicu RIGHT ak je vstup zlava a na neparnom riadku
			if (!isborder(map, r, c, LEFT))
				return RIGHT;
		if ((c == 0) && ((r % 2) != 0))				// nastavi hranicu DOWN ak je vstup zlava a na parnom riadku
			if (!isborder(map, r, c, LEFT))
				return DOWN;
		if ((c == map->cols-1) && ((r + c) % 2 == 0))		// nastavi hranicu UP ak je vstup sprava a trojuholnik je obrateny smerom dole
			if (!isborder(map, r, c, RIGHT))
				return UP;
		if ((c == map->cols-1) && ((r +c) % 2 != 0))		// nastavi hranicu LEFT ak je vstup sprava a trojuholnik je obrateny smerom hore
			if (!isborder(map, r, c, RIGHT)) 
				return LEFT;
		if ((r == 0) && ((r + c) % 2 == 0))			// nastavi hranicu LEFT ak je vstup zhora a trojuholnik je obrateny smerom dole
			if (!isborder(map, r, c, UP))
				return LEFT;
		if ((r == map->rows-1) && ((r +c) % 2 != 0))		// nastavi hranicu RIGHT ak je vstup zdola a trojuholnik je obrateny smerom hore
			if (!isborder(map, r, c, DOWN))
				return RIGHT;
	}	
	if (leftright == 1)						// start_border pre Lpath
	{
		if ((c == 0) && ((r % 2) == 0))				// nastavi pociatocnu hranicu DOWN ak je vstup zlava a na neparnom riadku
			if (!isborder(map, r, c, LEFT))
				return DOWN;
		if ((c == 0) && ((r % 2) != 0))				// nastavi hranicu RIGHT ak je vstup zlava a na parnom riadku
			if (!isborder(map, r, c, LEFT))
				return RIGHT;
		if ((c == map->cols-1) && ((r + c) % 2 == 0))		// nastavi hranicu LEFT ak je vstup sprava a trojuholnik je obrateny smerom dole
			if (!isborder(map, r, c, RIGHT))
				return LEFT;
		if ((c == map->cols-1) && ((r +c) % 2 != 0))		// nastavi hranicu UP ak je vstup sprava a trojuholnik je obrateny smerom hore
			if (!isborder(map, r, c, RIGHT)) 
				return UP;
		if ((r == 0) && ((r + c) % 2 == 0))			// nastavi hranicu RIGHT ak je vstup zhora a trojuholnik je obrateny smerom dole
			if (!isborder(map, r, c, UP))
				return RIGHT;
		if ((r == map->rows-1) && ((r +c) % 2 != 0))		// nastavi hranicu LEFT ak je vstup zdola a trojuholnik je obrateny smerom hore
			if (!isborder(map, r, c, DOWN))
				return LEFT;			
	}
	return -1; 							// ak nevyhovuje ani jedna podmienka vrati -1, lebo sa do daneho trojuholniku neda vstupit
}
// funkcia pre pohyb v bludisku
void move(int *r, int *c, int *direction, int leftright)
{
	printf("%d %d\n",*r+1, *c+1);
	if (leftright == 0)						// pre pohyb podla pravej ruky 
	{
		switch(*direction)
		{
			case LEFT:					// ak ide do trojuholnika vlavo, presunie sa o jedno policko dolava a priradi smer 
				(*c)--;					// podla toho ci vchadza do trojuholnika otoceneho smerom dole alebo hore
				if (*r % 2 == *c % 2)
					*direction = UP;
				if (*r % 2 != *c % 2)
					*direction = LEFT;
				break;
			case RIGHT:					// ak ide do trojuholnika vpravo, presunie sa o jedno policko do prava a priradi smer
				(*c)++;					// podla orientacie trojuholnika
				if (*r % 2 != *c %2)
					*direction = DOWN;
				if (*r % 2 == *c % 2)
					*direction = RIGHT;
				break;
			case UP:					// ak ide smerom hore, tak presunie sa o jedno policko vyssie v matici a prirade smer 
				(*r)--;
				*direction = RIGHT;
				break;
			case DOWN:					// ak ide smerom dole, tak presunie sa o jedno policko nizsie a priradi smer
				(*r)++;
				*direction = LEFT;
				break;
		}	
	}
	if (leftright == 1)						// pre pohyb podla lavej ruky
	{
		switch(*direction)
		{
			case LEFT:					// ak ide do trojuholnika vlavo, presunie sa o jedno policko dolava a priradi smer
				(*c)--;					// podla orientacie trojuholnika
				if (*r % 2 != *c % 2)
					*direction = DOWN;
				if (*r % 2 == *c % 2)
					*direction = LEFT;
				break;
			case RIGHT:					// ak ide do trojuholnika vpravo, presunie sa o jedno policko do prava a priradi smer
				(*c)++;					// podla orientacie trojuholnika
				if (*r % 2 == *c % 2)
					*direction = UP;
				if (*r % 2 != *c % 2)
					*direction = RIGHT;
				break;
			case UP:					// ak ide smerom hore, tak sa presunie o jedno policko vyssie v matici a priradi smer
				(*r)--;
				*direction = LEFT;
				break;
			case DOWN:					// ak ide smerom dole, tak sa presunie o jedno policko nizsie a priradi smer
				(*r)++;
				*direction = RIGHT;
				break;
		}
	}	
}
// funkcia na hladanie cesty z bludiska
int findway(Map *map, int r, int c, int leftright)
{
	int border = start_border(map, r, c, leftright);		// smer ktorym sa chce dalej ist
	if (border == -1)						// border je -1 ak sme mimo bludiska alebo nevstupujeme z kraja ale priamo do stredu
		{
		fprintf(stderr, "You are out of maze!\n");
		return 99;
		}
	while (((r >= 0) && (r <= map->rows-1)) && ((c >= 0) && (c <= map->cols-1)))		// cyklus, kym sa nedostaneme von z bludiska
	{
		while (isborder(map, r, c, border))						// kym je hranica v smere ktorym sa pohybujem
		{
			if(leftright == 0)							// ak idem podla pravej ruky
			{
				if (r % 2 == c % 2)						// ak je trojuholnik otoceny smerom dole
					{
					if (border == UP)					// ak ma prisiel z hora pojde dalej smerom dolava inak smerom dole
						border = LEFT;
					else
						border++;
					}
				else 								// ak je trojuholnik otoceny smerom hore
				{
					if (border == DOWN)					// ak vosiel zo spodu tak dalej ide vpravo, ak vosiel zlava dalej ide dole,
						border = RIGHT;					// inak ide hore
					else if (border == LEFT)
							border = DOWN;
						else 
							border--;
				}
					
			}
			if (leftright == 1)							// ak ide podla lavej ruky
			{
				if (r % 2 == c % 2)						// ak je trojuholnik otoceny smerom dole
				{
					if (border == LEFT)					// a vosiel zlava dalej pojde hore, inak ide dole
						border = UP;
					else 
						border--;
				}
				else								// ak je trojuholnik otoceny smerom hore
				{
					if (border == DOWN)					// ak vosiel z dola tak dalej ide vlavo
						border = LEFT;
					else if (border == RIGHT)				// ak vosiel sprava dalej ide dole, inak ide hore
							border = DOWN;
						else
							border++;
				}
			}
		}
	move(&r, &c, &border, leftright); 							// zavola funkciu pohyb a pohne sa dalej
	}
	return 0;
}
//hlavny program
int main(int argc, char *argv[])
{
	if (argc == 2)							// ak je pocet argumentov 2 a druhy je "--help" tak vypise napovedu, inak vypise error
	{
		char *control, *str = "--help";
		control = argv[1];
		if (strcmp(control,str) == 0)
		{
			printf("%s\n", HELPMSG);
			return 0;
		}
		else 
		{
			fprintf(stderr, "Invalid arguments!\n");
			return 1;	
		}
	}
	else if (argc == 3)								// ak je pocet argumentov 3 a druhy je "--test" a treti argument je subor.txt, 
	{										// tak skontroluje ci subor.txt obsahuje riadnu definiciu bludiska
		char *control1, *controlsub, *str1 = "--test", *sub = "subor.txt";
		control1 = argv[1];
		controlsub = argv[2];
		if ((strcmp(control1,str1) == 0) && (strcmp(controlsub,sub) == 0))
		{
			Map map;							
			nacitaj(&map);						// nacita mapu map zo suboru
			if (validity(&map))					// overuje ci subor obsahuje riadnu definiciu
				fprintf(stdout, "Invalid\n");
			else
				fprintf(stdout, "Valid\n");
		}
		else
		{
			fprintf(stderr, "Invalid arguments!\n");
			return 2;
		}
	}
	else if (argc == 5)								// ak je pocet argumentov 5 kontroluje spravny format argumentov 
	{										// a dalej sa vykonava cestu bludiskom podla pravej/lavej ruky, podla argumentu 1
		int r = 0, c = 0;
		char *control2, *controlsub1, *str2 = "--rpath", *str3 = "--lpath", *sub1 = "subor.txt";
		control2 = argv[1];
		r = atoi(argv[2]);
		c = atoi(argv[3]);
		controlsub1 = argv[4];
		if ((strcmp(control2,str2) == 0) && (strcmp(controlsub1,sub1) == 0) && (!isdigit(r)) && (!isdigit(c)))	// ak sa bude pohybovat podla pravej ruky
		{
			Map map;
			nacitaj(&map);							// nacita mapu zo suboru
			if (validity(&map) == 1)					// ak sa jedna o neplatnu mapu vypise error
			{
				fprintf(stderr, "Invalid map!\n");
				return 992;
			}
			else								// inak hlada cestu z bludiska
				findway(&map, r-1, c-1, 0);
		}
		if ((strcmp(control2,str3) == 0) && (strcmp(controlsub1,sub1) == 0) && (!isdigit(r)) && (!isdigit(c)))	// ak sa bude pohybovat podla pravidla lavej ruky
		{
			Map map; 
			nacitaj(&map);							// nacita mapu zo suboru
			if (validity(&map) == 1)					// ak sa jedna o nepaltnu mapu vypise error
			{
				fprintf(stderr, "Invalid map!\n");
				return 992;
			}
			else								// inak hlada cestu z bludiska
				findway(&map, r-1, c-1, 1);
		}
	}
	else 
	{
		fprintf(stderr, "Invalid Input!\n");					// ak je iny pocet argumentov, ako 2, 3 alebo 5
		return 999;
	}
	return 0;
}
