#ifndef CONTROLADOR_PRINCIPAL_H
#define CONTROLADOR_PRINCIPAL_H

#include "usuario.h"
#include "TelaBase.h"

class ControladorPrincipal {
private:
    Usuario* usuario; // Ponteiro para o usuário carregado

public:
    ControladorPrincipal(Usuario* u);
    void iniciar(); // O loop do programa
};

#endif