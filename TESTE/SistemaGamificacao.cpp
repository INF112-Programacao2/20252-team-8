#include <iostream>
#include <string>
#include "SistemaGamificacao.h"

SistemaGamificacao::SistemaGamificacao(int temp){
    _tempo_de_estudo=temp;
    pontos+=60*_tempo_de_estudo;
}

void SistemaGamificacao::Badges(){
    if(_tempo_de_estudo>=1) badge1=true;
    if(_tempo_de_estudo>=5) badge2=true;
    if(_tempo_de_estudo>=10) badge3=true;
    if(_tempo_de_estudo>=20) badge4=true;
}

void SistemaGamificacao::ComunicarSubidaDeNivel(){
    if(_tempo_de_estudo>=1 && nivel1==false){ 
        std::cout << "*************************" << std::endl;
        std::cout << "PARABENS! Voce subiu para o Nivel 1 " << std::endl;
        std::cout << "*************************\n" << std::endl;
        nivel1=true;
    }    
    if(_tempo_de_estudo>=5 && nivel2==false){ 
        std::cout << "*************************" << std::endl;
        std::cout << "PARABENS! Voce subiu para o Nivel 2 " << std::endl;
        std::cout << "*************************\n" << std::endl;
        nivel2=true;
    }
    if(_tempo_de_estudo>=10 && nivel3==false){ 
        std::cout << "*************************" << std::endl;
        std::cout << "PARABENS! Voce subiu para o Nivel 3 " << std::endl;
        std::cout << "*************************\n" << std::endl;
        nivel3=true;
    } 
    if(_tempo_de_estudo>=20 && nivel4==false){ 
        std::cout << "*************************" << std::endl;
        std::cout << "PARABENS! Voce subiu para o Nivel 4 " << std::endl;
        std::cout << "*************************\n" << std::endl;
        nivel4=true;
    } 

}
void SistemaGamificacao::ComunicarBadges(){
    std::cout << "--------------- NIVEIS ---------------" << std::endl;
    if(badge1)  std::cout << "NIVEL 1 (1 HORA DE ESTUDO COMPLETADA) **COMPLETO** " << std::endl;
    else  std::cout << "NIVEL 1 (1 HORA DE ESTUDO COMPLETADA) **INCOMPLETO** " << std::endl;

    if(badge2)  std::cout << "NIVEL 2 (5 HORAS DE ESTUDO COMPLETADA) **COMPLETO** " << std::endl;
    else  std::cout << "NIVEL 2 (5 HORAS DE ESTUDO COMPLETADA) **INCOMPLETO** " << std::endl;

    if(badge3)  std::cout << "NIVEL 3 (10 HORAS DE ESTUDO COMPLETADA) **COMPLETO** " << std::endl;
    else  std::cout << "NIVEL 3 (10 HORAS DE ESTUDO COMPLETADA) **INCOMPLETO** " << std::endl;

    if(badge4)  std::cout << "NIVEL 4 (20 HORAS DE ESTUDO COMPLETADA) **COMPLETO** " << std::endl;
    else  std::cout << "NIVEL 4 (20 HORAS DE ESTUDO COMPLETADA) **INCOMPLETO** " << std::endl;

    std::cout << "--------------- BADGES ---------------" << std::endl;
    if(badge1)  std::cout << "Calouro" << std::endl;
    if(badge2)  std::cout << "Estudante" << std::endl;
    if(badge3)  std::cout << "Veterano" << std::endl;
    if(badge4)  std::cout << "Formando" << std::endl;

}
int SistemaGamificacao::getPontos(){
    return pontos;
}
int SistemaGamificacao::getHoras(){
    return _tempo_de_estudo;
}
SistemaGamificacao::~SistemaGamificacao() {
}