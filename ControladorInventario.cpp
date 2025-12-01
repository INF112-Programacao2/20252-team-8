#include "ControladorInventario.h"
#include "ItemAudio.h" // Necessário para criar itens que tocam som
#include <iostream>
#include <sstream> // Necessário para dividir as strings (split)

ControladorInventario::ControladorInventario(Usuario* usuario, RepositorioInventario* repo)
    : usuario(usuario), repositorio(repo) {
    // A tela é inicializada automaticamente
}

ControladorInventario::~ControladorInventario() {
    limparMemoria();
}

void ControladorInventario::limparMemoria() {
    for (Item* item : itensCarregados) {
        delete item; // Deleta cada objeto individualmente
    }
    itensCarregados.clear(); // Limpa o vetor
}

void ControladorInventario::carregarItensDoRepositorio() {
    // 1. Limpa a lista antiga para não duplicar
    limparMemoria();

    // 2. Busca dados brutos do repositório
    // O Repositorio deve retornar linhas tipo: "Violao,Audio,500"
    std::vector<std::string> dados = repositorio->carregarItens(); 

    for (const std::string& linha : dados) {
        std::stringstream ss(linha);
        std::string nome, tipo, valorStr;

        // Separa a string pelas vírgulas
        std::getline(ss, nome, ',');
        std::getline(ss, tipo, ',');
        std::getline(ss, valorStr, ',');

        // Remove espaços em branco no início (trim simples), se houver
        if(!nome.empty() && nome.front() == ' ') nome.erase(0, 1);
        if(!tipo.empty() && tipo.front() == ' ') tipo.erase(0, 1);

        // Converte valor para inteiro
        int valor = 0;
        try { 
            if (!valorStr.empty()) valor = std::stoi(valorStr); 
        } catch(...) { valor = 0; }

        // --- LÓGICA DE CRIAÇÃO (FACTORY) ---
        Item* novoItem = nullptr;

        if (tipo == "Audio" || tipo == "Musica") {
            // Se for do tipo Audio, cria ItemAudio e define o caminho do arquivo
            std::string caminho = "assets/" + nome + ".mp3";
            novoItem = new ItemAudio(nome, valor, caminho);
        } 
        else {
            // Se for qualquer outro tipo, cria Item comum
            novoItem = new Item(nome, tipo, valor);
        }

        // Adiciona na lista se foi criado com sucesso
        if (novoItem) {
            itensCarregados.push_back(novoItem);
        }
    }
}

void ControladorInventario::executar() {
    bool sair = false;
    while (!sair) {
        // 1. Carrega (ou recarrega) os itens do arquivo
        carregarItensDoRepositorio();

        // 2. Chama a Tela para mostrar a lista
        // A tela retorna 0 para Voltar ou o número do item escolhido
        int opcao = tela.mostrarInventario(itensCarregados);

        if (opcao == 0) {
            sair = true;
        } 
        else {
            // Ajusta o índice (o menu começa em 1, o vetor em 0)
            int indice = opcao - 1; 
            
            if (indice >= 0 && indice < itensCarregados.size()) {
                // 3. Polimorfismo: Chama usar()
                // Se for ItemAudio, vai tocar música. Se for Item, vai mostrar texto.
                itensCarregados[indice]->usar();
                
                // Pausa para o usuário ver o resultado
                tela.esperarEnter();
            } else {
                tela.mostrarErro("Opcao invalida.");
            }
        }
    }
}