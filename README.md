# 💼 Sistema de Inventário
### Teste Técnico LabTIME

## 📹 Vídeo de Apresentação
- Vídeo testando o programa e explicando no Minecraft como funcionam as funções de adicionar, remover, trocar itens em um inventário e trocar itens entre dois inventários.

| *Clique na imagem abaixo para ver o vídeo 👇* |
| :---: |
| <a href="https://www.youtube.com/watch?v=EvJXv69PBZs"><img src="https://img.youtube.com/vi/EvJXv69PBZs/maxresdefault.jpg" width="500"></a> |

## 📖 O que é:
- Um sistema de gerenciamento de inventario via terminal, em que o usuário pode criar um personagem e associar um inventário de itens à esse personagem.
- É possível adicionar, remover e trocar itens no inventário do personagem.
- Também é possível trocar itens entre dois personagens.
- Minha maior referência foi o sistema de inventário do jogo Minecraft, por também ter um pack equivalente a 64.

## 📑 Organização
- O sistema foi organizado separando cada classe (Item, Itens, Inventario, Personagem) em arquivos .hpp e .cpp separados. Além do arquivo main e das funções auxiliares. Modularização feita para melhor entendimento e manutenção do código.
- O sistema usa POO em: classes, objetos, relação de composição (Personagem possui um Inventário), abstração, encapsulamento e variáveis/métodos estáticos (pertencentes à classe).
- O sistema também usa structs, para armazenar variáveis que precisam operar juntas (como um slot que possui item existente/vazio e ocupação ocupado/desocupado), comentários resumidos em variáveis e funções, para facilitar entendimento, e definições de constantes globais, para melhor entendimento e visualização do código.
- Além disso, organização padrão para melhor uso/otimização de C++: como "#pragma once" em .hpp, para compilar somente uma vez o .hpp, "using namespace std" somente em .cpp, evitando uso de namespace global em .hpp e conflito com nomes de outras bibliotecas, somente bibliotecas necessárias (como vector), leitura de entrada de dados com "getline" e verificação de "end of file" (EOF), para evitar erros de buffer de entrada e leitura.
- Boas práticas de programação: early return, deixando o código mais limpo para visualização e tratando casos de erro logo no início, modularização, para facilitar manutenções futuras e entendimento do código, variáveis sendo passadas por referência (&) em funções, para evitar cópia de variáveis e gasto desnecessário de memória, constantes globais bem definidas, para evitar números "perdidos" pelo código e encapsulamento em POO, deixando atributos privados (além de métodos privados que o usuário não precisa acessar) e métodos públicos para manipular esses atributos.

## 🏹 Itens:
- Atualmente, existem 2 tipos de itens: empilhaveis (possível acumular 64 quantidades em um slot) e não empilháveis (ocupam um slot inteiro);
- Empilháveis: flecha, poção, tocha;
- Não empilháveis: espada, escudo, arco.
- OBS: itens vazios: Quando um slot está desocupado ele armazena um item com nome "vazio" e qtd 0. Achei essa opção melhor do que trabalhar com ponteiros que apontam para itens nulos (NULL). Também pesquisei sobre isso (no Gemini) e descobri que o jeito que eu fiz é melhor, principalmente em jogos, por causa da rápida velocidade para carregar coisas que já estão no cache de memória, além de evitar o problema de falha de segmentação (segmentation fault).

## 📥 Dinâmica de empilhamento (inserção/adição):
- Ao adicionar um item (com nome do item e quantidade), é procurado um slot disponível para ocupar.
- Se o item for empilhável: varre todo o inventário procurando um slot do mesmo item, para empilhar a quantidade até chegar em 64. Se o slot ja tiver 64, procura o próximo slot livre para ocupar.
- Se o item for não empilhável: varre todo o inventário procurando o próximo slot livre e ocupa.
### Explicação detalhada sobre empilhamento:
- No inventário, a função "adicionar_item" executa a tarefa de empilhar até chegar em 64 em slots ja ocupados pelo mesmo item, se for empilhável e tiver espaço.
- Caso todos os slots do mesmo item empilhável já estejam com 64 ou o item seja não empilhável (ocupe um slot inteiro) e ainda tenha quantidade para adicionar, é chamada a função "distribuir_sobra", que procura o primeiro slot vazio do inventário e coloca a quantidade restante nesse slot, enquanto tiver quantidade restante (loop while). 
- Caso o inventário esteja cheio, a quantidade é descartada do inventário.

## 📤 Dinâmica de remoção (esvaziamento/subtração):
- Na remoção/subtração (com posição do slot e quantidade) é procurado a posição do slot desejado.
- Se a quantidade for maior que a existente no slot, informa um erro e a operação não é realizada.
- Se a quantidade for o total existente no slot, transforma o slot em vazio.
- Se a quantidade for menor que a existente no slot, apenas subtrai a quantidade.

## 🔀 Dinâmica de troca:
- No inventário do personagem: duas posições são escolhidas e os itens sao trocados de slot. Se um deles for vazio, a troca ocorre do mesmo modo.
- Entre dois personagens: uma posição é escolhida no inventário de cada personagem e os itens sao trocados de inventários. Mesma situação se um for vazio.

## ⌚ Melhorias futuras
- Pensando em um sistema com uma grande quantidade de itens, seria necessário usar um banco de dados para armazenar esses itens existentes. Por enquanto só existem 6 itens, então o sistema não apresenta nenhum problema de desempenho.
- Por ser um sistema de inventário de jogo, o foco seria consistência nos dados, então poderia ser utilizado SQLite (se o jogo for singleplayer offline), PostgreSQL (se o jogo for multiplayer online) ou, pensando em baixa latência + alta consistência, uso de Redis para salvar os dados na RAM e PostgreSQL para salvar os dados definitivamente de tempos em tempos.
- Atualmente, o sistema de busca de itens (na operação de adição) percorre todo o inventário com um laço for. Em um inventário muito grande, isso iria demorar bastante. No meu trabalho de AED1, tive a mesma questão. Então, a resposta é a mesma: poderia ser utilizado uma árvore binária de busca ou uma tabela hash, para a busca ser quase instantânea.

## 🤖 Uso de IA
- Usei o Gemini Pro 3.1 para me ajudar a fazer esse projeto. Usei para entender melhor a possível atualização futura de sistema gerenciador de banco de dados, sobre qual usar pensando em consistência e latência, resolução de problemas na entrada de dados, usando "getline" e verificação de "EOF", organização das pastas do código, deixando .hpp em "include" e .cpp em "src", revisão de conceitos de POO, como relação de composição e métodos estáticos, e verificação do README, para ver se eu realmente escrevi um README muito bom (mas não usei IA para escrever o README).

## 💻 Como compilar e executar

Testando via terminal:
```bash
git clone https://github.com/vvvvvdal/teste-tecnico-labtime
cd teste-tecnico-labtime/src
g++ *.cpp -o teste.out
./teste.out
```

Testando via arquivo de texto "teste.txt":
```bash
git clone https://github.com/vvvvvdal/teste-tecnico-labtime
cd teste-tecnico-labtime/src
g++ *.cpp -o teste.out
./teste.out < teste.txt
```
