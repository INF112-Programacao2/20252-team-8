#ifndef TELA_BASE_H
#define TELA_BASE_H

#include "Usuario.h"
#include <iostream>

class TelaBase {
    protected:
        void limparTela();
        
        void aguardarEnter();

    public:

        // Método virtual puro, para ser implementado pelas classes filhas
        // Recebe ponteiro para usuário para poder alterar dados
        virtual int exibir(Usuario* usuario) = 0; 

        virtual ~TelaBase();
        
};

#endif