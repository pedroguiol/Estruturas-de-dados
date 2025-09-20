#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


typedef struct biblioteca {
    uint64_t isbn;
    char autor[50];
    char titulo[100];
} biblioteca;

void armazenar(FILE *input, biblioteca *livros, uint32_t numLiv) {
    char linha[151];
    char espaco;

    for (uint32_t i = 0; i < numLiv; i++) {
        fscanf(input, "%" SCNu64, &livros[i].isbn);
        fscanf(input, "%c", &espaco);
        fgets(linha, 151, input);

        strcpy(livros[i].autor, strtok(linha, "&"));
        for (uint32_t j = 1; j < strlen(livros[i].autor); j++) {
            if (livros[i].autor[j] == ' ') {
                livros[i].autor[j] = '_';
            }
        }

        strcpy(livros[i].titulo, strtok(NULL, "\n"));
        for (uint32_t j = 1; j < strlen(livros[i].titulo); j++) {
            if (livros[i].titulo[j] == ' ') {
                livros[i].titulo[j] = '_';
            }
        }
    }
}

void trocar(biblioteca *livros1, biblioteca *livros2){

    biblioteca *aux;

    aux = livros1;
    livros1 = livros2;
    livros2 = aux;

}

void ordenar(biblioteca *livros, uint32_t numLiv) {
 
 
    for(uint32_t i = 1; i < numLiv; i++){
        for(uint32_t j = i; j > 0 && livros[j- 1].isbn > livros[j].isbn;j--){

            trocar(&livros[j], &livros[j- 1]);
        }

    }
 
}
 
int32_t binaria(biblioteca *livros, uint32_t numLiv, uint64_t isbnP, int32_t *contB) {
   
    int32_t i = 0;
    int32_t j = numLiv- 1;
    int32_t pos = (i + j)/2;
 
    while(j >= i && livros[pos].isbn != isbnP) {
        if(livros[pos].isbn > isbnP){
            
            j = pos- 1;
            
        }
        else{
            
            i = pos + 1;
            
        }
        pos = (i + j)/2;
        (*contB)++;
    } 
    
    if(livros[pos].isbn == isbnP){
        
        return pos;

    } else {
        return -1;
    }
}


int32_t interpolada(biblioteca *livros, uint32_t numLiv, uint64_t isbnP, int32_t *contI) {
    int32_t i = 0;
    int32_t j = numLiv - 1;
    int32_t pos;
    while(j >= i) {
        (*contI)++;
        
        pos = i + (livros[j].isbn - livros[i].isbn) % (j - i + 1);

        
        if(livros[pos].isbn == isbnP){
       
           return pos;

       }
        if(livros[pos].isbn > isbnP){

            j = pos- 1;
            
        }
        else{

            i = pos + 1;

        }
    } 

    return -1;

}   
 
void procura(FILE *input, FILE *output, biblioteca *livros, uint32_t consul, uint32_t numLiv) {
    uint64_t isbnP;
    int32_t pos;
    int32_t contB, somaB = 0, vitoriaB = 0;
    int32_t contI, somaI = 0, vitoriaI = 0;
    int32_t mediaB, mediaI;

    for (uint32_t i = 0; i < consul; i++) {
        contB = 1;
        contI = 0;

        fscanf(input, "%" SCNu64, &isbnP);

        binaria(livros, numLiv, isbnP, &contB);
        pos = interpolada(livros, numLiv, isbnP,&contI);
       
        
        if (contB >= contI) {
            vitoriaI++;
        } else {
            vitoriaB++;
        }

        somaB += contB;
        somaI += contI;

       if (pos >= 0) {
            fprintf(output, "[%" PRIu64 "]B=%d|I=%d|Author:%s,Title:%s\n",livros[pos].isbn, contB, contI, livros[pos].autor, livros[pos].titulo);
        } else {
            fprintf(output, "[%" PRIu64 "]B=%d|I=%d|ISBN_NOT_FOUND\n", isbnP, contB, contI);
        }
    } 

    mediaB = somaB / consul;
    mediaI = somaI / consul;

    fprintf(output, "BINARY=%d:%d\n", vitoriaB, mediaB);
    fprintf(output, "INTERPOLATION=%d:%d\n", vitoriaI, mediaI); 

}

int main(int argc, char *argv[]) {
    printf("Quantidade de argumentos (argc): %i\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("Argumento %i (argv[%i]): %s\n", i, i, argv[i]);
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    uint32_t numLiv;
    fscanf(input, "%u", &numLiv);

    biblioteca *livros = (biblioteca *)malloc(sizeof(biblioteca) * numLiv);

    armazenar(input, livros, numLiv);
    ordenar(livros, numLiv);

    uint32_t consul;
    fscanf(input, "%d", &consul);
    
    procura(input, output, livros, consul, numLiv);

    fclose(input);
    fclose(output);

    free(livros);

    return 0;
}

