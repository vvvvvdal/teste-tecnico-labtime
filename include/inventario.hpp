#pragma once

#include <iostream>
#include <vector>
#include "item.hpp"
#include "itens.hpp"


// struct de um slot
struct Slot {
    Item item; 
    bool ocupado = false; // (desocupado = false, ocupado = true. é inicializado como desocupado)
};

class Inventario {
private:
    static constexpr int SLOT_INVALIDO = -1; // constante de slot invalido
    
    std::vector<Slot> slots;
    Itens itens_inventario;
    int tam_max_inventario;

    void verificar_qtd_negativa(const Item& item, int posicao, int qtd) const;
    
    Item buscar_item(const std::string& nome) const;
    int encontrar_slot_vazio() const;
    void distribuir_sobra(const Item& item_base, int sobra);
    
public:
    Inventario(int tam_max_inventario);
    bool verificar_posicao(int posicao) const;
    bool verificar_ocupado(int posicao) const;
    
    // const Slot& e const Item& para evitar copia de variaveis
    void esvaziar_slot(int posicao);
    void ocupar_slot(const Item& item, int posicao);

    const Slot& get_slot(int posicao) const;
    void set_slot(const Slot& novo_slot, int posicao);
    int get_tam_max_inventario() const;

    void print_inventario() const;
    
    void adicionar_item(const std::string& nome, int qtd);
    void remover_item(int posicao, int qtd);
    void trocar_item(int posicao1, int posicao2);
};