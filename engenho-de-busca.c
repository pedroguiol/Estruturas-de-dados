#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct elemento {
    struct elemento *proximo;
    char *palavraCom;
} elemento;

void criarLista(elemento **nomes, uint32_t i, char *palavraCom) {
    elemento *novo = (elemento *)malloc(sizeof(elemento));
    novo->palavraCom = (char *)malloc(sizeof(char) * (strlen(palavraCom) + 1));
    strcpy(novo->palavraCom, palavraCom);
    novo->proximo = NULL;

    if (nomes[i] == NULL) {
        nomes[i] = novo;
    } else {
        elemento *atual = nomes[i];
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

void liberar(elemento **nomes, int t) {
    for (int i = 0; i < t; i++) {
        elemento *atual = nomes[i];
        while (atual != NULL) {
            elemento *aux = atual;
            atual = atual->proximo;
            free(aux->palavraCom);
            free(aux);
        }
    }
}

uint32_t checksum(char *nome) {
    uint32_t tamanho = strlen(nome);
    uint32_t soma = 0;
    for (uint32_t i = 0; i < tamanho; i++) {
        if (nome[i] != '_') {
            soma ^= nome[i];
        }
    }
    return soma;
}

void imprimir(elemento *lista, int i, FILE *output) {
    elemento *aux = lista;
    fprintf(output, "S%d:", i);
    while (aux != NULL) {
        fprintf(output, "%s", aux->palavraCom);
        if (aux->proximo != NULL) {
            fprintf(output, ",");
        }
        aux = aux->proximo;
    }
    fprintf(output, "\n");
}

void armazenar(elemento **nomes, FILE *input, uint32_t requis, uint32_t t, uint32_t capac, FILE *output) {
    char nome[100];
    char *palavraCom;
    uint32_t num;

    for (uint32_t i = 0; i < requis; i++) {
        fscanf(input, "%d", &num);

        palavraCom = (char *)malloc(sizeof(char) * (num * 100 + num)); 
        palavraCom[0] = '\0';  

        for (uint32_t j = 0; j < num; j++) {
            fscanf(input, "%s", nome);
            strcat(palavraCom, nome);
            if (j < num - 1) strcat(palavraCom, "_");
        }

        uint32_t soma = checksum(palavraCom);
        uint32_t origem = (7919 * soma) % t;
        uint32_t posic = origem;
        uint32_t cont = 0;
        uint32_t p = 0;

        elemento *aux = nomes[posic];
        while (aux != NULL) {
            cont++;
            aux = aux->proximo;
        }

        if (cont >= capac) {
            while (1) {
                p++;
                posic = ((7919 * soma) + p * (104729 * soma + 123)) % t;
                cont = 0;
                aux = nomes[posic];
                while (aux != NULL) {
                    cont++;
                    aux = aux->proximo;
                }
                if (cont < capac) {
                    fprintf(output, "S%d->S%d\n", origem, posic);
                    break;
                }
            }
        }

        criarLista(nomes, posic, palavraCom);
        imprimir(nomes[posic], posic, output);
        free(palavraCom);
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

   elemento **nomes = (elemento**) malloc(sizeof(elemento*) * numServ);
   for(uint32_t i = 0; i < numServ; i++){
       nomes[i] = NULL;
   }

   armazenar(nomes,input,requis,numServ,capac,output);
   
   liberar(nomes,numServ);
   free(nomes);
   fclose(input);
   fclose(output);

   return 0;
}   

