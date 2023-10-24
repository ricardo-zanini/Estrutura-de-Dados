#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "abp.h"

int main()
{
    pNodoA *arv1 = NULL;

    arv1 = insereDados(arv1);

    // Prints de resultados requisitados
    //====================================================================

    if(arv1 != NULL)
    {
        printf("--Pre Esquerda --\n");
        preFixadoE(arv1);
        printf("\n\n");

        printf("Maior valor: %d", pegaMaior(arv1));
        printf("\n\n");

        printf("Menor valor: %d", pegaMenor(arv1));
        printf("\n\n");

        printf("Valor medio: %f", pegaMedia(arv1));
        printf("\n\n");

        valMaisFrequentes(arv1, 10);

        valMaisFrequentes(arv1, 50);
    }

    return 0;
}


