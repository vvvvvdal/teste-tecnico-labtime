#pragma once

#define EMPILHAVEL true
#define NAO_EMPILHAVEL false
#define TAM_UNICO 1
#define TAM_MAX 64

#include <iostream>
using namespace std;

class Item {
private:
    string nome;
    bool empilhavel;
    int tam_max;
public:
    Item(string nome, bool empilhavel, int tam_max);
    void inicializar_itens();
};