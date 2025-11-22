#include "TelaBase.h"
#include <iostream>

void TelaBase::limparTela(){
    // Imprime 50 linhas vazias para limpar o terminal
    for(int i = 0; i < 50; i++){
        std::cout << std::endl;
    }
}

void TelaBase::aguardarEnter(){
    std::cout << "\n Pressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();

}
