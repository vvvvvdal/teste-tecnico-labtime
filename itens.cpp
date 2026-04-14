#include "itens.hpp"

Itens::Itens() {
    itens[0] = Item("Espada", NAO_EMPILHAVEL, QTD_NULA, TAM_MAX_UNICO);
    itens[1] = Item("Escudo", NAO_EMPILHAVEL, QTD_NULA, TAM_MAX_UNICO);
    itens[2] = Item("Arco", NAO_EMPILHAVEL, QTD_NULA, TAM_MAX_UNICO);
    itens[3] = Item("Flecha", EMPILHAVEL, QTD_NULA, TAM_MAX_PILHA);
    itens[4] = Item("Pocao", EMPILHAVEL, QTD_NULA, TAM_MAX_PILHA);
    itens[5] = Item("Tocha", EMPILHAVEL, QTD_NULA, TAM_MAX_PILHA);
}