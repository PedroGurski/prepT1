#include "liblista_ordenada.h"
#include <stdlib.h>
/*
 * Cria uma Lista vazia
 */
lista_t *lista_cria()
{
    lista_t *l;

    if (!(l = malloc(sizeof(lista_t))))
        return NULL;

    l->ini = NULL;

    return l;
}

/*
 * Destroi a Lista e a aponta para NULL
 */
void lista_destroi(lista_t **l)
{
    if (l != NULL && *l != NULL)
    {
        nodo_t *atual = (*l)->ini;
        while (atual != NULL)
        {
            nodo_t *prox = atual->prox;
            free(atual->elemento);
            free(atual);
            atual = prox;
        }
        free(*l);
        *l = NULL;
    }
}

/*
 * Adiciona um elemento em ordem de acordo com o valor elemento->chave na Lista.
 * Retorna 1 em caso de sucesso e 0 caso contrario.
 */
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
    }
    else
    {
        /* Se novo for 1 posicao */
        if (novo->elemento->chave < l->ini->elemento->chave)
        {
            novo->prox = l->ini;
            l->ini = novo;
        }
        else
        {
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
        }
    }

    return 1;
}

/*
 * Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista.
 */
int lista_remove_ordenado(lista_t *l, elemento_t *elemento)
{
    nodo_t *aux;
    nodo_t *atual;

    /* Se lista vazia */
    if (l->ini == NULL)
        return 0;
    else
    {
        /* Se remover for 1 posicao */
        if (l->ini->elemento->chave == elemento->chave)
        {
            aux = l->ini;
            l->ini = aux->prox;
        }
        else
        {
            atual = l->ini;

            while (atual->prox != NULL && elemento->chave > atual->prox->elemento->chave)
                atual = atual->prox;

            if (atual->prox == NULL && elemento->chave > atual->elemento->chave)
                return 0;
            /* Verifica se o elemento existe na lista */
            else if (atual->prox->elemento->chave == elemento->chave)
            {
                aux = atual->prox;
                atual->prox = aux->prox;
            }
            else
                return 0;
        }
        free(aux);
    }

    return 1;
}
