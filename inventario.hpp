#pragma once

#ifndef PERSONAGEM_HPP
#define PERSONAGEM_HPP

#include <iostream>
#include "item.hpp"
using namespace std;

class Inventario: public Item {
private:
    struct No {
        No *proximo;
    };
};

#endif