#ifndef REPOSITORIO_ESTUDOS_H
#define REPOSITORIO_ESTUDOS_H

#include "RepositorioBase.h"
#include "SessaoEstudo.h"
#include <string>
#include <vector>

class RepositorioEstudos : public RepositorioBase {
public:
    // Construtor: Recebe o nome do usuário para criar "nome_estudos.txt"
    RepositorioEstudos(const std::string& nomeUsuario);

    // Adiciona sessão, atualiza cabeçalho e salva no arquivo
    void adicionarSessao(const SessaoEstudo& sessao);

    // Retorna o total de sessões
    int getQuantidade() const;

    // Lê o arquivo e retorna o vetor de sessões 
    std::vector<SessaoEstudo> obterHistorico() const;

    // Retorna tempo total geral
    long long int getTempoTotal() const;

    // Retorna o tempo total de estudos de uma disciplina específica
    long long int getTempoTotalPorDisciplina(const std::string& disciplina) const;
    
};

#endif
