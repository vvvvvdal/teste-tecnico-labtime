#pragma once

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

class Item {
private:
    std::string nome;
    short int tipo; // empilhavel ou nao empilhavel
    int qtd;
    int tam_max; // 64 se for empilhavel ou 1 se for nao empilhavel
public:
    Item();
    Item(std::string nome, short int tipo, int qtd, int tam_max);
    std::string get_nome();
    short int get_tipo();
    int get_qtd();

    void set_qtd(int quantidade);
};