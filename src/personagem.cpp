#include "../include/personagem.hpp"
using namespace std;

// construtor: inicializa um personagem e seu inventario (relação de composição)
Personagem::Personagem(string nome, int tam_max_inv): nome(nome), inventario(tam_max_inv) {
    qtd_personagens++;
}


// inicialização da variavel que armazena a quantidade de personagens existentes
int Personagem::qtd_personagens = 0;

// retorna a quantidade de personagens existentes
int Personagem::get_qtd_personagens() {
    return qtd_personagens;
}

// menu de criacao de um personagem. usa o construtor de personagem. imprime uma quebra de linha se a quantidade de personagens for impar.
Personagem Personagem::criar_personagem() {
    if(Personagem::get_qtd_personagens() % 2 == 1) cout<<endl;

    cout<<"-<- Criacao do Personagem "<<Personagem::get_qtd_personagens()+1<<" ->-"<<endl;

    cout<<"Digite a seguir o nome do seu personagem"<<endl;
    string nome_personagem = ler_nome();

    cout<<"Digite a seguir o tamanho do inventario do seu personagem"<<endl;
    int tam_inventario_personagem = ler_tam_max_inventario();

    Personagem personagem(nome_personagem, tam_inventario_personagem);
    
    return personagem;
}

// retorna o nome do personagem
string Personagem::get_nome() {
    return nome;
}

// imprime o nome do personagem e seu respectivo inventario
void Personagem::print_inventario_personagem() {
    cout<<endl<<"Inventario de "<<nome<<":";
    inventario.print_inventario();
}

// adiciona um item no inventario do personagem
void Personagem::adicionar_item_inventario(string nome_item, int qtd){
    cout<<endl<<"Adicionando no inventario de "<<nome<<":"<<endl;
    inventario.adicionar_item(nome_item, qtd);
}

// remove um item de um slot especifico do inventario do personagem
void Personagem::remover_item_inventario(int posicao, int qtd){
    cout<<endl<<"Removendo no inventario de "<<nome<<":"<<endl;
    inventario.remover_item(posicao, qtd);
}

// troca 2 itens de slot no inventario do personagem
void Personagem::trocar_itens_inventario(int posicao1, int posicao2){
    cout<<endl<<"Trocando no inventario de "<<nome<<":"<<endl;
    inventario.trocar_item(posicao1, posicao2);
}

// troca um item entre 2 personagens
void Personagem::trocar_itens_inventario_entre_personagens(Personagem &pers1, Personagem &pers2, int posicao1, int posicao2) {
    cout<<endl<<"Trocando itens entre "<<pers1.get_nome()<<" e "<<pers2.get_nome()<<":"<<endl;

    formatar_posicao(posicao1);
    formatar_posicao(posicao2);

    if(pers1.inventario.verificar_posicao(posicao1) || pers2.inventario.verificar_posicao(posicao2)) {
        cout<<"Na troca de itens entre personagens: "<<endl;
        cout<<"Escolha uma posicao que esteja entre 1 e "<<pers1.inventario.get_tam_max_inventario()<<" para o personagem "<<pers1.get_nome()<<endl;
        cout<<"E escolha uma posicao que esteja entre 1 e "<<pers2.inventario.get_tam_max_inventario()<<" para o personagem "<<pers2.get_nome()<<endl;
        cout<<"Operacao nao realizada."<<endl;

        return;
    }

    if(!pers1.inventario.verificar_ocupado(posicao1) && !pers2.inventario.verificar_ocupado(posicao2)) {
        cout<<"Slot "<<posicao1+1<<" de "<<pers1.get_nome()<<" e slot "<<posicao2+1<<" de "<<pers2.get_nome()<<"estao vazios"<<endl;
        return;
    }
    
    Slot slot_temp, slot_aux;

    if(!pers1.inventario.verificar_ocupado(posicao1) && pers2.inventario.verificar_ocupado(posicao2)) { // 1 vazio e 2 ocupado
        slot_temp = pers2.inventario.get_slot(posicao2); // copia o item de 2 para o slot temporario

        pers1.inventario.set_slot(slot_temp, posicao1); // coloca no vazio do 1
        pers2.inventario.esvaziar_slot(posicao2); // apaga do 2

        cout<<"Item "<<slot_temp.item.get_nome()<<" do slot "<<posicao2+1<<" de "<<pers2.get_nome()<<" movido para o slot "<<posicao1+1<<" de "<<pers1.get_nome()<<endl;
        cout<<"Agora o item "<<slot_temp.item.get_nome()<<" esta no slot "<<posicao1+1<<" do inventario de "<<pers1.get_nome()<<endl;
        cout<<"e o slot "<<posicao2+1<<" do inventario de "<<pers2.get_nome()<<" esta vazio"<<endl;

    } else if(pers1.inventario.verificar_ocupado(posicao1) && !pers2.inventario.verificar_ocupado(posicao2)) { // 1 ocupado e 2 vazio
        slot_temp = pers1.inventario.get_slot(posicao1); // copia o item de 1 para o slot temporario

        pers2.inventario.set_slot(slot_temp, posicao2); // coloca no vazio do 2
        pers1.inventario.esvaziar_slot(posicao1); // apaga do 1

        cout<<"Item "<<slot_temp.item.get_nome()<<" do slot "<<posicao1+1<<" de "<<pers1.get_nome()<<" movido para o slot "<<posicao2+1<<" de "<<pers2.get_nome()<<endl;
        cout<<"Agora o item "<<slot_temp.item.get_nome()<<" esta no slot "<<posicao2+1<<" do inventario de "<<pers2.get_nome()<<endl;
        cout<<"e o slot "<<posicao1+1<<" do inventario de "<<pers1.get_nome()<<" esta vazio"<<endl;

    } else { // 1 ocupado e 2 ocupado
        slot_temp = pers1.inventario.get_slot(posicao1); // copia o item de 1 para o temp
        slot_aux = pers2.inventario.get_slot(posicao2);  // copia o item de 2 para o aux

        pers1.inventario.set_slot(slot_aux, posicao1);  // coloca o item de 2 no slot de 1
        pers2.inventario.set_slot(slot_temp, posicao2); // coloca o item de 1 no slot de 2

        // Substitua o primeiro cout do bloco 'else' por este:
        cout<<"Item "<<slot_aux.item.get_nome()<<" do slot "<<posicao2+1<<" de "<<pers2.get_nome()<<" trocado com o item "<<slot_temp.item.get_nome()<<" do slot "<<posicao1+1<<" de "<<pers1.get_nome()<<endl;
        cout<<"Agora o item "<<slot_aux.item.get_nome()<<" esta no slot "<<posicao1+1<<" do inventario de "<<pers1.get_nome()<<endl;
        cout<<"e o item "<<slot_temp.item.get_nome()<<" esta no slot "<<posicao2+1<<" do inventario de "<<pers2.get_nome()<<endl;
    }
}
