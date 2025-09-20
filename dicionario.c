#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    
    int32_t qtdeSin;
    char palavra[30];
    char sinonimos[10][30];
    
    int8_t balan;
    struct no *direita;
    struct no *esquerda;
    
} no;

int32_t maior(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

int32_t alturaNo(no *raiz) {
    if(raiz == NULL) {
        return 0;
    } else {
        return raiz->balan;
    }
}

no* rotacao_E(no *raiz)
{
    no *eixo,*filho;
    
    eixo = raiz->direita;
    filho = eixo->esquerda;
    
    eixo->esquerda = raiz;
    raiz->direita = filho;

    raiz->balan = maior(alturaNo(raiz->esquerda),alturaNo(raiz->direita)) + 1;
    eixo->balan = maior(alturaNo(eixo->esquerda),alturaNo(eixo->direita)) + 1;
    return eixo;
}
no* rotacao_D(no *raiz)
{
    no *eixo,*filho;
    
    eixo = raiz->esquerda;
    filho = eixo->direita;
    
    eixo->direita = raiz;
    raiz->esquerda = filho;

    raiz->balan = maior(alturaNo(raiz->esquerda),alturaNo(raiz->direita)) + 1;
    eixo->balan = maior(alturaNo(eixo->esquerda),alturaNo(eixo->direita)) + 1;
    return eixo;
   
}

no* rotacao_E_D(no *raiz)
{
    raiz->esquerda = rotacao_E(raiz->esquerda);
    return rotacao_D(raiz);
}

no* rotacao_D_E(no *raiz)
{
    raiz->direita = rotacao_D(raiz->direita);
    return rotacao_E(raiz);
  
}

int32_t fatorDeBalanceamento(no *raiz) {

    if(raiz) {
        return alturaNo(raiz->direita) - alturaNo(raiz->esquerda);
    } else {
        return 0;
    }

}

no* balancear(no *raiz) {
    if (!raiz) return NULL;

    int32_t altEsq = alturaNo(raiz->esquerda);
    int32_t altDir = alturaNo(raiz->direita);
    raiz->balan = maior(altEsq, altDir) + 1;

    if (fatorDeBalanceamento(raiz) < -1 && fatorDeBalanceamento(raiz->esquerda) <= 0)
        {
            return rotacao_D(raiz);
        }
        else if (fatorDeBalanceamento(raiz) > 1 && fatorDeBalanceamento(raiz->direita) >= 0)
        {
            return rotacao_E(raiz);
        }
        else if (fatorDeBalanceamento(raiz) < -1 && fatorDeBalanceamento(raiz->esquerda) > 0)
        {
            return rotacao_E_D(raiz);
        }
        else if (fatorDeBalanceamento(raiz) > 1 && fatorDeBalanceamento(raiz->direita) < 0)
        {
            return rotacao_D_E(raiz);
        }

    return raiz; 
}


no *montarArv(no *raiz, FILE *input, char *palavra, char sinonimos[10][30], int32_t numSin)
{

    if (raiz == NULL)
    {
        no *novo = (no *)malloc(sizeof(no));
        strcpy(novo->palavra, palavra);
        for (int i = 0; i < numSin; i++)
        {
            strcpy(novo->sinonimos[i], sinonimos[i]);
        }
        novo->qtdeSin = numSin;
        novo->balan = 1;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    else
    {

        if (strcmp(palavra, raiz->palavra) < 0) {
            raiz->esquerda = montarArv(raiz->esquerda, input, palavra, sinonimos, numSin); 
            
        }
        else {
            raiz->direita = montarArv(raiz->direita, input, palavra, sinonimos, numSin);
            
        }           
        
        return balancear(raiz);
    }
}

void buscar(no *raiz, FILE *output, char *palavra)
{

    fprintf(output, "[");

    while (1)
    {
    
        if (raiz == NULL)
        {
            fprintf(output, "?]\n");
            fprintf(output, "-\n");
            break;
        }
        else if (strcmp(palavra, raiz->palavra) == 0)
        {
         
            fprintf(output, "%s]\n", palavra);
            for (int32_t i = 0; i < raiz->qtdeSin; i++)
            {
                fprintf(output, "%s", raiz->sinonimos[i]);
                if (i != raiz->qtdeSin - 1)
                {
                    fprintf(output, ",");
                }
            }
            fprintf(output, "\n");
            break;
        }
        else if (strcmp(palavra, raiz->palavra) < 0)
        {
           
            fprintf(output, "%s->", raiz->palavra);
            raiz = raiz->esquerda;
        }
        else if (strcmp(palavra, raiz->palavra) > 0)
        {
            
            fprintf(output, "%s->", raiz->palavra);
            raiz = raiz->direita;
        }
    }
}

int main(int argc, char *argv[])
{

    printf("Quantidade de argumentos (argc): %i\n", argc);

    for (int i = 0; i < argc; i++)
    {
        printf("Argumento %i (argv[%i]): %s\n", i, i, argv[i]);
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    int32_t numPalav;
    int32_t numSin;
    int32_t numCons;

    fscanf(input, "%d", &numPalav);

    no *raiz = NULL;
    char palavra[30];
    char sinonimos[10][30];
    for (int32_t i = 0; i < numPalav; i++)
    {
        fscanf(input, "%s", palavra);
        fscanf(input, "%d", &numSin);
        for (int32_t i = 0; i < numSin; i++)
        {
            fscanf(input, "%s", sinonimos[i]);
        }
        raiz = montarArv(raiz, input, palavra, sinonimos, numSin);
      
    }

    fscanf(input, "%d", &numCons);

    for (int32_t i = 0; i < numCons; i++)
    {
        fscanf(input, "%s", palavra);
        buscar(raiz, output, palavra);
    }

    fclose(input);
    fclose(output);

    return 0;
}