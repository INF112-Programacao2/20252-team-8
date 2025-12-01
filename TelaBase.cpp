#include "TelaBase.h"
#include <iostream>
#include <cstdlib>

void TelaBase::limparTela(){
   // Verifica o sistema operacional
        #ifdef _WIN32
            std::system("cls");   // Comando do Windows
        #else
            std::system("clear"); // Comando do Linux/Mac
        #endif
}

void TelaBase::aguardarEnter(){
    std::cout << "\n Pressione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();

}
