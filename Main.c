#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Barvy.h"
#include "UkolyDB.h"

struct ukol* prvni = NULL; // globalni ukazatel na prvni auto

void OnAdd()
{
	char my_name[UKOL_SIZE];
	int my_year;

	printf("\nUkol : ");         // dotazeme se na polozky
	scanf_s("%s", my_name, UKOL_SIZE);
	while (getchar() != '\n');
	printf("\nRok : ");
	scanf_s("%d", &my_year);
	while (getchar() != '\n');
	add(my_name, my_year, &prvni);         // volame pridavaci funkci
}

void OnDel()
{
	int my_year;

	printf("\nRok : ");
	scanf_s("%d", &my_year);
	while (getchar() != '\n');
	del(my_year, &prvni);         // volame mazaci funkci
}

void ShowCars()
{
	struct ukol* aktUkol = prvni; // ukazatel na aktualni auto
	printf("\n\n");
	while (aktUkol) // prochazeni seznamu
	{
		printf("%d: %s\n", aktUkol->rok, aktUkol->nazev); // tisk radku
		aktUkol = aktUkol->dalsi; // posun na dalsi auto
	}
	getchar();
}


int main()
{
	char  cmd;

	do
	{
		system("cls");		// smaze obrazovku
		printf(ZLUTE("A: Pridat     "));
		printf(ZLUTE("D: Smazat     "));
		printf(ZLUTE("P: Tisk     "));
		printf(ZLUTE("Q: Konec\n\n"));

		cmd = tolower(getchar());
		while (getchar() != '\n');

		switch (cmd)
		{
		case 'a':
			OnAdd();					// volame pridani
			break;
		case 'd':
			OnDel();					// volame mazani
			break;
		case 'p':
			ShowCars();
			break;
		}
	} while (cmd != 'q');     // koncime az pri Q
	return 0;
}
