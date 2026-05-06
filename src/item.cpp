#include "../include/item.hpp"

using namespace std;

// construtor padrão: inicializa usando as constantes da classe e o enum
Item::Item(): nome("Vazio"), tipo(TipoItem::Invalido), qtd(Item::QTD_NULA), tam_max(Item::TAM_NULO) {}

// construtor: inicializa um item comum
Item::Item(const string& nome, TipoItem tipo, int qtd, int tam_max): nome(nome), tipo(tipo), qtd(qtd), tam_max(tam_max) {}

// retorna o nome por referência constante
const string& Item::get_nome() const {
    return nome;
}

// retorna o tipo do item
TipoItem Item::get_tipo() const {
    return tipo;
}

// retorna a quantidade do item
int Item::get_qtd() const {
    return qtd;
}

// define a quantidade do item
void Item::set_qtd(int quantidade) {
    qtd = quantidade;
}