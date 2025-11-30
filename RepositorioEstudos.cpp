#include "RepositorioEstudos.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

//construtor
RepositorioEstudos::RepositorioEstudos(std::string idUsuario)
    : idUsuario(idUsuario), quantidade(0), capacidade(2), tempoTotal(0)
{
    //aloca array dinâmico
    sessoes = new SessaoEstudo[capacidade];
}

//destrutor
RepositorioEstudos::~RepositorioEstudos() {
    delete[] sessoes; // libera memória
}

void RepositorioEstudos::gerarArquivoHistorico() {
    std::string nomeArquivo = idUsuario + "_estudos.txt";
    std::ofstream arquivo(nomeArquivo);
    
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao criar arquivo: " << nomeArquivo << std::endl;
        return;
    }
    
    //calcular tempo total antes de salvar
    calcularTempoTotal();
    
    //escrever cabeçalho do histórico
    arquivo << "HISTÓRICO ESTUDO:\n";
    arquivo << "nome_usuario: " << idUsuario << "\n";
    arquivo << "qtd_sessoes: " << quantidade << "\n";
    arquivo << "tempo_total: " << tempoTotal << " segundos\n";
    
    //escrever informações de cada sessão (idx começa em 1)
    for (int i = 0; i < quantidade; i++) {
        SessaoEstudo* sessao = getSessao(i);
        if (sessao != nullptr) {
            arquivo << "  SESSÃO ESTUDO:\n";
            arquivo << "  idx: " << (i + 1) << "\n";  // idx começa em 1
            arquivo << "  tempo_total_sessao: " << sessao->getSegundos() << " segundos\n";
            arquivo << "  data_inicio: " << sessao->getDataInicio() << "\n";
            arquivo << "  data_final: " << sessao->getDataFinal() << "\n";
            arquivo << "  horario_inicio: " << sessao->getHorarioInicio() << "\n";
            arquivo << "  horario_final: " << sessao->getHorarioFinal() << "\n";
            arquivo << "  disciplina: " << sessao->getDisciplina() << "\n";
            arquivo << "\n"; //linha em branco entre sessões
        }
    }
    arquivo.close();
    std::cout << "Arquivo de histórico gerado: " << nomeArquivo << std::endl;
}

//soma os tempos de todas as sessões
void RepositorioEstudos::calcularTempoTotal() {
    tempoTotal = 0;
    for (int i = 0; i < quantidade; i++) {
        tempoTotal += sessoes[i].getSegundos();
    }
    std::cout << "Tempo total calculado: " << tempoTotal << " segundos" << std::endl;
}

//define período
void RepositorioEstudos::definirPeriodo(std::string dataInicio, std::string dataFim, std::string horaInicio, std::string horaFim) {
    this->DataInicio = dataInicio;
    this->DataFim = dataFim;
    this->HoraInicio = horaInicio;
    this->HoraFinal = horaFim;
    std::cout << "Período definido: " << dataInicio << " " << horaInicio << " até " << dataFim << " " << horaFim << std::endl;
}

// Métodos get:

//retorna número de sessões
int RepositorioEstudos::getQuantidade() const {
    return quantidade;
}

//retorna ponteiro para sessão específica
SessaoEstudo* RepositorioEstudos::getSessao(int i) const {
    if (i < 0 || i >= quantidade) {
        std::cerr << "Índice inválido!" << std::endl;
        return nullptr;
    }
    return &sessoes[i];
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

//retorna tempo total
long long int RepositorioEstudos::getTempoTotal() const {
    return tempoTotal;
}

//retorna ID do usuário
std::string RepositorioEstudos::getIdUsuario() const {
    return idUsuario;

}
