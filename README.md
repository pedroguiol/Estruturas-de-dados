# Estruturas de Dados

Este repositório contém uma coleção de projetos desenvolvidos para a disciplina de Estruturas de Dados na Universidade Federal de Sergipe (UFS). Cada projeto aborda diferentes problemas e aplica estruturas de dados específicas para sua solução.

## Índice de Projetos

| Projeto | Descrição | Estruturas de Dados |
| :--- | :--- | :--- |
| **[Sistema de Impressão Centralizado](#-sistema-de-impressão-centralizado-poxim-tech)** | Simulação de um sistema que gerencia uma fila de impressão e uma pilha de trabalhos concluídos. | `Fila`, `Pilha` |
| **[Sistema de Armazenamento de Arquivos](#-sistema-de-armazenamento-de-arquivos-poxim-tech)** | Implementação de um sistema de arquivos ordenado utilizando uma árvore binária de busca. | `Árvore Binária de Busca` |
| **[Comparativo de Buscas em Biblioteca](#-comparativo-de-buscas-em-biblioteca-poxim-tech)** | Análise comparativa da eficiência entre os algoritmos de Busca Binária e Busca Interpolada. | `Busca Binária`, `Busca Interpolada` |
| **[Dicionário de Sinônimos](#-dicionário-de-sinônimos-poxim-tech)** | Sistema de dicionário de sinônimos que garante buscas eficientes através do autobalanceamento. | `Árvore AVL` |
| **[Engenho de Busca Experimental](#-engenho-de-busca-experimental-poxim-tech)** | Sistema que distribui requisições de busca para múltiplos servidores utilizando `hashing`. | `Hashing`, `Checksum` |
| **[Apuração de Loteria](#-apuração-de-loteria-poxim-tech)** | Sistema para apuração de resultados de loteria, identificando os maiores e menores acertadores. | `Heap Mínimo`, `Heap Máximo` |
| **[Rede Social "De Mãos Dadas"](#-rede-social-de-mãos-dadas-poxim-tech)** | Simulação de uma rede social em círculo, onde cada pessoa se conecta aos seus vizinhos. | `Lista Duplamente Encadeada Circular` |

---

## 🖨️ Sistema de Impressão Centralizado (Poxim Tech)

Este projeto simula um sistema de impressão centralizado, desenvolvido como exercício para a disciplina de Estruturas de Dados.

### 📄 Descrição do Problema

O sistema da "Poxim Tech" deve otimizar o uso de impressoras gerenciando documentos que chegam para impressão. As regras são:
* Os documentos são organizados e processados por **ordem de chegada**.
* Os nomes dos arquivos e das impressoras possuem até 50 caracteres, sendo limitados a letras e números.
* Eles são despachados para a primeira impressora que ficar ociosa.
* Após cada impressão ser concluída, as folhas impressas de todas as impressoras são automaticamente recolhidas e **empilhadas** para entrega.

### 💡 Estruturas de Dados Utilizadas

* **Fila (Queue):** Para gerenciar os documentos aguardando na fila de impressão. O princípio FIFO (First-In, First-Out) garante que os documentos sejam impressos na ordem em que foram recebidos.
* **Pilha (Stack):** Para armazenar o histórico de documentos já impressos. O princípio LIFO (Last-In, First-Out) é usado para exibir o histórico de impressões concluídas.

### 📥 Formato da Entrada

O programa espera um arquivo de entrada (ex: `entrada.txt`) com a seguinte estrutura:

1.  Número de impressoras (`#n`).
2.  Nome de cada impressora, um por linha.
3.  Número de documentos a serem impressos (`#m`).
4.  Nome de cada documento e seu respectivo número de páginas.

#### Exemplo de `entrada.txt`

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

### 📤 Formato da Saída

A saída do programa exibe o status de alocação de cada impressora e, ao final, um resumo com o total de páginas e a lista de documentos na ordem em que foram empilhados.

#### Exemplo de `saida.txt`

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

### ⚙️ Como Compilar e Executar

**1. Compilar o código:**
```bash
gcc -Wall -O3 sistema-de-impressao.c -o sistema-de-impressao
```

**2. Executar o programa:**
```bash
./sistema-de-impressao entrada.txt saida.txt
```

---

## 🌳 Sistema de Armazenamento de Arquivos (Poxim Tech)

Este projeto implementa um sistema de armazenamento de arquivos, organizando-os com base em seus nomes utilizando uma Árvore Binária de Busca.

### 📄 Descrição do Problema

O sistema da "Poxim Tech" deve armazenar arquivos e suas informações de maneira ordenada e eficiente, seguindo estas regras:

* Os arquivos são organizados em uma **Árvore Binária de Busca** usando o nome do arquivo como chave de ordenação.
* O nome do arquivo pode ter de 1 a 50 caracteres, contendo apenas letras, números e os símbolos `_` e `.`.
* Cada arquivo possui permissão de acesso (`ro` para somente leitura, `rw` para leitura e escrita) e tamanho em bytes.
* Se um arquivo com nome repetido for inserido, suas informações são atualizadas, **somente se** o arquivo existente permitir escrita (`rw`).

### 💡 Estruturas de Dados Utilizadas

* **Árvore Binária de Busca (Binary Search Tree):** Utilizada para armazenar e organizar os arquivos. Essa estrutura permite buscas, inserções e remoções eficientes, mantendo os arquivos ordenados lexicograficamente por seus nomes.

### 📥 Formato da Entrada

O programa espera um arquivo de entrada (ex: `entrada.txt`) com a seguinte estrutura:

1.  Número de arquivos a serem processados (`#n`).
2.  Em cada linha seguinte: `[Nome] [Permissão] [Tamanho]`.

#### Exemplo de `entrada.txt`

```
5
lista_ed.c rw 1123
senhas.txt ro 144
foto.jpg rw 8374719
documento.doc rw 64732
lista_ed.c ro 1
```

### 📤 Formato da Saída

A saída do programa deve listar todos os arquivos armazenados na árvore em três diferentes ordens de percurso: Em-ordem (EPD), Pré-ordem (PED) e Pós-ordem (EDP).

#### Exemplo de `saida.txt`

```
[EPD]
documento.doc|rw|64732_bytes
foto.jpg|rw|8374719_bytes
lista_ed.c|ro|1_byte
senhas.txt|ro|144_bytes

[PED]
lista_ed.c|ro|1_byte
foto.jpg|rw|8374719_bytes
documento.doc|rw|64732_bytes
senhas.txt|ro|144_bytes

[EDP]
documento.doc|rw|64732_bytes
foto.jpg|rw|8374719_bytes
senhas.txt|ro|144_bytes
lista_ed.c|ro|1_byte
```

### ⚙️ Como Compilar e Executar

**1. Compilar o código:**
```bash
gcc -Wall -O3 arvore-binaria.c -o arvore-binaria
```

**2. Executar o programa:**
```bash
./arvore-binaria entrada.txt saida.txt
```
---

## 📚 Comparativo de Buscas em Biblioteca (Poxim Tech)

Este projeto realiza um estudo comparativo entre os algoritmos de **Busca Binária** e **Busca Interpolada** em um sistema de consulta de livros.

### 📄 Descrição do Problema

O sistema deve determinar qual das duas abordagens de busca é mais eficiente para encontrar livros em uma coleção. As regras são:
 Os livros são identificados unicamente por seu **ISBN** de 13 dígitos. 
 Para cada consulta, o sistema deve registrar o número de chamadas (comparações) que cada algoritmo realizou para encontrar o livro. 
 A busca retorna o nome do autor (até 50 caracteres) e o título do livro (até 100 caracteres). 
 A Busca Interpolada utiliza a função de heurística `h(i, j) = floor(i + (ISBN_j - ISBN_i)) mod (j - i + 1)` para estimar o índice do livro procurado. 

### 💡 Algoritmos Utilizados

 **Busca Binária:** Algoritmo de busca eficiente para vetores ordenados que funciona dividindo repetidamente o intervalo de busca pela metade. 
 **Busca Interpolada:** Variação da busca binária que, em vez de sempre verificar o meio, estima a posição do item procurado com base na distribuição dos valores no vetor. 

### 📥 Formato da Entrada

1. Número de livros na base de dados. 
2. Para cada livro: `[#ISBN] [Autor] & [Titulo]`. 
3.  Número de consultas a serem realizadas.
4. ISBN de cada livro a ser consultado. 
#### Exemplo de `entrada.txt`

```
5
9780130224187 Niklaus Wirth&Algorithms+Data Structures=Programs
9780201416077 Gaston Gonnet&Handbook of Algorithms and Data Structures
9780262033848 Thomas Cormen&Introduction to Algorithms
9780321751041 Donald Knuth&The Art of Computer Programming
9781584884354 Dinesh Mehta&Handbook of Data Structures and Applications
3
9780130224187
9781584884354
1234567890123
```

### 📤 Formato da Saída

 Para cada consulta, exibe o número de chamadas de cada algoritmo (`B` para binária, `I` para interpolada) e os dados do livro, ou `ISBN_NOT_FOUND`. 
 Ao final, mostra o total de "vitórias" de cada algoritmo (a busca interpolada vence em caso de empate) e a média truncada de chamadas. 

#### Exemplo de `saida.txt`
```
[9780130224187]B=2|I=2|Author:Niklaus_Wirth, Title:Algorithms_+_Data_Structures_=_Programs
[9781584884354]B=3|I=2|Author:Dinesh_Mehta, Title:Handbook_of_Data_Structures_and_Applications
[1234567890123]B=3|I=2|ISBN_NOT_FOUND
BINARY=0:2
INTERPOLATION=3:2
```

### ⚙️ Como Compilar e Executar

**1. Compilar o código:**
```bash
gcc -Wall -O3 biblioteca.c -o biblioteca
```

**2. Executar o programa:**
```bash
./biblioteca entrada.txt saida.txt
```
---

##  AVL Dicionário de Sinônimos (Poxim Tech)

Este projeto desenvolve um sistema de dicionário de sinônimos utilizando uma **Árvore AVL** para garantir a eficiência das operações de busca.

### 📄 Descrição do Problema

O sistema deve armazenar palavras e suas respectivas listas de sinônimos, mantendo um tempo de busca otimizado. As regras são:
 As palavras e seus sinônimos são compostas por até 30 caracteres, exclusivamente em letras minúsculas. 
 Cada palavra pode ter uma lista de, no máximo, 10 sinônimos. 
 Para demonstrar a eficiência da busca, o programa deve exibir o percurso realizado na árvore para encontrar a palavra consultada. 

### 💡 Estruturas de Dados Utilizadas

 **Árvore AVL (Adelson-Velsky e Landis):** É uma árvore binária de busca autobalanceada. A cada inserção ou remoção, ela realiza rotações para garantir que a diferença de altura entre as subárvores de qualquer nó seja no máximo 1. Isso impede a degeneração da árvore e mantém a complexidade das operações em `O(log n)`. 

### 📥 Formato da Entrada

1. Número de palavras a serem inseridas no dicionário. 
2. Para cada palavra: `[Palavra] [#Sinônimos] [Sinônimo1] [Sinônimo2] ...`. 
3. Número de consultas a serem realizadas. 
4. Palavra a ser consultada. 

#### Exemplo de `entrada.txt`
```
5
demais 5 bastante numeroso demasiado abundante excessivo
facil 2 simples ed
elegante 3 natural descomplicado trivial
nada 4 zero vazio osso nulo
trabalho 3 atividade tarefa missao
3
facil
demais
zero
```

### 📤 Formato da Saída Para cada consulta, exibe o percurso realizado na árvore (ex: `[elegante->nada->facil]`) e a lista de sinônimos da palavra encontrada. [cite: 1910, 1911] Caso a palavra não exista, o percurso indicará o ponto onde a busca falhou (ex: `[elegante->nada->trabalho->?]`).

#### Exemplo de `saida.txt`
```
[elegante->nada->facil]
simples, ed
[elegante->demais]
bastante, numeroso, demasiado, abundante, excessivo
[elegante->nada->trabalho->?]
```

### ⚙️ Como Compilar e Executar

**1. Compilar o código:**
```bash
gcc -Wall -O3 dicionario.c -o dicionario
```

**2. Executar o programa:**
```bash
./dicionario entrada.txt saida.txt
```
---

## 🌐 Engenho de Busca Experimental (Poxim Tech)

Este projeto simula um engenho de busca que distribui requisições de texto para diferentes servidores usando uma tabela **Hash**.

### 📄 Descrição do Problema

O sistema mapeia requisições de busca para servidores dedicados, tratando colisões e limites de capacidade. As regras são:
 O mapeamento é feito a partir de um valor de chave gerado pelo texto da busca, usando um **checksum** de 8 bits para cada caractere. 
 Os padrões de busca são compostos por até 100 caracteres (letras e números). 
 Cada servidor possui uma capacidade máxima de requisições que pode atender simultaneamente. 
 Quando um servidor atinge sua capacidade (colisão), a requisição é realocada para outro servidor usando a técnica de **double hashing**. 
* As funções de hash são:
     `H1(x) = 7919 * checksum(x) mod T`
     `H2(x) = (104729 * checksum(x) + 123) mod T` 

### 💡 Estruturas de Dados Utilizadas

 **Tabela Hash com Endereçamento Aberto (Double Hashing):** Uma tabela hash é usada para mapear uma chave (o checksum do texto) a um índice de vetor (o servidor). O tratamento de colisões por *double hashing* utiliza uma segunda função de hash para calcular o deslocamento a ser percorrido na tabela até encontrar uma posição livre. 
 **Checksum XOR de 8 bits:** A função de `checksum("ufs")` calcula `117 ⊕ 102 ⊕ 115`, que resulta em `96`. Essa é a chave usada nas funções de hash.

### 📥 Formato da Entrada

1. Na primeira linha: `[#Servidores] [Capacidade Máxima por Servidor]`. 
2. Número de requisições. [cite: 2657]
3. Para cada requisição: `[#Padrões] [Padrão1] [Padrão2] ...`. 

#### Exemplo de `entrada.txt`
```
3 2
5
1 ufs
3 a b c
2 cd ef
2 e d
1 hash
```

### 📤 Formato da Saída Exibe o servidor alocado para cada padrão de busca e o conteúdo atual do servidor. [cite: 2679 Mostra também as realocações quando um servidor está cheio (ex: `S0->S1`). 

#### Exemplo de `saida.txt`
```
S0: ufs
S0: ufs, a_b_c
S2: cd_ef
S2: cd_ef, e_d
S0->S1
S1: hash
```

### ⚙️ Como Compilar e Executar

**1. Compilar o código:**
```bash
gcc -Wall -O3 engenho-de-busca.c -o engenho-de-busca
```

**2. Executar o programa:**
```bash
./engenho-de-busca entrada.txt saida.txt
```
---

## 💰 Apuração de Loteria (Poxim Tech & Banana Cap)

Este projeto desenvolve um sistema para apuração de resultados de loteria, identificando de forma eficiente as apostas com maior e menor número de acertos.

### 📄 Descrição do Problema

O sistema deve apurar os resultados de um concurso de loteria, premiando as faixas de maior e menor acertos. As regras são:
 Cada aposta consiste em 15 números, escolhidos de 1 a 50. 
 O sorteio define 10 números distintos. 
 O prêmio é dividido igualmente entre as apostas com o **maior número de acertos** e as com o **menor número de acertos**. 
 O código de cada aposta é um número hexadecimal de 128 bits. 

### 💡 Estruturas de Dados Utilizadas

 **Heap Máximo (Max-Heap):** É uma árvore binária onde o valor de cada nó pai é maior ou igual ao valor de seus filhos. É usada para gerenciar e encontrar rapidamente a faixa de apostas com o maior número de acertos.
 **Heap Mínimo (Min-Heap):** É uma árvore binária onde o valor de cada nó pai é menor ou igual ao valor de seus filhos. É usada para gerenciar e encontrar rapidamente a faixa de apostas com o menor número de acertos.

### 📥 Formato da Entrada

1. Valor total do prêmio em reais. 
2. Número de apostas. 
3. Os 10 números sorteados. 
4. Para cada aposta: `[Codigo_Hexadecimal] [Número_1] ... [Número_15]`. 

#### Exemplo de `entrada.txt`
```
3000
5
1 2 3 5 8 13 21 34 38 48
1234567890ABCDEF1234567890ABCDEF 1 2 3 9 11 17 19 20 21 30 34 38 39 40 44
1223334444555556666667777777ABCD 2 3 5 9 13 14 15 17 18 20 33 35 40 41 42
AAAAAABBBBBCCCCCDDDDDEEEEEFFFFFF 1 2 5 8 9 11 15 16 19 21 27 33 35 42 49
0A1B2C3D4E5F6A7B8C9DAEBFCEDFE0F1 3 4 5 7 11 16 18 20 24 25 31 34 35 42 50
F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0 3 4 7 9 15 18 23 24 26 31 32 38 41 43 48
```

### 📤 Formato da Saída Exibe as duas faixas de premiação no formato `[#Ganhadores:#Acertos:Prêmio_Individual]`, seguido pela lista dos códigos das apostas vencedoras em cada faixa. 

#### Exemplo de `saida.txt`
```
[2:6:750.00]
1234567890ABCDEF1234567890ABCDEF
AAAAAABBBBBCCCCCDDDDDEEEEEFFFFFF
[1:2:1500.00]
F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0F0
```

### ⚙️ Como Compilar e Executar

**1. Compilar o código:**
```bash
gcc -Wall -O3 loteria.c -o loteria
```

**2. Executar o programa:**
```bash
./loteria entrada.txt saida.txt
```
---

## 🤝 Rede Social "De Mãos Dadas" (Poxim Tech)

Este projeto simula uma rede social em que os usuários formam um círculo, desenvolvido como exercício para a disciplina de Estruturas de Dados.

### 📄 Descrição do Problema O sistema cria uma rede social com a ideia de unir as pessoas "de mãos dadas", onde cada usuário interage diretamente com seus vizinhos.  As regras são:
 Os nomes de usuários são compostos por até 50 caracteres, contendo exclusivamente letras. 
 Quando um novo usuário é adicionado, ele se torna amigo do primeiro e do último membro da rede, fechando o círculo. 
 Se um usuário é removido, seus antigos vizinhos (amigos) passam a ser amigos entre si, mantendo o círculo intacto. 
 O sistema permite buscar um usuário pelo nome e exibir quem são seus dois amigos. 

### 💡 Estruturas de Dados Utilizadas

* **Lista Duplamente Encadeada Circular:** Essa é a estrutura ideal para o problema A natureza **circular** garante que o último usuário esteja conectado ao primeiro. O encadeamento **duplo**, com ponteiros para o elemento anterior e o próximo, permite a navegação em ambas as direções e torna as operações de remoção eficientes, pois os "vizinhos" do nó removido podem ser facilmente religados. 

### 📥 Formato da Entrada

O programa processa uma série de comandos a partir de um arquivo de entrada:
 `ADD name`: Adiciona um novo usuário ao círculo. 
 `REMOVE name`: Remove um usuário do círculo. 
 `SHOW name`: Mostra os amigos (vizinhos) de um usuário. 

#### Exemplo de `entrada.txt`
```
ADD Jose da Silva
SHOW Jose da Silva
ADD Jose da Silva
ADD Joao dos Santos
ADD Maria da Penha
REMOVE Joao dos Santos
REMOVE Maria da Silva
ADD Alan Turing
SHOW Maria da Penha
SHOW Bruno Prado
```

### 📤 Formato da Saída Para cada operação, o sistema exibe uma mensagem de sucesso (`[SUCCESS]`) ou falha (`[FAILURE]`). Para o comando `SHOW`, o resultado é exibido no formato `Amigo_Anterior<-Usuario->Proximo_Amigo`. 

#### Exemplo de `saida.txt`
```
[SUCCESS] ADD=Jose_da_Silva
[SUCCESS] SHOW=Jose_da_Silva<-Jose_da_Silva->Jose_da_Silva
[FAILURE] ADD=Jose_da_Silva
[SUCCESS] ADD=Joao_dos_Santos
[SUCCESS] ADD=Maria_da_Penha
[SUCCESS] REMOVE=Joao_dos_Santos
[FAILURE] REMOVE=Maria_da_Silva
[SUCCESS] ADD=Alan_Turing
[SUCCESS] SHOW=Jose_da_Silva<-Maria_da_Penha->Alan_Turing
[FAILURE] SHOW=?<-Bruno_Prado->?
```

### ⚙️ Como Compilar e Executar

**1. Compilar o código:**
```bash
gcc -Wall -O3 rede-social.c -o rede-social
```

**2. Executar o programa:**
```bash
./rede-social entrada.txt saida.txt
```