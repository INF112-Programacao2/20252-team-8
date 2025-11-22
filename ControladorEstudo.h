#ifndef CONTROLADOR_ESTUDO_H
#define CONTROLADOR_ESTUDO_H
#include "usuario.h"
#include "SessaoEstudo.h"

class ControladorEstudo {
public:
    void salvarSessao(Usuario* u, SessaoEstudo& sessao) {
        sessao.armazenar();
        u->getHistorico().adicionarSessao(sessao);
    }
};
#endif