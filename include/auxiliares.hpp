#pragma once

#define TAM_MIN_NOME 3
#define TAM_MAX_NOME 128
#define TAM_MIN_INVENTARIO 6
#define TAM_MAX_INVENTARIO 1000
#define TAM_MAX_DIGITOS 9

#include <iostream>
#include <limits>

void formatar_posicao(int &posicao);
int ler_inteiro();
int ler_tam_max_inventario();
void formatar_nome(std::string &nome);
std::string ler_nome();