#include "../include/inventario.hpp"
#include "../include/auxiliares.hpp"
#include <algorithm>
#include <cctype>

using namespace std;

// verifica se a quantidade escolhida eh negativa (recebe item como const&)
void Inventario::verificar_qtd_negativa(const Item& item, int posicao, int qtd) const {
    if(qtd >= 0) return;

    string palavra_tipo = (item.get_tipo() == TipoItem::Empilhavel) ? "empilhaveis" : "nao empilhaveis";
    string palavra_qtd = (item.get_tipo() == TipoItem::Empilhavel) ? "de 0 a 64 unidades" : "so 1 unidade";

    cout << "Quantidade " << qtd << " invalida para remover do item " << item.get_nome() << " no slot " << posicao + 1 << "." << endl;
    cout << "Itens " << palavra_tipo << " (como " << item.get_nome() << ") possuem " << palavra_qtd << " de quantidade em um slot." << endl;
    cout << "Nao eh possivel remover uma quantidade maior que a quantidade existente ou quantidade negativa. Operacao nao realizada." << endl;
}

// busca um item presente no inventario
Item Inventario::buscar_item(const string& nome) const {
    for(int i = 0; i < Item::QTD_ITENS; i++) {
        if(nome == itens_inventario.get_item(i).get_nome()) {
            return itens_inventario.get_item(i);
        }
    }
    return Item();
}

// procura o primeiro slot desocupado no inventario
int Inventario::encontrar_slot_vazio() const {
    for(int i = 0; i < tam_max_inventario; i++) {
        if(!slots[i].ocupado) {
            return i;
        }
    }
    return SLOT_INVALIDO;
}

// distribui o excesso de quantidade para slots disponiveis
void Inventario::distribuir_sobra(const Item& item_base, int sobra) {
    while(sobra > 0) {
        int posicao_livre = encontrar_slot_vazio();

        if(posicao_livre == SLOT_INVALIDO) {
            cout << endl << "Inventario cheio. Sobrou " << sobra << " unidades do item " << item_base.get_nome() << " e isso foi descartado" << endl;
            break;
        }

        Item item_parte = item_base;

        if (item_base.get_tipo() == TipoItem::Empilhavel) {
            if (sobra > Item::TAM_MAX_PILHA) {
                item_parte.set_qtd(Item::TAM_MAX_PILHA);
                ocupar_slot(item_parte, posicao_livre);
                sobra -= Item::TAM_MAX_PILHA;

                cout << "Item: " << item_base.get_nome() << ", Qtd: " << Item::TAM_MAX_PILHA << " adicionado ao slot " << posicao_livre + 1 << endl;
            } else {
                item_parte.set_qtd(sobra);
                ocupar_slot(item_parte, posicao_livre);

                cout << "Item: " << item_base.get_nome() << ", Qtd: " << sobra << " adicionado ao slot " << posicao_livre + 1 << endl;
                sobra = 0;
            }
        } else {
            item_parte.set_qtd(Item::TAM_MAX_UNICO);
            ocupar_slot(item_parte, posicao_livre);

            cout << "Item: " << item_base.get_nome() << ", Qtd: " << Item::TAM_MAX_UNICO << " adicionado ao slot " << posicao_livre + 1 << endl;
            sobra -= 1;
        }
    }
}

// construtor de inventario com tamanho maximo definido pelo usuario
Inventario::Inventario(int tam_max_inventario) : tam_max_inventario(tam_max_inventario) {
    slots.resize(tam_max_inventario);
}

// verifica se a posicao escolhida esta entre 1 e o tamanho maximo do inventario
bool Inventario::verificar_posicao(int posicao) const {
    if(posicao < 0 || posicao >= tam_max_inventario) {
        cout << endl << "Posicao invalida" << endl;
        return false;
    }
    return true;
}

// retorna true se o slot estiver ocupado e false se estiver desocupado
bool Inventario::verificar_ocupado(int posicao) const {
    return slots[posicao].ocupado;
}

// esvazia slot
void Inventario::esvaziar_slot(int posicao) {
    slots[posicao].item = Item();
    slots[posicao].ocupado = false;
}

// ocupa slot passando item por referencia constante
void Inventario::ocupar_slot(const Item& item, int posicao) {
    slots[posicao].item = item;
    slots[posicao].ocupado = true;
}

// retorna slot por referencia constante
const Slot& Inventario::get_slot(int posicao) const {
    return slots[posicao];
}

void Inventario::set_slot(const Slot& novo_slot, int posicao) {
    slots[posicao] = novo_slot;
}

int Inventario::get_tam_max_inventario() const {
    return tam_max_inventario;
}

// imprime os itens do inventario com 2 itens por linha
void Inventario::print_inventario() const {
    for(int i = 0; i < tam_max_inventario; i++) {
        int tam_print;
        
        if(!slots[i].ocupado) tam_print = Item::TAM_NULO;
        else if(slots[i].item.get_tipo() == TipoItem::Empilhavel) tam_print = Item::TAM_MAX_PILHA;
        else tam_print = Item::TAM_MAX_UNICO;

        if(i % 2 == 0) cout << endl;

        cout << "Slot " << i + 1 << "\t|\t" 
             << "Nome: " << slots[i].item.get_nome() << "\t Qtd: " 
             << slots[i].item.get_qtd() << "/" << tam_print << "\t|\t";
    }
    cout << endl;
}

// adiciona um item no inventario de acordo com seu nome e quantidade.
// se a quantidade for maior que a ocupável por um slot, adiciona o que sobra em slots disponiveis do mesmo item (se for empilhavel) ou em slots vazios
void Inventario::adicionar_item(const string& nome, int qtd) {
    string nome_formatado = nome;
    auxiliares::formatar_nome(nome_formatado);

    Item novo_item = buscar_item(nome_formatado);

    if(novo_item.get_nome() == "Vazio") {
        cout << "Item " << nome_formatado << " nao existente no jogo" << endl;
        return;
    }

    if (qtd <= 0) {
        cout << "A quantidade deve ser maior que zero." << endl;
        return;
    }

    int sobra = qtd;
    if (novo_item.get_tipo() == TipoItem::Empilhavel) {
        for(int i = 0; i < tam_max_inventario; i++) {
            if(slots[i].ocupado && slots[i].item.get_nome() == novo_item.get_nome()) {
                int resto = Item::TAM_MAX_PILHA - slots[i].item.get_qtd();
                
                if (resto > 0) {
                    if (sobra <= resto) {
                        slots[i].item.set_qtd(slots[i].item.get_qtd() + sobra);
                        cout << "Item: " << nome_formatado << ", Qtd: " << sobra << " adicionado na pilha do slot " << i + 1 << endl;
                        sobra = 0;
                        break;
                    } else {
                        slots[i].item.set_qtd(Item::TAM_MAX_PILHA);
                        cout << "Item: " << nome_formatado << ", Qtd: " << resto << " adicionado na pilha do slot " << i + 1 << endl;
                        sobra -= resto;
                    }
                }
            }
        }
    }

    if (sobra > 0) distribuir_sobra(novo_item, sobra);
}

// remove um item do inventario, deixando o slot com um item vazio.
void Inventario::remover_item(int posicao, int qtd) {
    auxiliares::formatar_posicao(posicao);

    if(!verificar_posicao(posicao)) return;
    if(!verificar_ocupado(posicao)) {
        cout << "Slot " << posicao + 1 << " vazio. Nao eh possivel remover um item de um slot vazio" << endl;
        return;
    }

    if(slots[posicao].item.get_tipo() == TipoItem::Empilhavel) {
        if(qtd == slots[posicao].item.get_qtd()) {
            cout << "Quantidade " << qtd << " removida do item " << slots[posicao].item.get_nome() << " no slot " << posicao + 1 << "." << endl;
            cout << "Agora esse slot esta vazio." << endl;
            esvaziar_slot(posicao);
        } else if(qtd > slots[posicao].item.get_qtd() || qtd < 0) {
            verificar_qtd_negativa(slots[posicao].item, posicao, qtd);
            return;
        } else {
            slots[posicao].item.set_qtd(slots[posicao].item.get_qtd() - qtd);
            cout << "Quantidade " << qtd << " removida do item " << slots[posicao].item.get_nome() << " no slot " << posicao + 1 << "." << endl;
            cout << "Quantidade atual: " << slots[posicao].item.get_qtd() << endl;
        }
    } else {
        if(qtd == Item::TAM_MAX_UNICO) { // item não empihável: quantidade máxima de 1 por slot
            cout << "Item " << slots[posicao].item.get_nome() << " removido do slot " << posicao + 1 << "." << endl;
        } else if(qtd > Item::TAM_MAX_UNICO) {
            cout << "Item " << slots[posicao].item.get_nome() << " eh do tipo nao empilhavel. Para remover, sua quantidade deve ser " << Item::TAM_MAX_UNICO << "." << endl;
            cout << "Operacao nao realizada." << endl;
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
    auxiliares::formatar_posicao(posicao1);
    auxiliares::formatar_posicao(posicao2);

    if(!verificar_posicao(posicao1) || !verificar_posicao(posicao2)) {
        cout<<"Na troca de itens no inventario: "<<endl;
        cout<<"Tente escolher uma posicao que esteja entre 1 e "<<tam_max_inventario<<endl;
        cout<<"Operacao nao realizada."<<endl;
        
        return;
    }

    bool ocupado1 = verificar_ocupado(posicao1);
    bool ocupado2 = verificar_ocupado(posicao2);

    if(!ocupado1 && !ocupado2) {
        cout<<"Slot "<<posicao1+1<<" e slot "<<posicao2+1<<" estao vazios"<<endl;
        return;
    }

    // troca dos slots com a funcao swap
    std::swap(slots[posicao1], slots[posicao2]);

    if(!ocupado1 && ocupado2) { // 1 era vazio e 2 era ocupado
        cout<<"Item "<<slots[posicao1].item.get_nome()<<" do slot "<<posicao2+1<<" trocado para o slot "<<posicao1+1<<endl;

    } else if(ocupado1 && !ocupado2) { // 1 era ocupado e 2 era vazio
        cout<<"Item "<<slots[posicao2].item.get_nome()<<" do slot "<<posicao1+1<<" trocado para o slot "<<posicao2+1<<endl;

    } else { // ambos eram ocupados
        cout<<"Item "<<slots[posicao1].item.get_nome()<<" do slot "<<posicao2+1<<" trocado com o item "<<slots[posicao2].item.get_nome()<<" do slot "<<posicao1+1<<endl;
        cout<<"Agora o item "<<slots[posicao1].item.get_nome()<<" esta no slot "<<posicao1+1<<" e o item "<<slots[posicao2].item.get_nome()<<" esta no slot "<<posicao2+1<<endl;
    }
}