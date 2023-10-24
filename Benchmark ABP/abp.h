// ABP
typedef int tipoinfo;
typedef struct TNodoA pNodoA;

struct TNodoA{
        tipoinfo info;
        struct TNodoA *esq;
        struct TNodoA *dir;
};

pNodoA* insereDados(pNodoA *arv1);
pNodoA* InsereArvore(pNodoA *a, tipoinfo ch);
void preFixadoE(pNodoA *a);
int pegaMaior(pNodoA *a);
int pegaMenor(pNodoA *a);
int somaABP(pNodoA *a);
int countABP(pNodoA *a);
float pegaMedia(pNodoA *a);
void valMaisFrequentes(pNodoA *a, int n);

//Lista Simplesmente Encadeada

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
PtNo* pegaFreq(pNodoA *a, PtNo *l);
PtNo* buscaLista(PtNo *l, int info);
PtNo* remover(PtNo* l, int v);
PtNo* maiorLista(PtNo *l);
