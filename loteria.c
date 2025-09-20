 #include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct elemento {

    char codigo[33];
    int32_t numCer;

} elemento;

typedef struct no {
    int32_t num;
    struct no *esq;
    struct no *dir;
} no;

void liberarArvore(no* raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}


no* montarArv(no *raiz, int32_t num) {
    if(raiz == NULL) {
        no *novo = (no*) malloc(sizeof(no));
        novo->num = num;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    } else {
        if(num <= raiz->num) {
            raiz->esq = montarArv(raiz->esq,num);
        } else {
            raiz->dir = montarArv(raiz->dir,num);
        }
        return raiz;
    }
}

int32_t numCert(no *raiz, int32_t *numSort) {
    int32_t cont = 0;
    for(int32_t i = 0; i < 10; i++) {
        no *raiz_temp = raiz; 
        while(raiz_temp != NULL) {
            if(numSort[i] < raiz_temp->num) {
                raiz_temp = raiz_temp->esq;
            } else if(numSort[i] > raiz_temp->num) {
                raiz_temp = raiz_temp->dir;
            } else {
                cont++;
                break;
            }
        }
    }
    return cont;
}

int32_t esquerdo(int32_t i) {
    return (2 * i) + 1;
}

int32_t direito(int32_t i) {
    return (2 * i) + 2;
}


void trocar(elemento* V, int32_t P, int32_t i) {
    elemento aux; 
    
    aux = V[i];
    V[i] = V[P];
    V[P] = aux;
}


void heapifyMax(elemento* V, int32_t T, int32_t i) {
    int32_t P = i, E = esquerdo(i), D = direito(i);
    
   
    if(E < T && V[E].numCer > V[P].numCer){
        P = E;
    }
    
    if(D < T && V[D].numCer > V[P].numCer){
        P = D; 
    }

    if(P != i) {
        trocar(V, P, i);
        heapifyMax(V, T, P);
    }
}


void heapifyMin(elemento* V, int32_t T, int32_t i) {
    int32_t P = i, E = esquerdo(i), D = direito(i);
    
    if(E < T && V[E].numCer < V[P].numCer){
        P = E;
    }
    
    if(D < T && V[D].numCer < V[P].numCer){
        P = D; 
    }

    if(P != i) {
        trocar(V, P, i); 
        heapifyMin(V, T, P);
    }
}


int32_t maiorAcertoMax(elemento *heap, int32_t numApos) {

    int32_t cont = 1;
    int32_t i = 1;
    int32_t numMaior = heap[0].numCer;
	
    while(i < numApos) {
        if(heap[i].numCer == numMaior) {
            cont++;
			
        } 
        i++;
    }
    return cont;
}

int32_t maiorAcertoMin(elemento *heap, int32_t numApos) {

    int32_t cont = 1;
    int32_t i = 1;
    int32_t numMaior = heap[0].numCer;
	
    while(i < numApos) {
        if(heap[i].numCer == numMaior) {
            cont++;
			
        } 
        i++;
    }
    return cont;
}

void extrairIndiceMax(int32_t numApos, elemento *heapMax) {

    int32_t indice_inicial = ((numApos-1)-1/2);
    for(int32_t i = indice_inicial; i >= 0; i--) {

        heapifyMax(heapMax, numApos, i);

    }

}

void extrairIndiceMin(int32_t numApos, elemento *heapMin) {

    int32_t indice_inicial = ((numApos-1)-1/2);
    for(int32_t i = indice_inicial; i >= 0; i--) {

        heapifyMin(heapMin, numApos, i);

    }

}

void imprimir(int32_t totMaior, int32_t totMenor, int32_t premio1, int32_t premio2, FILE *output, elemento *heapMax, elemento *heapMin, int32_t numApos) {
    int32_t premioInd1 = premio1 / totMaior;
    int32_t premioInd2 = premio2 / totMenor;
    int32_t ultimoMax = numApos - 1;
    int32_t ultimoMin = numApos - 1;
	
    fprintf(output,"[%d:%d:%d]\n", totMaior, heapMax[0].numCer, premioInd1);
    for(int32_t i = 0; i < totMaior; i++) {
		extrairIndiceMax(numApos,heapMax);
        fprintf(output,"%s\n", heapMax[0].codigo);
        heapMax[0] = heapMax[ultimoMax];
        ultimoMax--;
      
    }

    fprintf(output,"[%d:%d:%d]\n", totMenor, heapMin[0].numCer, premioInd2);
    for(int32_t i = 0; i < totMenor; i++) {
		extrairIndiceMin(numApos,heapMin);
        fprintf(output,"%s\n", heapMin[0].codigo);
        heapMin[0] = heapMin[ultimoMin];
        ultimoMin--;
    }
}



int main(int argc, char* argv[]) {
   	
	printf("Quantidade de argumentos (argc): %i\n", argc);

    for (int i = 0; i < argc; i++)
    {
        printf("Argumento %i (argv[%i]): %s\n", i, i, argv[i]);
    }

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

  
    int32_t premio;
    int32_t numApos;
    int32_t numSort[10];

    fscanf(input, "%d", &premio);
    fscanf(input, "%d", &numApos);
    for(int32_t i = 0; i < 10; i++) {
        fscanf(input, "%d", &numSort[i]);
    }
    
    no **raizes = (no**) malloc(sizeof(no*) * numApos);     //Criando vetor que aponta para cada árvore binária da aposta
    char **codigos = (char**) malloc(sizeof(char*) * numApos);
    for(int32_t i = 0; i < numApos; i++) {
        codigos[i] = (char*) malloc(sizeof(char) * 33);
        raizes[i] = NULL;
    }

    for(int32_t i = 0; i < numApos; i++) {
        int32_t numList[15];
        fscanf(input, "%s", codigos[i]);
        for(int32_t j = 0; j < 15; j++) {
            fscanf(input, "%d", &numList[j]);
        }
        
        raizes[i] = montarArv(raizes[i], numList[7]);   //Raiz da árvore sendo o número do meio
        for(int32_t j = 0; j < 15; j++) {
            if(j != 7) {
                raizes[i] = montarArv(raizes[i], numList[j]);   //Criando árvore binária 
            }
        }
    }

    elemento *heapMax = (elemento*) malloc(sizeof(elemento) * numApos); //Criando um vetor para o heap máximo
    elemento *heapMin = (elemento*) malloc(sizeof(elemento) * numApos); //Criando um vetor para o heap mínimo

    for(int32_t i = 0; i < numApos; i++) {
        int32_t acertos = numCert(raizes[i], numSort);

        strcpy(heapMax[i].codigo, codigos[i]);
        heapMax[i].numCer = acertos;

        strcpy(heapMin[i].codigo, codigos[i]);
        heapMin[i].numCer = acertos;
    }

    extrairIndiceMax(numApos,heapMax);
    extrairIndiceMin(numApos,heapMin);

    int32_t premio1 = premio / 2;
    int32_t premio2 = premio / 2;
    
    int32_t totMaior = maiorAcertoMax(heapMax,numApos);
    int32_t totMenor = maiorAcertoMin(heapMin,numApos); 
    
    imprimir(totMaior, totMenor, premio1, premio2, output, heapMax, heapMin,numApos);

	
    fclose(input);
    fclose(output);
  

    

    return 0;
}  