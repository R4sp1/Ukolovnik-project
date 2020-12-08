#pragma warning(disable : 4996)
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <Windows.h>

#include "UkolyDB.h"
#include "Barvy.h"

int main() {
	system("cls");
	char command[16];
	char input[16];
	char cmd;

	/*SYSTEMTIME t; // Declare SYSTEMTIME struct
	GetLocalTime(&t); // Fill out the struct so that it can be used
	printf("%d.%d.%d, %d:%d:%d\n\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond); // Return year, month, day, hour, minute, second and millisecond in that order
	*/

	Ukol* start = NULL;

	printf("A: Pridat ukol\n");
	printf("P: Tisk celeho seznamu\n");
	printf("C: Upravit nebo smazat ukol\n");
	printf("I: Kopirovat ukol na jine datum\n");
	printf("Q: Konec\n\n");

	start = nacistSoubor(start);
	dnesniUkol(start);
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
			break;
		}
	} while (cmd != 'q');

	ZapsatDoSouboru(start);
	VycisteniPameti(start);

	return 0;
}