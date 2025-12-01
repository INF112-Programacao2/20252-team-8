#ifndef CONTROLADOR_ESTUDO_H
#define CONTROLADOR_ESTUDO_H

#include "Usuario.h"
#include "SessaoEstudo.h"
#include "ControladorGamificacao.h"
#include "RepositorioEstudos.h"
#include <string>

class ControladorEstudo {
private:
    SessaoEstudo* sessaoAtiva;
    std::string estado; // parado, rodando, pausado
    ControladorGamificacao* controladorGami;

public:
    ControladorEstudo(ControladorGamificacao* controladorG);
    ~ControladorEstudo();

    void iniciarSessao(int duracao);
    void pausarSessao();
    void finalizarSessao(Usuario* u);
    void salvarSessao(Usuario* u, SessaoEstudo& sessao);
    
    RepositorioEstudos& recuperarHistorico(Usuario* u);

    SessaoEstudo* getSessaoAtiva();
    std::string getEstado() const;
    
};

#endif
