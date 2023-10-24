//==================== DECLARAÇÕES DE VARIÁVEIS ======================
//====================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lse.h"


//===================== FUNÇÕES PRINCIPAIS ===========================
//====================================================================


// ----------------------- DADOS DO ARQUIVO --------------------------

PtNoLSE* insereDados(PtNoLSE *lse)
{
    clock_t start, end;
    FILE *entrada;

    char *palavra, linha[1000], arq_ent[] = "dados.txt";
    char separador[]= {" ,.&*%\?!;/-'@\"$#=><()][}{:\n\t"};

    entrada = fopen (arq_ent, "r");
    if (entrada == NULL)
    {
        printf ("Erro ao abrir o arquivo '%s'",arq_ent);
        return NULL;
    }
    else
    {
        start = clock();
        while (fgets(linha,1000,entrada))
        {
            palavra = strtok (linha, separador);
            while (palavra != NULL)
            {
                lse = InsereLSE(lse,atoi(palavra));
                palavra = strtok (NULL, separador);
            }
        }
        end = clock();
        float miliseconds = (float)(end - start) / CLOCKS_PER_SEC * 1000;

        printf("\n\nTempo usado para colocar dados do arquivo na ABP: %.5f ms\n\n",miliseconds);
    }

    fclose (entrada);
    return lse;
}

// ----------------------- INSERÇÃO DOS DADOS ----------------------

PtNoLSE* InsereLSE (PtNoLSE* lse, tipoinfo dados){
       PtNoLSE *novo;
       PtNoLSE *ant = NULL; //ponteiro auxiliar para a posição anterior
       PtNoLSE *ptaux = lse; //ponteiro auxiliar para percorrer a lista

       novo = (PtNoLSE*) malloc(sizeof(PtNoLSE));

       novo->info = dados;

       while ((ptaux!=NULL) && ptaux->info < dados)
       {
             ant = ptaux;
             ptaux = ptaux->prox;
       }

       if (ant == NULL){
               novo->prox = lse;
               lse = novo;
       }
       else{
            novo->prox = ant->prox;
            ant->prox = novo;
       }

       return lse;
}


// ------------------ MAIOR DADO DE UMA LSE -------------------

// dada uma LSE, pega o maior valor encontrado nela
int pegaMaior(PtNoLSE *a)
{
    if(a!=NULL)
    {
        PtNoLSE *ptaux = a;
        int maior_temp;
        maior_temp = ptaux->info;
        ptaux = ptaux->prox;

        while(ptaux != NULL){
            if(ptaux->info > maior_temp){
                maior_temp = ptaux->info;
            }
            ptaux = ptaux->prox;
        }
        return maior_temp;

    }
    return 0; // retorna 0 se a lista esta vazia
}

// ------------------ MENOR DADO DE UMA LSE ----------------------

// dada uma LSE, pega o menor valor encontrado nela
int pegaMenor(PtNoLSE *a)
{
    if(a!=NULL)
    {
        PtNoLSE *ptaux = a;
        int menor_temp;
        menor_temp = ptaux->info;
        ptaux = ptaux->prox;

        while(ptaux != NULL){
            if(ptaux->info < menor_temp){
                menor_temp = ptaux->info;
            }
            ptaux = ptaux->prox;
        }
        return menor_temp;

    }
    return 0; // retorna 0 se a lista esta vazia
}

// ----------------------- SOMA LSE ----------------------

// dada uma LSE, retorna a soma de todos valores nela encontrados
int somaLSE(PtNoLSE *a)
{
    if(a!=NULL)
    {
        return a->info + somaLSE(a->prox); // soma o valor do no com os valores de todos os seus descendentes
    }
    return 0; // retorna 0 se arvore esta vazia
}

// ------------------- CONTAGEM LSE ----------------------

// dada uma LSE, retorna quantos nos ela contem
int countLSE(PtNoLSE *a)
{
    if(a!=NULL)
    {
        return 1 + countLSE(a->prox); // conta o no e mais seus descendentes
    }
    return 0; // retorna 0 se arvore esta vazia
}

// ----------------- MÉDIA DOS VALORES LSE ------------------

// dada uma LSE, pega a media dos valores encontrados nela
float pegaMedia(PtNoLSE *a)
{
    return (float) somaLSE(a) / countLSE(a); // calcula a media aritmetica
}

// ----------------- VALORES MAIS FREQUÊNTES ------------------

// dada uma LSE e um numero inteiro n, printa na tela os n valores que mais aparecem nela
void valMaisFrequentes(PtNoLSE *a, int n)
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







PtNo* cria_lista(void)
{
       return NULL;
}


PtNo* insere_ord (PtNo* l, InfoNo dados){

       PtNo *novo;
       PtNo *ant = NULL; //ponteiro auxiliar para a posição anterior
       PtNo *ptaux = l; //ponteiro auxiliar para percorrer a lista

       novo = (PtNo*) malloc(sizeof(PtNo));

       novo->info = dados;

       while ((ptaux!=NULL) && ptaux->info.v < dados.v)
       {
             ant = ptaux;
             ptaux = ptaux->prox;
       }

       if (ant == NULL){
               novo->prox = l;
               l = novo;
       }
       else{
            novo->prox = ant->prox;
            ant->prox = novo;
       }

       return l;
}

// dada uma ABP e uma lista, salva na lista as frequencias dos valores repetidos da ABP
PtNo* pegaFreq(PtNoLSE *a, PtNo *l)
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
        if(a->prox != NULL){
           l = pegaFreq(a->prox,l);
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
