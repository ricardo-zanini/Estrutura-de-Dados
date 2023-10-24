#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lse.h"

int main()
{
    PtNoLSE *lse01 = NULL;

    lse01 = insereDados(lse01);

    // Prints de resultados requisitados
    //====================================================================

    if(lse01 != NULL)
    {

        printf("Maior valor: %d", pegaMaior(lse01));
        printf("\n\n");

        printf("Menor valor: %d", pegaMenor(lse01));
        printf("\n\n");

        printf("Valor medio: %f", pegaMedia(lse01));
        printf("\n\n");

        valMaisFrequentes(lse01, 10);

        valMaisFrequentes(lse01, 50);
    }

    return 0;
}


