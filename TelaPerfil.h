#ifndef TELA_PERFIL_H
#define TELA_PERFIL_H

#include "TelaBase.h"
#include <string>


class Usuario;

class TelaPerfil : public TelaBase {
public:
    int exibir(Usuario* usuario) override;
};

#endif