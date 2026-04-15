#pragma once

#ifndef AUXILIARES_HPP
#define AUXILIARES_HPP

#define TAM_MAX_NOME 128
#define TAM_MIN_INVENTARIO 6
#define TAM_MAX_INVENTARIO 1000
#define TAM_MAX_DIGITOS 9

#include <iostream>
#include <limits>
using namespace std;

void limpar_buffer_entrada();
int ler_inteiro();
int ler_tam_max_inventario();
void formatar_nome(string &nome);
string ler_nome();

#endif
