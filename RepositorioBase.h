#ifndef REPOSITORIO_BASE_H
#define REPOSITORIO_BASE_H

#include <string>
#include <vector>

class RepositorioBase {
protected:
    std::string caminhoArquivo;

public:
    // Construtor que recebe um caminho de arquivo existente
    RepositorioBase(const std::string& caminho);

    // Métodos de leitura e escrita
    std::vector<std::string> LerLinhasDoArquivo();

    // Declarado como 'virtual' para permitir sobrescrita nas classes filhas
    virtual void escreverLinhasNoArquivo(const std::vector<std::string>& linhasParaEscrever);

    // Destrutor virtual 
    virtual ~RepositorioBase() {} 
};

#endif