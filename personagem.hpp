#pragma once

#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <iostream>
#include "inventario.hpp"
using namespace std;

class Personagem {
private:
    string nome;

public:
    Inventario inventario;

    Personagem(string nome, int tam_max_inv);
    void print_inventario_personagem();
};

#endif
