#include "../include/itens.hpp"

// construtor padrao: inicializa os itens existentes no programa
Itens::Itens() {
    itens_array[0] = Item("Espada", TipoItem::NaoEmpilhavel, Item::QTD_NULA, Item::TAM_MAX_UNICO);
    itens_array[1] = Item("Escudo", TipoItem::NaoEmpilhavel, Item::QTD_NULA, Item::TAM_MAX_UNICO);
    itens_array[2] = Item("Arco", TipoItem::NaoEmpilhavel, Item::QTD_NULA, Item::TAM_MAX_UNICO);
    itens_array[3] = Item("Flecha", TipoItem::Empilhavel, Item::QTD_NULA, Item::TAM_MAX_PILHA);
    itens_array[4] = Item("Pocao", TipoItem::Empilhavel, Item::QTD_NULA, Item::TAM_MAX_PILHA);
    itens_array[5] = Item("Tocha", TipoItem::Empilhavel, Item::QTD_NULA, Item::TAM_MAX_PILHA);
}

// retorna o item da lista usando referencia constante para evitar copias
const Item& Itens::get_item(int index) const {
    // a funcao 'at()' garante protecao contra indices fora do tamanho do array
    return itens_array.at(index); 
}