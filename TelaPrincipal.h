#ifndef TELA_PRINCIPAL_H
#define TELA_PRINCIPAL_H

#include "TelaBase.h"

class telaPrincipal : public TelaBase {
    public:
        int exibir(Usuario* usuario) override;
};

#endif