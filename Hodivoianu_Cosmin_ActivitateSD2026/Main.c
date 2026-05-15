//#define _CRT_SECURE_NO_WARNINGS
//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct {
//	int cod_rezervare;
//	char* destinatie;
//	char* oras_plecare;
//	char* data_plecare;
//	int nr_turisti;
//	char clasa;             // NOU: char
//	int nr_servicii;        // NOU: dimensiune pentru vectorul float*
//	float* pret_servicii;   // NOU: vector dinamic float*
//} Rezervare;
//
//typedef struct Nod {
//	Rezervare info;
//	struct Nod* next;
//} Nod;
//
//Nod* inserare(Nod* start, Rezervare r) {
//
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->info = r;
//
//	if (start == NULL) {
//		nou->next = nou;
//		return nou;
//	}
//
//	Nod* temp = start;
//	while (temp->next != start) {
//		temp = temp->next;
//	}
//	temp->next = nou;
//	nou->next = start;
//	return start;
//}
//
//void afisare(Nod* start) {
//	if (start == NULL) return;
//
//	Nod* temp = start;
//	do {
//		printf("%d, %s, %s, %s, %d, Clasa: %c, Servicii: %d [ ",
//			temp->info.cod_rezervare, temp->info.destinatie, temp->info.oras_plecare,
//			temp->info.data_plecare, temp->info.nr_turisti, temp->info.clasa, temp->info.nr_servicii);
//
//		// Afisare vector float
//		for (int i = 0; i < temp->info.nr_servicii; i++) {
//			printf("%.2f ", temp->info.pret_servicii[i]);
//		}
//		printf("]\n");
//
//		temp = temp->next;
//	} while (temp != start);
//}
//
//// ATENTIE: Functia de cautare returneaza o COPIE. 
//// In C, asta inseamna ca ambele (lista si copia) puncteaza catre aceeasi memorie float*.
//Rezervare cautare(Nod* start, char* destinatie) {
//	if (start != NULL) {
//		Nod* temp = start;
//		do {
//			if (strcmp(temp->info.destinatie, destinatie) == 0) {
//				return temp->info;
//			}
//			temp = temp->next;
//		} while (temp != start);
//	}
//	Rezervare goala = { 0, NULL, NULL, NULL, 0, ' ', 0, NULL };
//	return goala;
//}
//
//// Functie necesara pentru a sterge un nod corect fara memory leaks
//void freeRezervare(Rezervare r) {
//	free(r.destinatie);
//	free(r.oras_plecare);
//	free(r.data_plecare);
//	if (r.pret_servicii) free(r.pret_servicii); // Eliberam vectorul float*
//}
//
//Nod* stergere(Nod* cap) {
//	if (cap == NULL) return NULL;
//
//	Nod* temp = cap;
//	Nod* prev = NULL;
//	int max = -1;
//
//	// Gasim maximul
//	do {
//		if (temp->info.nr_turisti > max) max = temp->info.nr_turisti;
//		temp = temp->next;
//	} while (temp != cap);
//
//	temp = cap;
//	Nod* ultim = cap;
//	while (ultim->next != cap) ultim = ultim->next;
//
//	// Cazul in care stergem capul
//	if (cap->info.nr_turisti == max) {
//		Nod* deSters = cap;
//		if (cap->next == cap) { // un singur nod
//			freeRezervare(deSters->info);
//			free(deSters);
//			return NULL;
//		}
//		ultim->next = cap->next;
//		cap = cap->next;
//		freeRezervare(deSters->info);
//		free(deSters);
//		return cap;
//	}
//
//	// Stergere in interior/final
//	prev = cap;
//	temp = cap->next;
//	while (temp != cap) {
//		if (temp->info.nr_turisti == max) {
//			prev->next = temp->next;
//			freeRezervare(temp->info);
//			free(temp);
//			return cap;
//		}
//		prev = temp;
//		temp = temp->next;
//	}
//	return cap;
//}
//
//void scriereInFisier(Nod* cap) {
//	FILE* f = fopen("RezervariScrise.txt", "w");
//	if (!f) return;
//
//	Nod* temp = cap;
//	do {
//		fprintf(f, "%d, %s, %s, %s, %d, %c, %d",
//			temp->info.cod_rezervare, temp->info.oras_plecare, temp->info.destinatie,
//			temp->info.data_plecare, temp->info.nr_turisti, temp->info.clasa, temp->info.nr_servicii);
//
//		for (int i = 0; i < temp->info.nr_servicii; i++) {
//			fprintf(f, ", %.2f", temp->info.pret_servicii[i]);
//		}
//		fprintf(f, "\n");
//		temp = temp->next;
//	} while (temp != cap);
//
//	fclose(f);
//}
//
//int main() {
//	Nod* cap = NULL;
//	FILE* f = fopen("Rezervari.txt", "r");
//	if (!f) return -1;
//
//	Rezervare r;
//	char buffer[100];
//
//	// FORMAT FISIER ASTEPTAT:
//	// cod destinatie oras data turisti clasa nr_servicii pret1 pret2...
//	while (fscanf(f, "%d", &r.cod_rezervare) == 1) {
//		fscanf(f, "%s", buffer);
//		r.destinatie = _strdup(buffer);
//
//		fscanf(f, "%s", buffer);
//		r.oras_plecare = _strdup(buffer);
//
//		fscanf(f, "%s", buffer);
//		r.data_plecare = _strdup(buffer);
//
//		fscanf(f, "%d", &r.nr_turisti);
//
//		// CITIRE CHAR (Atentie la spatiul din format " %c" pentru a sari peste whitespace/enter)
//		fscanf(f, " %c", &r.clasa);
//
//		// CITIRE VECTOR DINAMIC
//		fscanf(f, "%d", &r.nr_servicii);
//		r.pret_servicii = (float*)malloc(sizeof(float) * r.nr_servicii);
//		for (int i = 0; i < r.nr_servicii; i++) {
//			fscanf(f, "%f", &r.pret_servicii[i]);
//		}
//
//		cap = inserare(cap, r);
//	}
//	fclose(f);
//
//	printf("S-a citit tot (inclusiv char si float*)\n");
//	afisare(cap);
//
//	// ... restul functiilor raman similare, dar ai grija la memory leaks!
//
//	scriereInFisier(cap);
//
//	return 0;
//}



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct {
	int cod_rezervare;
	char* destinatie;
	char* oras_plecare;
	char* data_plecare;
	int nr_turisti;
	char clasa;             // NOU: char
	int nr_servicii;        // NOU: dimensiune pentru vectorul float*
	float* pret_servicii;   // NOU: vector dinamic float*
} Rezervare;

typedef struct Nod {
	Rezervare info;
	struct Nod* next;
} Nod;


Nod* inserare(Nod* start, Rezervare r) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = r;

	if (start == NULL) {
		nou->next = nou;
		return nou;
	}

	Nod* temp = start;
	while (temp->next != start) {
		temp = temp->next;
	}
	temp->next = nou;
	nou->next = start;
	return start;
}

void afisare(Nod* start) {
	if (start == NULL) {
		return;
	}

	Nod* temp = start;
	do {
		printf("%d, %s, %s, %s, %d, %c, %d ", temp->info.cod_rezervare, temp->info.destinatie, temp->info.oras_plecare, temp->info.data_plecare, temp->info.nr_turisti, temp->info.clasa, temp->info.nr_servicii);
		for (int i = 0; i < temp->info.nr_servicii; i++) {
			printf("%.2f ", temp->info.pret_servicii[i]);
		}
		printf("\n");

		temp = temp->next;
	} while (temp != start);
	printf("\n\n");
	return;
}

Rezervare cautare(Nod* start, char* destinatie) {
	if (start == NULL) {
		Rezervare goala = { 0, NULL, NULL, NULL, 0, "", 0, "" };
		return goala;
	}

	Nod* temp = start;
	do {
		if (strcmp(temp->info.destinatie, destinatie) == 0) {
			return temp->info;
		}
		temp = temp->next;
	} while (temp != start);

	printf("Not found\n");
	return;
}

void scriereInFisier(Rezervare r) {
	FILE* f = fopen("RezervareScrisa.txt", "w");
	if (!f) {
		return;
	}

	if (!&r && r.cod_rezervare == NULL) {
		return;
	}

	fprintf(f, "%d %s %s %s %d %c %d ", r.cod_rezervare, r.destinatie, r.oras_plecare, r.data_plecare, r.nr_turisti, r.clasa, r.nr_servicii);
	for (int i = 0; i < r.nr_servicii; i++) {
		fprintf(f, "%.2f ", r.pret_servicii[i]);
	}
	return;
}

void actualizare(Nod* start, char* data_noua, int cod) {
	if (start == NULL)
		return;

	Nod* temp = start;
	do {
		if (temp->info.cod_rezervare == cod) {
			free(temp->info.data_plecare);
			temp->info.data_plecare == (char*)malloc(strlen(data_noua) + 1);
			strcpy(temp->info.data_plecare, data_noua);
			return;
		}
		temp = temp->next;
	} while (temp != start);
	return;
}

Nod* stergere(Nod* start) {
	if (start == NULL) {
		return NULL;
	}

	int max = 0;
	Nod* temp = start;
	Nod* prev;
	do {
		if (temp->info.nr_turisti > max)
			max = temp->info.nr_turisti;

		prev = temp;
		temp = temp->next;
	} while (temp != start);

	//star case
	if (temp->info.nr_turisti == max) {
		prev->next = temp->next;
		Nod* newStart = temp->next;
		free(temp->info.data_plecare);
		free(temp->info.destinatie);
		free(temp->info.oras_plecare);
		if (temp->info.nr_servicii > 0) {
			free(temp->info.pret_servicii);
		}
		return newStart;
	}

	//other case
	do {
		if (temp->info.nr_turisti == max) {
			prev->next = temp->next;
			free(temp->info.data_plecare);
			free(temp->info.destinatie);
			free(temp->info.oras_plecare);
			if (temp->info.nr_servicii > 0) {
				free(temp->info.pret_servicii);
			}
			return start;
		}
		prev = temp;
		temp = temp->next;
	} while (temp != start);
}

int* transformareVector(Nod* start, char* oras, int* dimensiuneVector) {
	int* v = NULL;
	if (start == NULL) {
		return v;
	}

	//aflat dimenisune
	Nod* temp = start;
	do {
		if (strcmp(temp->info.destinatie, oras) == 0) {
			(*dimensiuneVector)++;
		}
		temp = temp->next;
	} while (temp != start);

	v = (int*)malloc((*dimensiuneVector) * sizeof(int));
	int i = 0;
	do {
		if (strcmp(temp->info.destinatie, oras) == 0) {
			v[i] = temp->info.cod_rezervare;
			i++;
		}
		temp = temp->next;
	} while (temp != start);

	for (int i = 0; i < *dimensiuneVector; i++) {
		printf("%d ", v[i]);
	}

	return v;
}

int main() {
	Nod* cap = NULL;
	char buffer[100];
	Rezervare r;

	FILE* f = fopen("Rezervari2.txt", "r");
	if (!f) {
		printf("File not found\n\n");
		return -1;
	}

	while (fscanf(f, "%d", &r.cod_rezervare) == 1) {
		fscanf(f, "%s", buffer);
		r.destinatie = (char*)malloc(strlen(buffer) + 1);
		strcpy(r.destinatie, buffer);

		fscanf(f, "%s", buffer);
		r.oras_plecare = (char*)malloc(strlen(buffer) + 1);
		strcpy(r.oras_plecare, buffer);

		fscanf(f, "%s", buffer);
		r.data_plecare = (char*)malloc(strlen(buffer) + 1);
		strcpy(r.data_plecare, buffer);

		fscanf(f, "%d", &r.nr_turisti);

		fscanf(f, " %c", &r.clasa);

		fscanf(f, "%d", &r.nr_servicii);

		r.pret_servicii = (float*)malloc(r.nr_servicii * sizeof(float));
		for (int i = 0; i < r.nr_servicii; i++) {
			fscanf(f, "%f", &r.pret_servicii[i]);
		}

		cap = inserare(cap, r);
	}
	fclose(f);

	afisare(cap);

	actualizare(cap, "09012003", 102);

	Rezervare gasita = cautare(cap, "Dubai");
	scriereInFisier(gasita);

	//cap = stergere(cap);
	afisare(cap);

	printf("\n\n");

	int dimensiune = 0;
	transformareVector(cap, "Roma", &dimensiune);

	return 0;
}