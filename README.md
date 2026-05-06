# 💼 Sistema de Inventário

## 📹 Vídeo de Apresentação
Vídeo testando o programa e explicando (com analogias ao Minecraft) como funcionam as funções de adicionar, remover, trocar itens no mesmo inventário e transferir itens entre dois inventários distintos.

*Nota:* O vídeo está desatualizado em relação as novas refatorações de C++ moderno. Mas a lógica de funcionamento do sistema é a mesma apresentada no vídeo.

| *Clique na imagem abaixo para ver o vídeo 👇* |
| :---: |
| <a href="https://www.youtube.com/watch?v=EvJXv69PBZs"><img src="https://img.youtube.com/vi/EvJXv69PBZs/maxresdefault.jpg" width="500"></a> |

---

## 📖 Sobre o Projeto
Um sistema de gerenciamento de inventário via terminal, desenvolvido em **C++**. O usuário pode criar múltiplos personagens, atribuir capacidades de inventário personalizadas e gerenciar recursos de forma dinâmica.

**Principais Funcionalidades:**
- Criação interativa de personagens.
- Adição, remoção e troca de itens dentro do inventário de um personagem.
- Intercâmbio completo de itens entre inventários de personagens diferentes.
- *Inspiração:* A lógica de agrupamento (packs de 64 unidades) foi fortemente baseada no sistema de inventário do jogo Minecraft.

---

## 🏗️ Arquitetura e C++ Moderno (Refatoração)
O projeto passou por uma rigorosa evolução arquitetural focada em boas práticas de Engenharia de Software, **C++ Moderno** e **Programação Orientada a Objetos (POO)**:

- **Abstrações Modernas:** Substituição completa de macros herdadas do C (`#define`) por constantes resolvidas em tempo de compilação (`constexpr`) e tipagem forte (`enum class`), prevenindo bugs silenciosos de escopo.
- **Gestão de Memória e Performance:** Uso intensivo de passagem de parâmetros por referência constante (`const std::string&`, `const Item&`), evitando cópias desnecessárias na memória (copy elision) e garantindo *Const Correctness*.
- **Encapsulamento e SRP (Princípio da Responsabilidade Única):** As classes de modelo (`Item`, `Inventario`, `Personagem`) são estritamente isoladas. A interface de interação com o usuário (menus e inputs) e o gerenciamento de estado global foram movidos para o fluxo principal e funções auxiliares.
- **Isolamento de Escopo:** Funções de validação e leitura de inputs foram encapsuladas em um `namespace auxiliares`, evitando a poluição do escopo global da aplicação.
- **Uso Idiomático da STL:** Aplicação da função nativa `std::swap` para realizar trocas diretas de memória de forma otimizada entre os *slots* dos inventários, eliminando a alocação de variáveis temporárias.
- **Design de Dados Seguros:** Utilização de `structs` modernas com inicialização padrão para emparelhar itens e *flags* de ocupação (`bool ocupado = false`), simplificando a lógica de validação.

---

## 🏹 Sistema de Itens
Atualmente, a base de dados suporta 2 categorias de itens:
1. **Empilháveis** (Ocupam até 64 unidades por slot): Flecha, Poção, Tocha.
2. **Não Empilháveis** (Ocupam o slot inteiro de forma única): Espada, Escudo, Arco.

> 💡 **Design Pattern para Espaços Vazios:** > Quando um slot está desocupado, ele armazena um objeto do tipo "Vazio" com quantidade 0, ao invés de utilizar ponteiros nulos (`NULL` ou `nullptr`). Em sistemas voltados para jogos, essa abordagem maximiza a performance devido à localidade de cache (Cache Hit) e mitiga completamente os riscos de *Segmentation Fault*.

---

## ⚙️ Dinâmicas do Inventário

### 📥 Adição e Empilhamento
Ao inserir um item, o algoritmo otimiza o espaço disponível:
- **Itens Empilháveis:** O sistema varre o inventário buscando slots que já contenham o mesmo item para preenchê-los até o limite máximo (64). Caso reste quantidade excedente (função `distribuir_sobra`), o sistema localiza os próximos slots vazios e distribui o restante do pacote automaticamente (via loop).
- **Itens Não Empilháveis:** O sistema busca o primeiro slot vazio e o ocupa. Quantidades excedentes preenchem os próximos slots subsequentes.
- *Nota:* Se a capacidade máxima do inventário for atingida, a quantidade excedente do item é processada como "descartada".

### 📤 Remoção
A lógica de subtração realiza tratamento de erros (Early Return) para garantir a integridade dos dados:
- Verifica se a quantidade solicitada é maior que a existente ou se é um valor negativo.
- Se a quantidade removida for igual ao total do slot, o espaço tem seu estado formatado de volta para "Vazio".
- Se for menor, ocorre a subtração aritmética da quantidade.

### 🔀 Trocas (Swap)
- **Interna:** Ocorre a inversão de memória entre dois slots do mesmo inventário. Suporta perfeitamente a movimentação de um item para um espaço vazio.
- **Externa:** Permite cruzar dados entre a classe de dois personagens diferentes, validando posições e ocupações de ambos os lados de forma segura antes de realizar o `swap`.

---

## 🚀 Melhorias Futuras
- **Persistência de Dados:** Para escalar a quantidade de itens, o ideal seria adotar um Banco de Dados. Pensando em alta consistência para um ambiente multiplayer, um PostgreSQL seria ideal. Para otimizar a latência em tempo real, o uso de **Redis** na memória RAM sincronizando em *background* com um banco relacional seria a arquitetura definitiva.
- **Otimização de Busca (Time Complexity):** Atualmente, a busca (`buscar_item`) varre o inventário de forma linear (`O(n)`). Para inventários de grande escala (MMORPGs), isso causaria gargalos. A solução seria refatorar a estrutura de busca implementando uma **Tabela Hash** (Hash Map) ou uma **Árvore Binária de Busca**, reduzindo o tempo de consulta para `O(1)` ou `O(log n)`.

---

## 🤖 Uso de IA
Utilizei ferramentas de IA (Google Gemini) como suporte ao estudo durante o desenvolvimento deste projeto. O uso foi focado em:
- Arquitetura de software: discussão sobre a transição de bancos de dados visando baixa latência vs consistência.
- Resolução de bugs e fluxos de `stdin/stdout` em C++ (limpeza de buffer, validações com `getline` e `EOF`).
- Revisão de paradigmas e **aplicação de refatoração final** baseada em boas práticas (ajuste de *namespaces*, construtores e passagem de memória) para alinhar o projeto ao nível de exigência da indústria.

---

## 💻 Como Compilar e Executar

Para compilar o projeto em sua máquina local, certifique-se de ter um compilador C++ (como o `g++` do GCC) instalado.

**Testando interativamente via terminal:**
```bash
git clone https://github.com/vvvvvdal/teste-tecnico-labtime
cd teste-tecnico-labtime/src
g++ *.cpp -o teste.out
./teste.out
```

**Testando via arquivo de texto "teste.txt":**
```bash
git clone https://github.com/vvvvvdal/teste-tecnico-labtime
cd teste-tecnico-labtime/src
g++ *.cpp -o teste.out
./teste.out < teste.txt
```
