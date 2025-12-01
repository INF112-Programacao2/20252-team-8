#include "RepositorioEstudos.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// Construtor
RepositorioEstudos::RepositorioEstudos(const std::string& nomeUsuario)
    : RepositorioBase(nomeUsuario + "_estudos.txt", true) {} // true = usa construtor 2


// Abre arquivo e faz um append com informações da nova sessão
void RepositorioEstudos::adicionarSessao(const SessaoEstudo& sessao) {
    // 1. Prepara as linhas da nova sessão
    std::vector<std::string> dadosSessao;
    
    dadosSessao.push_back("--- SESSAO ---");
    dadosSessao.push_back("Disciplina: " + sessao.getDisciplina());
    dadosSessao.push_back("Descricao: " + sessao.getDescricao());
    dadosSessao.push_back("Tempo: " + std::to_string(sessao.getSegundos()));
    dadosSessao.push_back("DataInicio: " + sessao.getDataInicio());
    dadosSessao.push_back("DataFinal: " + sessao.getDataFinal());
    dadosSessao.push_back("HoraInicio: " + sessao.getHorarioInicio());
    dadosSessao.push_back("HoraFinal: " + sessao.getHorarioFinal());
    
    // 2. Salva no arquivo (Modo Append)
    this->escreverLinhasNoArquivo(dadosSessao, true); 
}


// Le repositorio e retorna vector de sessões de estudo
std::vector<SessaoEstudo> RepositorioEstudos::obterHistorico() const {
    std::vector<SessaoEstudo> historico;
    std::vector<std::string> linhas = LerLinhasDoArquivo();
    
    // 1. Variáveis temporárias para TODAS as informações
    std::string disc = "", desc = "";
    std::string dataIni = "", dataFim = "";
    std::string horaIni = "", horaFim = "";
    long long int tempo = 0;
    
    for (const auto& linha : linhas) {
        // Parse dos campos simples
        if (linha.find("Disciplina: ") != std::string::npos) {
            disc = linha.substr(12);
        }
        else if (linha.find("Descricao: ") != std::string::npos) {
            desc = linha.substr(11);
        }
        else if (linha.find("Tempo: ") != std::string::npos) {
            try { tempo = std::stoll(linha.substr(7)); } catch(...) { tempo = 0; }
        }
        // Parse das Datas e Horas (Note os índices baseados no tamanho da string)
        else if (linha.find("DataInicio: ") != std::string::npos) {
            dataIni = linha.substr(12); // "DataInicio: " tem 12 chars
        }
        else if (linha.find("DataFinal: ") != std::string::npos) {
            dataFim = linha.substr(11); // "DataFinal: " tem 11 chars
        }
        else if (linha.find("HoraInicio: ") != std::string::npos) {
            horaIni = linha.substr(12); // "HoraInicio: " tem 12 chars
        }
        // 2. O gatilho: HoraFinal é o último dado salvo, então criamos o objeto aqui
        else if (linha.find("HoraFinal: ") != std::string::npos) {
            horaFim = linha.substr(11); // "HoraFinal: " tem 11 chars
            
            // Cria o objeto base com o construtor que você já tem
            SessaoEstudo s(tempo, 0, disc, desc);
            
            // Popula os dados de tempo/data que não estavam no construtor
            // (Você precisará adicionar esses setters na SessaoEstudo, veja abaixo)
            s.setDataInicio(dataIni);
            s.setDataFinal(dataFim);
            s.setHoraInicio(horaIni);
            s.setHoraFinal(horaFim);
            
            historico.push_back(s);

            // 3. Limpeza das variáveis para a próxima iteração
            disc = ""; desc = ""; 
            dataIni = ""; dataFim = "";
            horaIni = ""; horaFim = "";
            tempo = 0;
        }
    }
    return historico;
}


// Retorna número de sessões
int RepositorioEstudos::getQuantidade() const{
    return obterHistorico().size();
}


// Retorna o tempo total de estudos de uma disciplina específica (em segundos)
long long int RepositorioEstudos::getTempoTotalPorDisciplina(const std::string& disciplina) const {
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


// Retorna tempo total (em segundos)
long long int RepositorioEstudos::getTempoTotal() const {
    std::vector<SessaoEstudo> sessoes = obterHistorico();
        long long int total = 0;
        for (const auto& s : sessoes) {
            total += s.getSegundos(); // Note que no seu .h getter é const, perfeito
        }
        return total;
}

