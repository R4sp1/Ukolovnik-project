#pragma warning(disable : 4996)
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <Windows.h>

#include "UkolyDB.h"
#include "Barvy.h"

int main() {

	char command[16];
	char input[16];
	char cmd;

	/*SYSTEMTIME t; // Declare SYSTEMTIME struct

	GetLocalTime(&t); // Fill out the struct so that it can be used

	// Use GetSystemTime(&t) to get UTC time 

	printf("%d.%d.%d, %d:%d:%d\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond); // Return year, month, day, hour, minute, second and millisecond in that order
	*/
	Ukol* start = NULL;

	printf("A: Pridat ukol\n");
	printf("D: Smazat ukol\n");
	printf("P: Tisk celeho seznamu\n");
	printf("C: Upravit ukol\n");
	printf("I: Kopirovat ukol\n");
	printf("Q: Konec\n\n");

	start = nacistSoubor(start);
	dnesniUkol(start);
	do
	{
		//system("cls");		// smaze obrazovku



		cmd = tolower(getchar());
		while (getchar() != '\n');

		switch (cmd)
		{
		case 'a':
			start = pridatNaKonec(start);				// volame pridani
			break;
		case 'd':
			start = smazatUkol(start);					// volame mazani
			break;
		case 'p':
			ZobrazitSeznam(start);
			break;
		case 'm':
			minuleUkoly(start);
			break;
		case 'b':
			budouciUkoly(start);
			break;
		case 'i':
			start = kopirovatUkol(start);
			break;
		case 'c':
			zmenitUkol(start);
			/*if (start == NULL) {
				start = pridatNaZacatek(start);
			}
			else {
				start = Vlozeni(start);
			}
			ZobrazitSeznam(start);*/
			break;
		}
	} while (cmd != 'q');

	while (1) {
		ZapsatDoSouboru(start);

		VycisteniPameti(start);
		break;
	}


	return 0;


}