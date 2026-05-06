#include "../include/auxiliares.hpp"
#include <cctype>
#include <cstdlib>

using namespace std;

namespace auxiliares {

    // formata o nome para o modelo: primeira letra de cada palavra maiuscula e o resto minuscula
    void formatar_nome(string &nome) {
        for(size_t i = 0; i < nome.length(); i++) {
            if(i == 0 || nome[i-1] == ' ') {
                nome[i] = toupper(nome[i]);
            } else {
                nome[i] = tolower(nome[i]);
            }
        }
    }

    // formata a posicao do slot (diminui 1 para ser usado em arrays que tem o primeiro índice como 0)
    void formatar_posicao(int &posicao) {
        posicao -= 1;
    }

    // le um inteiro. repete a leitura se for um tipo diferente
    int ler_inteiro() {
        string entrada;
        int qtd;
        
        while(true) {
            getline(cin, entrada);

            if(cin.eof()) {
                cout << endl << endl << "fim da leitura do arquivo teste.txt" << endl;
                exit(0); 
            }
            
            // length() retorna size_t. entao TAM_MAX_DIGITOS eh convertido para esse mesmo formato, para garantir que a comparacao ocorra sem problemas.
            if (entrada.length() > static_cast<size_t>(TAM_MAX_DIGITOS)) {
                cout << endl << "numero muito grande." << endl;
                cout << "digite novamente." << endl;
                continue;
            }

            bool eh_int = true;
            for(char c : entrada) { // loop q percore toda a entrada. para se encontrar um caractere diferente de numero.
                if(!isdigit(c)) {
                    eh_int = false;
                    break;
                }
            }
            
            // previne que uma entrada vazia passe pelo teste antes de tentar o stoi
            if(eh_int && !entrada.empty()) {
                qtd = stoi(entrada);
                return qtd;
            } else {
                cout << endl << "o numero digitado foi invalido. deve ser digitado um numero inteiro maior que 0." << endl;
                cout << "digite novamente." << endl;
            }
        }
    }

    // le o tamanho maximo do inventario
    int ler_tam_max_inventario() {
        int tamanho;
        
        while(true) {
            cout << "digite o tamanho maximo do inventario (min " << TAM_MIN_INVENTARIO << ", max " << TAM_MAX_INVENTARIO << "): ";
            tamanho = ler_inteiro();
            
            if(tamanho >= TAM_MIN_INVENTARIO && tamanho <= TAM_MAX_INVENTARIO) {
                break;
            }

            cout << endl << "o tamanho minimo eh " << TAM_MIN_INVENTARIO << " e o maximo eh " << TAM_MAX_INVENTARIO << "." << endl;
            cout << "digite novamente." << endl;
        }

        return tamanho;
    }

    // le um nome. repete a leitura se fugir do escopo de letras, espaco ou virgula
    string ler_nome() {
        string nome;

        while(true) {
            cout << "digite o nome: ";
            getline(cin, nome);

            if(cin.eof()) {
                cout << endl << endl << "fim da leitura do arquivo teste.txt" << endl;
                exit(0); 
            }

            if(nome.length() > static_cast<size_t>(TAM_MAX_NOME)) {
                cout << endl << "nome muito grande." << endl;
                cout << "digite novamente." << endl;
                continue;

            } else if(nome.length() < static_cast<size_t>(TAM_MIN_NOME)) {
                cout << endl << "nome muito pequeno." << endl;
                cout << "digite novamente." << endl;
                continue;
            }

            bool eh_palavra = true;

            for(char c : nome) { // loop q percorre todo o nome. para se encontrar caractere diferente de letra, espaco ou virgula.
                if(!isalpha(c) && c != ' ' && c != ',') {
                    cout << endl << "somente letras sao permitidas no nome." << endl;
                    cout << "digite novamente." << endl;

                    eh_palavra = false;
                    break;
                }
            }

            if(eh_palavra) {
                formatar_nome(nome);
                return nome;
            }
        }
    }

    // funcao que cria um novo personagem.
    Personagem criar_personagem_menu(int& qtd_personagens) {
        if(qtd_personagens % 2 == 1) cout << endl;

        cout << "-<- Criacao do Personagem " << qtd_personagens + 1 << " ->-" << endl;

        cout << "Digite a seguir o nome do seu personagem" << endl;
        string nome_personagem = auxiliares::ler_nome();

        cout << "Digite a seguir o tamanho do inventario do seu personagem" << endl;
        int tam_inventario_personagem = auxiliares::ler_tam_max_inventario();

        qtd_personagens++; 
        
        return Personagem(nome_personagem, tam_inventario_personagem);
    }
}