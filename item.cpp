#include "item.hpp"

Item::Item(string nome, bool empilhavel, int tam_max): nome(nome), empilhavel(empilhavel), tam_max(tam_max) {}

void Item::inicializar_itens() {
    Item espada("Espada", NAO_EMPILHAVEL, TAM_UNICO);
    Item escudo("Escudo", NAO_EMPILHAVEL, TAM_UNICO);
    Item arco("Arco", NAO_EMPILHAVEL, TAM_UNICO);
    Item flecha("Flecha", EMPILHAVEL, TAM_MAX);
    Item pocao("Poção", EMPILHAVEL, TAM_MAX);
    Item tocha("Tocha", EMPILHAVEL, TAM_MAX);
}