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

    // adicionando 134 flechas no inventario do personagem 1 (indo 64 para o slot 1, 64 para o slot 2 e 6 para o slot 3)
    per1.adicionar_item_inventario("Flecha", 134);
    per1.print_inventario_personagem();

    // removendo qtd 20 do slot 2 do personagem 1 (nesse caso, removendo 20 flechas que estao no slot 2, ficando com 44 flechas)
    per1.remover_item_inventario(2, 20);
    per1.print_inventario_personagem();

    // adicionando 35 flechas no inventario do personagem 1 (indo 20 flechas pro slot 2 e 15 flechas pro slot 3, ficando 64 no slot 2 e 21 no slot 3)
    per1.adicionar_item_inventario("Flecha", 35);

    // troca o slot 1 com o slot 8 do inventario do personagem 1 (nesse caso, troca 44 flechas com um slot vazio)
    per1.trocar_itens_inventario(1,8);
    per1.print_inventario_personagem();

    // adiciona 2 arcos no inventario do personagem 1 (um vai para o slot 1 e um vai para o slot 4)
    per1.adicionar_item_inventario("Arco", 2);
    per1.print_inventario_personagem();

    // tentativa de remover qtd 5 do slot 10 do personagem 1. gera uma mensagem de erro de slot vazio.
    per1.remover_item_inventario(10,5);
    per1.print_inventario_personagem();

    // tentativa de remover qtd negativa (-10) do slot 1 do personagem 1. gera uma mensagem de erro de qtd invalida.
    per1.remover_item_inventario(1,-10);
    per1.print_inventario_personagem();

    // tentativa de remover qtd maior que a existente no slot. por ser um arco (nao empilhavel: somente 1 por slot). gera uma mensagem de erro de qtd invalida.
    per1.remover_item_inventario(1,4);
    per1.print_inventario_personagem();

    // adicionando 2 espadas ao inventario do personagem 2 (uma espada vai para o slot 1 e a outra vai para o proximo slot livre, q nesse caso é o 2)
    per2.adicionar_item_inventario("Espada", 2);
    per2.print_inventario_personagem();

    // adicionando qtd 50 de pocao no inventario do personagem 2. adiciona no slot 3, pq os 2 anteriores ja estao ocupados pelas espadas
    per2.adicionar_item_inventario("Pocao", 50);
    per2.print_inventario_personagem();

    // troca os slots 1 e 3 do inventario do personagem 2. nesse caso: troca espada do slot 1 com pocao do slot 3.
    per2.trocar_itens_inventario(1,3);
    per2.print_inventario_personagem();

    // remove o item espada de tamanho unico (nao empilhavel: somente 1 por slot) do slot 3 do inventario do personagem 2. ficando um slot vazio.
    per2.remover_item_inventario(3, TAM_MAX_UNICO);

    // troca 2 slots entre os personagens 1 e 2. nesse caso, troca o slot 3 do personagem 1 (21 flechas) com o slot 2 do personagem 2 (espada).
    // funciona exatamente como a função trocar_itens_inventario(), mas entre 2 personagens
    Personagem::trocar_itens_inventario_entre_personagens(per1, per2, 3, 2);

    // imprime o inventario do personagem 1
    per1.print_inventario_personagem();

    // imprime o inventario do personagem 2
    per2.print_inventario_personagem();
    
    return 0;
}