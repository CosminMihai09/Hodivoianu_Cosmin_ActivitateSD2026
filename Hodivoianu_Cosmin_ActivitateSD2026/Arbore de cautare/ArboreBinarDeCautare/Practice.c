//#define _CRT_SECURE_NO_WARNINGS
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct Comanda {
//	int timpLivrare;
//	int codClient;
//	int idComanda;
//	char* numeClient;
//	char* denumireMancare;
//	int numarProduse;
//	float pret;
//} Comanda;
//
//typedef struct Nod {
//	Comanda info;
//	struct Nod* st, * dr;
//} Nod;
//
//typedef struct pula {
//	int pula;
//	char* pizda;
//	float inima;
//} pula;
//
//typedef struct Nod {
//	pula info;
//	Nod* st, * dr;
//} Nod;
//
//
//pula inserarePula(int lala, char* pizdaa, float inima) {
//	pula pl;
//	pl.pula = lala;
//	pl.pizda = (char*)malloc(sizeof(pizdaa) + 1);
//	strcpy(pl.pizda, pizdaa);
//	pl.inima = inima;
//}
//
//
//
//Comanda creeazaComanda(int timp, int cod, int id, char* client, char* mancare, int numarProduse, float pret) {
//	Comanda noua;
//	noua.timpLivrare = timp;
//	noua.codClient = cod;
//	noua.idComanda = id;
//	noua.numeClient = (char*)malloc(strlen(client) + 1);
//	strcpy(noua.numeClient, client);
//	noua.denumireMancare = (char*)malloc(strlen(mancare) + 1);
//	noua.numarProduse = numarProduse;
//	noua.pret = pret;
//	return noua;
//}
//
//
//Nod* inseration(Nod* rad, pula p)
//{
//	if (rad == NULL) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = p;
//		nou->dr = nou->st = NULL;
//		return nou;
//	}
//
//	if (p.pula < rad->info.pula) {
//		rad->st = inseration(rad->st, p);
//	}
//	else if (p.pula > rad->info.pula) {
//		rad->dr = inseration(rad->dr, p);
//	}
//	return rad;
//}
//
//
//void afisareOrdination(Nod* rad) {
//	if (rad) {
//		afisareOrdination(rad->st);
//		printf("%d%S%.2f", rad->info.inima, rad->info.pizda, rad->info.pula);
//		afisareOrdination(rad->dr);
//	}
//}
//
//Nod* inserare(Nod* rad, Comanda c) {
//	if (rad == NULL) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = c;
//		nou->st = NULL;
//		nou->dr = NULL;
//		return nou;
//	}
//
//	if (c.idComanda < rad->info.idComanda) {
//		rad->st = inserare(rad->st, c);
//	}
//	else if (c.idComanda > rad->info.idComanda) {
//		rad->dr = inserare(rad->dr, c);
//	}
//	return rad;
//}
//
//
//void afisareInOrdine(Nod* rad) {
//	if (rad) {
//		afisareInOrdine(rad->st);
//		printf("Id %d, Cliend %s, Timpd %d, Pret %.2f\n", rad->info.idComanda, rad->info.numeClient, rad->info.timpLivrare, rad->info.pret);
//		afisareInOrdine(rad->dr);
//	}
//}



//
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//
//typedef struct Comanda {
//	int id_comanda;
//	int timp_livrare;
//	int cod_client;
//	char* nume_client;
//	char* descriere_comanda;
//	float pret;
//	int telefon;
//} Comanda;
//
//typedef struct Nod {
//	Comanda info;
//	Nod* st, * dr;
//} Nod;
//
//Comanda creareComanda(int id, int timp, int codClient, char* numeClient, char* descriere, float pret, int telefon) {
//	Comanda noua;
//	noua.id_comanda = id;
//	noua.timp_livrare = timp;
//	noua.cod_client = codClient;
//	noua.nume_client = (char*)malloc(sizeof(numeClient) + 1);
//	strcpy(noua.nume_client, numeClient);
//	noua.descriere_comanda = (char*)malloc(sizeof(descriere) + 1);
//	strcpy(noua.descriere_comanda, descriere);
//	noua.pret = pret;
//	noua.telefon = telefon;
//	return noua;
//}
//
//Nod* inserare(Nod* rad, Comanda c) {
//	if (rad == NULL) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = c;
//		nou->st = nou->dr = NULL;
//		return nou;
//	}
//
//	if (c.id_comanda < rad->info.id_comanda) {
//		rad->st = inserare(rad->st, c);
//	}
//	else if (c.id_comanda > rad->info.id_comanda) {
//		rad->dr = inserare(rad->dr, c);
//	}
//	return rad;
//}
//
//void afisareInOrdine(Nod* rad) {
//	if (rad) {
//		afisareInOrdine(rad->st);
//		printf("%d, %d, %d, %s, %s, %.2f, %d", rad->info.id_comanda, rad->info.timp_livrare, rad->info.cod_client, rad->info.nume_client, rad->info.descriere_comanda, rad->info.pret, rad->info.telefon);
//		afisareInOrdine(rad->dr);
//	}
//}
//
//void numaraComenzi(Nod* rad, int valoare, int* nr) {
//	if (rad) {
//		if (rad->info.timp_livrare > valoare) {
//			(*nr)++;
//		}
//		numaraComenzi(rad->st, valoare, nr);
//		numaraComenzi(rad->dr, valoare, nr);
//	}
//}
//
//void populeazaVector(Nod* rad, Comanda* c, int* index, int prag) {
//	if (rad) {
//		if (rad->info.timp_livrare > prag) {
//			c[*index] = creareComanda(rad->info.id_comanda, rad->info.timp_livrare, rad->info.cod_client, rad->info.nume_client, rad->info.descriere_comanda, rad->info.pret, rad->info.telefon);
//			(*index)++;
//		}
//		populeazaVector(rad->st, c, index, prag);
//		populeazaVector(rad->dr, c, index, prag);
//	}
//}
//
//typedef struct Heap {
//	Comanda* elemente;
//	int dim;
//} Heap;
//
//void filtrareHeap(Heap h, int index) {
//	int max = index;
//	int st = 2 * index + 1;
//	int dr = 2 * index + 2;
//
//	if (st < h.dim && h.elemente[st].timp_livrare > h.elemente[max].timp_livrare) {
//		max = st;
//	}
//	if (dr < h.dim && h.elemente[st].timp_livrare > h.elemente[max].timp_livrare) {
//		max = dr;
//	}
//}

