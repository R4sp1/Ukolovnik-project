#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "UkolyDB.h"

void ZobrazitSeznam(Ukol* start) {
	Ukol* aktualniUkol = start;
	int pocet = 0;

	Ukol* vepredu = NULL;
	Ukol* vzadu = NULL;

	while (aktualniUkol != NULL) {
		pocet++;

		vepredu = aktualniUkol->dalsi;
		vzadu = aktualniUkol->predchozi;

		printf("Ukol: %-5d datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", pocet, aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
		aktualniUkol = aktualniUkol->dalsi;
		vepredu = NULL;
		vzadu = NULL;
	}
	printf("Pocet ukolu:%d\n", pocet);
}

Ukol* NovyUkol() {

	printf("Vlozte den (1-31), mesic (1-12), rok (xxxx), jmeno ukolu, prioritu (1 (nejmensi) - 3 (nejvetsi)), hotovy ukol? (0=ne, 1=ano):\n");
	char input[70];
	fgets(input, 70, stdin);

	Ukol* novyUkol = malloc(sizeof(Ukol));
	sscanf(input, "%d %d %d %s %d %d", &novyUkol->den, &novyUkol->mesic, &novyUkol->rok, &novyUkol->jmeno, &novyUkol->priorita, &novyUkol->hotovo);
	printf("Novy ukol pridan. Datum: %d.%d.%d, jmeno: %s, priorita: %d, hotovo?: %d\n\n", novyUkol->den, novyUkol->mesic, novyUkol->rok, novyUkol->jmeno, novyUkol->priorita, novyUkol->hotovo);

	novyUkol->dalsi = NULL;
	novyUkol->predchozi = NULL;

	return novyUkol;
}

Ukol* pridatNaZacatek(Ukol* startPtr) {
	Ukol* novyUkol = NovyUkol();
	if (startPtr != NULL) {
		startPtr->predchozi = novyUkol;
		novyUkol->dalsi = startPtr;
	}

	return novyUkol;
}

Ukol* pridatNaKonec(Ukol* startPtr) {
	Ukol* returnPtr = startPtr;
	Ukol* novyUkol = NULL;

	if (startPtr == NULL) {
		novyUkol = pridatNaZacatek(startPtr);
		returnPtr = novyUkol;
	}
	else {
		Ukol* indexUkolu = startPtr;
		while (indexUkolu->dalsi != NULL) {
			indexUkolu = indexUkolu->dalsi;
		}
		novyUkol = NovyUkol();
		indexUkolu->dalsi = novyUkol;
		novyUkol->dalsi = NULL;
		novyUkol->predchozi = indexUkolu;
	}
	return returnPtr;
}


Ukol* smazatUkol(Ukol* startPtr) {

	printf("Zadejte jmeno ukolu ktery chcete smazat:");
	char input[16];
	fgets(input, 15, stdin);

	Ukol* ukolRef = startPtr;
	Ukol* ukolSmazani = NULL;

	while (ukolRef != NULL) {

		if (strncmp(input, ukolRef->jmeno, strlen(ukolRef->jmeno)) == 0) {
			ukolSmazani = ukolRef;
			break;
		}

		ukolRef = ukolRef->dalsi;
	}

	if (startPtr != NULL && ukolSmazani == startPtr) {
		if (ukolSmazani->dalsi != NULL) {
			ukolSmazani->dalsi->predchozi = NULL;
			startPtr = ukolSmazani->dalsi;
		}
		else {
			startPtr = NULL;
		}
	}
	else {
		if (ukolSmazani != NULL) {
			if (ukolSmazani->predchozi != NULL) {
				ukolSmazani->predchozi->dalsi = ukolSmazani->dalsi;
			}

			if (ukolSmazani->dalsi != NULL) {
				ukolSmazani->dalsi->predchozi = ukolSmazani->predchozi;
			}
		}
	}

	if (ukolSmazani != NULL) {
		ukolSmazani = NULL;
		free(ukolSmazani);
	}

	return startPtr;

}

Ukol* Vlozeni(Ukol* startPtr) {
	printf("Vloz ukol po ukolu:");
	char input[16];
	fgets(input, 15, stdin);

	Ukol* poUkolu = startPtr;
	Ukol* novyUkol = NULL;

	if (strncmp(input, poUkolu->jmeno, strlen(poUkolu->jmeno)) == 0) {
		novyUkol = NovyUkol();
	}
	else {
		while (poUkolu->dalsi != NULL) {
			poUkolu = poUkolu->dalsi;
			if (strncmp(input, poUkolu->jmeno, strlen(poUkolu->jmeno)) == 0) {
				novyUkol = NovyUkol();
				break;
			}
		}
	}

	if (novyUkol != NULL) {
		novyUkol->dalsi = poUkolu->dalsi;
		if (novyUkol->dalsi != NULL) {
			novyUkol->dalsi->predchozi = novyUkol;
		}
		poUkolu->dalsi = novyUkol;
		novyUkol->predchozi = poUkolu;
	}
	else {
		printf("Ukol nenalezen\n");
	}

	return startPtr;
}

Ukol* oznacitUkolJakoHotovy(Ukol* startPtr) {

	printf("Zadejte jmeno ukolu ktery chcete oznacit jako hotovy:");
	char input[16];
	fgets(input, 15, stdin);

	Ukol* ukolRef = startPtr;
	Ukol* ukolOznaceny = NULL;

	while (ukolRef != NULL) {

		if (strncmp(input, ukolRef->jmeno, strlen(ukolRef->jmeno)) == 0) {
			ukolOznaceny = ukolRef;
			ukolOznaceny->hotovo = 1;
			break;
		}

		ukolRef = ukolRef->dalsi;
	}

	return startPtr;

}

void VycisteniPameti(Ukol* start) {

	Ukol* uvolneniPameti = start;
	Ukol* drzeniPameti = NULL;
	while (uvolneniPameti != NULL) {
		drzeniPameti = uvolneniPameti->dalsi;
		free(uvolneniPameti);
		uvolneniPameti = drzeniPameti;
	}
	//printf("Uvolneni pameti\n");
}

void ZapsatDoSouboru(Ukol* start) {
	FILE* pSoubor;
	pSoubor = fopen("ukoly.bin", "wb");

	if (pSoubor != NULL) {
		Ukol* aktualniUkol= start;

		Ukol* holdDalsi = NULL;
		Ukol* holdPredchozi = NULL;

		while (aktualniUkol != NULL) {
			holdDalsi = aktualniUkol->dalsi;
			holdPredchozi = aktualniUkol->predchozi;

			aktualniUkol->dalsi = NULL;
			aktualniUkol->predchozi= NULL;

			fseek(pSoubor, 0, SEEK_END);
			fwrite(aktualniUkol, sizeof(Ukol), 1, pSoubor);

			printf("Zapisovani:%s do souboru\n", aktualniUkol->jmeno);

			aktualniUkol->dalsi = holdDalsi;
			aktualniUkol->predchozi = holdPredchozi;

			holdDalsi = NULL;
			holdPredchozi = NULL;

			aktualniUkol = aktualniUkol->dalsi;
		}
		fclose(pSoubor);
		pSoubor = NULL;
	}
	else {
		printf("Chyba pøi otevírání souboru\n");
	}

}

Ukol* CteniDalsihoUkolu(Ukol* start, FILE* pSoubor) {
	size_t navratovaHodnota;
	if (start == NULL) {
		start = malloc(sizeof(Ukol));
		navratovaHodnota = fread(start, sizeof(Ukol), 1, pSoubor);
		start->dalsi = NULL;
		start->predchozi = NULL;
	}
	else {
		Ukol* indexUkolu = start;
		Ukol* novyUkol = malloc(sizeof(Ukol));
		while (indexUkolu->dalsi != NULL) {
			indexUkolu = indexUkolu->dalsi;
		}
		navratovaHodnota = fread(novyUkol, sizeof(Ukol), 1, pSoubor);
		indexUkolu->dalsi = novyUkol;
		novyUkol->dalsi = NULL;
		novyUkol->predchozi = indexUkolu;
	}
	return start;
}

Ukol* nacistSoubor(Ukol* start) {

	FILE* pSoubor;
	pSoubor = fopen("ukoly.bin", "rb");
	if (pSoubor != NULL) {

		VycisteniPameti(start);
		start = NULL;

		fseek(pSoubor, 0, SEEK_END);
		long velikostSouboru = ftell(pSoubor);
		rewind(pSoubor);

		int pocetUkolu = (int)(velikostSouboru / (sizeof(Ukol)));
		//printf("Pocet ukolu:%d\n", pocetUkolu);

		int loop = 0;
		for (loop = 0; loop < pocetUkolu; ++loop) {
			fseek(pSoubor, (sizeof(Ukol) * loop), SEEK_SET);
			start = CteniDalsihoUkolu(start, pSoubor);
		}
	}
	else {
		printf("Chyba otevreni souboru\n");
	}

	return start;

}


void dnesniUkol(Ukol* start) {
	Ukol* aktualniUkol = start;
	int pocet = 0;
	SYSTEMTIME t; // Declare SYSTEMTIME struct
	GetLocalTime(&t); // Fill out the struct so that it can be used

	printf("Dnesni ukoly:\n");
	while (aktualniUkol != NULL) {
		if (aktualniUkol->rok == t.wYear) {
			if (aktualniUkol->mesic == t.wMonth) {
				if (aktualniUkol->den == t.wDay) {
					pocet++;
					printf("		Ukol: %-5d Jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", pocet, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
			}
		}
		aktualniUkol = aktualniUkol->dalsi;

	}
	if (pocet == 0) {
		printf("		Zadny ukol\n");
	}
	else {
		printf("		Pocet ukolu: %d\n", pocet);
	}
	printf("		Zobrazeni minulych ukolu - M, zobrazeni budoucich ukolu - B\n");
}

void budouciUkoly(Ukol* start) {
	Ukol* aktualniUkol = start;
	int pocet = 0;
	SYSTEMTIME t; // Declare SYSTEMTIME struct
	GetLocalTime(&t); // Fill out the struct so that it can be used

	printf("Budouci ukoly:\n");
	while (aktualniUkol != NULL) {
		if (aktualniUkol->rok == t.wYear) {
			if (aktualniUkol->mesic == t.wMonth) {
				if (aktualniUkol->den > t.wDay) {
					pocet++;
					printf("		Ukol: %-5d datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", pocet, aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
			}
			else if(aktualniUkol->mesic > t.wMonth){
				pocet++;
				printf("		Ukol: %-5d datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", pocet, aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
		}
		else if (aktualniUkol->rok > t.wYear) {
			pocet++;
			printf("		Ukol: %-5d datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", pocet, aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
		}
		aktualniUkol = aktualniUkol->dalsi;

	}
	if (pocet == 0) {
		printf("		Zadne budouci ukoly\n");
	}
	else {
		printf("		Pocet budoucich ukolu: %d\n", pocet);
	}
}


void minuleUkoly(Ukol* start) {
	Ukol* aktualniUkol = start;
	int pocet = 0;
	SYSTEMTIME t; // Declare SYSTEMTIME struct
	GetLocalTime(&t); // Fill out the struct so that it can be used

	printf("Minule ukoly:\n");
	while (aktualniUkol != NULL) {
		if (aktualniUkol->rok == t.wYear) {
			if (aktualniUkol->mesic == t.wMonth) {
				if (aktualniUkol->den < t.wDay) {
					pocet++;
					printf("		Ukol: %-5d datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", pocet, aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
			}
			else if (aktualniUkol->mesic < t.wMonth) {
				pocet++;
				printf("		Ukol: %-5d datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", pocet, aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
		}
		else if (aktualniUkol->rok < t.wYear) {
			pocet++;
			printf("		Ukol: %-5d datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", pocet, aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
		}
		aktualniUkol = aktualniUkol->dalsi;

	}
	if (pocet == 0) {
		printf("		Zadne minule ukoly\n");
	}
	else {
		printf("		Pocet minulych ukolu: %d\n", pocet);
	}
}

