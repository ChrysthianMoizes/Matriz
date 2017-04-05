#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

void iniciarString(char* text) {
	text[0] = '\0';	
}

struct HomesDoCeu
{
	char nome[30];
	float capVoo;
	float peso;
	float altura;				
	float forca;					
};
struct viventesSup
{
	char nome[30];
	float forca;	
};
struct subTerra
{
	char nome[30];
	float densidade;
	float visao;
	float forca;
};
struct cidade
{
	char nome[30];
	int n;
	int c;
	float focaT;
	void *ponteiro;
	HomesDoCeu *hc;
	viventesSup *vs;
	subTerra *sb;	
	char classe[30];
};


cidade *lerCeu(int *nTotalC) {
	int nCidade,i,k,np;
	float soma;
	cidade *city;
	float capVoo, peso, altura;
	char *nomeC = (char*)malloc(30 * sizeof(char));	
	iniciarString(nomeC);
	char *nomeP = (char*)malloc(30 * sizeof(char));	
	iniciarString(nomeP);
	FILE *fp = fopen("Ceu.txt","r");
	if (!fp) {
		printf("\n Erro na abertura do arquivo Ceu.txt \n");
	}
	else {
		fscanf(fp, "%d", &nCidade);
		city = (cidade*)malloc(nCidade*sizeof(cidade));			
		for (i = 0; i < nCidade; i++){						
			fscanf(fp, "%s %d ", nomeC, &np);		
			strcpy(city[i].nome, nomeC);
			city[i].n = np;
			nTotalC = nTotalC + np;
			city[i].c = nCidade;		
			city[i].hc = (HomesDoCeu*)malloc(np*sizeof(HomesDoCeu));
			city[i].focaT = 0;			
			for (k = 0; k < np; k++) {				
				fscanf(fp, "%s %f %f %f ", nomeP, &capVoo, &peso, &altura);
				strcpy(city[i].hc[k].nome, nomeP);
				city[i].hc[k].capVoo = capVoo;
				city[i].hc[k].peso = peso;
				city[i].hc[k].altura = altura;
				city[i].hc[k].forca = capVoo * peso * altura;
				city[i].focaT = city[i].focaT + (capVoo * peso * altura);				
				strcpy(city[i].classe, "Homens Do Ceu");
			
			}	
		}		
	}
	
	free(nomeC);
	free(nomeP);
	return city;
}

cidade *lerViventes(int *nTotalV) {
	int nCidade,i,k,np;	
	float forca = 0;
	cidade *cityV;
	char *nomeC = (char*)malloc(30 * sizeof(char));	
	iniciarString(nomeC);
	char *nomeP = (char*)malloc(30 * sizeof(char));	
	iniciarString(nomeP);
	FILE *fp = fopen("Viventes.txt","r");
	if (!fp) {
		printf(" \n Erro na abertura do arquivo Viventes.txt \n");
	}
	else {
		fscanf(fp, "%d", &nCidade);
		cityV = (cidade*)malloc(nCidade*sizeof(cidade));			
		for (i = 0; i < nCidade; i++){						
			fscanf(fp, "%s %d ", nomeC, &np);		
			strcpy(cityV[i].nome, nomeC);
			cityV[i].n = np;
			nTotalV = nTotalV + np;
			cityV[i].c = nCidade;		
			cityV[i].vs = (viventesSup*)malloc(np*sizeof(viventesSup));
			cityV[i].focaT = 0;			
			for (k = 0; k < np; k++) {				
				fscanf(fp, "%s %f", nomeP, &forca);
				strcpy(cityV[i].vs[k].nome, nomeP);
				cityV[i].vs[k].forca = forca;
				cityV[i].focaT = cityV[i].focaT + forca;				
				strcpy(cityV[i].classe, "Viventes da Superficie");
			}		
		}
	}
	free(nomeC);
	free(nomeP);
	
	return cityV;
}

cidade *lerSubTerra(int *nTotalST) {
	int nCidade,i,k,np;
	cidade *cityST;
	float densidade, visao, forca;
	char *nomeC = (char*)malloc(30 * sizeof(char));	
	iniciarString(nomeC);
	char *nomeP = (char*)malloc(30 * sizeof(char));	
	iniciarString(nomeP);
	FILE *fp = fopen("Sub.txt","r");
	if (!fp) {
		printf("\n Erro na abertura do arquivo Sub.txt \n");
	}
	else {
		fscanf(fp, "%d", &nCidade);
		cityST = (cidade*)malloc(nCidade*sizeof(cidade));		
		for (i = 0; i < nCidade; i++){						
			fscanf(fp, "%s %d ", nomeC, &np);		
			strcpy(cityST[i].nome, nomeC);
			cityST[i].n = np;
			nTotalST = nTotalST + np;
			cityST[i].c = nCidade;					
			cityST[i].sb = (subTerra*)malloc(np*sizeof(subTerra));
			cityST[i].focaT = 0;			
			for (k = 0; k < np; k++) {				
				fscanf(fp, "%s %f %f %f ", nomeP, &densidade, &visao, &forca);
				strcpy(cityST[i].sb[k].nome, nomeP);
				cityST[i].sb[k].densidade = densidade;
				cityST[i].sb[k].visao = visao;
				cityST[i].sb[k].forca = (float)pow(2,(double)densidade - visao);				
				cityST[i].focaT = cityST[i].focaT + (float)pow(2, (double)densidade - visao);
				strcpy(cityST[i].classe, "Sub Terras");
			}			
		}
	}
	
	free(nomeC);
	free(nomeP);
	return cityST;
}

void exibirForcas(cidade *citC,cidade *citV, cidade *citST) {
	printf(" \n\n \t Cidades da Classe Homens Do Ceu \n");
	for (int i = 0; i < citC[0].c; i++) {
		printf("\nCidade: %s \n", citC[i].nome);
		printf("Forca total: %.2f \n", citC[i].focaT);
	}
	printf("\n\n \t Cidades da Classe Viventes da Superficie \n");
	for (int i = 0; i < citV[0].c; i++) {
		printf("\nCidade: %s \n", citV[i].nome);
		printf("Forca total: %.2f \n", citV[i].focaT);
	}
	printf("\n\n \t Cidades da Classe Sub Terras \n");
	for (int i = 0; i < citST[0].c; i++) {
		printf("\nCidade: %s \n", citST[i].nome);
		printf("Forca total: %.2f \n", citST[i].focaT);
	}
}

void forcaA(cidade *citC, cidade *citV, cidade *citST) {
	float soma = 0;
	int somaA = 0;
	for (int i = 0; i < citC[0].c; i++) {
		for (int k = 0; k < citC[i].n; k++) {
			int tam = strlen(citC[i].hc[k].nome);
			somaA = 0;
			for (int j = 0; j < tam; j++) {
				if (citC[i].hc[k].nome[j] == 'a')
					if (somaA < 2)
						somaA = somaA + 1;
					else {
						soma = soma + citC[i].hc[k].forca;
					}
			}
		}
	}
	for (int i = 0; i < citV[0].c; i++) {
		for (int k = 0; k < citV[i].n; k++) {
			int tam = strlen(citV[i].vs[k].nome);
			somaA = 0;
			for (int j = 0; j < tam; j++) {
				if (citV[i].vs[k].nome[j] == 'a')
					if (somaA < 2)
						somaA = somaA + 1;
					else {
						soma = soma + citV[i].vs[k].forca;
					}
			}
		}
	}
	for (int i = 0; i < citST[0].c; i++) {
		for (int k = 0; k < citST[i].n; k++) {
			int tam = strlen(citST[i].sb[k].nome);
			somaA = 0;
			for (int j = 0; j < tam; j++) {
				if (citST[i].sb[k].nome[j] == 'a')
					if (somaA < 2)
						somaA = somaA + 1;
					else {
						soma = soma + citST[i].sb[k].forca;
					}
			}
		}
	}
	printf("\n A soma das forcas de todos os individuos com duas letras 'a' no nome: %.2f", soma);
}

void medirForcas(cidade *citC, cidade *citV, cidade *citST, int nPersonagensTotal) {
	float *maiorF = (float*)malloc(nPersonagensTotal*sizeof(float)); 
	maiorF[0] = citC[0].hc[0].forca;
	float *menorF = (float*)malloc(nPersonagensTotal*sizeof(float));
	menorF[0] = citC[0].hc[0].forca;
	int jMaior = 0, jMenor = 0;

	for (int i = 0; i < citC[0].c; i++) {
		for (int k = 0; k < citC[i].n; k++) {			
			if (citC[i].hc[k].forca > maiorF[jMaior]) {
				maiorF[jMaior] = citC[i].hc[k].forca;				
			}
			else if (citC[i].hc[k].forca == maiorF[jMaior]) {
				maiorF[jMaior + 1] = citC[i].hc[k].forca;
				jMaior++;
			}
		}
	}
	for (int i = 0; i < citC[0].c; i++) {
		for (int k = 0; k < citC[i].n; k++) {
			if (citC[i].hc[k].forca < menorF[jMenor]) {
				menorF[jMenor] = citC[i].hc[k].forca;
			}
			else if (citC[i].hc[k].forca == menorF[jMenor]) {
				menorF[jMenor + 1] = citC[i].hc[k].forca;
				jMenor++;
			}
		}
	}
	
	free(maiorF);
	free(menorF);
}


void insertionSort(cidade *city, cidade *cityV, cidade *cityST){
	
	float forcaC = 0;
	float forcaV = 0;
	float forcaST = 0;
	
	for (int i = 0; i < city[0].c; i++) {
		
		for (int k = 0; k < city[i].n; k++) {	
				
			forcaC = forcaC + city[i].hc[k].forca;
		}
	}
	
	for (int i = 0; i < cityV[0].c; i++) {
		
		for (int k = 0; k < cityV[i].n; k++) {	
				
			forcaV = forcaV + cityV[i].vs[k].forca;
		}
	}
	
	for (int i = 0; i < cityST[0].c; i++) {
		
		for (int k = 0; k < cityST[i].n; k++) {	
				
			forcaST = forcaST + cityST[i].sb[k].forca;
		}
	}
	
	printf("\n\n \t A ordenacao dos povos por forca eh:");
	
	if (forcaC > forcaV){
		
		if (forcaV > forcaST){
			printf("\n\n %s, %s, %s.", city[0].classe, cityV[0].classe, cityST[0].classe);
			
		} else{
			printf("\n\n %s, %s, %s.", city[0].classe, cityST[0].classe, cityV[0].classe);
		}
	} 
	
	if (forcaV > forcaC){
		
		if (forcaC > forcaST){
			printf("\n\n %s, %s, %s.", cityV[0].classe, city[0].classe, cityST[0].classe);
			
		} else{
			printf("\n\n %s, %s, %s.", cityV[0].classe, cityST[0].classe, city[0].classe);
		}
	}
	
	if (forcaST > forcaC){
		
		if (forcaC > forcaV){
			printf("\n\n %s, %s, %s.", cityST[0].classe, city[0].classe, cityV[0].classe);
			
		} else{
			printf("\n\n %s, %s, %s.", cityST[0].classe, cityV[0].classe, city[0].classe);
		}
	}
	
}

int main() {
	int totalC, totalV, totalST, nPersonagensTotal;

	cidade *citysCeu = lerCeu(&totalC);
	cidade *citysV = lerViventes(&totalV);
	cidade *citysST = lerSubTerra(&totalST);

	nPersonagensTotal = totalC + totalV + totalST;

	exibirForcas(citysCeu, citysV, citysST);
	forcaA(citysCeu, citysV, citysST);
	
	insertionSort(citysCeu, citysV, citysST);

	getchar();
	return 0;
}
