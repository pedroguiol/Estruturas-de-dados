#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct documento {

    struct documento* proximo;

    char nomeDoc[50];
    uint32_t numPag;

}documento;

typedef struct pilha {

    documento* topo;

}pilha;

typedef struct documPrim {

    struct documPrim* proximo;

    char nomeDoc[50];
    uint32_t numPag;
}documPrim;

typedef struct pilhaPrin {

    documPrim* topo;

}pilhaPrin;

pilhaPrin ordemtot;

uint32_t tempo(uint32_t *somaPag, uint32_t numImp, uint32_t impAloc, uint32_t numDoc) {

    uint32_t imprimiu = 0;
    uint32_t i = 0;

    while(!imprimiu){
        
        for(uint32_t j = 0; j < numImp; j++){
            if(somaPag[j] == 0 && impAloc < numDoc){
                imprimiu = 1;
                i = j;
                break;
            } else if(somaPag[j] == 0 && impAloc >= numDoc) {
                imprimiu = 1;
                i = j;
                somaPag[j] = -1;
                break;
            }

            if(impAloc >= numImp) {

                somaPag[j] -= 1;
            }
        }

    }

    return i;  


}

void historico(pilha *pDocs, uint32_t i, char **nomeImp, FILE* output) {

    
    documento *aux = pDocs[i].topo;
    
    fprintf(output,"%s:",nomeImp[i]);

    while(aux != NULL){

        fprintf(output,"%s-%dp",aux->nomeDoc,aux->numPag);
        if(aux->proximo != NULL){
            fprintf(output,",");
        }
        aux = aux->proximo;
        
    }
    fprintf(output,"\n");
    
}


void pegarDocs(pilhaPrin *pilhaPrin,documento **docs, pilha *pDocs, uint32_t *totPag, uint32_t numImp,uint32_t numDoc, FILE* input, char **nomeImp,FILE *output) {
    
    
    uint32_t *somaPag = (uint32_t*) calloc(numImp,sizeof(uint32_t));
    uint32_t impAloc = 0;
    uint32_t i;
    for(uint32_t j = 0; j < numDoc + numImp; j++){
        
        char nome[50];
        uint32_t pag;
        i = tempo(somaPag, numImp,impAloc,numDoc);

        if(impAloc >= numImp) {

            documPrim* novo = (documPrim*) malloc(sizeof(documPrim));
            strcpy(novo->nomeDoc,docs[i]->nomeDoc);
            novo->numPag = docs[i]->numPag;
            
            novo->proximo = pilhaPrin->topo;
            pilhaPrin->topo = novo; 
        } 

        if(j < numDoc) {

            fscanf(input,"%s",nome); 
            fscanf(input,"%d",&pag);
            (*totPag) += pag;
           
            docs[i] = (documento*) malloc(sizeof(documento));
            strcpy(docs[i]->nomeDoc,nome);
            docs[i]->numPag = pag;
            docs[i]->proximo=NULL;
            somaPag[i] += pag;
            
            docs[i]->proximo = pDocs[i].topo;
            pDocs[i].topo = docs[i];
            historico(pDocs,i,nomeImp,output);  
            
        }
    
        impAloc++;
    }

    free(somaPag);

}

void mostrarPag(uint32_t pag,FILE* output){
    
    fprintf(output,"%dp\n",pag);

}

void ordemImp(pilhaPrin *pilhaPrin,FILE* output) {

    documPrim *aux = pilhaPrin->topo;

    while(aux != NULL) {
        fprintf(output,"%s-%dp\n",aux->nomeDoc,aux->numPag);
        aux = aux->proximo;
    }

}

void liberar(documento **docs, pilha *pDocs,pilhaPrin *pilhaPrin, uint32_t t) {

    for(uint32_t i = 0; i < t; i++) {

        documento *aux = pDocs[i].topo;
        while(aux != NULL) {
            documento *atual = aux;
            aux = aux->proximo;
            free(atual);
        }
    }

    documPrim *aux = pilhaPrin->topo;

    while (aux != NULL)
    {
        documPrim *atual = aux;
        aux = aux->proximo;
        free(atual);
    }
    
}


int main(int argc, char* argv[]) {

    printf("Quantidade de argumentos (argc): %i\n", argc);

	for(uint32_t i = 0; i < argc; i++) {
		printf("Argumento %i (argv[%i]): %s\n", i, i, argv[i]);
	}
    
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    
    uint32_t numDoc;
    uint32_t numImp;
    uint32_t totPag = 0;
    
    fscanf(input,"%d",&numImp);

   
    char **nomeImp = (char**) malloc(sizeof(char*) * numImp);
    for(uint32_t i = 0; i < numImp; i++){

        nomeImp[i] = (char*) malloc(sizeof(char) * 50);
    
    }

    for(uint32_t i = 0; i < numImp; i++){

        fscanf(input,"%s",nomeImp[i]);

    }
    
    fscanf(input,"%d",&numDoc);
    
    documento **docs = (documento**) malloc(sizeof(documento*) * numImp);

    for(uint32_t i = 0; i < numImp; i++){
        docs[i] = NULL;
    }

    pilha *pDocs = (pilha*) malloc(sizeof(pilha) * numImp);

    for(uint32_t i = 0; i < numImp; i++){
        pDocs[i].topo = NULL;
    }

    ordemtot.topo = NULL;
    pegarDocs(&ordemtot,docs,pDocs,&totPag,numImp,numDoc,input,nomeImp,output);
    mostrarPag(totPag,output);
    ordemImp(&ordemtot,output);

    liberar(docs,pDocs,&ordemtot,numImp);

    for (uint32_t i = 0; i < numImp; i++) {
        free(nomeImp[i]);
    }

    free(nomeImp);
    free(pDocs);
    free(docs);

    fclose(input);
    fclose(output);
    
    return 0;
}  
