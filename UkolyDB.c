#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UkolyDB.h"

void add(char* nazev, int rok, struct ukol** uk_prvni) // pridani auta
{
	struct ukol* novyUkol; // ukazatel pro nove vkladany ukol
	struct ukol* aktUkol; // ukazatel na aktualni ukol

	// alokace dynamicke promenne
	novyUkol = (struct ukol*)malloc(sizeof(struct ukol));

	strcpy_s(novyUkol->nazev, UKOL_SIZE, nazev); // naplneni struktury
	novyUkol->rok = rok;
	novyUkol->dalsi = NULL;

	if (*uk_prvni == NULL) // linearni seznam je prazdny
	{
		*uk_prvni = novyUkol;
		return;
	}
	else if (novyUkol->rok < (*uk_prvni)->rok) // vlozime na zacatek
	{
		novyUkol->dalsi = *uk_prvni;
		*uk_prvni = novyUkol;
		return;
	}

	aktUkol = *uk_prvni;
	while (aktUkol) // prochazeni seznamu
	{
		if (aktUkol->dalsi == NULL) // jsme na poslednim aute
		{
			aktUkol->dalsi = novyUkol; // pridavame na konec
			return;
		}
		else if (novyUkol->rok < aktUkol->dalsi->rok)
		{
			novyUkol->dalsi = aktUkol->dalsi; // vlozime za aktUkol
			aktUkol->dalsi = novyUkol;
			return;
		}
		aktUkol = aktUkol->dalsi; // posun na dalsi auto
	}
}

void del(int rok, struct ukol** uk_prvni)
{
	struct ukol* aktUkol;

	while (*uk_prvni && (*uk_prvni)->rok == rok)
	{
		struct ukol* newPrvni = (*uk_prvni)->dalsi;
		free(*uk_prvni);  // uvolneni auta z pameti
		*uk_prvni = newPrvni;
	}

	aktUkol = *uk_prvni;
	while (aktUkol && aktUkol->dalsi) // prochazeni seznamu
	{
		if (aktUkol->dalsi->rok == rok) // auto je ke smazani
		{
			struct ukol* newDalsi = aktUkol->dalsi->dalsi;
			free(aktUkol->dalsi);  // uvolneni auta z pameti
			aktUkol->dalsi = newDalsi;
		}
		aktUkol = aktUkol->dalsi; // posun na dalsi auto
	}
}