#ifndef REPOSITORIO_BASE_H
#define REPOSITORIO_BASE_H

#include <string>
#include <vector>

class RepositorioBase {
protected:
    std::string caminhoArquivo;

    // Função auxiliar para garantir que o arquivo exista
    void garantirArquivoExiste(); 

public:
    // Construtor que recebe um caminho de arquivo existente
    RepositorioBase(const std::string& caminho);

    // Construtor que gera um nome de arquivo com base no nome do usuário
    RepositorioBase(const std::string& nomeUsuario, bool gerarArquivo);

    // Métodos de leitura e escrita
    std::vector<std::string> LerLinhasDoArquivo();

    // Declarado como 'virtual' para permitir sobrescrita nas classes filhas
    // (conforme solicitado para permitir lógica de substituição de linha)
    virtual void escreverLinhasNoArquivo(const std::vector<std::string>& linhasParaEscrever);

    // Um destrutor virtual é uma boa prática para classes base
    virtual ~RepositorioBase() {} 
};

#endif