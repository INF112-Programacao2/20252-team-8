#ifndef REPOSITORIO_INVENTARIO_H
#define REPOSITORIO_INVENTARIO_H

#include <vector>
#include <string>

class RepositorioInventario {
private:
    std::string caminhoArquivo;

public:
    // Construtor
    RepositorioInventario();

    // --- ESTE É O MÉTODO QUE O ERRO DIZ ESTAR FALTANDO ---
    std::vector<std::string> carregarItens();

    // Método para salvar novos itens
    void adicionarItem(const std::string& dadosItem);
};

#endif