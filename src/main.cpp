#include <iostream>
#include "../include/personagem.hpp"
using namespace std;

int main() {
    Personagem per1 = Personagem::criar_personagem();
    per1.print_inventario_personagem();

    Personagem per2 = Personagem::criar_personagem();
    per2.print_inventario_personagem();

    per1.adicionar_item_inventario("Flecha", 64);
    per1.remover_item_inventario(1, 20);
    per1.remover_item_inventario(1,-10);

    per2.adicionar_item_inventario("Espada", 2);
    per2.adicionar_item_inventario("Pocao", 50);
    per2.trocar_itens_inventario(1,3);

    Personagem::trocar_itens_inventario_entre_personagens(per1, per2);

    per1.print_inventario_personagem();
    per2.print_inventario_personagem();
    
    return 0;
}