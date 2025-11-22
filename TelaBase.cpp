#include "TelaBase.h"
#include <iostream>

void telaBase::limparTela(){
    // Imprime 50 linhas vazias para limpar o terminal
    for(int i = 0; i < 50; i++){
        std::cout << std::endl;
    }
}

void telaBase::aguardarEnter(){
    std::cout << "\n Pressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();

}

void telaBase::exibir(){
    
}