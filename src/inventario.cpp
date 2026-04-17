#include "../include/inventario.hpp"
#include <string>
#include <cctype>
using namespace std;

// verifica se a quantidade escolhida é negativa
void Inventario::verificar_qtd_negativa(Item &item, int posicao, int qtd) {
    if(qtd >= 0) return;

    string palavra_tipo = (item.get_tipo() == EMPILHAVEL) ? "empilhaveis" : "nao empilhaveis";
    string palavra_qtd = (item.get_tipo() == EMPILHAVEL) ? "de 0 a 64 unidades" : "so 1 unidade";

    cout<<"Quantidade "<<qtd<<" invalida para remover do item "<<item.get_nome()<<" no slot "<<posicao+1<<"."<<endl;
    cout<<"Itens "<<palavra_tipo<<" (como "<<item.get_nome()<< ") possuem "<<palavra_qtd<<" de quantidade em um slot."<<endl;
    cout<<"Nao eh possivel remover uma quantidade maior que a quantidade existente ou quantidade negativa. Operacao nao realizada."<<endl;
}

// busca um item pelo seu nome e verifica se ele existe, se não existir retorna item vazio.
Item Inventario::buscar_item(string nome) {
    for(int i=0; i<QTD_ITENS; i++) {
        if(nome == itens_inventario.itens[i].get_nome()) {
            return itens_inventario.itens[i];
        }
    }

    return Item();
}

// procura um slot desocupado no inventario
int Inventario::encontrar_slot_vazio() {
    for(int i=0; i<tam_max_inventario; i++) {

        if(slots[i].ocupado == DESOCUPADO) {
            return i;
        }
    }

    return SLOT_INVALIDO;
}

// distribui o excesso de quantidade para slots disponiveis
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
                ocupar_slot(item_parte, posicao_livre);
                sobra -= TAM_MAX_PILHA;

                cout<<"Item: "<<item_base.get_nome()<<", Qtd: "<<TAM_MAX_PILHA<<" adicionado ao slot "<<posicao_livre+1<<endl;
            } else {
                item_parte.set_qtd(sobra);
                ocupar_slot(item_parte, posicao_livre);

                cout<<"Item: "<<item_base.get_nome()<<", Qtd: "<<sobra<<" adicionado ao slot "<<posicao_livre+1<<endl;
                sobra = 0;
            }
        } else {
            item_parte.set_qtd(TAM_MAX_UNICO);
            ocupar_slot(item_parte, posicao_livre);

            cout<<"Item: "<<item_base.get_nome()<<", Qtd: "<<TAM_MAX_UNICO<<" adicionado ao slot "<<posicao_livre+1<<endl;
            sobra -= 1;
        }
    }
}

// construtor: inicializa um inventario com tam_max_inventario de slots e ocupa esses slots como vazios (desocupados).
Inventario::Inventario(int tam_max_inventario): tam_max_inventario(tam_max_inventario) {
    slots.resize(tam_max_inventario);

    for(int i=0; i<tam_max_inventario; i++) slots[i].ocupado = DESOCUPADO;
}

// verifica se a posicao escolhida esta entre o minimo e maximo do inventario
short int Inventario::verificar_posicao(int posicao) {
    if(posicao < 0 || posicao >= tam_max_inventario) {
        cout<<endl<<"Posicao invalida"<<endl;
        return POSICAO_INVALIDA;
    }

    return POSICAO_VALIDA;
}

// verifica se o slot esta ocupado ou nao
short int Inventario::verificar_ocupado(int posicao) {
    if(slots[posicao].ocupado == OCUPADO) return OCUPADO;
    
    return DESOCUPADO;
}

// esvazia um slot no inventario, removendo um item e colocando um item vazio no lugar
void Inventario::esvaziar_slot(int posicao){
    slots[posicao].item = Item();
    slots[posicao].ocupado = DESOCUPADO;
}

// ocupa um slot no inventario, colocando um item
void Inventario::ocupar_slot(Item &item, int posicao) {
    slots[posicao].item = item;
    slots[posicao].ocupado = OCUPADO;
}

// retorna um slot de uma posicao especifica
Slot Inventario::get_slot(int posicao) {
    return slots[posicao];
}

// define um novo slot
void Inventario::set_slot(Slot &novo_slot, int posicao) {
    slots[posicao] = novo_slot;
}

int Inventario::get_tam_max_inventario(){
    return tam_max_inventario;
}

// imprime os itens do inventario com 2 itens por linha
void Inventario::print_inventario() {
    for(int i=0; i<tam_max_inventario; i++){

        int tam_print;
        if(slots[i].ocupado == DESOCUPADO) tam_print = TAM_NULO;
        else if(slots[i].item.get_tipo() == EMPILHAVEL) tam_print = TAM_MAX_PILHA;
        else tam_print = TAM_MAX_UNICO;

        if(i%2==0) cout<<endl;

        cout<<"Slot "<<i+1<<"\t|\t"<<"Nome: "<<slots[i].item.get_nome()<<"\t Qtd: "<<slots[i].item.get_qtd()<<"/"<<tam_print<<"\t|\t";
    }
    cout<<endl;
}

// adiciona um item no inventario de acordo com seu nome e quantidade.
// se a quantidade for maior que a ocupável por um slot, adiciona o que sobra em slots disponiveis do mesmo item (se for empilhavel) ou em slots vazios
void Inventario::adicionar_item(string nome, int qtd) {
    formatar_nome(nome);

    Item novo_item = buscar_item(nome);

    if(novo_item.get_nome() == "Vazio") {
        cout<<"Item "<<nome<<" nao existente no jogo"<<endl;
        return;
    }

    if (qtd <= 0) {
        cout<<"A quantidade deve ser maior que zero."<<endl;
        return;
    }

    int sobra = qtd;
    if (novo_item.get_tipo() == EMPILHAVEL) {
        for(int i=0; i<tam_max_inventario; i++) {
            if(slots[i].ocupado == OCUPADO && slots[i].item.get_nome() == novo_item.get_nome()) {
                int resto = TAM_MAX_PILHA - slots[i].item.get_qtd();
                
                if (resto > 0) {
                    if (sobra <= resto) {
                        slots[i].item.set_qtd(slots[i].item.get_qtd() + sobra);
                        cout<<"Item: "<<nome<<", Qtd: "<<sobra<<" adicionado na pilha do slot "<<i+1<<endl;

                        sobra = 0;
                        break;
                    } else {
                        slots[i].item.set_qtd(TAM_MAX_PILHA);
                        cout<<"Item: "<<nome<<", Qtd: "<<resto<<" adicionado na pilha do slot "<<i+1<<endl;
                        
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

// remove um item do inventario, deixando o slot com um item vazio.
void Inventario::remover_item(int posicao, int qtd) {
    formatar_posicao(posicao);

    if(verificar_posicao(posicao)) return;
    if(!verificar_ocupado(posicao)){
        cout<<"Slot "<<posicao+1<<" vazio. Nao eh possível remover um item de um slot vazio"<<endl;
        return;
    }

    if(slots[posicao].item.get_tipo() == EMPILHAVEL){

        if(qtd == slots[posicao].item.get_qtd()) {
            cout<<"Quantidade "<<qtd<<" removida do item "<<slots[posicao].item.get_nome()<< " no slot "<<posicao+1<<"."<<endl;
            cout<<"Agora esse slot esta vazio."<<endl;

            esvaziar_slot(posicao);

        } else if(qtd > slots[posicao].item.get_qtd() || qtd < 0) {
            verificar_qtd_negativa(slots[posicao].item, posicao, qtd);

            return;

        } else {
            slots[posicao].item.set_qtd((slots[posicao].item.get_qtd()-qtd));

            cout<<"Quantidade "<<qtd<<" removida do item "<<slots[posicao].item.get_nome()<< " no slot "<<posicao+1<<"."<<endl;
            cout<<"Quantidade atual: "<<slots[posicao].item.get_qtd()<<endl;
        }
    } else {
        if(qtd == TAM_MAX_UNICO) { // item não empihável: quantidade máxima de 1 por slot
            cout<<"Item "<<slots[posicao].item.get_nome()<<" removido do slot "<<posicao+1<<"."<<endl;
        } else if(qtd > TAM_MAX_UNICO) {
            cout<<"Item "<<slots[posicao].item.get_nome()<<" eh do tipo nao empilhavel. Para remover, sua quantidade deve ser "<<TAM_MAX_UNICO<<" ."<<endl;
            cout<<"Operacao nao realizada."<<endl;

            return;
        } else {
            verificar_qtd_negativa(slots[posicao].item, posicao, qtd);
                
            return;
        }

        esvaziar_slot(posicao);
    }
}

// troca dois itens de posicao. se uma das posicoes for vazia, realiza a troca deixando uma posicao como item vazio.
void Inventario::trocar_item(int posicao1, int posicao2) {
    formatar_posicao(posicao1);
    formatar_posicao(posicao2);

    if(verificar_posicao(posicao1) || verificar_posicao(posicao2)) {
        cout<<"Na troca de itens no inventario: "<<endl;
        cout<<"Tente escolher uma posicao que esteja entre 1 e "<<tam_max_inventario<<endl;
        cout<<"Operacao nao realizada."<<endl;
        
        return;
    }

    if(!verificar_ocupado(posicao1) && !verificar_ocupado(posicao2)) {
        cout<<"Slot "<<posicao1+1<<" e slot "<<posicao2+1<<"estao vazios"<<endl;
        return;
    }

    if(!verificar_ocupado(posicao1) && verificar_ocupado(posicao2)) { // 1 vazio e 2 ocupado
        slots[posicao1] = slots[posicao2];
        esvaziar_slot(posicao2);

        cout<<"Item "<<slots[posicao1].item.get_nome()<<" do slot "<<posicao2+1<<" trocado para o slot "<<posicao1+1<<endl;

    } else if(verificar_ocupado(posicao1) && !verificar_ocupado(posicao2)) { // 1 ocupado e 2 vazio
        slots[posicao2] = slots[posicao1];
        esvaziar_slot(posicao1);

        cout<<"Item "<<slots[posicao2].item.get_nome()<<" do slot "<<posicao1+1<<" trocado para o slot "<<posicao2+1<<endl;

    } else { // 1 ocupado e 2 ocupado
        Slot temp = slots[posicao1];
        slots[posicao1] = slots[posicao2];
        slots[posicao2] = temp;

        cout<<"Item "<<slots[posicao1].item.get_nome()<<" do slot "<<posicao2+1<<" trocado com o item "<<slots[posicao2].item.get_nome()<<" do slot "<<posicao1+1<<endl;
        cout<<"Agora o item "<<slots[posicao1].item.get_nome()<<" esta no slot "<<posicao1+1<<" e o item "<<slots[posicao2].item.get_nome()<<" esta no slot "<<posicao2+1<<endl;
    }
}