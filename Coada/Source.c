#include<stdio.h>
#include<malloc.h>

struct Oras
{
	char* denumire;
	int nrLocuitori;
	float suprafata;
};

struct Nod
{
	struct Oras info;
	struct Nod* next;
};

// inserare element in coada
void put(struct Nod** prim, struct Nod** ultim, struct Oras o)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->info.denumire = (char*)malloc((strlen(o.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, o.denumire);

	nou->info.nrLocuitori = o.nrLocuitori;
	nou->info.suprafata = o.suprafata;

	nou->next = NULL;
	
	if (*prim == NULL && *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

// extragere element din coada
int get(struct Nod** prim, struct Nod** ultim, struct Oras* o)
{
	if (*prim != NULL && *ultim != NULL)
	{
		(*o).denumire = (char*)malloc((strlen((*prim)->info.denumire) + 1) * sizeof(char));
		strcpy((*o).denumire, (*prim)->info.denumire);

		(*o).nrLocuitori = (*prim)->info.nrLocuitori;
		(*o).suprafata = (*prim)->info.suprafata;

		struct Nod* aux = *prim;
		*prim = (*prim)->next;

		free(aux->info.denumire);
		free(aux);

		return 0;
	}
	else
	{
		if (*prim == NULL)
		{
			*ultim = NULL;
			return -1;
		}
	}
}

// afisare coada
void afisare(struct Nod* prim)
{
	struct Nod* aux = prim;
	while (aux != NULL)
	{
		printf("Denumire oras: %s, nr locuitori: %d, suprafata: %5.2f\n",
			aux->info.denumire, aux->info.nrLocuitori, aux->info.suprafata);
		aux = aux->next;
	}
}

void main()
{
	int nr;
	struct Nod* prim = NULL;
	struct Nod* ultim = NULL;
	struct Oras o;
	char buffer[20];

	FILE* f = fopen("oras.txt", "r");
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%s", buffer);
		o.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(o.denumire, buffer);

		fscanf(f, "%d", &o.nrLocuitori);
		fscanf(f, "%f", &o.suprafata);

		put(&prim, &ultim, o);
		free(o.denumire);
	}
	fclose(f);

	afisare(prim);

	// eliminare element dupa denumire
	get(&prim, &ultim, &o);
	printf("\n A fost sters orasul cu denumirea: %s \n", o.denumire);
	free(o.denumire);
	afisare(prim);
}