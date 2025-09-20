#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct elemento {

    struct elemento *proximo;
    char palavraCom[100];

}elemento;

void criarLista(elemento **nomes,uint32_t i, char *palavraCom) {

    elemento  *novo = (elemento*) malloc(sizeof(elemento));

    strcpy(novo->palavraCom,palavraCom);
    novo->proximo = NULL;

    if (nomes[i] == NULL) {
        nomes[i] = novo;  
    } else {
        elemento* atual = nomes[i];
        while (atual->proximo != NULL) {
            atual = atual->proximo; 
        }
        atual->proximo = novo;  
    }

}

uint32_t checksum(char *nome) {

   uint32_t tamanho = strlen(nome);
   uint32_t soma = 0;
   for(uint32_t i = 0; i < tamanho; i++) {
    
        if(nome[i] != '_'){

            soma ^= nome[i];
        }

   }

   return soma;

}

void imprimir(elemento *lista,int i, FILE *output) {

    elemento *aux = lista;

    fprintf(output,"S%d:",i);    
    while(aux !=NULL){
        if(aux->proximo != NULL) {
            fprintf(output,",");
        }
        fprintf(output,"%s",aux->palavraCom);
    }
    fprintf(output,"\n");

}

void armazenar(elemento **nomes, FILE *input, uint32_t requis, uint32_t t, uint32_t capac,FILE *output) {

    char nome[100];
    char palavraCom[100];
    uint32_t num;
    
    uint32_t ultimo;
    
    for(uint32_t i = 0; i < requis; i++) {
        
        fscanf(input,"%d",&num);
        
        for(uint32_t j = 0; j < num; j++){
           
           fscanf(input,"%s",nome);
           ultimo = strlen(nome);

            if(j != num-1){
            nome[ultimo-1] = '_';
        }
        
        strcat(palavraCom,nome);
        
    }
    
    uint32_t cont = 0;
    uint32_t soma;
    uint32_t posic;
    uint32_t origem;
    uint32_t p = 0;
    uint32_t vazia = 0;
    
    soma = checksum(palavraCom);
    origem = (7919 * soma) % t;
    elemento *aux = nomes[origem];
    

    while (aux != NULL)
    {
        cont++;
        aux = aux->proximo;

    }

    if(cont < capac){
        posic = origem;
        vazia = 1;
    } 
    
    cont = 0;
    while (!vazia)
    {

        posic = ((7919 * soma) + p * (104729 * soma + 123)) % t;   
        aux = nomes[posic];

        if(aux != NULL){
            cont++;
            aux = aux->proximo;
        }

        if(cont < capac){

            vazia = 1;
        } else if(cont >= capac){
            break;
        }

        p++;
       
        
    
    }
    
    criarLista(nomes,posic,palavraCom);
    if(p > 0){
        fprintf(output,"S%d->S%d\n",origem,posic);
    }
    imprimir(nomes[posic],posic,output);


   }

}

int main(int argc, char* argv[]) {
   
   printf("Quantidade de argumentos (argc): %i\n", argc);
   
   for(int i = 0; i < argc; i++) {
       
       printf("Argumento %i (argv[%i]): %s\n", i, i, argv[i]);
   }
   
   FILE* input = fopen(argv[1], "r");
   FILE* output = fopen(argv[2], "w");

   uint32_t numServ;
   uint32_t capac;
   uint32_t requis;

   fscanf(input,"%d",&numServ);
   fscanf(input,"%d",&capac);
   fscanf(input,"%d",&requis);
   //capVetor = numServ * capac;

   elemento **nomes = (elemento**) malloc(sizeof(elemento*) * numServ);
   for(uint32_t i = 0; i < numServ; i++){
       nomes[i] = NULL;
   }

   armazenar(nomes,input,requis,numServ,capac,output);

   fclose(input);
   fclose(output);

   return 0;
}   

