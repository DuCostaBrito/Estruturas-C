#include <stdio.h>
#include <stdlib.h>
#include "libavl.h"

//Funcao interna para auxiliar (retorna o maior inteiro)
int maximo(int n1, int n2){
    if (n1 > n2) return n1;
    return n2;
}

//Funcao inicializadora de nodo
tNo_t* criaNodo(int chave){
    tNo_t* nodo = (tNo_t*)malloc(sizeof(tNo_t));
    nodo->chave = chave;
    nodo->esq = NULL;
    nodo->dir = NULL;
    nodo->altura = 0; //Vamos considerar as folhas como altura == 0
    return nodo;
} 

//Devolve a altura do nodo
int getAltura(tNo_t* nodo){
    if (nodo == NULL) return -1;
    return 1 + maximo(getAltura(nodo->esq), getAltura(nodo->dir));
}

//Calcula o Fator de Balaceamento
int getFB(tNo_t* nodo){
    if (nodo == NULL) return 0;
    return getAltura(nodo->dir) - getAltura(nodo->esq);
}

void atualizaNodo(tNo_t* nodo){
    nodo->altura = getAltura(nodo);
}

//Funcao para encontrar o nodo maximo, sera usada
//para encontrar o antecessor do nodo a ser excluido
tNo_t* maxNodo(tNo_t* nodo){
    while (nodo->dir != NULL) nodo = nodo->dir;
    return nodo;
}

// Rotacao para direita
tNo_t* RotacaoDir(tNo_t* nodo){
    tNo_t* filho = nodo->esq;
    tNo_t* neto = filho->dir;

    filho->dir = nodo;
    nodo->esq = neto;

    //Ajustando as alturas
    atualizaNodo(nodo);
    atualizaNodo(filho);
    
    return filho;
}

// Rotacao para esquerda
tNo_t* RotacaoEsq(tNo_t* nodo){
    tNo_t* filho = nodo->dir;
    tNo_t* neto = filho->esq;

    nodo->dir = neto;
    filho->esq = nodo;

    //Ajustando as alturas
    atualizaNodo(nodo);
    atualizaNodo(filho);
    
    return filho;
}

//Rotacao esquerda, direita
tNo_t* RotacaoLeftRight(tNo_t* nodo){
    nodo->esq = RotacaoEsq(nodo->esq);
    return RotacaoDir(nodo);
}

//Rotacao direita, esquerda
tNo_t* RotacaoRightLeft(tNo_t* nodo){
    nodo->dir = RotacaoDir(nodo->dir);
    return RotacaoEsq(nodo);
}

//Funcao para rebalancear a arvore AVL
tNo_t* balanceiaAVL(tNo_t* raiz){
    //Calcular os FB da raiz e de seus filhos
    int pai_FB = getFB(raiz);
    int esq_FB = getFB(raiz->esq);
    int dir_FB = getFB(raiz->dir);

    //Temos que rotacionar de acordo com os diferentes casos
    
    //Caso: Rotacao esquerda, esquerda
    if (pai_FB < -1 && esq_FB <= 0)
        return RotacaoDir(raiz);

    //Caso: Rotacao direita, direita
    if (pai_FB > 1 && dir_FB >= 0)
        return RotacaoEsq(raiz);

    //Caso: Rotacao esquerda, direita
    if (pai_FB < -1 && esq_FB > 0)
        return RotacaoLeftRight(raiz);
    
    //Caso: Rotacao direita, esquerda
    if (pai_FB > 1 && dir_FB < 0)
        return RotacaoRightLeft(raiz);

    //Nodo tem FB igual a -1, 0 ou +1. O que esta correto
    return raiz;
}

//Funcao de insercao
tNo_t* insercao(tNo_t* raiz, int chave){
    //Caso base
    if (raiz == NULL) return criaNodo(chave);

    //Achando o lugar apropriado para inserir o nodo(BST )
    if (chave < raiz->chave)
        raiz->esq = insercao(raiz->esq, chave);
    else if (chave >= raiz->chave)
        raiz->dir = insercao(raiz->dir, chave);

    //Ajustando as alturas
    atualizaNodo(raiz);

    //Rebalanceia a arvore
    return balanceiaAVL(raiz);
}

//Funcao de exclusao
tNo_t* exclusao(tNo_t* raiz, int chave){
    //Caso base
    if (raiz == NULL) return raiz;

    //Vamos achar o nodo a ser excluido (algoritmo de busca)
    if (chave < raiz->chave)
        raiz->esq = exclusao(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = exclusao(raiz->dir, chave);
    //Achamos o nodo
    else{
        //Caso: nodo com 1 filho ou nenhum
        if (raiz->esq == NULL){
            tNo_t* nodo_aux = raiz->dir;
            free(raiz);
            return nodo_aux;
        } else if (raiz->dir == NULL){
            tNo_t* nodo_aux = raiz->esq;
            free(raiz);
            return nodo_aux;
        } else {
            //Caso: nodo com 2 filhos
            //Neste caso, vamos trocar os valores do antecessor com o nodo a ser excluido
            //e chamar a funcao novamente para excluir o sucessor

            //Pegado o nodo antecessor (menor valor na sub-arvore da direita)
            tNo_t* nodo_antecessor = maxNodo(raiz->esq);

            
            raiz->chave = nodo_antecessor->chave;
            // Chamando a funcao novamente para o sucessor 
            //(chamamos para raiz->chave, pois eles tem a mesma chave agora)
            raiz->esq = exclusao(raiz->esq, raiz->chave);
        }
    }
    
    //Ajustando as alturas
    atualizaNodo(raiz);

    //Rebalanceia a arvore AVL
    return balanceiaAVL(raiz);
}

//Funcao para destruir a arvore
void destroiAVL(tNo_t* raiz){
    if (raiz == NULL) return;
    
    destroiAVL(raiz->esq);
    destroiAVL(raiz->dir);
    free(raiz);
}

//Encontra a altura cobrada no trabalho
int alturaTrab(tNo_t* raiz, tNo_t* nodo, int chave){
    if (nodo == NULL) return 0;
    if (chave > nodo->chave) 
        return 1 + alturaTrab(raiz, nodo->dir, chave);
    else if (chave < nodo->chave)
        return 1 + alturaTrab(raiz, nodo->esq, chave);
    else 
        return 0;
}

int verificaBST(tNo_t* raiz){
    if (raiz == NULL) return 1; //retorna TRUE
    if (raiz->chave < raiz->esq->chave || raiz->chave > raiz->dir->chave) return 0; //retorna False
    return verificaBST(raiz->esq) + verificaBST(raiz->dir);
}

//Printa a arvore em-ordem juntos com as alturas
void print_in_order(tNo_t* raiz, tNo_t* nodo){
    if(nodo == NULL) return;
    print_in_order(raiz, nodo->esq);
    printf("%d,%d\n", nodo->chave, alturaTrab(raiz, raiz, nodo->chave));
    print_in_order(raiz, nodo->dir);
}