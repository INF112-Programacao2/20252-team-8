#ifndef REPOSITORIO_BASE_H
#define REPOSITORIO_BASE_H

#include <string>
#include <vector>

class RepositorioBase {
protected:
    std::string caminhoArquivo;

public:
    // Construtor 1: Para Gamificação - Gera "nome_repositorio.txt"
    RepositorioBase(const std::string& nomeUsuario);

    // Construtor 2: Novo (Para Inventário e Estudos) - Recebe "nome_inventario.txt"
    // Bool diferencia assinatura do método
    RepositorioBase(const std::string& nomeRepo, bool isCaminho);

    // Métodos de leitura e escrita
    std::vector<std::string> LerLinhasDoArquivo() const;

    // Declarado como 'virtual' para permitir sobrescrita nas classes filhas
    // Escreve no modo truncate por padrão
    virtual void escreverLinhasNoArquivo(const std::vector<std::string>& linhasParaEscrever, bool modoAppend = false);

    // Destrutor virtual 
    virtual ~RepositorioBase() {} 
};

#endif