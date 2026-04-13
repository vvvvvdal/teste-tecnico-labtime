#include "inventario.hpp"
#include "item.hpp"

bool Inventario::verificar_posicao(int &posicao) {
    if(posicao < 0 || posicao > 9) {
        cout<<"posicao invalida"<<endl;
        return true;
    }

    return false;
}

bool Inventario::verificar_ocupado(int &posicao) {
    if(ocupado[posicao] == OCUPADO) return true;

    return false;
}

void Inventario::formatar_nome(string &nome) {
    for(char &c: nome) {
        c = tolower(c);
    }

    nome[0] = toupper(nome[0]);
}

void Inventario::print_inventario() {
    for(int i=0; i<TAM_MAX_INVENTARIO; i++){

        int tam_temp;
        if(slots[i].get_empilhavel() == EMPILHAVEL) tam_temp = TAM_MAX_PILHA;
        else if(slots[i].get_empilhavel() == NAO_EMPILHAVEL)tam_temp = TAM_MAX_UNICO;
        else tam_temp = TAM_NULO;

        cout<<"|\t"<<"Nome: "<<slots[i].get_nome()<<", Qtd: "<<slots[i].get_qtd()<<"/"<<tam_temp<<"\t|";
    }
    cout<<endl;
}

int acrescenta_item_empilhavel_qtd() {
    int qtd;
    cout << "qual quantidade?" << endl;
    cin >> qtd;

    return qtd;
}

void Inventario::adicionar_item(int posicao, string nome) {
    posicao -= 1;

    formatar_nome(nome);

    if(verificar_posicao(posicao)) return;
    if(verificar_ocupado(posicao)) return;

    for(int i=0; i<QTD_ITENS; i++) {
        if(nome == itens_inventario.itens[i].get_nome()) {
            Item novo_item = itens_inventario.itens[i];
            int qtd;

            if(novo_item.get_empilhavel() == EMPILHAVEL) {
                qtd = acrescenta_item_empilhavel_qtd();

                if(qtd > TAM_MAX_PILHA) {
                    int sobra = qtd - TAM_MAX_PILHA;
                    novo_item.set_qtd(TAM_MAX_PILHA);
                    
                    slots[posicao] = novo_item;
                    ocupado[posicao] = OCUPADO;

                    for(int j = 0; j < TAM_MAX_INVENTARIO; j++) {
                        if(ocupado[j] == DESOCUPADO) {
                            Item sobra_item = novo_item;

                            if(sobra > TAM_MAX_PILHA) {
                                sobra_item.set_qtd(TAM_MAX_PILHA);
                                slots[j] = sobra_item;
                                ocupado[j] = OCUPADO;
                                sobra -= TAM_MAX_PILHA;

                            } else {
                                sobra_item.set_qtd(sobra);
                                slots[j] = sobra_item;
                                ocupado[j] = OCUPADO;
                                sobra = 0;

                                break;
                            }
                        }
                    }

                    if(sobra > 0) {
                        cout<<"inventario cheio. sobrou "<<sobra<<" e isso foi descartado"<<endl;
                    }

                } else {
                    novo_item.set_qtd(qtd);
                    
                    slots[posicao] = novo_item;
                    ocupado[posicao] = OCUPADO; 
                }

            } else {
                novo_item.set_qtd(1);
                
                slots[posicao] = novo_item;
                ocupado[posicao] = OCUPADO;
            }

            cout << "item " << nome << " adicionado ao slot " << posicao + 1 << endl;

            return;
        }
    }

    cout << "item " << nome << " nao existente no jogo" << endl;
}

void Inventario::remover_item(int posicao) {
    posicao -= 1;

    if(verificar_posicao(posicao)) return;
    if(!verificar_ocupado(posicao)) return;

    slots[posicao] = Item();
    ocupado[posicao] = false;
}

void Inventario::trocar_item(int posicao1, int posicao2) {
    posicao1 -= 1;
    posicao2 -= 1;

    if(verificar_posicao(posicao1) || verificar_posicao(posicao2)) return;
    if(!verificar_ocupado(posicao1) && !verificar_ocupado(posicao2)) return;

    if(!verificar_ocupado(posicao1) && verificar_ocupado(posicao2)) { // 1 vazio e 2 ocupado
        slots[posicao1] = slots[posicao2];
        slots[posicao2] = Item();

        ocupado[posicao1] = OCUPADO;
        ocupado[posicao2] = DESOCUPADO;

        cout<<"item "<<slots[posicao1].get_nome()<<" trocado para a posicao"<<posicao1+1<<endl;

    } else if(verificar_ocupado(posicao1) && !verificar_ocupado(posicao2)) {// 1 ocupado e 2 vazio
        slots[posicao2] = slots[posicao1];
        slots[posicao1] = Item();

        ocupado[posicao1] = DESOCUPADO;
        ocupado[posicao2] = OCUPADO;

        cout<<"item "<<slots[posicao2].get_nome()<<" trocado para a posicao"<<posicao2+1<<endl;

    } else {
        Item temp = slots[posicao1];
        slots[posicao1] = slots[posicao2];
        slots[posicao2] = temp;
        
        cout<<"item "<<slots[posicao1].get_nome()<<" trocado com o item "<<slots[posicao2].get_nome()<<endl;
    }
}