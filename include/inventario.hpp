#pragma once

#define OCUPADO 1
#define DESOCUPADO 0
#define POSICAO_INVALIDA 1
#define POSICAO_VALIDA 0
#define SLOT_INVALIDO -1

#include <iostream>
#include <vector>
#include <cstring>
#include "auxiliares.hpp"
#include "item.hpp"
#include "itens.hpp"

// struct de um slot
typedef struct {
    Item item; // item (existente ou vazio)
    int ocupado; // ocupado (ocupado ou desocupado)
} Slot;

class Inventario{
private:
    std::vector<Slot> slots; // vetor da struct Slot
    Itens itens_inventario;
    int tam_max_inventario; // tamanho maximo do inventario escolhido pelo usuario (entre TAM_MIN_INVENTARIO e TAM_MAX_INVENTARIO)
    
    void verificar_qtd_negativa(Item &item, int posicao,int qtd);
    
    Item buscar_item(std::string nome);
    int encontrar_slot_vazio();
    void distribuir_sobra(Item &item_base, int sobra);
    
public:
    Inventario(int tam_max_inventario);

    short int verificar_posicao(int posicao);
    short int verificar_ocupado(int posicao);
    void esvaziar_slot(int posicao);
    void ocupar_slot(Item &item, int posicao);

    Slot get_slot(int posicao);
    void set_slot(Slot &novo_slot, int posicao);
    int get_tam_max_inventario();

    void print_inventario();
    void adicionar_item(std::string nome, int qtd);
    void remover_item(int posicao, int qtd);
    void trocar_item(int posicao1, int posicao2);
};