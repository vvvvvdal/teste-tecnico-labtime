#pragma once

#ifndef ITEM_HPP
#define ITEM_HPP

#define EMPILHAVEL 0
#define NAO_EMPILHAVEL 1
#define TIPO_INVALIDO -1
#define TAM_MAX_UNICO 1
#define TAM_MAX_PILHA 64
#define TAM_NULO 0
#define QTD_ITENS 6
#define QTD_NULA 0

#include <iostream>
#include <array>
using namespace std;

class Item {
private:
    string nome;
    short int tipo;
    int qtd;
    int tam_max;
public:
    Item();
    Item(string nome, short int tipo, int qtd, int tam_max);
    string get_nome();
    short int get_tipo();
    int get_qtd();

    void set_qtd(int quantidade);
};

#endif