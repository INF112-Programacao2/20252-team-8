#ifndef TELA_PRINCIPAL_H
#define TELA_PRINCIPAL_H

#include "TelaBase.h"

class TelaPrincipal : public TelaBase {
    public:
        int exibir(Usuario* usuario) override;
};

#endif