#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Task {
	unsigned int id;
	char* date;
	char* name;
	float completion;
} Task;

typedef struct Nod {
	Task* info;
	struct Nod* next;
} Nod;

typedef struct Hash {
	Nod** info;
	int dimensiune;
} Hash;

Task* creeazaTask(unsigned int id, char* date, char* name, float comple) {
	Task* nou = (Task*)malloc(sizeof(Task));
	nou->id = id;
	nou->date = (char*)malloc(strlen(date) + 1);
	nou->name = (char*)malloc(strlen(name) + 1);
	nou->completion = comple;
	strcpy(nou->date, date);
	strcpy(nou->name, name);
	return nou;
}

int functieHash(const char* cheie, int dimensiune) {
	return strlen(cheie) % dimensiune;
}

void inserareHash(Hash ht, Task* t) {
	if (ht.info != NULL) {
		int pozitie = functieHash(t->name, ht.dimensiune);
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = t;
		nou->next = ht.info[pozitie];
		ht.info[pozitie] = nou;
	}
}


int main() {
Hash h;
h.dimensiune = 7;
h.info = (Nod**)malloc(sizeof(Nod*) * h.dimensiune);
for (int i = 0; i < h.dimensiune; i++) {
	h.info = (Nod**)malloc(sizeof(Nod*) * h.dimensiune);
	for (int i = 0; i < h.dimensiune; i++) {
		h.info[i] = NULL;
	}

	FILE* f = fopen("tasks.txt", "r");
	if (!f) {
		printf("Nu s-a putut deschide fisierul tasks.txt!\n");
		return -1;
	}

	unsigned int id;
	char b_date[100], b_name[100];
	float completion;

	while (fscanf(f, "%u %s %s %f", &id, b_date, b_name, &completion) == 4) {
		Task* t = creeazaTask(id, b_date, b_name, completion);
		inserareHash(h, t);
	}

	fclose(f);

	printf("Tabela Hash dupa citirea din fisier:\n");
	afisareHash(h);

	dezalocareHash(&h);
	printf("\nMemorie eliberata. Succes!\n");

	return 0;
