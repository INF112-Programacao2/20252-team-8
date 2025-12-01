#ifndef REPOSITORIO_INVENTARIO_H
#define REPOSITORIO_INVENTARIO_H

#include <vector>
#include <string>

class RepositorioInventario {
private:
    std::string caminhoArquivo;
    std::string nomeUsuario;
public:
    // Construtor
    RepositorioInventario(const std::string& nome);

    std::vector<std::string> carregarItens();

    // Método para salvar novos itens
    void adicionarItem(const std::string& dadosItem);
};

#endif