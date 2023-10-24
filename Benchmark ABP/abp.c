#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "abp.h"

//ABP
//====================================================================

// insere dados do arquivo de dados em uma ABP
pNodoA* insereDados(pNodoA *arv1)
{
    clock_t start, end; //para contar o tempo decorrido

    // Coleta dos dados do arquivo de dados
    //====================================================================

    FILE *entrada;

    char *palavra, linha[1000], arq_ent[] = "dados.txt"; // linhas a serem lidas do arquivo
    char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    entrada = fopen (arq_ent, "r"); // abre o arquivo para leitura
    if (entrada == NULL) //se nao conseguiu abrir o arquivo
    {
        printf ("Erro ao abrir o arquivo '%s'",arq_ent);
        return NULL;
    }
    else // arquivo de entrada OK
    {
        start = clock(); //inicia a contagem do tempo

        //percorre todo o arquivo lendo linha por linha
        while (fgets(linha,1000,entrada))
        {
            palavra = strtok (linha, separador); //considera qualquer caractere nao alfabetico como separador
            while (palavra != NULL)
            {
                arv1 = InsereArvore(arv1,atoi(palavra));
                palavra = strtok (NULL, separador);
            }
        }

        end = clock(); // finaliza contagem do tempo
        float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000; //calcula o tempo decorrido
        printf("\n\nTempo usado para colocar dados do arquivo na ABP: %.5f ms\n\n",miliseconds);
    }
    fclose (entrada); //fecha o arquivo

    return arv1;
}

// insere um no em uma arvore ABP
pNodoA* InsereArvore(pNodoA *a, tipoinfo ch)
{
     if (a == NULL)
     {
         a =  (pNodoA*) malloc(sizeof(pNodoA));
         a->info = ch;
         a->esq = NULL;
         a->dir = NULL;
         return a;
     }
     else
          if (ch < a->info)
              a->esq = InsereArvore(a->esq,ch);
          else
              a->dir = InsereArvore(a->dir,ch);
     return a;
}

// gera o caminhamento pre-fixado a esquerda de uma ABP
void preFixadoE(pNodoA *a)
{
     if (a!= NULL)
     {
          printf("%d - ",a->info);
          preFixadoE(a->esq);
          preFixadoE(a->dir);
      }
}

// dada uma ABP, pega o maior valor encontrado nela
int pegaMaior(pNodoA *a)
{
    if(a!=NULL)
    {
        if(a->dir == NULL)
        {
            return a->info; // o maior valor da ABP e o vertice folha mais a direita da arvore
        }
        else{
            return pegaMaior(a->dir);
        }
    }
    return 0; // retorna 0 se arvore esta vazia
}

// dada uma ABP, pega o menor valor encontrado nela
int pegaMenor(pNodoA *a)
{
    if(a!=NULL)
    {
        if(a->esq == NULL)
        {
            return a->info; // o menor valor da ABP e o vertice folha mais aesquerda da arvore
        }
        else{
            return pegaMenor(a->esq);
        }
    }
    return 0; // retorna 0 se arvore esta vazia
}

// dada uma ABP, retorna a soma de todos valores nela encontrados
int somaABP(pNodoA *a)
{
    if(a!=NULL)
    {
        return a->info + somaABP(a->esq) + somaABP(a->dir); // soma o valor do no com os valores de todos os seus descendentes
    }
    return 0; // retorna 0 se arvore esta vazia
}

// dada uma ABP, retorna quantos nos ela contem
int countABP(pNodoA *a)
{
    if(a!=NULL)
    {
        return 1 + countABP(a->esq) + countABP(a->dir); // conta o no e mais seus descendentes
    }
    return 0; // retorna 0 se arvore esta vazia
}

// dada uma ABP, pega a media dos valores encontrados nela
float pegaMedia(pNodoA *a)
{
    return (float) somaABP(a) / countABP(a); // calcula a media aritmetica
}

// dada uma ABP e um numero inteiro n, printa na tela os n valores que mais aparecem nela
void valMaisFrequentes(pNodoA *a, int n)
{
    PtNo *l, *aux;
    l = cria_lista();
    l = pegaFreq(a,l);
    int c;
    printf("\n%d valores mais frequentes:\n\n", n);
    for(c = 1; c <= n; c++)
    {
        aux = maiorLista(l);
        if(aux != NULL)
        {
            printf("%d) %d\n\n", c, aux->info.v);
            l = remover(l,aux->info.v);
        }
        else{
            printf("%d) --\n\n", c);
        }
    }
}

//Lista Simplesmente Encadeada
//====================================================================

// cria uma lista simplesmente encadeada
PtNo* cria_lista(void)
{
       return NULL;
}

// insere os dados de forma ordenada na lista simplesmente encadeada
PtNo* insere_ord (PtNo* l, InfoNo dados)
{
       PtNo *novo; //novo elemento
       PtNo *ant = NULL; //ponteiro auxiliar para a posição anterior
       PtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista

       /*aloca um novo nodo */
       novo = (PtNo*) malloc(sizeof(PtNo));

       /*insere a informação no novo nodo*/
       novo->info = dados;


       /*procurando a posição de inserção*/
       while ((ptaux!=NULL) && ptaux->info.v < dados.v) //se info.titulo < dados.titulo então strcmp retorna um valor menor que zero
       {
             ant = ptaux;
             ptaux = ptaux->prox;
       }

       /*encaeia o elemento*/
       if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
       {
             //  puts("inserindo primeiro");
               novo->prox = l;
               l = novo;
       }
       else /*elemento inserido no meio da lista*/
       {
            novo->prox = ant->prox;
            ant->prox = novo;
       }

       return l;
}

// dada uma ABP e uma lista, salva na lista as frequencias dos valores repetidos da ABP
PtNo* pegaFreq(pNodoA *a, PtNo *l)
{
    PtNo* aux;
    InfoNo dados;

    if(a!=NULL)
    {
        aux = buscaLista(l, a->info);
        if(aux != NULL)
        {
            aux->info.freq++; //se ja estiver na lista, aumenta o contador de repeticoes
        }
        else{
            dados.freq = 1;
            dados.v = a->info;
            l = insere_ord(l,dados); // se nao estiver na lista, deve ser inserido
        }
        if(a->esq != NULL)
        {
           l = pegaFreq(a->esq,l);
        }
        if(a->dir != NULL)
        {
           l = pegaFreq(a->dir,l);
        }
    }
    return l;
}

// dada uma lista e um valor, retorna o no que contem esse valor
PtNo* buscaLista(PtNo *l, int info)
{
    PtNo* aux = l;

    while(aux!=NULL){
        if(aux->info.v == info)
        {
            return aux;
        }
        else{
            aux = aux->prox;
        }
    }
    return NULL;
}

// remove um no de uma lista simplesmente encadeada
PtNo* remover(PtNo* l, int v)
{
     PtNo *ant = NULL; //ponteiro auxiliar para a posição anterior
     PtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista

     /*procura o elemento na lista*/
     while (ptaux != NULL && ptaux->info.v != v)
     {
          ant = ptaux;
          ptaux = ptaux->prox;
     }

     /*verifica se achou*/
     if (ptaux == NULL)
       return l; /*retorna a lista original*/

    if (ant == NULL) /*vai remover o primeiro elemento*/
      l = ptaux->prox;
    else /*vai remover do meio ou do final*/
      ant->prox = ptaux->prox;

    free(ptaux); /*libera a memória alocada*/

    return l;
}

// dada uma lista, retorna o no com maior parametro 'frequencia'
PtNo* maiorLista(PtNo *l)
{
    PtNo *aux1 = l, *aux2 = l;

    while(aux1!=NULL){
        if(aux1->info.freq > aux2->info.freq)
        {
            aux2 = aux1;
        }
        aux1 = aux1->prox;
    }
    return aux2;
}
