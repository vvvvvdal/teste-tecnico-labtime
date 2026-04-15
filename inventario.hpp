#pragma once

#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#define OCUPADO 1
#define DESOCUPADO 0
#define POSICAO_INVALIDA 1
#define POSICAO_VALIDA 0
#define SLOT_INVALIDO -1

#include <iostream>
#include <vector>
#include <cstring>
#include "auxiliares.hpp"
#include "item.hpp"
#include "itens.hpp"
using namespace std;

class Inventario{
private:
    vector<Item> slots;
    vector<int> ocupado;
    Itens itens_inventario;
    int tam_max_inventario;

    short int verificar_posicao(int posicao);
    short int verificar_ocupado(int posicao);
    void formatar_posicao(int &posicao);
    void verificar_qtd_negativa(Item &item, int posicao,int qtd);
    
    Item buscar_item(string nome);
    int encontrar_slot_vazio();
    void set_slot(int posicao, Item &item);
    void distribuir_sobra(Item &item_base, int sobra);
    void esvaziar_slot(int posicao);

public:
    Inventario(int tam_max_inventario);
    void print_inventario();
    void adicionar_item(string nome, int qtd);
    void remover_item(int posicao, int qtd);
    void trocar_item(int posicao1, int posicao2);
};

#endif
