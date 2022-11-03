#ifndef _LIBAVL_H_
#define _LIBAVL_H_

//Declarando estrutura do nodo
struct tNo
{
    int chave; //Valor de busca
    int altura; 
    struct tNo *esq, *dir; //Filhos esquerda e direita
};
typedef struct tNo tNo_t;

//Cria Nodo
tNo_t* criaNodo(int chave);

//Devolve a altura do nodo
int getAltura(tNo_t* nodo);

//atualiza a altura do nodo
void atualizaNodo(tNo_t* nodo);

//Calcular Fator de Balanceamento
int getFB(tNo_t* nodo);

//Funcao para encontrar o nodo maximo
tNo_t* maxNodo(tNo_t* nodo);

//Rotacao para esquerda
tNo_t* RotacaoEsq(tNo_t* nodo);

//Rotacao para direita
tNo_t* RotacaoDir(tNo_t* nodo);

//Rotacao para esquerda, direita
tNo_t* RotacaoLeftRight(tNo_t* nodo);

//Rotacao para direita, esquerda
tNo_t* RotacaoRightLeft(tNo_t* nodo);

//Deixa a arvore balanceada novamente
tNo_t* balanceiaAVL(tNo_t* raiz);

//Funcao de insercao
tNo_t* insercao(tNo_t* raiz, int chave);

//Funcao de exclusao
tNo_t* exclusao(tNo_t* raiz, int chave);

//Funcao para destruir a arvore
void destroiAVL(tNo_t* raiz);

//Encontra a altura cobrada no trabalho
int alturaTrab(tNo_t* raiz, tNo_t* nodo, int chave);

int verificaBST(tNo_t* raiz);

//Printa a arvore em-ordem junto com as alturas
void print_in_order(tNo_t* raiz, tNo_t* nodo);

#endif