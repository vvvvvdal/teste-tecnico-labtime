#include <iostream>
#include "../include/personagem.hpp"
using namespace std;

int main() {
    
    // Criação do personagem 1
    Personagem per1 = Personagem::criar_personagem();
    per1.print_inventario_personagem();

    // Criação do personagem 2
    Personagem per2 = Personagem::criar_personagem();
    per2.print_inventario_personagem();

    // adicionando um pack (qtd 64) de flecha no inventario do personagem 1 (agora o slot 1 esta cheio com 64 flechas)
    per1.adicionar_item_inventario("Flecha", 64);
    per1.print_inventario_personagem();

    // removendo qtd 20 do slot 1 do personagem 1 (nesse caso, removendo 20 flechas que estao no slot 1, ficando com 44 flechas)
    per1.remover_item_inventario(1, 20);
    per1.print_inventario_personagem();

    // troca o slot 1 com o slot 2 do inventario do personagem 1 (nesse caso, troca 44 flechas com um slot vazio)
    per1.trocar_itens_inventario(1,2);
    per1.print_inventario_personagem();

    // tentativa de remover qtd 10 do slot 1 do personagem 1. com a troca anterior, o slot 1 ficou vazio. gera uma mensagem de erro de slot vazio.
    per1.remover_item_inventario(1,10);
    per1.print_inventario_personagem();

    // tentativa de remover qtd negativa (-10) do slot do personagem 1. gera uma mensagem de erro de qtd invalida.
    per1.remover_item_inventario(1,-10);
    per1.print_inventario_personagem();

    // adicionando 2 espadas ao inventario do personagem 2 (uma espada vai para o slot 1 e a outra vai para o proximo slot, q nesse caso é o 2)
    per2.adicionar_item_inventario("Espada", 2);
    per2.print_inventario_personagem();

    // adicionando qtd 50 de pocao no inventario do personagem 2. adiciona no slot 3, pq os 2 anteriores ja estao ocupados pelas espadas
    per2.adicionar_item_inventario("Pocao", 50);
    per2.print_inventario_personagem();

    // troca os slots 1 e 3 do inventario do personagem 2. nesse caso: troca espada do 1 com pocao do 3.
    per2.trocar_itens_inventario(1,3);
    per2.print_inventario_personagem();

    // troca 2 slots entre os personagens 1 e 2. nesse caso, troca o slot 2 do personagem 1 (44 flechas) com o slot 3 do personagem 2 (espada).
    // funciona exatamente como a função trocar_itens_inventario(), mas entre 2 personagens
    Personagem::trocar_itens_inventario_entre_personagens(per1, per2, 2, 3);

    // imprime o inventario do personagem 1
    per1.print_inventario_personagem();

    // imprime o inventario do personagem 2
    per2.print_inventario_personagem();
    
    return 0;
}