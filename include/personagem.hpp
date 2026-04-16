#pragma once

#include <iostream>
#include "inventario.hpp"
#include "auxiliares.hpp"

class Personagem {
private:
    std::string nome;
    static int qtd_personagens;
public:
    Inventario inventario;
    Personagem(std::string nome, int tam_max_inv);

    static int get_qtd_personagens();
    static Personagem criar_personagem();
    
    std::string get_nome();
    void print_inventario_personagem();
    void adicionar_item_inventario(std::string nome_item, int qtd);
    void remover_item_inventario(int posicao, int qtd);
    void trocar_itens_inventario(int posicao1, int posicao2);

    static void trocar_itens_inventario_entre_personagens(Personagem &pers1, Personagem &pers2);
};