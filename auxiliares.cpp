#include "auxiliares.hpp"

void limpar_buffer_entrada() {
    cin.clear(); 
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int get_inteiro() {
    string entrada;
    int qtd;
    
    while(true) {
        cin >> entrada;
        
        if (entrada.length() > 9) {
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

int get_tam_max_inventario() {
    int tamanho;
    
    while(true) {
        cout<<"Digite o tamanho maximo do inventario (min 6 max 1000): ";
        tamanho = get_inteiro();
        
        if(tamanho >= 6 && tamanho <= 1000) break;

        cout<<endl<<"O tamanho minimo eh 6 e o maximo eh 1000."<<endl;
        cout<<"Digite novamente."<<endl;
    }

    return tamanho;
}