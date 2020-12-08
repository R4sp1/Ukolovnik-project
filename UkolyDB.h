#pragma once

#define UKOL_SIZE 50 //max velikost jmena ukolu

typedef struct S_Ukol {
	int den;
	int mesic;
	int rok;
	char jmeno[UKOL_SIZE];
	int priorita;
	int hotovo;
	struct S_Ukol* dalsi; //ukazatel na dalsi ukol
	struct S_Ukol* predchozi; //ukazatel na predchozi ukol
} Ukol;

void ZobrazitSeznam(Ukol* start);
void VycisteniPameti(Ukol* start);
void ZapsatDoSouboru(Ukol* start);
void dnesniUkol(Ukol* start);
void budouciUkoly(Ukol* start);
void minuleUkoly(Ukol* start);
void zmenitUkol(Ukol* strat);