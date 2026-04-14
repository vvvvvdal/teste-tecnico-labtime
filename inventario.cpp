
#include "inventario.hpp"
#include "item.hpp"

short int Inventario::verificar_posicao(int posicao) {
    if(posicao < 0 || posicao > 9) {
        cout<<"posicao invalida"<<endl;
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

Item Inventario::buscar_item(string nome) {
    for(int i=0; i<QTD_ITENS; i++) {
        if(nome == itens_inventario.itens[i].get_nome()) {
            return itens_inventario.itens[i];
        }
    }

    return Item();
}

int Inventario::encontrar_slot_vazio() {
    for(int i=0; i<TAM_MAX_INVENTARIO; i++) {
        if(ocupado[i] == DESOCUPADO) {
            return i;
        }
    }

    return POSICAO_INVALIDA;
}

void Inventario::set_slot(int posicao, Item &item) {
    slots[posicao] = item;
    ocupado[posicao] = OCUPADO;
}

void Inventario::distribuir_sobra(Item &item_base, int sobra) {
    while(sobra > 0) {
        int posicao_livre = encontrar_slot_vazio();

        if(posicao_livre == POSICAO_INVALIDA) {
            cout<<"inventario cheio. sobrou "<<sobra<<" e isso foi descartado"<<endl;
            break;
        }

        Item item_parte = item_base;

        if (sobra > TAM_MAX_PILHA) {
            item_parte.set_qtd(TAM_MAX_PILHA);
            set_slot(posicao_livre, item_parte);
            sobra -= TAM_MAX_PILHA;

            cout<<"Item: " <<item_base.get_nome()<<", Qtd: "<<TAM_MAX_PILHA<< " adicionado ao slot "<<posicao_livre+1<< endl;
        } else {
            item_parte.set_qtd(sobra);
            set_slot(posicao_livre, item_parte);
            cout<<"Item: " <<item_base.get_nome()<<", Qtd: "<<sobra<< " adicionado ao slot "<<posicao_livre+1<< endl;

            sobra = 0;
        }
    }
}

int Inventario::acrescenta_item_empilhavel_qtd() {
    int qtd;
    cout << "qual quantidade?" << endl;
    cin >> qtd;

    return qtd;
}

void Inventario::print_inventario() {
    for(int i=0; i<TAM_MAX_INVENTARIO; i++){

        int tam_temp;
        if(slots[i].get_empilhavel() == EMPILHAVEL) tam_temp = TAM_MAX_PILHA;
        else if(slots[i].get_empilhavel() == NAO_EMPILHAVEL)tam_temp = TAM_MAX_UNICO;
        else tam_temp = TAM_NULO;

        if(i%2==0) cout<<endl;

        cout<<"Slot "<<i+1<<"\t|\t"<<"Nome: "<<slots[i].get_nome()<<"\t Qtd: "<<slots[i].get_qtd()<<"/"<<tam_temp<<"\t|\t";
    }
    cout<<endl;
}

void Inventario::adicionar_item(int posicao, string nome) {
    formatar_posicao(posicao);
    formatar_nome(nome);

    if(verificar_posicao(posicao)) return;
    if(verificar_ocupado(posicao)) return;

    Item novo_item = buscar_item(nome);

    if(novo_item.get_nome() == "Vazio") {
        cout << "item " << nome << " nao existente no jogo" << endl;
        return;
    }

    int qtd = 1;
    if(novo_item.get_empilhavel() == EMPILHAVEL) {
        qtd = acrescenta_item_empilhavel_qtd();
    }

    if(qtd > TAM_MAX_PILHA) {
        novo_item.set_qtd(TAM_MAX_PILHA);
        set_slot(posicao, novo_item);

        distribuir_sobra(novo_item, (qtd - TAM_MAX_PILHA));

        cout<<"Item: " <<nome<<", Qtd: "<<TAM_MAX_PILHA<< " adicionado ao slot "<<posicao+1<< endl;
    } else {
        novo_item.set_qtd(qtd);
        set_slot(posicao, novo_item);

        cout<<"Item: " <<nome<<", Qtd: "<<qtd<< " adicionado ao slot "<<posicao+1<< endl;
    }
}

void Inventario::remover_item(int posicao) {
    formatar_posicao(posicao);

    if(verificar_posicao(posicao)) return;
    if(!verificar_ocupado(posicao)) return;

    slots[posicao] = Item();
    ocupado[posicao] = DESOCUPADO;
}

void Inventario::trocar_item(int posicao1, int posicao2) {
    formatar_posicao(posicao1);
    formatar_posicao(posicao2);

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
