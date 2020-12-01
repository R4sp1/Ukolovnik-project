#pragma once

#define UKOL_SIZE 50

typedef struct S_Ukol {

	int den;
	int mesic;
	int rok;
	char jmeno[UKOL_SIZE];
	int priorita;
	int hotovo;
	struct S_Ukol* dalsi;
	struct S_Ukol* predchozi;

} Ukol;

void ZobrazitSeznam(Ukol* start);
void VycisteniPameti(Ukol* start);
void ZapsatDoSouboru(Ukol* start);
void dnesniUkol(Ukol* start);
void budouciUkoly(Ukol* start);
void minuleUkoly(Ukol* start);