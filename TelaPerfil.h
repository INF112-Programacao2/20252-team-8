#ifndef TELA_PERFIL_H
#define TELA_PERFIL_H

#include "TelaBase.h"
#include "Usuario.h"
#include <string>

class TelaPerfil : public TelaBase {
public:
    int exibir(Usuario* usuario) override;
};

#endif