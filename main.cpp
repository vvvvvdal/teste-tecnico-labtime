#include <iostream>
#include "inventario.hpp"
using namespace std;

int main() {
    Inventario inv;
    inv.adicionar_item(1, "espada");
    inv.adicionar_item(3, "flecha");
    inv.trocar_item(1,3);

    inv.print_inventario();

    return 0;
}