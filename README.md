# Estruturas-de-dados

Aqui estão projetos desenvolvidos durante a disciplina de Estruturas de Dados, onde nesses projetos foram aplicados conceitos da mesma, como lista encadeada, árvore binária e etc

# Sistema de Impressão Centralizado (Poxim Tech)

Este projeto simula um sistema de impressão centralizado, desenvolvido como exercício para a disciplina de Estruturas de Dados.

## 📄 Descrição do Problema

O sistema da "Poxim Tech" deve otimizar o uso de impressoras gerenciando documentos que chegam para impressão. As regras são:
* Os documentos são organizados e processados por **ordem de chegada** . 
* Os nomes dos arquivos e das impressoras possuem até 50 caracteres, sendo limitados a letras e números.
* Eles são despachados para a primeira impressora que ficar ociosa. 
* Após cada impressão ser concluída, as folhas impressas de todas as impressoras são automaticamente recolhidas e **empilhadas** para entrega. 

## 💡 Estruturas de Dados Utilizadas

* **Fila (Queue):** Para gerenciar os documentos aguardando na fila de impressão. O princípio FIFO (First-In, First-Out) garante que os documentos sejam impressos na ordem em que foram recebidos. [cite: 9]
* **Pilha (Stack):** Para armazenar o histórico de documentos já impressos. O princípio LIFO (Last-In, First-Out) é usado para exibir o histórico de impressões concluídas. [cite: 102, 1071]

## 📥 Formato da Entrada

O programa espera um arquivo de entrada (ex: `entrada.txt`) com a seguinte estrutura:

1. Número de impressoras (`#n`). 
2. Nome de cada impressora, um por linha. 
3. Número de documentos a serem impressos (`#m`). 
4. Nome de cada documento e seu respectivo número de páginas. 

### Exemplo de `entrada.txt`

```
2
jatodetinta
laser
6
sigaa 2
bbbbb 7
documento 3
abc 2
xyz 5
aaaaa 6
```

## 📤 Formato da Saída

A saída do programa exibe o status de alocação de cada impressora e, ao final, um resumo com o total de páginas e a lista de documentos na ordem em que foram empilhados. [cite: 1070, 1072]

### Exemplo de `saida.txt`

```
jatodetinta: sigaa-2p
laser: bbbbb-7p
jatodetinta: documento-3p, sigaa-2p
jatodetinta: abc-2p, documento-3p, sigaa-2p
jatodetinta: xyz-5p, abc-2p, documento-3p, sigaa-2p
laser: aaaaa-6p, bbbbb-7p

25p
xyz-5p
aaaaa-6p
abc-2p
documento-3p
bbbbb-7p
sigaa-2p
```

## ⚙️ Como Compilar e Executar

**1. Compilar o código:**
Use um compilador C (como o GCC) para gerar o executável.

```bash
gcc -Wall -O3 sistema-de-impressao.c -o sistema-de-impressao
```

**2. Executar o programa:**
Passe o arquivo de entrada como primeiro argumento e o nome do arquivo de saída como segundo.

```bash
./sistema-de-impressao entrada.txt saida.txt
```

---