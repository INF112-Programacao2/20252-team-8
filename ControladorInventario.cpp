#include "ControladorInventario.h"
#include "ItemAudio.h"
#include <iostream>
#include <sstream>

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
    std::vector<std::string> dados = repositorio->carregarItens(); 

    for (const std::string& linha : dados) {
        std::stringstream ss(linha);
        std::string nome, tipo, valorStr, arquivoMusica;

        // Separa a string pelas vírgulas (formato: Nome,Tipo,Valor,Arquivo)
        std::getline(ss, nome, ',');
        std::getline(ss, tipo, ',');
        std::getline(ss, valorStr, ',');
        
        // Tenta ler o nome do arquivo da música (pode não existir para itens antigos)
        if (!ss.eof()) {
            std::getline(ss, arquivoMusica, ',');
        }

        // Remove espaços em branco no início
        if(!nome.empty() && nome.front() == ' ') nome.erase(0, 1);
        if(!tipo.empty() && tipo.front() == ' ') tipo.erase(0, 1);
        if(!arquivoMusica.empty() && arquivoMusica.front() == ' ') 
            arquivoMusica.erase(0, 1);

        // Converte valor para inteiro
        int valor = 0;
        try { 
            if (!valorStr.empty()) valor = std::stoi(valorStr); 
        } catch(...) { 
            valor = 0; 
        }

        // --- LÓGICA DE CRIAÇÃO (FACTORY) ---
        Item* novoItem = nullptr;

        if (tipo == "Audio") {
            // Para músicas, usa o caminho direto do arquivo
            std::string caminhoCompleto;
            if (!arquivoMusica.empty()) {
                // As músicas da loja já tem o nome do arquivo
                caminhoCompleto = "assets/" + arquivoMusica;
            } else {
                // Para itens de áudio antigos
                caminhoCompleto = "assets/" + nome + ".mp3";
            }
            novoItem = new ItemAudio(nome, valor, caminhoCompleto);
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
        int opcao = tela.mostrarInventario(itensCarregados);

        if (opcao == 0) {
            sair = true;
        } 
        else {
            // Ajusta o índice (o menu começa em 1, o vetor em 0)
            int indice = opcao - 1; 
            
            if (indice >= 0 && indice < itensCarregados.size()) {
                // 3. Polimorfismo: Chama usar()
                itensCarregados[indice]->usar();
                
                // Pausa para o usuário ver o resultado
                tela.esperarEnter();
            } else {
                tela.mostrarErro("Opcao invalida.");
            }
        }
    }
}