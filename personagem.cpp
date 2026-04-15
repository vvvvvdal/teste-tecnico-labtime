#include "personagem.hpp"

Personagem::Personagem(string nome, int tam_max_inv): nome(nome), inventario(tam_max_inv) {}

void Personagem::print_inventario_personagem() {
    cout<<endl<<"Inventario de "<<nome<<":";
    inventario.print_inventario();
}
