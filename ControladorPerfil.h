#ifndef CONTROLADOR_PERFIL_H
#define CONTROLADOR_PERFIL_H

#include "usuario.h"
#include <string>

class ControladorPerfil {
public:
    void alterarNome(Usuario* u, std::string novoNome) {
        u->setNome(novoNome);
    }
};

#endif