#include "RepositorioInventario.h"
#include <fstream>
#include <iostream>

RepositorioInventario::RepositorioInventario() {
    this->caminhoArquivo = "inventario.txt";
}

// --- IMPLEMENTAÇÃO DO MÉTODO QUE FALTAVA ---
std::vector<std::string> RepositorioInventario::carregarItens() {
    std::vector<std::string> linhas;
    std::ifstream arquivo(this->caminhoArquivo);

    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha)) {
            if (!linha.empty()) {
                linhas.push_back(linha);
            }
        }
        arquivo.close();
    } else {
        // Se não existir, cria um vazio
        std::ofstream novoArquivo(this->caminhoArquivo);
        novoArquivo.close();
    }

    return linhas;
}

void RepositorioInventario::adicionarItem(const std::string& dadosItem) {
    std::ofstream arquivo(this->caminhoArquivo, std::ios::app);
    if (arquivo.is_open()) {
        arquivo << dadosItem << "\n";
        arquivo.close();
    }
}