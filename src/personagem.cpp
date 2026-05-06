#include "../include/personagem.hpp"
#include "../include/auxiliares.hpp"

using namespace std;

// construtor: inicializa um personagem e seu inventario (relação de composição)
Personagem::Personagem(const string& nome, int tam_max_inv): nome(nome), inventario(tam_max_inv) {}

// retorna o nome do personagem
const string& Personagem::get_nome() const {
    return nome;
}

// retorna o inventario do personagem
Inventario& Personagem::get_inventario() {
    return inventario;
}

// imprime o nome do personagem e o seu inventario
void Personagem::print_inventario_personagem() const {
    cout << endl << "Inventario de " << nome << ":";
    inventario.print_inventario();
}

// adiciona um item no inventario do personagem
void Personagem::adicionar_item_inventario(const string& nome_item, int qtd) {
    cout << endl << "Adicionando no inventario de " << nome << ":" << endl;
    inventario.adicionar_item(nome_item, qtd);
}

// remove um item do inventario do personagem
void Personagem::remover_item_inventario(int posicao, int qtd) {
    cout << endl << "Removendo no inventario de " << nome << ":" << endl;
    inventario.remover_item(posicao, qtd);
}

// troca 2 itens de slot no inventario do personagem
void Personagem::trocar_itens_inventario(int posicao1, int posicao2) {
    cout << endl << "Trocando no inventario de " << nome << ":" << endl;
    inventario.trocar_item(posicao1, posicao2);
}

// troca um item entre 2 personagens
void Personagem::trocar_itens_inventario_entre_personagens(Personagem& pers1, Personagem& pers2, int posicao1, int posicao2) {
    cout << endl << "Trocando itens entre " << pers1.get_nome() << " e " << pers2.get_nome() << ":" << endl;

    auxiliares::formatar_posicao(posicao1);
    auxiliares::formatar_posicao(posicao2);

    Inventario& inv1 = pers1.get_inventario();
    Inventario& inv2 = pers2.get_inventario();

    if (!inv1.verificar_posicao(posicao1) || !inv2.verificar_posicao(posicao2)) {
        cout << "Na troca de itens entre personagens: " << endl;
        cout << "Escolha uma posicao que esteja entre 1 e " << inv1.get_tam_max_inventario() << " para o personagem " << pers1.get_nome() << endl;
        cout << "E escolha uma posicao que esteja entre 1 e " << inv2.get_tam_max_inventario() << " para o personagem " << pers2.get_nome() << endl;
        cout << "Operacao nao realizada." << endl;

        return;
    }

    if (!inv1.verificar_ocupado(posicao1) && !inv2.verificar_ocupado(posicao2)) {
        cout << "Slot " << posicao1 + 1 << " de " << pers1.get_nome() << " e slot " << posicao2 + 1 << " de " << pers2.get_nome() << " estao vazios" << endl;
        return;
    }

    // variaveis auxiliares para armazenar a copia dos slots durante a troca
    Slot slot_temp, slot_aux;

    if (!inv1.verificar_ocupado(posicao1) && inv2.verificar_ocupado(posicao2)) { // 1 vazio e 2 ocupado
        slot_temp = inv2.get_slot(posicao2); // copia o item de 2 para o slot temporario

        inv1.set_slot(slot_temp, posicao1); // coloca no vazio do 1
        inv2.esvaziar_slot(posicao2); // apaga do 2

        cout << "Item " << slot_temp.item.get_nome() << " do slot " << posicao2 + 1 << " de " << pers2.get_nome() << " movido para o slot " << posicao1 + 1 << " de " << pers1.get_nome() << endl;
        cout << "Agora o item " << slot_temp.item.get_nome() << " esta no slot " << posicao1 + 1 << " do inventario de " << pers1.get_nome() << endl;
        cout << "e o slot " << posicao2 + 1 << " do inventario de " << pers2.get_nome() << " esta vazio" << endl;

    } else if (inv1.verificar_ocupado(posicao1) && !inv2.verificar_ocupado(posicao2)) { // 1 ocupado e 2 vazio
        slot_temp = inv1.get_slot(posicao1); // copia o item de 1 para o slot temporario

        inv2.set_slot(slot_temp, posicao2); // coloca no vazio do 2
        inv1.esvaziar_slot(posicao1); // apaga do 1

        cout << "Item " << slot_temp.item.get_nome() << " do slot " << posicao1 + 1 << " de " << pers1.get_nome() << " movido para o slot " << posicao2 + 1 << " de " << pers2.get_nome() << endl;
        cout << "Agora o item " << slot_temp.item.get_nome() << " esta no slot " << posicao2 + 1 << " do inventario de " << pers2.get_nome() << endl;
        cout << "e o slot " << posicao1 + 1 << " do inventario de " << pers1.get_nome() << " esta vazio" << endl;

    } else { // 1 ocupado e 2 ocupado
        slot_temp = inv1.get_slot(posicao1); // copia o item de 1 para o temp
        slot_aux = inv2.get_slot(posicao2);  // copia o item de 2 para o aux

        inv1.set_slot(slot_aux, posicao1);  // coloca o item de 2 no slot de 1
        inv2.set_slot(slot_temp, posicao2); // coloca o item de 1 no slot de 2

        cout << "Item " << slot_aux.item.get_nome() << " do slot " << posicao2 + 1 << " de " << pers2.get_nome() << " trocado com o item " << slot_temp.item.get_nome() << " do slot " << posicao1 + 1 << " de " << pers1.get_nome() << endl;
        cout << "Agora o item " << slot_aux.item.get_nome() << " esta no slot " << posicao1 + 1 << " do inventario de " << pers1.get_nome() << endl;
        cout << "e o item " << slot_temp.item.get_nome() << " esta no slot " << posicao2 + 1 << " do inventario de " << pers2.get_nome() << endl;
    }
}