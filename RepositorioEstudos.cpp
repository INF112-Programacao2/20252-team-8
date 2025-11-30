#include "RepositorioEstudos.h"
#include <iostream>
#include <vector>

// construtor
RepositorioEstudos::RepositorioEstudos(std::string idUsuario)
    : idUsuario(idUsuario), quantidade(0), capacidade(2), tempoTotal(0)
{
    // aloca array dinâmico
    sessoes = new SessaoEstudo[capacidade];
}

// destrutor
RepositorioEstudos::~RepositorioEstudos() {
    delete[] sessoes; // libera memória
}

// adiciona sessão com realocação dinâmica
void RepositorioEstudos::adicionarSessao(const SessaoEstudo& sessao) {
    if (quantidade >= capacidade) {
        // dobra o tamanho
        capacidade *= 2;
        // cria novo array maior
        SessaoEstudo* novoArray = new SessaoEstudo[capacidade];
        // copia sessões antigas
        for (int i = 0; i < quantidade; i++) {
            novoArray[i] = sessoes[i];
        }
        // libera array antigo
        delete[] sessoes;
        // aponta para novo array
        sessoes = novoArray;
    }
    // adiciona nova sessão
    sessoes[quantidade] = sessao;
    quantidade++;
    std::cout << "Sessão adicionada. Total: " << quantidade << " sessões" << std::endl;
}

// retorna número de sessões
int RepositorioEstudos::getQuantidade() const {
    return quantidade;
}

// retorna ponteiro para sessão específica
SessaoEstudo* RepositorioEstudos::getSessao(int i) const {
    if (i < 0 || i >= quantidade) {
        std::cerr << "Índice inválido!" << std::endl;
        return nullptr;
    }
    return &sessoes[i];
}

// soma os tempos de todas as sessões
void RepositorioEstudos::calcularTempoTotal() {
    tempoTotal = 0;
    for (int i = 0; i < quantidade; i++) {
        tempoTotal += sessoes[i].getSegundos();
    }
    std::cout << "Tempo total calculado: " << tempoTotal << " segundos" << std::endl;
}

//retorna o tempo total de estudos de uma disciplina específica
long long int RepositorioEstudos::getTempoTotalPorDisciplina(const std::string& disciplina) const {
    long long int total = 0;
    for (int i = 0; i < quantidade; i++) {
        if (sessoes[i].getDisciplina() == disciplina) {
            total += sessoes[i].getSegundos();
        }
    }
    return total;
}

// define período
void RepositorioEstudos::definirPeriodo(std::string dataInicio, std::string dataFim, std::string horaInicio, std::string horaFim) {
    this->DataInicio = dataInicio;
    this->DataFim = dataFim;
    this->HoraInicio = horaInicio;
    this->HoraFinal = horaFim;
    std::cout << "Período definido: " << dataInicio << " " << horaInicio << " até " << dataFim << " " << horaFim << std::endl;
}

// retorna tempo total
long long int RepositorioEstudos::getTempoTotal() const {
    return tempoTotal;
}

// retorna ID do usuário
std::string RepositorioEstudos::getIdUsuario() const {
    return idUsuario;

}
