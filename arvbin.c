#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct elemento {

    char nome[50];
    int32_t tamanho;
    char tipo[5];
    int32_t indice;

    struct elemento *direita;
    struct elemento *esquerda;

}elemento;

typedef struct lista {

    elemento *inicio;

}lista;

lista arvore;

void montarArv(lista *arvore, FILE *input, int32_t numArq,FILE *output) {
    

    for(int i = 0; i < numArq; i++) {
        elemento *novo = (elemento*) malloc(sizeof(elemento));
        

        fscanf(input,"%s",novo->nome);
        fscanf(input,"%s",novo->tipo);
        fscanf(input,"%d",&novo->tamanho);
        novo->indice = i;
      
        if(arvore->inicio == NULL) {
            arvore->inicio = novo;
            novo->esquerda = NULL;
            novo->direita = NULL;
            
        } else {
            
            elemento *aux = arvore->inicio;
            while (1)
            {

               if(strcmp(novo->nome,aux->nome) == 0 && strcmp(aux->tipo,"ro") == 0) {
                    break;

                } else if(strcmp(novo->nome,aux->nome) == 0 && strcmp(aux->tipo,"rw") == 0 ) {
                    aux->indice = novo->indice;
                    strcpy(aux->tipo,novo->tipo);
                    aux->tamanho = novo->tamanho;
                    break;

                } else if(strcmp(novo->nome,aux->nome) < 0) {
                    
                    if(aux->esquerda == NULL) {
                        aux->esquerda = novo;
                        novo->esquerda = NULL;
                        novo->direita = NULL;
                        break;
                    } else {
                        aux = aux->esquerda;
                    }
    
                    
                } else {
                
                    if(aux->direita == NULL) {
                        aux->direita = novo;
                        novo->esquerda = NULL;
                        novo->direita = NULL;
                        break;

                    } else {
                        aux = aux->direita;
                    }
                  
                } 
                
            }        
            
        }

    }
    

} 

void preOrdem(elemento *no,FILE *output) {
   
    if(no == NULL) {
        return;
    }

    if(no->tamanho > 1){
        fprintf(output,"%d:%s|%s|%d_bytes\n",no->indice,no->nome,no->tipo,no->tamanho);
    } else {
        fprintf(output,"%d:%s|%s|%d_byte\n",no->indice,no->nome,no->tipo,no->tamanho);
    }
    preOrdem(no->esquerda,output);
    preOrdem(no->direita,output);
} 

void ordem(elemento *no, FILE *output) {

     
    if(no == NULL) {
        return;
    }

    ordem(no->esquerda,output);

    if(no->tamanho > 1){
        fprintf(output,"%d:%s|%s|%d_bytes\n",no->indice,no->nome,no->tipo,no->tamanho);
    } else {
        fprintf(output,"%d:%s|%s|%d_byte\n",no->indice,no->nome,no->tipo,no->tamanho);
    }

    ordem(no->direita,output);


}

void posOrdem(elemento *no, FILE *output) {
    
    if(no == NULL) {
        return;
    }

    
    posOrdem(no->esquerda,output);
    posOrdem(no->direita,output);

    if(no->tamanho > 1){
        fprintf(output,"%d:%s|%s|%d_bytes\n",no->indice,no->nome,no->tipo,no->tamanho);
    } else {
        fprintf(output,"%d:%s|%s|%d_byte\n",no->indice,no->nome,no->tipo,no->tamanho);
    }
}

void liberar(elemento *no) {

     
    if(no == NULL) {
        return;
    }

    
    liberar(no->esquerda);
    liberar(no->direita);

    free(no);


}

int main(int argc, char* argv[]) {
	
	printf("Quantidade de argumentos (argc): %i\n", argc);
	
	for(uint32_t i = 0; i < argc; i++) {
		
		printf("Argumento %i (argv[%i]): %s\n", i, i, argv[i]);
	}
	
	FILE* input = fopen(argv[1], "r");
	FILE* output = fopen(argv[2], "w");

    int32_t numArq;

    fscanf(input,"%d",&numArq);
    
    arvore.inicio = NULL;
    montarArv(&arvore,input,numArq,output);

    fprintf(output,"[EPD]\n");
    ordem(arvore.inicio,output);
    fprintf(output,"[PED]\n");
    preOrdem(arvore.inicio,output); 
    fprintf(output,"[EDP]\n");
    posOrdem(arvore.inicio,output);
    liberar(arvore.inicio);
	
	fclose(input);
	fclose(output);
	
	return 0;
}