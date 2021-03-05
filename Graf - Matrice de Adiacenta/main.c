#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define N 100

int contor = 0;
int contorMatrice = 0;
int noduri[N]; //noduri
int matadj[N][N]; //arce

/* graf neponderat, neorientat */

void InitGraf(void);
int GrafVid(void);
int GrafPlin(void);
int CheieElemGraf(int x);
void InserNod(int key);
void InserArc(int keyA, int keyB);
int IndicaArc(int keyA, int keyB);
int ArcVid(int arc);
void SuprimArc(int indArc, int keyA, int keyB);

void _afisareMeniu(void);

int main(void) {
	system("COLOR 3");
	int select;

	while (1) {
		printf("\nAfisare meniu:\n");
		_afisareMeniu();

		printf("Selectati optiunea din meniu: ");
		scanf("%d", &select);
		printf("\n");
		switch (select) {
		case 0: return 0; break;
		case 1: InitGraf();
			printf("Graful a fost initializat.\n");
			break;
		case 2:
		{
			if (GrafVid()) printf("Graful este vid\n");
			else printf("Graful nu este vid\n");
		}
		break;
		case 3:
		{
			if (GrafPlin()) printf("Graful este plin\n");
			else printf("Graful nu este plin\n");
		}
		break;
		case 4: {
			printf("Introduceti cheia: ");
			int x;
			scanf("%d", &x);
			x = CheieElemGraf(x);
			if (x < 0) printf("\nNu am gasit cheia cautata.\n");
			else printf("\nCheia se afla in graf.\n");
		}
			  break;
		case 5: {
			printf("Introduceti cheia nodului de inserat: ");
			int x;
			scanf("%d", &x);
			InserNod(x);
			printf("S-a introdus nodul %d\n", x);
		}
			  break;
		case 6: {
			printf("Introduceti cheia nodului A: ");
			int keyA, keyB;
			scanf("%d", &keyA);
			printf("Introduceti cheia nodului B: ");
			scanf("%d", &keyB);
			InserArc(keyA, keyB);
			printf("Arc inserat.\n");
		}
			  break;
		case 7: {
			printf("Introduceti cheia nodului A: ");
			int keyA, keyB;
			scanf("%d", &keyA);
			printf("Introduceti cheia nodului B: ");
			scanf("%d", &keyB);
			int arc;
			arc = IndicaArc(keyA, keyB);
			printf("Arcul indicat este %d\n", arc);
		}
			  break;
		case 8: {printf("Introduceti cheia nodului: ");
			int iN;
			scanf("%d", &iN);
			iN = IndicaNod(iN);
			printf("Nodul este %d.\n", iN);
		}
			  break;
		case 9: {printf("Introduceti cheia nodului A: ");
			int keyA, keyB;
			scanf("%d", &keyA);
			printf("Introduceti cheia nodului B: ");
			scanf("%d", &keyB);
			int arc;
			arc = IndicaArc(keyA, keyB);
			arc = ArcVid(arc);
			if (arc) printf("\nArcul este vid.\n");
			else { printf("\nArcul nu este vid.\n"); }
		}
			  break;
		case 10: {
			printf("Introduceti cheia nodului: ");
			int key;
			scanf("%d", &key);
			int aux;
			aux = FurnNod(key);
			if (aux == -1) printf("\nNu se gaseste nodul.\n");
			else printf("\nCheia nodului este %d.\n", aux);
		}
			   break;
		case 11: {
			printf("Introduceti cheia nodului: ");
			int key;
			scanf("%d", &key);
			key = IndicaNod(key);
			printf("Introduceti noua cheie: ");
			int x;
			scanf("%d", &x);
			noduri[key] = x;
		}
			   break;
		case 12: {
			printf("Introduceti cheia nodului A: ");
			int keyA, keyB;
			scanf("%d", &keyA);
			printf("\nIntroduceti cheia nodului B: ");
			scanf("%d", &keyB);
			int arc;
			arc = IndicaArc(keyA, keyB);
			SuprimArc(arc, keyA, keyB);
		}
			   break;
		case 20: {
			printf("\n\n");
			printf("      ");
			int i, j;
			for (i = 0; i < contor; i++) printf(" %3d |", noduri[i]);
			printf("\n-------------------------------\n");
			for (i = 0; i < contor; i++) {
				printf(" %3d |", noduri[i]);
				for (j = 0; j < contor; j++) {
					printf(" %3d |", matadj[i][j]);
				}
				printf("\n");
			}
			printf("\ncontor = %d\n", contor);
			printf("contorMatrice = %d\n", contorMatrice);
		}
			   break;
		default: printf("Optiune gresita.\n");
			break;

		}
	}
	system("pause");
	return 0;
}

void _afisareMeniu(void) {
	printf("    0. Iesire din program\n");
	printf("    1. Initializare Graf\n");
	printf("    2. Graf Vid?\n");
	printf("    3. Graf Plin?\n");
	printf("    4. Cauta Cheie Graf\n");
	printf("    5. Insereaza Nod\n");
	printf("    6. Insereaza Arc\n");
	printf("    7. Indica Arc\n");
	printf("    8. Indica Nod\n");
	printf("    9. Arc Vid?\n");
	printf("    10. Furnizeaza Nod\n");
	printf("    11. Actualizeaza Nod\n");
	printf("    12. Suprima Arc\n");
	printf("    20. Afisare de Depanare\n");
}

void InitGraf(void) {
	int i, j;

	for (i = 0; i < N; i++) noduri[i] = -1;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) matadj[i][j] = -1;
	}
	contor = 0;
	contorMatrice = 0;
}

int GrafVid(void) {
	if (contor == 0) return 1; 
	else return 0; 
}

int GrafPlin(void) {
	if (contor == N) return 1; 

	if (contorMatrice == N * N) return 1; 

	return 0; 
}

int CheieElemGraf(int x) {
	if ((x < 0) || (x > N)) return -1;
	int i;

	for (i = 0; i < contor; i++) {
		if (noduri[i] == x) return 1;
	}
	return -1;
}

void InserNod(int key) {
	if (GrafPlin()) {
		printf("Graful este plin. Nu pot insera nodul cu cheia %d\n", key);
		return;
	}

	noduri[contor] = key;
	contor++;
}

void InserArc(int keyA, int keyB) {
	if (GrafPlin()) {
		printf("Graful este plin. Nu pot insera arce in matadj[]. \n");
		return;
	}
	int indexA = -1, indexB = -1;
	int i;

	for (i = 0; i < contor; i++) {
		if (noduri[i] == keyA) { indexA = i; break; }
	}

	for (i = 0; i < contor; i++) {
		if (noduri[i] == keyB) { indexB = i; break; }
	}

	if ((indexA < 0) || (indexB < 0) || (indexA > N) || (indexB > N)) {
		printf("Nu pot insera arc intre cheile solicitate.\n");
		return;
	}

	if (matadj[indexA][indexB] == 1) {
		printf("Arcul de introdus este deja prezent in graf!\n");
		return;
	}

	matadj[indexA][indexB] = 1;
	matadj[indexB][indexA] = 1;
	contorMatrice += 2;
}

int CautaCheieGraf(int key) {
	int i;
	for (i = 0; i < contor; i++) {
		if (noduri[i] == key) return 1;
	}
	return 0; 
}

int IndicaNod(int key)
{
	int i;
	for (i = 0; i < contor; i++) {
		if (noduri[i] == key) return i; 
	}
	return -1;
}

int IndicaArc(int keyA, int keyB) 
{
	int i;
	int indexA = -1, indexB = -1;
	for (i = 0; i < contor; i++) {
		if (noduri[i] == keyA) { indexA = i; break; }
	}

	for (i = 0; i < contor; i++) {
		if (noduri[i] == keyB) { indexB = i; break; }
	}

	if ((indexA < 0) || (indexB < 0)) { printf("Nu gasesc arcul cerut\n"); return -1; }

	if ((matadj[indexA][indexB] == 1) && (matadj[indexB][indexA] == 1)) return (indexA * contor + indexB);

	return -1; 
}

int ArcVid(int arc) {
	int* a;
	a = &matadj;

	if (a[arc] == 0) return 1; 
	else return 0; 
}

void SuprimArc(int indArc, int keyA, int keyB)
{
	if (indArc < 0)
	{
		printf("\nArcul nu exista.\n");
	}
	else if (indArc >= 0)
	{
		int i;
		int indexA = -1, indexB = -1;
		for (i = 0; i < contor; i++) {
			if (noduri[i] == keyA) { indexA = i; break; }
		}

		for (i = 0; i < contor; i++) {
			if (noduri[i] == keyB) { indexB = i; break; }
		}
		matadj[indexA][indexB] = -1;
		matadj[indexB][indexA] = -1;
		contorMatrice -= 2;
	}
}

int FurnNod(int keyX)
{
	int x;
	x = IndicaNod(keyX);
	if (x == -1) return -1;
	else return keyX;
}