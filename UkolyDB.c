#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "UkolyDB.h"
#include "Barvy.h"

void ZobrazitSeznam(Ukol* start) {
	Ukol* aktualniUkol = start;
	int pocet = 0;

	SYSTEMTIME t;
	GetLocalTime(&t);

	Ukol* vepredu = NULL;
	Ukol* vzadu = NULL;

	printf("Vase ukoly:\n");

	while (aktualniUkol != NULL) {
		pocet++;

		vepredu = aktualniUkol->dalsi;
		vzadu = aktualniUkol->predchozi;

		//zobrazeni ukolu s urcitou barvou. cerna - hotove ukoly, dale barva dle priority
		if (aktualniUkol->hotovo == 1) {
			printf(CERNE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
		}
		else if (aktualniUkol->priorita == 1) {
			printf(ZELENE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
		}
		else if (aktualniUkol->priorita == 2) {
			printf(ZLUTE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
		}
		else if (aktualniUkol->priorita == 3) {
			printf(MODRE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
		}
		else {
			printf("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
		}

		aktualniUkol = aktualniUkol->dalsi; //posun na dalsi ukol
		vepredu = NULL;
		vzadu = NULL;
	}
	printf("		Ukolu celkem: %d\n\n", pocet);
}

Ukol* NovyUkol() { //funkce "novy ukol". Navratovou hodnotou jsou data noveho ukolu

	printf("Vlozte den (1-31), mesic (1-12), rok (xxxx), jmeno ukolu, prioritu (1 (nejmensi) - 3 (nejvetsi)), hotovy ukol? (0=ne, 1=ano):\n");
	char input[100];
	fgets(input, 99, stdin); //nacitani vstupu z klavesnice

	Ukol* novyUkol = malloc(sizeof(Ukol)); //alokovani pameti
	sscanf(input, "%d %d %d %s %d %d", &novyUkol->den, &novyUkol->mesic, &novyUkol->rok, &novyUkol->jmeno, &novyUkol->priorita, &novyUkol->hotovo);
	printf("Novy ukol pridan. Datum: %d.%d.%d, jmeno: %s, priorita: %d, hotovo?: %d\n\n", novyUkol->den, novyUkol->mesic, novyUkol->rok, novyUkol->jmeno, novyUkol->priorita, novyUkol->hotovo);

	novyUkol->dalsi = NULL;
	novyUkol->predchozi = NULL;

	return novyUkol;
}


Ukol* pridatNaZacatek(Ukol* startPtr) { //pokud chceme vlozot ukol na zacatek seznamu volame tuto funkci
	Ukol* novyUkol = NovyUkol();
	if (startPtr != NULL) {
		startPtr->predchozi = novyUkol;
		novyUkol->dalsi = startPtr;
	}

	return novyUkol;
}

Ukol* pridatNaKonec(Ukol* startPtr) { //zakladni vlozeni na konec seznamu
	Ukol* returnPtr = startPtr;
	Ukol* novyUkol = NULL;

	if (startPtr == NULL) { //pokud v seznamu nic neni volame funkci ktera ukol prida na zacatek seznamu
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

	printf("Zadejte jmeno ukolu ktery chcete smazat: ");
	char input[30];
	fgets(input, 29, stdin);

	Ukol* ukolRef = startPtr;
	Ukol* ukolSmazani = NULL;

	while (ukolRef != NULL) { //prochazeni vsech ukolu

		if (strncmp(input, ukolRef->jmeno, strlen(ukolRef->jmeno)) == 0) { //porovnani vstupniho stringu s nazvem ukolu - moc se to neosvedcilo, porovnava snad pouze prvni pismeno takze neni spolehlivy, mazani ukolu dale vyreseno v upravach ukolu (posledni funkce)
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

Ukol* Vlozeni(Ukol* startPtr) { //vlozeni ukolu mezi ostatni ukoly
	printf("Vloz ukol po ukolu:");
	char input[30];
	fgets(input, 29, stdin);

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

Ukol* presunoutUkol(Ukol* startPtr) { //presunuti ukolu na jine datum. Funkci ve vysledku ani nevolame, vyreseno v posledni funkci upravy ukolu
	printf("Zadejte jmeno ukolu ktery chcete presunout na jine datum: ");
	char input[30];
	fgets(input, 29, stdin);

	Ukol* ukolRef = startPtr;
	Ukol* ukolOznaceny = NULL;

	while (ukolRef != NULL) {

		if (strncmp(input, ukolRef->jmeno, strlen(ukolRef->jmeno)) == 0) {
			ukolOznaceny = ukolRef;
			int new_den, new_mesic, new_rok;

			printf("Zadejte nove datum (den (1-31) mesic (1-12) rok (xxxx))\n");
			char dat[30];
			fgets(dat, 29, stdin);


			sscanf(dat, "%d %d %d", &new_den, &new_mesic, &new_rok);


			ukolOznaceny->den = new_den;
			ukolOznaceny->mesic = new_mesic;
			ukolOznaceny->rok = new_rok;

			printf("Nove datum ukolu: %s je: %d.%d.%d\n", ukolOznaceny->jmeno, ukolOznaceny->den, ukolOznaceny->mesic, ukolOznaceny->rok);
			//free(ukolOznaceny);
			break;
		}
		ukolRef = ukolRef->dalsi;
	}
	return startPtr;
}

Ukol* kopirovatUkol(Ukol* startPtr) { //kopirovani ukolu na jine datum, vytvori se novy ukol, ktery ma krome datumu vsechny parametry prevzate po svem "rodici"
	printf("Zadejte jmeno ukolu ktery chcete kopirovat na jine datum: ");
	char input[30];
	fgets(input, 29, stdin);

	Ukol* ukolRef = startPtr;
	Ukol* ukolOznaceny = NULL;

	while (ukolRef != NULL) {

		if (strncmp(input, ukolRef->jmeno, strlen(ukolRef->jmeno)) == 0) {
			ukolOznaceny = ukolRef;
			int new_den, new_mesic, new_rok;
			char src[UKOL_SIZE], dest[UKOL_SIZE];

			Ukol* indexUkolu = startPtr;
			while (indexUkolu->dalsi != NULL) {
				indexUkolu = indexUkolu->dalsi;
			}
			//Ukol* novyUkol = NULL;
			Ukol* novyUkol = malloc(sizeof(Ukol));

			strcpy(src, ukolOznaceny->jmeno);
			strcpy(dest, "_kopie"); //pro odliseni od "rodice" se nakonec jmena prida "_kopie"

			printf("Zadejte nove datum (den (1-31) mesic (1-12) rok (xxxx))\n");
			char dat[30];
			fgets(dat, 29, stdin);
			sscanf(dat, "%d %d %d", &new_den, &new_mesic, &new_rok);

			novyUkol->den = new_den;
			novyUkol->mesic = new_mesic;
			novyUkol->rok = new_rok;

			strncat(src, dest, UKOL_SIZE);
			strcpy(novyUkol->jmeno, src);

			novyUkol->priorita = ukolOznaceny->priorita;
			novyUkol->hotovo = ukolOznaceny->hotovo;

			novyUkol->dalsi = NULL;
			novyUkol->predchozi = NULL;


			indexUkolu->dalsi = novyUkol;
			novyUkol->dalsi = NULL;
			novyUkol->predchozi = indexUkolu;


			printf("Kopie ukolu: %s byla vytvorena s datumem: %d.%d.%d\n", ukolOznaceny->jmeno, novyUkol->den, novyUkol->mesic, novyUkol->rok);
			//free(ukolOznaceny);
			break;
		}
		ukolRef = ukolRef->dalsi;
	}
	return startPtr;
}

Ukol* oznacitUkolJakoHotovy(Ukol* startPtr) { //funkce neni volana, vyreseno nakonci ve funkci uprav ukolu

	printf("Zadejte jmeno ukolu ktery chcete oznacit jako hotovy: ");
	char input[30];
	fgets(input, 29, stdin);

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

void ZapsatDoSouboru(Ukol* start) { //zapisovani seznamu do souboru ukoly.bin
	FILE* pSoubor;
	pSoubor = fopen("ukoly.bin", "wb"); //zapisovani je binarni

	if (pSoubor != NULL) {
		Ukol* aktualniUkol = start;

		Ukol* holdDalsi = NULL;
		Ukol* holdPredchozi = NULL;

		while (aktualniUkol != NULL) {
			holdDalsi = aktualniUkol->dalsi;
			holdPredchozi = aktualniUkol->predchozi;

			aktualniUkol->dalsi = NULL;
			aktualniUkol->predchozi = NULL;

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
	SYSTEMTIME t; // deklarace struktury systemoveho casu
	GetLocalTime(&t); // naplneni struktury

	printf("Dnesni ukoly:\n");
	while (aktualniUkol != NULL) {
		if (aktualniUkol->rok == t.wYear) { //porovnavani systemoveho data s daty ukolu
			if (aktualniUkol->mesic == t.wMonth) {
				if (aktualniUkol->den == t.wDay) {
					pocet++;
					if (aktualniUkol->hotovo == 1) {
						printf(CERNE("		Jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else if (aktualniUkol->priorita == 1) {
						printf(ZELENE("		Jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else if (aktualniUkol->priorita == 2) {
						printf(ZLUTE("		Jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else if (aktualniUkol->priorita == 3) {
						printf(MODRE("		Jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else {
						printf("		Jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
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
	SYSTEMTIME t;
	GetLocalTime(&t);

	printf("Budouci ukoly:\n");
	while (aktualniUkol != NULL) {
		if (aktualniUkol->rok == t.wYear) {
			if (aktualniUkol->mesic == t.wMonth) {
				if (aktualniUkol->den > t.wDay) {
					pocet++;
					if (aktualniUkol->hotovo == 1) {
						printf(CERNE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else if (aktualniUkol->priorita == 1) {
						printf(ZELENE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else if (aktualniUkol->priorita == 2) {
						printf(ZLUTE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else if (aktualniUkol->priorita == 3) {
						printf(MODRE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else {
						printf("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
				}
			}
			else if (aktualniUkol->mesic > t.wMonth) {
				pocet++;
				if (aktualniUkol->hotovo == 1) {
					printf(CERNE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
				else if (aktualniUkol->priorita == 1) {
					printf(ZELENE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
				else if (aktualniUkol->priorita == 2) {
					printf(ZLUTE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
				else if (aktualniUkol->priorita == 3) {
					printf(MODRE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
				else {
					printf("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
			}
		}
		else if (aktualniUkol->rok > t.wYear) {
			pocet++;
			if (aktualniUkol->hotovo == 1) {
				printf(CERNE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
			else if (aktualniUkol->priorita == 1) {
				printf(ZELENE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
			else if (aktualniUkol->priorita == 2) {
				printf(ZLUTE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
			else if (aktualniUkol->priorita == 3) {
				printf(MODRE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
			else {
				printf("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
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
	SYSTEMTIME t;
	GetLocalTime(&t);

	printf("Minule ukoly:\n");
	while (aktualniUkol != NULL) {
		if (aktualniUkol->rok == t.wYear) {
			if (aktualniUkol->mesic == t.wMonth) {
				if (aktualniUkol->den < t.wDay) {
					pocet++;
					if (aktualniUkol->hotovo == 1) {
						printf(CERNE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else if (aktualniUkol->priorita == 1) {
						printf(ZELENE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else if (aktualniUkol->priorita == 2) {
						printf(ZLUTE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else if (aktualniUkol->priorita == 3) {
						printf(MODRE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
					else {
						printf("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
					}
				}
			}
			else if (aktualniUkol->mesic < t.wMonth) {
				pocet++;
				if (aktualniUkol->hotovo == 1) {
					printf(CERNE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
				else if (aktualniUkol->priorita == 1) {
					printf(ZELENE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
				else if (aktualniUkol->priorita == 2) {
					printf(ZLUTE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
				else if (aktualniUkol->priorita == 3) {
					printf(MODRE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
				else {
					printf("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
				}
			}
		}
		else if (aktualniUkol->rok < t.wYear) {
			pocet++;
			if (aktualniUkol->hotovo == 1) {
				printf(CERNE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
			else if (aktualniUkol->priorita == 1) {
				printf(ZELENE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
			else if (aktualniUkol->priorita == 2) {
				printf(ZLUTE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
			else if (aktualniUkol->priorita == 3) {
				printf(MODRE("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n"), aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
			else {
				printf("		Datum: %d.%d.%-5d\t jmeno: %-12s\t priorita: %-1d\t hotovo: %-1d\n", aktualniUkol->den, aktualniUkol->mesic, aktualniUkol->rok, aktualniUkol->jmeno, aktualniUkol->priorita, aktualniUkol->hotovo);
			}
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

void zmenitUkol(Ukol* start) {
	int den, mesic, rok;
	char jmeno[UKOL_SIZE];

	printf("Zadejte datum (d m r) a jmeno ukolu ktery chcete zmenit/smazat: "); //navigace pomoci data a jmena ukolu

	char input[70];
	fgets(input, 69, stdin);
	sscanf(input, "%d %d %d %s", &den, &mesic, &rok, &jmeno);

	Ukol* ukolRef = start;
	Ukol* ukolOznaceny = NULL;

	while (ukolRef != NULL) {
		if ((den == ukolRef->den) && (mesic == ukolRef->mesic) && (rok == ukolRef->rok)) {
			if (strncmp(jmeno, ukolRef->jmeno, strlen(ukolRef->jmeno)) == 0) {
				ukolOznaceny = ukolRef;

				//menu uprav ukolu
				printf("	Vybrali jste ukol: %s\n\n", ukolOznaceny->jmeno);
				printf("	H: Oznacit ukol jako hotovy\n");
				printf("	P: Zmenit prioritu ukolu\n");
				printf("	D: Presunout ukol na jine datum\n");
				printf("	S: Smazat ukol\n");
				printf("	Q: Odejit z uprav ukolu\n\n");

				char cmd;
				char zmena;
				char input[30];
				int new_den, new_mesic, new_rok, new_priorita;

				do
				{
					cmd = tolower(getchar());
					while (getchar() != '\n');

					switch (cmd)
					{
					case 'h':
						if (ukolOznaceny->hotovo == 1) { //moznost oznaceni jiz hotoveho ukolu jako nehotovy
							printf("	Ukol je jiz oznacen jako hotovy. Prejete si ho oznacit jako nehotovy? (A/N) ");
							do {
								zmena = tolower(getchar());
								while (getchar() != '\n');
								switch (zmena) {
								case 'a':
									printf("	Ukol %s oznaceny jako nehotovy\n", ukolOznaceny->jmeno);
									ukolOznaceny->hotovo = 0;
									break;
								case 'n':
									break;
								}
								break;
							} while (1);
						}
						else {
							ukolOznaceny->hotovo = 1; //pokud ukol je oznaceny jako nehotovy, oznaci se jako hotovy
						}
						break;
					case 'p': //zmena priority ukolu
						printf("	Aktulani priorita ukolu je: %d\n", ukolOznaceny->priorita);
						printf("	Zadejte novou prioritu ukolu (1 (nejmensi) - 3 (nejvetsi))\n");
						fgets(input, 29, stdin);
						sscanf(input, "%d", &new_priorita);

						ukolOznaceny->priorita = new_priorita;

						printf("	Nova priorita ukolu: %s je: %d\n", ukolOznaceny->jmeno, ukolOznaceny->priorita);
						break;
					case 'd': //zmena data ukolu
						printf("	Zadejte nove datum (den (1-31) mesic (1-12) rok (xxxx))\n");
						fgets(input, 30, stdin);

						sscanf(input, "%d %d %d", &new_den, &new_mesic, &new_rok);

						ukolOznaceny->den = new_den;
						ukolOznaceny->mesic = new_mesic;
						ukolOznaceny->rok = new_rok;

						printf("	Nove datum ukolu: %s je: %d.%d.%d\n", ukolOznaceny->jmeno, ukolOznaceny->den, ukolOznaceny->mesic, ukolOznaceny->rok);
						break;
					case 's': //smazani ukolu
						if (start != NULL && ukolOznaceny == start) {
							if (ukolOznaceny->dalsi != NULL) {
								ukolOznaceny->dalsi->predchozi = NULL;
								start = ukolOznaceny->dalsi;
							}
							else {
								start = NULL;
							}
						}
						else {
							if (ukolOznaceny != NULL) {
								if (ukolOznaceny->predchozi != NULL) {
									ukolOznaceny->predchozi->dalsi = ukolOznaceny->dalsi;
								}

								if (ukolOznaceny->dalsi != NULL) {
									ukolOznaceny->dalsi->predchozi = ukolOznaceny->predchozi;
								}
							}
						}

						if (ukolOznaceny != NULL) {
							ukolOznaceny = NULL;
							free(ukolOznaceny);
						}
					}
				} while (cmd != 'q');
				break;
			}
		}
		ukolRef = ukolRef->dalsi;
	}
}
