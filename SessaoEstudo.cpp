#include "SessaoEstudo.h"
#include <iostream>
#include <ctime>
#include <stdexcept>
#include <iomanip>
#include <sstream>

// construtor default
SessaoEstudo::SessaoEstudo()
    : segundos(0), estadoSessao(parado), tempoInicial(0),
      disciplina(""), descricao("") {}

// construtor parametrizado
SessaoEstudo::SessaoEstudo(long long int segundos, Estado estado, std::string disciplina, std::string descricao)
    :segundos(segundos), estadoSessao(estado), disciplina(disciplina), descricao(descricao), tempoInicial(0) {}

// métodos para gerenciar estados
void SessaoEstudo::sessaoiniciada() {
    if (disciplina.empty()) {
        throw std::logic_error("Nao e possivel iniciar sessao sem disciplina");
    }
    std::cout << "Sessao iniciada para: " << disciplina << std::endl;
}

void SessaoEstudo::sessaopausada() {
    std::cout << "Sessao pausada" << std::endl;
}

void SessaoEstudo::sessaofinalizada() {
     if (segundos < 0) {
        throw std::logic_error("Tempo de sessao invalido");
    }
    std::cout << "Sessao finalizada. Tempo total: " << segundos << " segundos" << std::endl;
}

// Função auxiliar para obter data e hora 
void SessaoEstudo::obterDataHoraAtual(std::string& data, std::string& hora) {
    std::time_t agora = std::time(nullptr);
    std::tm* tempoLocal = std::localtime(&agora);
    
    std::stringstream ssData, ssHora;
    
    // Formata data: dd/mm/aa
    ssData << std::setfill('0') << std::setw(2) << tempoLocal->tm_mday << "/"
           << std::setfill('0') << std::setw(2) << (tempoLocal->tm_mon + 1) << "/"
           << std::setfill('0') << std::setw(2) << (tempoLocal->tm_year % 100);
    
    // Formata hora: hh:mm:ss
    ssHora << std::setfill('0') << std::setw(2) << tempoLocal->tm_hour << ":"
           << std::setfill('0') << std::setw(2) << tempoLocal->tm_min << ":"
           << std::setfill('0') << std::setw(2) << tempoLocal->tm_sec;
    
    data = ssData.str();
    hora = ssHora.str();
}

// Gerenciar estado
void SessaoEstudo::gerenciar() {
    switch(estadoSessao) {
      case 0:
            std::cout << "Sessao parada" << std::endl;
            break;
        case 1:
            std::cout << "Sessao em andamento..." << std::endl;
            break;
        case 2:
            std::cout << "Sessao pausada" << std::endl;
            break;
        default:
            throw std::logic_error("Estado invalido nao detectado");

    }
}

// iniciar cronômetro
void SessaoEstudo::iniciar() {
    if (estadoSessao == parado) {
        tempoInicial = time(nullptr);
        estadoSessao = rodando;
        
        // Registrar data e hora de início
        obterDataHoraAtual(dataInicio, horarioInicio);
        
        sessaoiniciada();
    } else if (estadoSessao == rodando) {
        throw std::logic_error("Sessao ja está em andamento");
    } else if (estadoSessao == pausado) {
        throw std::logic_error("Sessao esta pausada. Use continuar() em vez de iniciar()");
    }
}

// Pausar cronômetro
void SessaoEstudo::pausar() {
    if (estadoSessao == rodando) {
        long long int tempoAtual = std::time(nullptr);
        segundos += (tempoAtual - tempoInicial);
        estadoSessao = pausado;
        sessaopausada();
    } else if (estadoSessao == parado) {
        throw std::logic_error("Sessao não esta em andamento");
    } else if (estadoSessao == pausado) {
        throw std::logic_error("Sessao ja está pausada");
    }
}

// Resetar cronômetro
void SessaoEstudo::resetar() {
    segundos = 0;
    tempoInicial = 0;
    estadoSessao = parado;
    
    // Limpar dados de data/hora
    dataInicio = "";
    dataFinal = "";
    horarioInicio = "";
    horarioFinal = "";
    
    std::cout << "Sessao resetada" << std::endl;
}

// continuar sessão pausada
void SessaoEstudo::continuar() {
    if (estadoSessao == pausado) {
        tempoInicial = time(nullptr);
        estadoSessao = rodando;
        std::cout << "Sessao retomada" << std::endl;
    } else if (estadoSessao == parado) {
        throw std::logic_error("Sessao nao esta pausada. Use iniciar()");
    } else if (estadoSessao == rodando) {
        throw std::logic_error("Sessao ja esta em andamento");
    }
}

void SessaoEstudo::finalizar() {
    if (estadoSessao == rodando) {
        // Registrar tempo final antes de pausar
        long long int tempoAtual = time(nullptr);
        segundos += (tempoAtual - tempoInicial);
        
    }

    // Registrar data e hora final
    obterDataHoraAtual(dataFinal, horarioFinal);
    
    sessaofinalizada();
    estadoSessao = parado;
}


long long int SessaoEstudo::getSegundos() const {
    // Se está rodando, adiciona o tempo decorrido
    if (estadoSessao == rodando) {
        long long int tempoAtual = time(nullptr);
        return segundos + (tempoAtual - tempoInicial);
    }
    return segundos;
}


std::string SessaoEstudo::getDisciplina() const { return disciplina; }
std::string SessaoEstudo::getDescricao() const { return descricao; }
std::string SessaoEstudo::getDataInicio() const { return dataInicio; }
std::string SessaoEstudo::getDataFinal() const { return dataFinal; }
std::string SessaoEstudo::getHorarioInicio() const { return horarioInicio; }
std::string SessaoEstudo::getHorarioFinal() const { return horarioFinal; }
SessaoEstudo::Estado SessaoEstudo::getEstado() const {return estadoSessao;}

void SessaoEstudo::setDisciplina(const std::string& d) { disciplina = d; }
void SessaoEstudo::setDescricao(const std::string& d) { descricao = d; }
void SessaoEstudo::setDataInicio(const std::string& d) { dataInicio = d; }
void SessaoEstudo::setDataFinal(const std::string& d)  { dataFinal = d; }
void SessaoEstudo::setHoraInicio(const std::string& h) { horarioInicio = h; }
void SessaoEstudo::setHoraFinal(const std::string& h)  { horarioFinal = h; }
