#include "item.hpp"

Item::Item(): nome("Vazio"), empilhavel(NAO_EMPILHAVEL), qtd(QTD_NULA), tam_max(TAM_NULO) {}

Item::Item(string nome, bool empilhavel, int qtd, int tam_max): nome(nome), empilhavel(empilhavel), qtd(QTD_NULA), tam_max(tam_max) {}

string Item::get_nome() {
    return nome;
}

bool Item::get_empilhavel() {
    return empilhavel;
}

int Item::get_qtd() {
    return qtd;
}

void Item::set_qtd(int quantidade) {
    qtd = quantidade;
}

Itens::Itens() {
    itens[0] = Item("Espada", NAO_EMPILHAVEL, QTD_NULA, TAM_MAX_UNICO);
    itens[1] = Item("Escudo", NAO_EMPILHAVEL, QTD_NULA, TAM_MAX_UNICO);
    itens[2] = Item("Arco", NAO_EMPILHAVEL, QTD_NULA, TAM_MAX_UNICO);
    itens[3] = Item("Flecha", EMPILHAVEL, QTD_NULA, TAM_MAX_PILHA);
    itens[4] = Item("Poção", EMPILHAVEL, QTD_NULA, TAM_MAX_PILHA);
    itens[5] = Item("Tocha", EMPILHAVEL, QTD_NULA, TAM_MAX_PILHA);
}
