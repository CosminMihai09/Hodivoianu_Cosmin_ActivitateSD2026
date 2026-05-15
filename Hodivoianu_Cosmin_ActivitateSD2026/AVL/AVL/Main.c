#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Rezervare {
    unsigned int id_rezervare;
    char* denumire_hotel;
    unsigned char nr_camere;
    char* nume_client;
    float suma_plata;
    int zi, luna;
} Rezervare;

typedef struct NodAVL {
    Rezervare info;
    int inaltime;
    struct NodAVL* st, * dr;
} NodAVL;


int getInaltime(NodAVL* nod) {
    return nod ? nod->inaltime : 0;
}

int maxim(int a, int b) {
    return (a > b) ? a : b;
}

int getFactorEchilibru(NodAVL* nod) {
    if (!nod) return 0;
    return getInaltime(nod->dr) - getInaltime(nod->st);
}

NodAVL* rotatieDreapta(NodAVL* b) {
    NodAVL* a = b->st;
    b->st = a->dr;
    a->dr = b;

    b->inaltime = 1 + maxim(getInaltime(b->st), getInaltime(b->dr));
    a->inaltime = 1 + maxim(getInaltime(a->st), getInaltime(a->dr));
    return a;
}

NodAVL* rotatieStanga(NodAVL* a) {
    NodAVL* b = a->dr;
    a->dr = b->st;
    b->st = a;

    a->inaltime = 1 + maxim(getInaltime(a->st), getInaltime(a->dr));
    b->inaltime = 1 + maxim(getInaltime(b->st), getInaltime(b->dr));
    return b;
}


NodAVL* inserareAVL(NodAVL* rad, Rezervare r) {
    if (!rad) {
        NodAVL* nou = (NodAVL*)malloc(sizeof(NodAVL));
        nou->info = r;
        nou->st = nou->dr = NULL;
        nou->inaltime = 1;
        return nou;
    }

    if (r.id_rezervare < rad->info.id_rezervare)
        rad->st = inserareAVL(rad->st, r);
    else if (r.id_rezervare > rad->info.id_rezervare)
        rad->dr = inserareAVL(rad->dr, r);
    else return rad;

    rad->inaltime = 1 + maxim(getInaltime(rad->st), getInaltime(rad->dr));

    int ge = getFactorEchilibru(rad);

    if (ge == -2 && getFactorEchilibru(rad->st) <= 0)
        return rotatieDreapta(rad);

    if (ge == -2 && getFactorEchilibru(rad->st) > 0) {
        rad->st = rotatieStanga(rad->st);
        return rotatieDreapta(rad);
    }

    if (ge == 2 && getFactorEchilibru(rad->dr) >= 0)
        return rotatieStanga(rad);

    if (ge == 2 && getFactorEchilibru(rad->dr) < 0) {
        rad->dr = rotatieDreapta(rad->dr);
        return rotatieStanga(rad);
    }

    return rad;
}


void afisareAVL(NodAVL* rad) {
    if (rad) {
        afisareAVL(rad->st);
        printf("ID: %u, Hotel: %s, Inaltime: %d, GE: %d\n",
            rad->info.id_rezervare, rad->info.denumire_hotel, rad->inaltime, getFactorEchilibru(rad));
        afisareAVL(rad->dr);
    }
}

void dezalocareAVL(NodAVL* rad) {
    if (rad) {
        dezalocareAVL(rad->st);
        dezalocareAVL(rad->dr);
        free(rad->info.denumire_hotel);
        free(rad->info.nume_client);
        free(rad);
    }
}

int main() {
    NodAVL* rad = NULL;
    FILE* f = fopen("rezervari.txt", "r");
    if (!f) return -1;

    Rezervare r;
    char b_client[100], b_hotel[100];
    int c_temp;

    while (fscanf(f, "%s %u %s %d %f %d %d", b_client, &r.id_rezervare, b_hotel, &c_temp, &r.suma_plata, &r.zi, &r.luna) != EOF) {
        r.nume_client = _strdup(b_client);
        r.denumire_hotel = _strdup(b_hotel);
        r.nr_camere = (unsigned char)c_temp;

        rad = inserareAVL(rad, r);
    }
    fclose(f);

    printf("--- Arbore AVL Echilibrat ---\n");
    afisareAVL(rad);

    dezalocareAVL(rad);
    return 0;
}