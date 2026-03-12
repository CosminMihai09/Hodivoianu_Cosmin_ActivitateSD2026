#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct {
	int cod_rezervare;
	char* destinatie;
	char* oras_plecare;
	char* data_plecare;
	int nr_turisti;
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
		printf("%d, %s, %s, %s, %d\n", temp->info.cod_rezervare, temp->info.destinatie, temp->info.oras_plecare, temp->info.data_plecare, temp->info.nr_turisti);
		temp = temp->next;
	} while (temp != start);
	return;
}

Rezervare cautare(Nod* start, char* destinatie) {
	if (start != NULL) {
		Nod* temp = start;
		do {
			if (strcmp(temp->info.destinatie, destinatie) == 0) {
				return temp->info;
			}
			temp = temp->next;
		} while (temp != start);
	}
	else {
		Rezervare goala = { 0, NULL, NULL, NULL, 0 };
		return goala;
	}
}

Nod* actualizare(Nod* start, int cod, char* data_plecare) {
	if (start == NULL) {
		return NULL;
	}

	Nod* temp = start;
	do {
		if (temp->info.cod_rezervare == cod) {
			free(temp->info.data_plecare);
			temp->info.data_plecare = (char*)malloc(strlen(data_plecare) + 1);
			strcpy(temp->info.data_plecare, data_plecare);
			return temp;
		}
		temp = temp->next;
	} while (temp != start);
}

Nod* stergere(Nod* cap) {
	if (cap == NULL) {
		return NULL;
	}

	Nod* temp = cap;
	Nod* prev;
	int max = -1;

	do {
		if (temp->info.nr_turisti > max) {
			max = temp->info.nr_turisti;
		}
		prev = temp;
		temp = temp->next;
	} while (temp != cap);

	if (temp->info.nr_turisti == max) {
		prev->next = temp->next;
		Nod* valueToReturn = temp->next;
		free(temp->info.data_plecare);
		free(temp->info.oras_plecare);
		free(temp->info.destinatie);
		free(temp);
		return valueToReturn;
	}

	do {
		if (temp->info.nr_turisti == max) {
			prev->next = temp->next;
			free(temp->info.data_plecare);
			free(temp->info.oras_plecare);
			free(temp->info.destinatie);
			free(temp);
			return cap;
		}
		prev = temp;
		temp = temp->next;
	} while (temp != cap);
	return cap;
}

int* transformareInVector(Nod* cap, char* oras_pelcare, int* dimensiuneVector) {
	if (cap == NULL) {
		return NULL;
	}

	Nod* temp = cap;
	do {
		if (strcmp(temp->info.oras_plecare, oras_pelcare) == 0) {
			(*dimensiuneVector)++;
		}
		temp = temp->next;
	} while (temp != cap);

	int* vector = (int*)malloc((*dimensiuneVector) * sizeof(int));
	int i = 0;

	do {
		if (strcmp(temp->info.oras_plecare, oras_pelcare) == 0) {
			vector[i] = temp->info.cod_rezervare;
			i++;
		}
		temp = temp->next;
	} while (temp != cap);
	for (int j = 0; j < i; j++) {
		printf("%d, ", vector[j]);
	}
	return vector;
}

void scriereInFisier(Nod* cap) {
	FILE* f = fopen("RezervariScrise.txt", "w");
	if (!f) {
		return NULL;
	}

	Nod* temp = cap;
	do {
		fprintf(f, "%d, %s, %s, %s, %d\n\n", temp->info.cod_rezervare, temp->info.oras_plecare, temp->info.destinatie, temp->info.data_plecare, temp->info.nr_turisti);
		temp = temp->next;
	} while (temp != cap);

	fclose(f);
}

int main() {
	Nod* cap = NULL;
	FILE* f = fopen("Rezervari.txt", "r");
	if (!f) {
		return NULL;
	}
	Rezervare r = { 0 ,NULL, NULL, NULL, 0 };
	char buffer[100];

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

		cap = inserare(cap, r);
	}
	fclose(f);

	printf("S a citit tot\n");
	afisare(cap);

	Rezervare dubaiana = cautare(cap, "Dubai");
	printf("\nRezervare gasita: %d %s %s %s %d\n", dubaiana.cod_rezervare, dubaiana.destinatie, dubaiana.oras_plecare, dubaiana.data_plecare, dubaiana.nr_turisti);


	Rezervare actualizata;
	actualizare(cap, 102, "01-01-1000");
	printf("\nRezervare actualizata\n\n");
	afisare(cap);
	cap = stergere(cap);
	printf("\n\n\n");
	afisare(cap);

	printf("\n\n");
	int dim = 0;
	int* vector = transformareInVector(cap, "Craiova", &dim);

	scriereInFisier(cap);

	return 0;
}

//To do: matrice, sau vector in structura initiala, char, float, deep clone, inversare noduri