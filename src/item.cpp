#include "../include/item.hpp"
using namespace std;

// construtor padrão: inicializa um item do tipo vazio
Item::Item(): nome("Vazio"), tipo(TIPO_INVALIDO), qtd(QTD_NULA), tam_max(TAM_NULO) {}

// construtor: inicializa um item comum
Item::Item(string nome, short int tipo, int qtd, int tam_max): nome(nome), tipo(tipo), qtd(QTD_NULA), tam_max(tam_max) {}

// retorna o nome do item
string Item::get_nome() {
    return nome;
}

// retorna o tipo do item (empilhavel ou nao empilhavel)
short int Item::get_tipo() {
    return tipo;
}

// retorna a quantidade do item
int Item::get_qtd() {
    return qtd;
}

// define a quantidade do item
void Item::set_qtd(int quantidade) {
    qtd = quantidade;
}