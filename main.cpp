#include <iostream>
#include "inventario.hpp"
#include "item.hpp"
using namespace std;

int main() {
    Inventario inv;
    inv.adicionar_item(1, "espada");
    inv.adicionar_item(3, "flecha");
    inv.print_inventario();

    return 0;
}
