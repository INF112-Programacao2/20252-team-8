#include "RepositorioEstudos.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// Construtor
RepositorioEstudos::RepositorioEstudos(const std::string& nomeUsuario)
    : RepositorioBase(nomeUsuario + "_estudos.txt", true) {} // true = usa construtor 2


// Abre arquivo e faz um append com informações da nova sessão
void RepositorioEstudos::adicionarSessao(SessaoEstudo& sessao) {
    // 1. Prepara as linhas da nova sessão
    std::vector<std::string> dadosSessao;
    
    dadosSessao.push_back("--- SESSAO ---");
    dadosSessao.push_back("Disciplina: " + sessao.getDisciplina());
    dadosSessao.push_back("Descricao: " + sessao.getDescricao());
    dadosSessao.push_back("Tempo: " + std::to_string(sessao.getSegundos()));
    dadosSessao.push_back("Data: " + sessao.getDataInicio()); // Ex: 01/01/24
    
    // 2. Salva no arquivo (Modo Append)
    this->escreverLinhasNoArquivo(dadosSessao, true); 
}


// Le repositorio e retorna vector de sessões de estudo
std::vector<SessaoEstudo> RepositorioEstudos::obterHistorico() {
    std::vector<SessaoEstudo> historico;
    std::vector<std::string> linhas = LerLinhasDoArquivo();
    
    // Variáveis temporárias para montar o objeto
    std::string disc, desc, data;
    long long int tempo = 0;
    
    for (const auto& linha : linhas) {
        if (linha.find("Disciplina: ") != std::string::npos) {
            disc = linha.substr(12);
        }
        else if (linha.find("Descricao: ") != std::string::npos) {
            desc = linha.substr(11);
        }
        else if (linha.find("Tempo: ") != std::string::npos) {
            try { tempo = std::stoll(linha.substr(7)); } catch(...) { tempo = 0; }
        }
        else if (linha.find("Data: ") != std::string::npos) {
            data = linha.substr(6);
            
            // Quando lemos a última info, criamos o objeto e adicionamos ao vetor
            SessaoEstudo s(tempo, 0, disc, desc);
            
            s.setDataInicio(data);
            
            historico.push_back(s);
        }
    }
    return historico;
}


// Retorna número de sessões
int RepositorioEstudos::getQuantidade() {
    return obterHistorico().size();
}


// Retorna o tempo total de estudos de uma disciplina específica
long long int RepositorioEstudos::getTempoTotalPorDisciplina(const std::string& disciplina) {
    std::vector<SessaoEstudo> sessoes = obterHistorico();
        long long int total = 0;
        for (auto& s : sessoes) {
            // Comparação de string simples
            if (s.getDisciplina() == disciplina) {
                total += s.getSegundos();
            }
        }
        return total;
}


// Retorna tempo total
long long int RepositorioEstudos::getTempoTotal() {
    std::vector<SessaoEstudo> sessoes = obterHistorico();
        long long int total = 0;
        for (auto& s : sessoes) {
            total += s.getSegundos(); // Note que no seu .h getter é const, perfeito
        }
        return total;
}

