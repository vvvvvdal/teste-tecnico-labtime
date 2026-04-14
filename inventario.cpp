#include "inventario.hpp"
#include <string>
#include <cctype>

short int Inventario::verificar_posicao(int posicao) {
    if(posicao < 0 || posicao > 9) {
        cout<<endl<<"Posicao invalida"<<endl;
        return POSICAO_INVALIDA;
    }

    return POSICAO_VALIDA;
}

short int Inventario::verificar_ocupado(int posicao) {
    if(ocupado[posicao] == OCUPADO) return OCUPADO;

    return DESOCUPADO;
}

void Inventario::formatar_nome(string &nome) {
    for(char &c: nome) {
        c = tolower(c);
    }

    nome[0] = toupper(nome[0]);
}

void Inventario::formatar_posicao(int &posicao) {
    posicao -= 1;
}

void Inventario::verificar_qtd_negativa(Item &item, int posicao, int qtd) {
    if(qtd >= 0) return;

    string palavra_tipo = (item.get_tipo() == EMPILHAVEL) ? "empilhaveis" : "nao empilhaveis";
    string palavra_qtd = (item.get_tipo() == EMPILHAVEL) ? "de 0 a 64 unidades" : "so 1 unidade";

    cout<<endl<<"Quantidade "<<qtd<<" invalida para remover do item "<<item.get_nome()<<" no slot "<<posicao+1<<"."<<endl;
    cout<<"Itens "<<palavra_tipo<<" (como "<<item.get_nome()<< ") possuem "<<palavra_qtd<<" de quantidade em um slot."<<endl;
    cout<<"Nao eh possivel remover uma quantidade maior que a quantidade existente ou quantidade negativa. Operacao nao realizada."<<endl;

}

Item Inventario::buscar_item(string nome) {
    for(int i=0; i<QTD_ITENS; i++) {
        if(nome == itens_inventario.itens[i].get_nome()) {
            return itens_inventario.itens[i];
        }
    }

    return Item();
}

int Inventario::encontrar_slot_vazio() {
    for(int i=0; i<tam_max_inventario; i++) {
        if(ocupado[i] == DESOCUPADO) {
            return i;
        }
    }

    return SLOT_INVALIDO;
}

void Inventario::set_slot(int posicao, Item &item) {
    slots[posicao] = item;
    ocupado[posicao] = OCUPADO;
}

void Inventario::distribuir_sobra(Item &item_base, int sobra) {
    while(sobra > 0) {
        int posicao_livre = encontrar_slot_vazio();

        if(posicao_livre == SLOT_INVALIDO) {
            cout<<endl<<"Inventario cheio. Sobrou "<<sobra<<" unidades do item "<<item_base.get_nome()<<" e isso foi descartado"<<endl;
            break;
        }

        Item item_parte = item_base;

        if (item_base.get_tipo() == EMPILHAVEL) {
            if (sobra > TAM_MAX_PILHA) {
                item_parte.set_qtd(TAM_MAX_PILHA);
                set_slot(posicao_livre, item_parte);
                sobra -= TAM_MAX_PILHA;

                cout<<endl<<"Item: "<<item_base.get_nome()<<", Qtd: "<<TAM_MAX_PILHA<<" adicionado ao slot "<<posicao_livre+1<<endl;
            } else {
                item_parte.set_qtd(sobra);
                set_slot(posicao_livre, item_parte);

                cout<<endl<<"Item: "<<item_base.get_nome()<<", Qtd: "<<sobra<<" adicionado ao slot "<<posicao_livre+1<<endl;
                sobra = 0;
            }
        } else {
            item_parte.set_qtd(TAM_MAX_UNICO);
            set_slot(posicao_livre, item_parte);

            cout<<endl<<"Item: "<<item_base.get_nome()<<", Qtd: "<<TAM_MAX_UNICO<<" adicionado ao slot "<<posicao_livre+1<<endl;
            sobra -= 1;
        }
    }
}

void Inventario::esvaziar_slot(int posicao){
    slots[posicao] = Item();
    ocupado[posicao] = DESOCUPADO;
}

Inventario::Inventario(int tam_max_inventario): tam_max_inventario(tam_max_inventario) {
    slots.resize(tam_max_inventario); 
    ocupado.resize(tam_max_inventario, 0);
}

void Inventario::print_inventario() {
    for(int i=0; i<tam_max_inventario; i++){

        int tam_print;
        if(ocupado[i] == DESOCUPADO) tam_print = TAM_NULO;
        else if(slots[i].get_tipo() == EMPILHAVEL) tam_print = TAM_MAX_PILHA;
        else tam_print = TAM_MAX_UNICO;

        if(i%2==0) cout<<endl;

        cout<<"Slot "<<i+1<<"\t|\t"<<"Nome: "<<slots[i].get_nome()<<"\t Qtd: "<<slots[i].get_qtd()<<"/"<<tam_print<<"\t|\t";
    }
    cout<<endl;
}

void Inventario::adicionar_item(string nome, int qtd) {
    formatar_nome(nome);

    Item novo_item = buscar_item(nome);

    if(novo_item.get_nome() == "Vazio") {
        cout<<endl<<"Item "<<nome<<" nao existente no jogo"<<endl;
        return;
    }

    if (qtd <= 0) {
        cout<<endl<<"A quantidade deve ser maior que zero."<<endl;
        return;
    }

    int sobra = qtd;
    if (novo_item.get_tipo() == EMPILHAVEL) {
        for(int i = 0; i < tam_max_inventario; i++) {
            if(ocupado[i] == OCUPADO && slots[i].get_nome() == novo_item.get_nome()) {
                int resto = TAM_MAX_PILHA - slots[i].get_qtd();
                
                if (resto > 0) {
                    if (sobra <= resto) {
                        slots[i].set_qtd(slots[i].get_qtd() + sobra);
                        cout<<endl<<"Item: "<<nome<<", Qtd: "<<sobra<< " adicionado na pilha do slot "<<i+1<<endl;

                        sobra = 0;
                        break;
                    } else {
                        slots[i].set_qtd(TAM_MAX_PILHA);
                        cout<<endl<<"Item: "<<nome<<", Qtd: "<<sobra<< " adicionado na pilha do slot "<<i+1<<endl;
                        
                        sobra -= resto;
                    }
                }
            }
        }
    }

    if (sobra > 0) {
        distribuir_sobra(novo_item, sobra);
    }
}

void Inventario::remover_item(int posicao, int qtd) {
    formatar_posicao(posicao);

    if(verificar_posicao(posicao)) return;
    if(!verificar_ocupado(posicao)){
        cout<<endl<<"Slot "<<posicao+1<<" vazio. Não é possível remover um item de um slot vazio"<<endl;
        return;
    }

    if(slots[posicao].get_tipo() == EMPILHAVEL){

        if(qtd == slots[posicao].get_qtd()) {
            cout<<endl<<"Quantidade "<<qtd<<" removida do item "<<slots[posicao].get_nome()<< " no slot "<<posicao+1<<"."<<endl;
            cout<<"Agora esse slot esta vazio."<<endl;

            esvaziar_slot(posicao);

        } else if(qtd > slots[posicao].get_qtd() || qtd < 0) {
            verificar_qtd_negativa(slots[posicao], posicao, qtd);

            return;

        } else {
            slots[posicao].set_qtd((slots[posicao].get_qtd()-qtd));

            cout<<endl<<"Quantidade "<<qtd<<" removida do item "<<slots[posicao].get_nome()<< " no slot "<<posicao+1<<"."<<endl;
            cout<<"Quantidade atual: "<<slots[posicao].get_qtd()<<endl;
        }
    } else {
        if(qtd == TAM_MAX_UNICO) {
            cout<<endl<<"Item "<<slots[posicao].get_nome()<<" removido do slot "<<posicao+1<<"."<<endl;
        } else {
            verificar_qtd_negativa(slots[posicao], posicao, qtd);

            return;
        }

        esvaziar_slot(posicao);
    }
}

void Inventario::trocar_item(int posicao1, int posicao2) {
    formatar_posicao(posicao1);
    formatar_posicao(posicao2);

    if(verificar_posicao(posicao1) || verificar_posicao(posicao2)) return;
    if(!verificar_ocupado(posicao1) && !verificar_ocupado(posicao2)) {
        cout<<"Slot "<<posicao1+1<<" e slot "<<posicao2+1<<"estao vazios"<<endl;
        return;
    }

    if(!verificar_ocupado(posicao1) && verificar_ocupado(posicao2)) { // 1 vazio e 2 ocupado
        slots[posicao1] = slots[posicao2];
        ocupado[posicao1] = OCUPADO;

        esvaziar_slot(posicao2);

        cout<<endl<<"Item "<<slots[posicao1].get_nome()<<" do slot "<<posicao2+1<<" trocado para o slot"<<posicao1+1<<endl;

    } else if(verificar_ocupado(posicao1) && !verificar_ocupado(posicao2)) { // 1 ocupado e 2 vazio
        slots[posicao2] = slots[posicao1];
        ocupado[posicao2] = OCUPADO;
        esvaziar_slot(posicao1);

        cout<<endl<<"Item "<<slots[posicao1].get_nome()<<" do slot "<<posicao1+1<<" trocado para o slot"<<posicao2+1<<endl;

    } else {
        Item temp = slots[posicao1];
        slots[posicao1] = slots[posicao2];
        slots[posicao2] = temp;

        cout<<endl<<"Item "<<slots[posicao1].get_nome()<<" do slot "<<posicao2+1<<" trocado com o item "<<slots[posicao2].get_nome()<<" do slot "<<posicao1+1<<endl;
        cout<<"Agora o item "<<slots[posicao1].get_nome()<<" esta no slot "<<posicao1+1<<" e o item " <<slots[posicao2].get_nome()<<" esta no slot "<<posicao2+1<<endl;
    }
}