#pragma once

#ifndef ITEM_HPP
#define ITEM_HPP

#define EMPILHAVEL true
#define NAO_EMPILHAVEL false
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
    bool empilhavel;
    int qtd;
    int tam_max;
public:
    Item();
    Item(string nome, bool empilhavel, int qtd, int tam_max);
    string get_nome();
    bool get_empilhavel();
    int get_qtd();

    void set_qtd(int quantidade);
};

class Itens{
public:
    array<Item,6> itens;
    Itens();
};

#endif
