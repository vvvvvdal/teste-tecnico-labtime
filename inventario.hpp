#pragma once

#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#define TAM_MAX_INVENTARIO 10
#define OCUPADO true
#define DESOCUPADO false

#include <iostream>
#include <array>
#include "item.hpp"
#include "inventario.hpp"
using namespace std;

void verificar_posicao_inventario(int &posicao);
void verificar_ocupado_inventario(int &posicao);

class Inventario{
private:
    array<Item,TAM_MAX_INVENTARIO> slots;
    array<bool,TAM_MAX_INVENTARIO> ocupado;
    Itens itens_inventario;
public:
    bool verificar_posicao(int &posicao);
    bool verificar_ocupado(int &posicao);
    void formatar_nome(string &nome);

    void print_inventario();
    void acrescenta_item_empilhavel(Item &novo_item);
    void adicionar_item(int posicao, string nome);
    void remover_item(int posicao);
    void trocar_item(int posicao1, int posicao2);
};

#endif
