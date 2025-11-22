#ifndef SESSAOESTUDO_H
#define SESSAOESTUDO_H

#include <string>

class SessaoEstudo {
private:
    // tempo
    long long int segundos;
    long long int tempoInicial;
    // métodos privados para gerenciar estados
    void sessaoiniciada();
    void sessaopausada();
    void sessaofinalizada();
    // estado da sessão
    int estadoSessao; //0 = parado, 1 = rodando, 2 = pausado
    // metadados
    std::string disciplina;
    std::string etiqueta;
    std::string descricao;

public:
    // construtor default (necessário para array dinâmico)
    SessaoEstudo();
    // construtor
    SessaoEstudo(long long int segundos, int estadoSessao, std::string disciplina, std::string etiqueta, std::string descricao);
    // gerenciar o estado de uma sessão
    void gerenciar();
    // para marcar o tempo
    void iniciar();
    void pausar();
    void resetar();
    void continuar();
    // armazenar disciplina, etiqueta e descrição
    void armazenar();
    // retorna o tempo estudado
    long long int getSegundos();
    // retorna a disciplina estudada
    std::string getDisciplina();
    // retorna a etiqueta do seu estudo
    std::string getEtiqueta();
    // retorna a descrição do seu estudo
    std::string getDescricao();
};

#endif
