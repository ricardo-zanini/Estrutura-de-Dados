
// ============================ LSE ============================

typedef int tipoinfo;
typedef struct TipoPtNoLSE PtNoLSE;


struct TipoPtNoLSE{
       tipoinfo info;
       PtNoLSE *prox;
};


PtNoLSE* insereDados(PtNoLSE *lse);
PtNoLSE* InsereLSE(PtNoLSE *lse, tipoinfo dados);

int pegaMaior(PtNoLSE *a);
int pegaMenor(PtNoLSE *a);
int somaLSE(PtNoLSE *a);

int countLSE(PtNoLSE *a);
float pegaMedia(PtNoLSE *a);
void valMaisFrequentes(PtNoLSE *a, int n);



//====================== LSE para frequências ======================

typedef struct TipoInfoNo InfoNo;
typedef struct TipoPtNo PtNo;

struct TipoInfoNo{
       int v;
       int freq;
};

struct TipoPtNo{
       InfoNo info;
       PtNo *prox;
};

PtNo* cria_lista(void);
PtNo* insere_ord (PtNo *l, InfoNo dados);
PtNo* pegaFreq(PtNoLSE *a, PtNo *l);
PtNo* buscaLista(PtNo *l, int info);
PtNo* remover(PtNo* l, int v);
PtNo* maiorLista(PtNo *l);
