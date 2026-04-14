#pragma once

#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#define TAM_MAX_INVENTARIO 10

#define OCUPADO 1
#define DESOCUPADO 0
#define POSICAO_INVALIDA 1
#define POSICAO_VALIDA 0
#define SLOT_INVALIDO -1

#include <iostream>
#include <array>
#include "auxiliares.hpp"
#include "item.hpp"
#include "itens.hpp"
using namespace std;

class Inventario{
private:
    array<Item,TAM_MAX_INVENTARIO> slots;
    array<int,TAM_MAX_INVENTARIO> ocupado;
    Itens itens_inventario;

    short int verificar_posicao(int posicao);
    short int verificar_ocupado(int posicao);
    void formatar_nome(string &nome);
    void formatar_posicao(int &posicao);

    Item buscar_item(string nome);
    int encontrar_slot_vazio();
    void set_slot(int posicao, Item &item);
    void distribuir_sobra(Item &item_base, int sobra);
    void esvaziar_slot(int posicao);
public:
    Inventario();
    
    void print_inventario();
    void adicionar_item(int posicao, string nome);
    void remover_item(int posicao);
    void trocar_item(int posicao1, int posicao2);
};

#endif