#ifndef SESSAOESTUDO_H
#define SESSAOESTUDO_H

#include <string>

class SessaoEstudo {
private:
    // tempo
    long long int segundos;
    long long int tempoInicial;
    
    // métodos para gerenciar estados
    void sessaoiniciada();
    void sessaopausada();
    void sessaofinalizada();
    void obterDataHoraAtual(std::string& data, std::string& hora);
    
    // estado da sessão
    int estadoSessao; //0 = parado, 1 = rodando, 2 = pausado
    
    // metadados
    std::string disciplina;
    std::string descricao;
    
    // dados de data e hora
    std::string dataInicio;
    std::string dataFinal;
    std::string horarioInicio;
    std::string horarioFinal;

public:
    // construtor default 
    SessaoEstudo();

    enum Estado {
        parado = 0,
        rodando = 1,
        pausado = 2
    };
    
    // construtor
    SessaoEstudo(long long int segundos, Estado estado, std::string disciplina, std::string descricao);
    
    // gerenciar o estado de uma sessão
    void gerenciar();

    // para marcar o tempo
    void iniciar();
    void pausar();
    void resetar();
    void continuar();
    void finalizar();
    
    // getters
    long long int getSegundos() const;
    std::string getDisciplina() const;
    std::string getDescricao() const;
    std::string getDataInicio() const;
    std::string getDataFinal() const;
    std::string getHorarioInicio() const;
    std::string getHorarioFinal() const;
    Estado getEstado() const;

    void setDataInicio(const std::string& d);
    void setDataFinal(const std::string& d);
    void setHoraInicio(const std::string& h);
    void setHoraFinal(const std::string& h);

};
#endif