#include "auxiliares.hpp"

void limpar_buffer_entrada() {
    cin.clear(); 
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int ler_inteiro() {
    string entrada;
    int qtd;
    
    while(true) {
        getline(cin, entrada);
        
        if (entrada.length() > TAM_MAX_DIGITOS) {
            cout<<endl<<"Numero muito grande." << endl;
            cout<<"Digite novamente."<<endl;
            limpar_buffer_entrada();
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
            limpar_buffer_entrada();

            return qtd;
        } else {
            cout<<endl<<"O numero digitado foi invalido. Deve ser digitado um numero inteiro maior que 0."<<endl;
            cout<<"Digite novamente."<<endl;
            limpar_buffer_entrada();
        }
    }
}

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

void formatar_nome(string &nome) {
    for(char &c: nome) {
        c = tolower(c);
    }

    nome[0] = toupper(nome[0]);
}

string ler_nome() {
    string nome;

    while(true) {
        cout<<"Digite o nome: ";
        getline(cin, nome);

        if(nome.length() > TAM_MAX_NOME) {
            cout<<endl<<"Nome muito grande."<<endl;
            cout<<"Digite novamente."<<endl;
            limpar_buffer_entrada();
        }

        bool eh_palavra = true;

        for(char c: nome) {
            if(!isalpha(c)) {
                cout<<endl<<"Somente letras sao permitidas no nome."<<endl;
                cout<<"Digite novamente."<<endl;
                limpar_buffer_entrada();

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
