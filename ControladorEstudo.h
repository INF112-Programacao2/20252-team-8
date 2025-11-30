#ifndef CONTROLADOR_ESTUDO_H
#define CONTROLADOR_ESTUDO_H

#include "usuario.h"
#include "SessaoEstudo.h"
#include "ControladorGamificacao.h"
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
    void finalizarSessao();
    void salvarSessao(Usuario* u, SessaoEstudo& sessao);
    
    SessaoEstudo* getSessaoAtiva();
    std::string getEstado() const;
};

#endif
