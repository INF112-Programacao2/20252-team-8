#include "ControladorInventario.h"
#include <iostream>

// Construtor
// Inicializa os ponteiros e a tela (que é composta)
ControladorInventario::ControladorInventario(Usuario* usuario, RepositorioInventario* repositorio)
    : usuario(usuario), RepositorioInventario(repositorio) {
}


// Método Principal
void ControladorInventario::executar() {
    bool sair = false;

    while (!sair) {
        // 1. Buscar dados atualizados
        // O repositório carrega a lista de itens que o usuário já comprou
        std::vector<Item*> itensComprados = repositorio->obterItensComprados();

        // 2. Exibir na Tela
        // Passamos a lista para a tela desenhar e aguardamos a escolha do usuário
        // Assumimos que mostrarMenu retorna o índice escolhido ou 0 para voltar
        int opcao = tela.mostrarMenu(itensComprados);

        // 3. Processar escolha
        if (opcao == 0) {
            sair = true; // Voltar ao menu principal
        } 
        else {
            // Ajustamos o índice (Menu é 1..N, Vetor é 0..N-1)
            int indiceVetor = opcao - 1;

            if (indiceVetor >= 0 && indiceVetor < itensComprados.size()) {
                equiparItem(indiceVetor);
            } else {
                tela.mostrarMensagem("Opcao invalida!");
            }
        }
    }
}

// Método Auxiliar para Equipar
void ControladorInventario::equiparItem(int indiceItem) {
    // Recupera o item específico da lista do repositório
    std::vector<Item*> itens = repositorio->obterItensComprados();
    Item* itemSelecionado = itens[indiceItem];

    // Aqui conectamos com a Entidade Usuario
    // O usuário guarda o estado atual, então avisamos a ele qual item usar
    // Supondo que a classe Usuario tenha um método 'equiparItem' ou 'setItemAtivo'
    usuario->equiparItem(itemSelecionado);

    // Feedback visual
    tela.mostrarMensagem("Voce equipou: " + itemSelecionado->getNome());
    
    // Opcional: Se o equipamento for algo permanente, poderia chamar 
    // repositorio->salvarUsuario(usuario) aqui, mas geralmente salvamos ao sair.
}