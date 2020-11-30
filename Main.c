#pragma warning(disable : 4996)
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <Windows.h>

#include "UkolyDB.h"

int main() {

	char command[16];
	char input[16];
	char cmd;

	SYSTEMTIME t; // Declare SYSTEMTIME struct

	GetLocalTime(&t); // Fill out the struct so that it can be used

	// Use GetSystemTime(&t) to get UTC time 

	printf("%d.%d.%d, %d:%d:%d\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute, t.wSecond); // Return year, month, day, hour, minute, second and millisecond in that order

	Ukol* start = NULL;

	printf("A: Pridat     ");
	printf("D: Smazat     ");
	printf("P: Tisk     ");
	printf("I: Vlozit     ");
	printf("Q: Konec\n\n");

	start = nacistSoubor(start);
	do
	{
		//system("cls");		// smaze obrazovku



		cmd = tolower(getchar());
		while (getchar() != '\n');

		switch (cmd)
		{
		case 'a':
			start = pridatNaKonec(start);
			ZobrazitSeznam(start);					// volame pridani
			break;
		case 'd':
			start = smazatUkol(start);
			ZobrazitSeznam(start);					// volame mazani
			break;
		case 'p':
			ZobrazitSeznam(start);
			break;
		case 'i':
			if (start == NULL) {
				start = pridatNaZacatek(start);
			}
			else {
				start = Vlozeni(start);
			}
			ZobrazitSeznam(start);
			break;
		}
	} while (cmd != 'q');
	ZapsatDoSouboru(start);

	VycisteniPameti(start);

	return 0;

}