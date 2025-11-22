#ifndef TELA_PERFIL_H
#define TELA_PERFIL_H

#include "TelaBase.h"

class telaPerfil : public TelaBase {
public:
    int exibir(Usuario* usuario) override;
};

#endif