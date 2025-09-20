#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct Usuario
{
	char nome[50];

	struct Usuario *anterior;
	struct Usuario *proximo;

} Usuario;

typedef struct lista
{
	Usuario *inicio;

} lista;
lista amigos;



void mudarNome(char *nome) {

	for (uint32_t i = 0; i < strlen(nome); i++)
	{
		if (nome[i] == ' ')
		{
			nome[i] = '_';
		}
	}

}

void adicionar(lista *lista, FILE *output, char *nome, uint32_t *cont)
{
	Usuario *novo = (Usuario *)malloc(sizeof(Usuario));
    uint32_t i = 0;
    uint32_t verif = 0;
	Usuario *aux = lista->inicio;
    nome[strcspn(nome, "\n")] = '\0';

	while (i < (*cont))
	{

		if (strcmp(aux->nome, nome) == 0)
		{
            verif = 1;
			break;
		} 
		aux = aux->proximo;
		i++;
	}

	strcpy(novo->nome, nome);

    if(!verif){

        if (lista->inicio == NULL)
        {
            novo->proximo = novo->anterior = novo;
            lista->inicio = novo;
        }
        else
        {
            Usuario *ultimo = lista->inicio->anterior;

            novo->proximo = lista->inicio;
            novo->anterior = ultimo;

            ultimo->proximo = novo;
            lista->inicio->anterior = novo;
        }
        (*cont)++;

	    fprintf(output, "[SUCCESS]ADD=%s\n", nome);
    } else {

        free(novo);
        fprintf(output, "[FAILURE]ADD=%s\n", nome);

    }


}

void remover(lista *lista, char *nome, FILE *output,uint32_t *cont)
{
    
    uint32_t i = 0;
    uint32_t verif = 0;
	Usuario *aux = lista->inicio;
    nome[strcspn(nome, "\n")] = '\0';

	while (i < (*cont))
	{
		if (strcmp(aux->nome, nome) == 0)
		{
            verif = 1;
			break;
		}
		aux = aux->proximo;
		i++;
	}

    if(!verif){
        fprintf(output, "[FAILURE]REMOVE=%s\n", nome);

    } else {

        if(aux == aux->proximo){

            lista->inicio = NULL;
            
        } else {
            aux->anterior->proximo = aux->proximo;
		    aux->proximo->anterior = aux->anterior;

            if (aux == lista->inicio)
            {

                lista->inicio = aux->proximo;
            }
        }

        fprintf(output, "[SUCCESS]REMOVE=%s\n", aux->nome);
        free(aux);
        (*cont)--;

    }



}


void mostrar(lista *lista, uint32_t cont,char *nome, FILE *output)
{
    uint32_t i = 0;
    uint32_t verif = 0;
    Usuario *aux = lista->inicio;

    nome[strcspn(nome, "\n")] = '\0';
    
    while (i < cont)
	{

		if (strcmp(aux->nome, nome) == 0)
		{
            verif = 1;
			break;
		}
		aux = aux->proximo;
		i++;
	}


    if(!verif){
        fprintf(output, "[FAILURE]SHOW=?<-%s->?\n", nome);
    } else {

        aux->nome[strcspn(aux->nome, "\n")] = '\0';
        aux->proximo->nome[strcspn(aux->proximo->nome, "\n")] = '\0';
        aux->anterior->nome[strcspn(aux->anterior->nome, "\n")] = '\0';
	    fprintf(output, "[SUCCESS]SHOW=%s<-%s->%s\n", aux->anterior->nome, aux->nome, aux->proximo->nome);

    }

}

void libera(lista *lista, uint32_t cont) {

    uint32_t i = 0;

    if(!lista->inicio){
        return;
    }

    Usuario *atual = lista->inicio;
    Usuario *proximo = lista-> inicio;

    while(i < cont) {

        proximo = atual->proximo;
        free(atual);
        atual = proximo;
		i++;
    }
    lista->inicio = NULL;

}

int main(int argc, char *argv[])
{
	char comando[10];
	char frase[60];
	char nome[50];
	uint32_t cont = 0;

	printf("Quantidade de argumentos (argc): %i\n", argc);

	for (uint32_t i = 0; i < argc; i++)
	{

		printf("Argumento %i (argv[%i]): %s", i, i, argv[i]);
	}

	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");

	while (fscanf(input, "%s", comando) != EOF)
	{

		uint32_t j = 0;
		fgets(frase, sizeof(frase), input);

		for (int i = 1; frase[i] != '\0'; i++)
		{
			nome[j] = frase[i];
			j++;
		}
		nome[j] = '\0';

		mudarNome(nome);

		if (strcmp(comando, "ADD") == 0)
		{
			adicionar(&amigos,output,nome,&cont);
		}
		else if (strcmp(comando, "REMOVE") == 0)
		{

			remover(&amigos,nome,output,&cont);
		}
		else if (strcmp(comando,"SHOW") == 0)
		{
			mostrar(&amigos,cont,nome,output);
		}
	}
    libera(&amigos,cont);
	fclose(input);
	fclose(output);

	return 0;
}
