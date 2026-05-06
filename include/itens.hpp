#pragma once

#include <array>
#include "item.hpp"

class Itens {
private:
    // array da qtd de itens existentes no programa
    std::array<Item, Item::QTD_ITENS> itens_array; 

public:
    Itens();

    const Item& get_item(int index) const;
};