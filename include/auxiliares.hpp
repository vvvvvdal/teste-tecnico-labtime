#pragma once

#include <iostream>
#include <string>
#include "personagem.hpp"

// escopo fechado para as funcoes auxiliares
namespace auxiliares {
    
    constexpr int TAM_MIN_NOME = 3;
    constexpr int TAM_MAX_NOME = 128;
    constexpr int TAM_MIN_INVENTARIO = 6;
    constexpr int TAM_MAX_INVENTARIO = 1000;
    constexpr int TAM_MAX_DIGITOS = 9;

    void formatar_nome(std::string &nome);
    void formatar_posicao(int &posicao);
    int ler_inteiro();
    int ler_tam_max_inventario();
    std::string ler_nome();
    Personagem criar_personagem_menu(int& qtd_personagens);
}