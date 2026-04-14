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
            cout<<"Numero muito grande." << endl;
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
            cout<<"O numero digitado foi invalido. Deve ser digitado um numero inteiro."<<endl;
            cout<<"Digite novamente."<<endl;
            limpar_buffer_entrada();
        }
    }
}