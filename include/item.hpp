#pragma once

#include <iostream>
#include <string>

enum class TipoItem {
    Invalido = -1,
    Empilhavel = 0,
    NaoEmpilhavel = 1
};

class Item {
public:
    // constantes de tempo de compilação dentro do escopo da classe
    static constexpr int TAM_MAX_UNICO = 1;
    static constexpr int TAM_MAX_PILHA = 64;
    static constexpr int TAM_NULO = 0;
    static constexpr int QTD_ITENS = 6;
    static constexpr int QTD_NULA = 0;

private:
    std::string nome;
    TipoItem tipo;
    int qtd;
    int tam_max;

public:
    Item();
    
    // passagem de string por referência constante (const &)
    Item(const std::string& nome, TipoItem tipo, int qtd, int tam_max);

    // getters marcados como 'const' para garantir que nao modificam o objeto
    // get_nome retorna const std::string& para evitar cópia da string ao ser chamada
    const std::string& get_nome() const;
    TipoItem get_tipo() const;
    int get_qtd() const;

    void set_qtd(int quantidade);
};