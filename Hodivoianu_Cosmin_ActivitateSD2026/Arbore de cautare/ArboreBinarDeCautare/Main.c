//#define _CRT_SECURE_NO_WARNINGS
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//// Structura Rezervare (am adaugat campurile zi si luna pentru a avea minim 7 campuri conform biletului) [cite: 7, 8, 10]
//typedef struct Rezervare {
//	unsigned int id_rezervare; // camp obligatoriu 
//	char* denumire_hotel; // camp char* obligatoriu [cite: 8]
//	unsigned char numar_camere_rezervate; // camp obligatoriu 
//	char* nume_client; // camp char* obligatoriu [cite: 8]
//	float suma_de_plata; // camp la alegere [cite: 8]
//	int zi; // camp extra [cite: 8]
//	int luna; // camp extra [cite: 8]
//} Rezervare;
//
//// Structura Nod pentru ABC [cite: 4, 12]
//typedef struct Nod {
//	Rezervare r;
//	struct Nod* st, * dr; // Corectie: in interiorul structurii folosim 'struct Nod*'
//} Nod;
//
//// Functie pentru crearea rezervarii cu Deep Copy [cite: 5, 20]
//Rezervare creareRezervare(unsigned int id, char* denumire, unsigned char nr, char* nume, float suma, int zi, int luna) {
//	Rezervare r;
//	r.id_rezervare = id;
//	r.numar_camere_rezervate = nr;
//	r.suma_de_plata = suma;
//	r.zi = zi;
//	r.luna = luna;
//
//	// Alocare si copiere string-uri
//	r.denumire_hotel = (char*)malloc(strlen(denumire) + 1);
//	strcpy(r.denumire_hotel, denumire); // Corectie: era scris 'strpcy'
//
//	r.nume_client = (char*)malloc(strlen(nume) + 1);
//	strcpy(r.nume_client, nume); // Adaugat: lipsea copierea pentru nume_client
//
//	return r;
//}
//
//// Inserare in Arbore Binar de Cautare dupa id_rezervare [cite: 5, 12]
//Nod* inserareNod(Nod* rad, Rezervare r) {
//	if (rad == NULL) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->r = r;
//		nou->dr = nou->st = NULL;
//		return nou;
//	}
//
//	if (r.id_rezervare < rad->r.id_rezervare) {
//		rad->st = inserareNod(rad->st, r);
//	}
//	else if (r.id_rezervare > rad->r.id_rezervare) {
//		rad->dr = inserareNod(rad->dr, r);
//	}
//	return rad;
//}
//
//// Afisare Inordine (Stanga - Radacina - Dreapta) [cite: 14]
//void afisareInOrdine(Nod* rad) {
//	if (rad) {
//		afisareInOrdine(rad->st);
//		printf("Id: %u, Hotel: %s, Camere: %hhu, Client: %s, Suma: %.2f, Data: %d/%d\n",
//			rad->r.id_rezervare, rad->r.denumire_hotel, rad->r.numar_camere_rezervate,
//			rad->r.nume_client, rad->r.suma_de_plata, rad->r.zi, rad->r.luna);
//		afisareInOrdine(rad->dr);
//	}
//}
//
//// Cerinta 2: Total camere din nodurile frunza
//int totalCamereFrunze(Nod* rad) {
//	if (rad == NULL) return 0;
//	if (rad->st == NULL && rad->dr == NULL) {
//		return rad->r.numar_camere_rezervate;
//	}
//	return totalCamereFrunze(rad->st) + totalCamereFrunze(rad->dr);
//}
//
//// Cerinta 3: Inaltime arbore (numar de niveluri)
//int calculInaltime(Nod* rad) {
//	if (rad == NULL) return 0;
//	int hSt = calculInaltime(rad->st);
//	int hDr = calculInaltime(rad->dr);
//	return 1 + (hSt > hDr ? hSt : hDr);
//}
//
//// Cerinta 5: Dezalocare completa (absență memory leaks) [cite: 11, 44, 49]
//void dezalocareBST(Nod* rad) {
//	if (rad) {
//		dezalocareBST(rad->st);
//		dezalocareBST(rad->dr);
//		free(rad->r.denumire_hotel);
//		free(rad->r.nume_client);
//		free(rad);
//	}
//}
//
//int main() {
//	Nod* rad = NULL;
//	FILE* f = fopen("rezervari.txt", "r");
//	if (!f) {
//		printf("Eroare la deschiderea fisierului!\n");
//		return -1;
//	}
//
//	unsigned int id;
//	char b_client[100], b_hotel[100];
//	int c_temp, zi, luna;
//	float suma;
//
//	// Citirea pana la finalul fisierului (EOF) [cite: 13]
//	// Ordinea: nume_client id hotel camere suma zi luna
//	while (fscanf(f, "%s %u %s %d %f %d %d", b_client, &id, b_hotel, &c_temp, &suma, &zi, &luna) != EOF) {
//
//		// Cream rezervarea si o inseram in arbore [cite: 5, 12]
//		Rezervare r = creareRezervare(id, b_hotel, (unsigned char)c_temp, b_client, suma, zi, luna);
//		rad = inserareNod(rad, r);
//	}
//	fclose(f);
//
//	printf("--- Arbore BST Inordine ---\n");
//	afisareInOrdine(rad);
//
//	printf("\nTotal camere frunze (Cerinta 2): %d\n", totalCamereFrunze(rad));
//	printf("Inaltime arbore (Cerinta 3): %d\n", calculInaltime(rad));
//
//	// Dezalocare finala (obligatorie pentru a evita memory leaks) [cite: 44, 49]
//	dezalocareBST(rad);
//	rad = NULL;
//
//	printf("\nMemorie eliberata cu succes!\n");
//	return 0;
//}



#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct Rezervare {
	unsigned int id;
	char* hotel;
	unsigned char nr_camere;
	char* client;
	float suma;
} Rezervare;

typedef struct Nod {
	Rezervare info;
	Nod* st, * dr;
} Nod;


Rezervare creazaRezervare(unsigned int id, char* hotel, unsigned char nr, char* client, float suma) {
	Rezervare noua;
	noua.id = id;
	noua.hotel = (char*)malloc(strlen(hotel) + 1);
	strcpy(noua.hotel, hotel);
	noua.nr_camere = nr;
	noua.client = (char*)malloc(strlen(client) + 1);
	strcpy(noua.client, client);
	noua.suma = suma;
	return noua;
}

Nod* inserareNod(Nod* rad, Rezervare r) {
	if (rad == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = r;
		nou->st = nou->dr = NULL;
		return nou;
	}

	if (r.id < rad->info.id) {
		rad->st = inserareNod(rad->st, r);
	}
	else if (r.id > rad->info.id) {
		rad->dr = inserareNod(rad->dr, r);
	}
	return rad;
}

void afisareInOrdine(Nod* rad) {
	if (rad) {
		afisareInOrdine(rad->st);
		printf("Id: %u, Hotel: %s, Nr. camere: %hhu, Client: %s, Suma: %.2f\n", rad->info.id, rad->info.hotel, rad->info.nr_camere, rad->info.client, rad->info.suma);
		afisareInOrdine(rad->dr);
	}
}

void dezalocareMemorie(Nod* rad) {
	if (rad) {
		dezalocareMemorie(rad->st);
		dezalocareMemorie(rad->dr);
		free(rad->info.client);
		free(rad->info.hotel);
		free(rad);
	}
}

int main() {
	Nod* rad = NULL;
	
	FILE* f = fopen("rezervari.txt", "r");
	if (!f) {
		printf("Nu s a gasit fisierul.. :(\n");
		return -1;
	}

	unsigned int id;
	char hotel[100];
	unsigned char nr_camere;
	char client[100];
	float suma;

	while (fscanf(f, "%u %s %hhu %s %f", &id, hotel, &nr_camere, client, &suma) != EOF) {
		Rezervare r = creazaRezervare(id, hotel, nr_camere, client, suma);
		rad = inserareNod(rad, r);
	}
	fclose(f);

	afisareInOrdine(rad);
	
	dezalocareMemorie(rad);

	return 0;
}
