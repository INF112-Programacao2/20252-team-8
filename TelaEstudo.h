#ifndef TELA_ESTUDO_H
#define TELA_ESTUDO_H

#include <iostream>
#include "TelaBase.h"

class telaEstudo : public telaBase {
    private:
        void mostrarOpcoesEstudo();
        void mostrarProgressoEstudo();
        void menuSelecionarEstudo();
        
    public:
        telaEstudo();
        void exibir() override;
};

#endif