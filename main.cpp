#include <iostream>
#include "personagem.hpp"
using namespace std;

int main() {
    int tam_max_inv = get_tam_max_inventario();
    Personagem felipe("Felipe", tam_max_inv);
    
    felipe.inventario.adicionar_item("Flecha", 64);
    felipe.inventario.remover_item(1, 20);
    felipe.inventario.remover_item(1,-10);

    felipe.inventario.print_inventario();

    return 0;
}