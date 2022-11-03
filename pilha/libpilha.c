#include <stdlib.h>
#include <stdio.h>
#include "libpilha.h"
/* 
 * Cria e retorna uma nova pilha com capacidade de nelem elementos. 
 * Retorna NULL em caso de erro de alocação 
*/
pilha_t* pilha_cria (int nelem){
    pilha_t *p = malloc(sizeof(pilha_t));
    p->elems = (int*)malloc(sizeof(int) * nelem);

    /* confere erro de alocacao */
    if (!(p) || !(p->elems)) return NULL;

    p->topo = -1;
    p->nelem = nelem;
    return p;
}

/* 
 * Insere elem na pilha (politica LIFO). Retorna o número de elementos na pilha 
 * em caso de sucesso e -1 em caso de pilha cheia 
*/
int push (pilha_t* pilha, int elem){
    /* Caso a pilha esteja cheia */
    if (pilha->topo == pilha->nelem - 1) return -1;

    pilha->topo++;
    pilha->elems[pilha->topo] = elem;
    return ((pilha->topo) + 1);
}

/* 
 * Remove (politica LIFO) e retorna um elemento da pilha. 
 * Em caso de pilha vazia retorna 0 
*/
int pop (pilha_t* pilha){
    if (pilha_vazia(pilha) == 1) return 0;

    return pilha->elems[pilha->topo--];
}
 
/* Similar ao Pop, mas retorna sem remover */
int pilha_topo (pilha_t* pilha){
    return pilha->elems[pilha->topo];    
} 

/* Retorna o numero de elementos da pilha, que pode ser 0 */
int pilha_tamanho (pilha_t* pilha){
    return ((pilha->topo) + 1);
}

/* Retorna 1 se pilha vazia, 0 em caso contrario */ 
int pilha_vazia (pilha_t* pilha){
    if (pilha->topo == -1) return 1;
    return 0;
}

/* Desaloca memoria de pilha_t e retorna NULL */
pilha_t* pilha_destroi (pilha_t* pilha){
    free(pilha->elems);
    free(pilha);
    return NULL;
}

/* 
 * Imprime a pilha, da base ate o topo, este por ultimo, sem espaco no final.
 * Quando a pilha estiver vazia, nao imprime nada, nem um \n.
 * Esta funcao eh somente para facilitar teus testes.
 * Normalmente ela nao existe nas implementacoes de um TAD pilha.
*/
void pilha_imprime (pilha_t* pilha){
    if (pilha_vazia(pilha) == 1) return;
    int i = 0;

    while (i < pilha->topo){
        printf("%d ", pilha->elems[i]);
        i++;
    }
    printf("%d", pilha->elems[pilha->topo]);
}
