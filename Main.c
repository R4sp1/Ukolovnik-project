#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "UkolyDB.h"
#include "Barvy.h"

int main() {
	system("cls"); //smazani obrazovky
	char command[16];
	char input[16];
	char cmd;

	/*SYSTEMTIME t; // struktura systemoveho casu
	GetLocalTime(&t); // naplneni struktury
	printf("%d.%d.%d, %d:%d:%d\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond); // rok, mesic, den, hodina, minuta, sekunda
	*/

	Ukol* start = NULL; //start zacina na 0

	//zakladni menu
	printf("A: Pridat ukol\n");
	printf("P: Tisk celeho seznamu\n");
	printf("C: Upravit nebo smazat ukol\n");
	printf("I: Kopirovat ukol na jine datum\n");
	printf("Q: Konec\n\n");

	start = nacistSoubor(start); //volani funkce ktera nacte ukoly ze souboru ukoly.bin do pameti
	dnesniUkol(start); //volani funkce ktera porovna systemove datum a zobrazi ukoly s timto datem
	do
	{
		cmd = tolower(getchar());
		while (getchar() != '\n');

		switch (cmd)
		{
		case 'a':
			start = pridatNaKonec(start);				// volame pridani
			break;
		case 'p':
			ZobrazitSeznam(start); //zobrazeni vsech ukolu
			break;
		case 'm':
			minuleUkoly(start); //zobrazeni ukolu ktere jiz probehly
			break;
		case 'b':
			budouciUkoly(start); //zobrazeni pouze budoucich ukolu
			break;
		case 'i':
			start = kopirovatUkol(start); //kopirovani ukolu na jine datum
			break;
		case 'c':
			zmenitUkol(start); //volame menu s upravami ukolu
			break;
		}
	} while (cmd != 'q');

	ZapsatDoSouboru(start); //po ukonceni zapsani do souboru a vycisteni pameti
	VycisteniPameti(start);

	return 0;
}