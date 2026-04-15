#include <iostream>
#include "personagem.hpp"
using namespace std;

int main() {
    Personagem felipe(ler_nome(), ler_tam_max_inventario());
    
    felipe.inventario.adicionar_item("Flecha", 64);
    felipe.inventario.remover_item(1, 20);
    felipe.inventario.remover_item(1,-10);

    felipe.print_inventario_personagem();

    return 0;
}
