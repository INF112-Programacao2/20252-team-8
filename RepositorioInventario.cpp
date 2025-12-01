#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "RepositorioInventario.h"

// ==========================================================
// CONSTRUTOR
// ==========================================================
RepositorioInventario::RepositorioInventario(const std::string& nomeUsuario)
    : RepositorioBase(nomeUsuario + "_inventario.txt", true) {}


// ==========================================================
// ADICIONAR ITEM
// ==========================================================
void RepositorioInventario::adicionarItem(int id) {
    if (possuiItem(id)) {
        std::cout << "Item ja esta no inventario." << std::endl;
        return;
    }

    // Adiciona o ID no final do arquivo (Modo Append = true)
    std::vector<std::string> linha = { std::to_string(id) };
    this->escreverLinhasNoArquivo(linha, true);
}


// ==========================================================
// VERIFICAR POSSE
// ==========================================================
bool RepositorioInventario::possuiItem(int id) {
    std::vector<std::string> linhas = LerLinhasDoArquivo();
    
    for (const auto& linha : linhas) {
        try {
            if (std::stoi(linha) == id) return true;
        } catch (...) { continue; }
    }
    return false;
}


// Le repositorio e retorna IDs brutos dos Itens
std::vector<int> RepositorioInventario::carregarIds() {
    std::vector<int> ids;
    std::vector<std::string> linhas = LerLinhasDoArquivo();

    for (const auto& linha : linhas) {
        try {
            if(!linha.empty()) ids.push_back(std::stoi(linha));
        } catch(...) {}
    }
    return ids;
}