#pragma once

#define UKOL_SIZE 50

struct ukol
{
    char  nazev[UKOL_SIZE];
    int   rok;
    struct ukol* dalsi;
};

void add(char* nazev, int rok, struct ukol** uk_prvni);
void del(int rok, struct ukol** uk_prvni);
