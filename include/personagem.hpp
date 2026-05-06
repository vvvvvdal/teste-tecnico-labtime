#pragma once

#include <iostream>
#include <string>
#include "inventario.hpp"

class Personagem {
private:
    std::string nome;
    Inventario inventario;

public:
    Personagem(const std::string& nome, int tam_max_inv);

    const std::string& get_nome() const;
    void print_inventario_personagem() const;

    void adicionar_item_inventario(const std::string& nome_item, int qtd);
    void remover_item_inventario(int posicao, int qtd);
    void trocar_itens_inventario(int posicao1, int posicao2);

    static void trocar_itens_inventario_entre_personagens(Personagem& pers1, Personagem& pers2, int posicao1, int posicao2);

    Inventario& get_inventario();
};