#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

/* Arbore AVL: 10 20 30 40 50 -> pentru testare */

struct arbore
{
	int cheie;
	struct arbore* stanga;
	struct arbore* dreapta;
	int inaltime;
};

int inaltime(struct arbore* N)
{
	if (N == NULL)
	{
		return 0;
	}
	return N->inaltime;
}

int maxim(int a, int b)
{
	return (a > b) ? a : b;
}

struct arbore* rotatie_dreapta(struct arbore* y)
{
	struct arbore* x = y->stanga;
	struct arbore* T2 = x->dreapta;
	x->dreapta = y;
	y->stanga = T2;
	y->inaltime = maxim(inaltime(y->stanga), inaltime(y->dreapta)) + 1;
	x->inaltime = maxim(inaltime(x->stanga), inaltime(x->dreapta)) + 1;
	return x;
}

struct arbore* rotatie_stanga(struct arbore* x)
{
	struct arbore* y = x->dreapta;
	struct arbore* T2 = y->stanga;
	y->stanga = x;
	x->dreapta = T2;
	x->inaltime = maxim(inaltime(x->stanga), inaltime(x->dreapta)) + 1;
	y->inaltime = maxim(inaltime(y->stanga), inaltime(y->dreapta)) + 1;
	return y;
}

int echilibrare(struct arbore* N)
{
	if (N == NULL)
	{
		return 0;
	}
	return inaltime(N->stanga) - inaltime(N->dreapta);
}

struct arbore* initializare(int cheie)
{
	struct arbore* nod = malloc(sizeof(struct arbore));
	nod->cheie = cheie;
	nod->stanga = NULL;
	nod->dreapta = NULL;
	nod->inaltime = 1;
	return(nod);
}

struct arbore* insereaza(struct arbore* nod, int cheie)
{
	if (nod == NULL)
		return(initializare(cheie));

	if (cheie < nod->cheie)
		nod->stanga = insereaza(nod->stanga, cheie);
	else if (cheie > nod->cheie)
		nod->dreapta = insereaza(nod->dreapta, cheie);
	else
		return nod;
	nod->inaltime = 1 + maxim(inaltime(nod->stanga), inaltime(nod->dreapta));
	int echilibrat = echilibrare(nod);
	if (echilibrat > 1 && cheie < nod->stanga->cheie)
	{
		return rotatie_dreapta(nod);
	}
	if (echilibrat < -1 && cheie>nod->dreapta->cheie)
	{
		return rotatie_stanga(nod);
	}
	if (echilibrat > 1 && cheie > nod->stanga->cheie)
	{
		nod->stanga = rotatie_stanga(nod->stanga);
		return rotatie_dreapta(nod);
	}
	if (echilibrat < -1 && cheie < nod->dreapta->cheie)
	{
		nod->dreapta = rotatie_dreapta(nod->dreapta);
		return rotatie_stanga(nod);
	}
	return nod;
}

void preordine(struct arbore* r)
{
	if (r != NULL)
	{
		printf("%d, ", r->cheie);
		preordine(r->stanga);
		preordine(r->dreapta);
	}
}

void inordine(struct arbore* r)
{
	if (r != NULL)
	{
		inordine(r->stanga);
		printf("%d, ", r->cheie);
		inordine(r->dreapta);
	}
}

void postordine(struct arbore* r)
{
	if (r != NULL)
	{
		postordine(r->stanga);
		postordine(r->dreapta);
		printf("%d, ", r->cheie);
	}
}

struct arbore* stergereNod(struct arbore* r, int cheie)
{
	if (r == NULL)
	{
		return r;
	}

	if (r->cheie > cheie)
	{
		r->stanga = stergereNod(r->stanga, cheie);
		return r;
	}
	else if (r->cheie < cheie)
	{
		r->dreapta = stergereNod(r->dreapta, cheie);
		return r;
	}

	if (r->stanga == NULL)
	{
		struct arbore* temporar = r->dreapta;
		free(r);
		return temporar;
	}
	else if (r->dreapta == NULL)
	{
		struct arbore* temporar = r->stanga;
		free(r);
		return temporar;
	}
	else
	{
		struct arbore* succesorParinte = r;
		struct arbore* succesor = r->dreapta;
		while (succesor->stanga != NULL)
		{
			succesorParinte = succesor;
			succesor = succesor->stanga;
		}

		if (succesorParinte != r)
		{
			succesorParinte->stanga = succesor->dreapta;
		}
		else
		{
			succesorParinte->dreapta = succesor->dreapta;
		}
		r->cheie = succesor->cheie;
		free(succesor);
		return r;
	}
}

int main()
{
	system("color 3");
	struct arbore* arbore = NULL;
	int opt,nod,nod_sters;
	do {
		printf("	0.Iesire.\n");
		printf("	1.Insereaza nod.\n");
		printf("	2.Preordine.\n");
		printf("	3.Inordine.\n");
		printf("	4.Postordine.\n");
		printf("	5.Echilibrat AVL?\n");
		printf("	6.Sterge nod.\n");
		printf("Dati optiunea: "); scanf("%d", &opt);
		switch (opt)
		{
		case 0:break;
		case 1:printf("\nDati nod: "); scanf("%d", &nod);
			arbore = insereaza(arbore, nod);
			printf("Nod inserat cu succes.\n\n");
			break;
		case 2:printf("\nPreordine:  ");
			preordine(arbore);
			printf("\n\n");
			break;
		case 3:printf("\nInordine: ");
			inordine(arbore);
			printf("\n\n");
			break;
		case 4:printf("\nPostordine: ");
			postordine(arbore);
			printf("\n\n");
			break;
		case 5:if (echilibrare(arbore) > -1 || echilibrare(arbore) > 1)
		{
			printf("\nDezechilibrat.\n\n");
		}
			  else
		{
			printf("\nEchilibrat in sens AVL.\n\n");
		}
			break;
		case 6:printf("\nDati nod: "); scanf("%d", &nod_sters);
			arbore = stergereNod(arbore, nod_sters);
			printf("Nod sters cu succes.\n\n");
			break;
		default:printf("Optiune gresita!\n");
			break;
		}
	} while (opt!=0);
	system("pause");
	return 0;
}