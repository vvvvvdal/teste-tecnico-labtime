#include "../include/auxiliares.hpp"
using namespace std;

// formata a posicao do slot -> no código: 0 a tamanho do inventario, na execução do usuario: 1 a tamanho do inventario
void formatar_posicao(int &posicao) {
    posicao -= 1;
}

// lê um inteiro. repete a leitura se for um tipo diferente de inteiro (char, string, float)
int ler_inteiro() {
    string entrada;
    int qtd;
    
    while(true) {
        getline(cin, entrada);

        if(cin.eof()) {
            cout<<endl<<endl<<"Fim da leitura do arquivo teste.txt"<<endl;
            exit(0); 
        }
        
        if (entrada.length() > TAM_MAX_DIGITOS) {
            cout<<endl<<"Numero muito grande." << endl;
            cout<<"Digite novamente."<<endl;

            continue;
        }

        bool eh_int = true;
        for(int i=0; i<entrada.length(); i++) {
            if(!isdigit(entrada[i])) {
                eh_int = false;
                break;
            }
        }
        
        if(eh_int) {
            qtd = stoi(entrada);

            return qtd;
        } else {
            cout<<endl<<"O numero digitado foi invalido. Deve ser digitado um numero inteiro maior que 0."<<endl;
            cout<<"Digite novamente."<<endl;
        }
    }
}

// lê o tamanho maximo do inventario. minimo de TAM_MIN_INVENTARIO e maximo de TAM_MAX_INVENTARIO
int ler_tam_max_inventario() {
    int tamanho;
    
    while(true) {
        cout<<"Digite o tamanho maximo do inventario (min "<<TAM_MIN_INVENTARIO<<", max "<<TAM_MAX_INVENTARIO<<"): ";
        tamanho = ler_inteiro();
        
        if(tamanho >= TAM_MIN_INVENTARIO && tamanho <= TAM_MAX_INVENTARIO) break;

        cout<<endl<<"O tamanho minimo eh "<<TAM_MIN_INVENTARIO<<" e o maximo eh "<<TAM_MAX_INVENTARIO<<"."<<endl;
        cout<<"Digite novamente."<<endl;
    }

    return tamanho;
}

// formata o nome para o modelo: primeira letra de cada palavra maiusculo e o resto minusculo
void formatar_nome(string &nome) {
    for(int i=0; i<nome.length(); i++) {
        if(i == 0 || nome[i-1] == ' ') nome[i] = toupper(nome[i]);
        else nome[i] = tolower(nome[i]);
    }
}

// lê um nome. repete a leitura se for um tipo diferente de letras (char de 'A' a 'Z' e 'a' a 'z'), espaço (" ") ou vírgula(",")
string ler_nome() {
    string nome;

    while(true) {
        cout<<"Digite o nome: ";
        getline(cin, nome);

        if(cin.eof()) {
            cout<<endl<<endl<<"Fim da leitura do arquivo teste.txt"<<endl;
            exit(0); 
        }

        if(nome.length() > TAM_MAX_NOME) {
            cout<<endl<<"Nome muito grande."<<endl;
            cout<<"Digite novamente."<<endl;
            
            continue;

        } else if(nome.length() < TAM_MIN_NOME) {
            cout<<endl<<"Nome muito pequeno."<<endl;
            cout<<"Digite novamente."<<endl;

            continue;
        }

        bool eh_palavra = true;

        for(char c: nome) {
            if(!isalpha(c) && c != ' ' && c != ',') {
                cout<<endl<<"Somente letras sao permitidas no nome."<<endl;
                cout<<"Digite novamente."<<endl;

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