#ifndef TELA_BASE_H
#define TELA_BASE_H

#include <iostream>

class telaBase {
    protected:
        std::string Titulo;
        void limparTela();
        void aguardarEnter();
        void virtual exibirTela();
    public:
        telaBase();
        virtual ~telaBase();
        
};

#endif