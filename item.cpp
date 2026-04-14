#include "item.hpp"

Item::Item(): nome("Vazio"), tipo(TIPO_INVALIDO), qtd(QTD_NULA), tam_max(TAM_NULO) {}

Item::Item(string nome, short int tipo, int qtd, int tam_max): nome(nome), tipo(tipo), qtd(QTD_NULA), tam_max(tam_max) {}

string Item::get_nome() {
    return nome;
}

short int Item::get_tipo() {
    return tipo;
}

int Item::get_qtd() {
    return qtd;
}

void Item::set_qtd(int quantidade) {
    qtd = quantidade;
}