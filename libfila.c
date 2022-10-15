#include <stdlib.h>
#include <stdio.h>
#include "libfila.h"

/*
 * Cria uma fila vazia e a retorna, se falhar retorna NULL.
*/
fila_t* fila_cria (){
    /* aloca a fila */
    fila_t* f = malloc(sizeof(fila_t));

    /* testa a validade da alocacao */
    if (!(f)) return NULL;

    /* inicializando os valores da fila */
    f->ini = NULL;
    f->fim = NULL;
    f->tamanho = 0;

    return f;
}

/*
 * Remove todos os elementos da fila, libera espaco e devolve NULL.
*/
fila_t* fila_destroi (fila_t* f){
    /* Como dequeue pede um ponteiro, foi criado um ponteiro aux */
    int* aux = (int*)malloc(sizeof(int));

    /* itera a fila aplicando dequeue em todos os elementos, deixando-a vazia */
    while (f->ini != NULL){
        dequeue(f, aux);
    }

    /* libera o restante de memoria */
    free(aux);

    free(f);
    return NULL;
}

/*
 * Retorna 1 se a fila esta vazia e 0 caso contrario.
*/
int fila_vazia (fila_t* f){
    if (f->ini == NULL) return 1;
    return 0;
}

/*
 * Retorna o tamanho da fila, isto eh, o numero de elementos presentes nela.
*/
int fila_tamanho (fila_t* f){
    return f->tamanho;
}

/*
 * Insere o elemento no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int queue (fila_t* f, int elemento){
    /* cria um novo nodo */
    nodo_f_t *novo = malloc(sizeof(nodo_f_t)); 

    if (!(novo)) return 0;

    novo->chave = elemento;


    if(f->ini == NULL) { /*lista vazia*/
        novo->prox = f->fim;

        f->ini = novo;
        f->fim = novo;
    } else { 
        novo->prox = f->fim->prox;
        f->fim->prox = novo;
        f->fim = novo;
    }
    f->tamanho++;
    return 1;
}

/*
 * Remove elemento do inicio da fila (politica FIFO) e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int dequeue (fila_t* f, int* elemento){
    
    if (f == NULL) return 0;

    /* caso nao esteja vazia */
    if(fila_vazia(f) == 1) return 0; 
        
    nodo_f_t *remover = f->ini;

    *elemento = (int)remover->chave;
       
    f->ini = f->ini->prox;
    f->tamanho--;
    /* caso a fila tenha ficado vazia */
    if(f->ini == NULL)
        f->fim = NULL;
        
    free(remover);
    return 1;
}

/*
 * Imprime a fila, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a fila estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD fila.
*/
void fila_imprime (fila_t* f){
    if (!(f)) return;
    if (fila_vazia(f) == 1) return;

    nodo_f_t *inicio = f->ini;
    /* itera a fila imprimindo elemento por elemento */
    while(inicio != NULL) {
        printf("%d ", inicio->chave);
        inicio = inicio->prox;
    }
    printf("\n");
}


