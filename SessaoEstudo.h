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
    // construtor
    SessaoEstudo(long long int segundos, int estadoSessao, std::string disciplina, std::string descricao);
    
    // gerenciar o estado de uma sessão
    void gerenciar();
    
    // para marcar o tempo
    void iniciar();
    void pausar();
    void resetar();
    void continuar();
    void finalizar();
    
    // getters
    long long int getSegundos();
    std::string getDisciplina();
    std::string getDescricao();
    std::string getDataInicio();
    std::string getDataFinal();
    std::string getHorarioInicio();
    std::string getHorarioFinal();

    void setDataInicio(const std::string& data);
};
#endif