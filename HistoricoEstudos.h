#ifndef HISTORICOESTUDOS_H
#define HISTORICOESTUDOS_H
#include "SessaoEstudo.h"
#include <string>

class HistoricoEstudos {
    private:
        long long int tempoTotal = 0;  //para o período, representa as horas os segundos totais
        std::string DataInicio;  //data de início de uma sessão
        std::string DataFim;  //data final de uma sessão
        std::string HoraInicio; //horario de início de uma sessão
        std::string HoraFinal; //horario final de uma sessão
        std::string idUsuario;  //ID do usuário associado ao histórico
        SessaoEstudo* sessoes;  // ponteiro para um array dinâmico de SessaoEstudo
        int quantidade;  // quantidade atual de sessões armazenadas
        int capacidade; // tamanho máximo atual do array
    public:
        //construtor
        HistoricoEstudos(std::string idUsuario);
        //destrutor
        ~HistoricoEstudos();

        //adiciona uma nova sessão
        void adicionarSessao(const SessaoEstudo& sessao);

        //retorna o total de sessões
        int getQuantidade() const;

        //retorna ponteiro para uma sessão específica
        SessaoEstudo* getSessao(int i) const;

        //calcula tempo total estudado
        void calcularTempoTotal();

        //define período
        void definirPeriodo(std::string dataInicio, std::string dataFim, std::string horaInicio, std::string horaFim);

        //retorna tempo total
        long long int getTempoTotal() const;

        //retorna ID do usuário
        std::string getIdUsuario() const;

        //retorna o tempo total de estudos de uma disciplina específica
        long long int getTempoTotalPorDisciplina(const std::string& disciplina) const;
    
};

#endif

