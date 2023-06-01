#include "liblista_ordenada.h"
#include <stdlib.h>

lista_t *lista_cria()
{
    lista_t *l;

    if (!(l = malloc(sizeof(lista_t))))
        return NULL;

    l->ini = NULL;

    return l;
}

void lista_destroi(lista_t **l)
{
    nodo_t *atual = (*l)->ini;
    nodo_t *temp;

    while (atual != NULL)
    {
        temp = atual;
        atual = atual->prox;
        free(temp->elemento);
        free(temp);
    }

    free(*l);
    *l = NULL;
}

int lista_insere_ordenado(lista_t *l, elemento_t *elemento)
{
    nodo_t *novo;
    nodo_t *aux;

    if (!(novo = malloc(sizeof(nodo_t))))
        return 0;

    novo->elemento = elemento;

    /* Se lista vazia */
    if (l->ini == NULL)
    {
        l->ini = novo;
        novo->prox = NULL;
        return 1;
    }

    /* Se novo for 1 posicao */
    if (novo->elemento->chave < l->ini->elemento->chave)
    {
        novo->prox = l->ini;
        l->ini = novo;
        return 1;
    }
    
    aux = l->ini;

    while (aux->prox != NULL && novo->elemento->chave >
                                aux->prox->elemento->chave)
        aux = aux->prox;

    /* Se novo estiver no meio */
    if (aux->prox != NULL)
    {
        novo->prox = aux->prox;
        aux->prox = novo;
    }
    /* Se novo for ultima posicao */
    else
    {
        aux->prox = novo;
        novo->prox = NULL;
    }

    return 1;
}

int lista_remove_ordenado(lista_t *l, elemento_t *elemento)
{
    nodo_t *temp;
    nodo_t *atual;

    /* Se lista for vazia */
    if (l->ini == NULL)
        return 0;

    /* Se elemento for 1 posicao */
    if (l->ini->elemento->chave == elemento->chave)
    {
        temp = l->ini;
        l->ini = l->ini->prox;
        free(temp->elemento);
        free(temp);
        return 1;
    }

    atual = l->ini;

    while (atual->prox != NULL && atual->prox->elemento->chave != elemento->chave)
        atual = atual->prox;

    /* Se nao achou na lista */
    if (atual->prox == NULL)
        return 0;

    temp = atual->prox;
    atual->prox = atual->prox->prox;
    free(temp->elemento);
    free(temp);

    return 1;
}