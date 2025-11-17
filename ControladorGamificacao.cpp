#include "ControladorGamificacao.h"
#include <iostream>

// Construtor inicializa tudo
ControladorGamificacao::ControladorGamificacao(int tempo_inicial)
    : _tempo_de_estudo(tempo_inicial), pontos(0),
      badge1(false), badge2(false), badge3(false), badge4(false),
      nivel1(false), nivel2(false), nivel3(false), nivel4(false) 
{
    // Calcula pontos iniciais
    pontos += 60 * _tempo_de_estudo;
    
    // Define o status inicial de badges/níveis
    atualizarStatusBaseadoNoTempo();
}

ControladorGamificacao::~ControladorGamificacao() {
}

// atualiza as variáveis booleanas
void ControladorGamificacao::atualizarStatusBaseadoNoTempo() {
    if (_tempo_de_estudo >= 1)  badge1 = true;
    if (_tempo_de_estudo >= 5)  badge2 = true;
    if (_tempo_de_estudo >= 10) badge3 = true;
    if (_tempo_de_estudo >= 20) badge4 = true;
}

// Tenta gastar pontos, retorna true se conseguir
bool ControladorGamificacao::gastarPontos(int valor) {
    if (pontos >= valor) {
        pontos -= valor;
        return true;
    }
    return false;
}

// Getters
int ControladorGamificacao::getPontos() { return pontos; }
int ControladorGamificacao::getHoras()  { return _tempo_de_estudo; }


//Funções de Comunicação

void ControladorGamificacao::comunicarSubidaDeNivel() {
    if (_tempo_de_estudo >= 1 && !nivel1) {
        std::cout << "*************************\n"
                  << "PARABENS! Voce subiu para o Nivel 1 \n"
                  << "*************************\n" << std::endl;
        nivel1 = true;
    }
    if (_tempo_de_estudo >= 5 && !nivel2) {
        std::cout << "*************************\n"
                  << "PARABENS! Voce subiu para o Nivel 2 \n"
                  << "*************************\n" << std::endl;
        nivel2 = true;
    }
    if (_tempo_de_estudo >= 10 && !nivel3) {
        std::cout << "*************************\n"
                  << "PARABENS! Voce subiu para o Nivel 3 \n"
                  << "*************************\n" << std::endl;
        nivel3 = true;
    }
    if (_tempo_de_estudo >= 20 && !nivel4) {
        std::cout << "*************************\n"
                  << "PARABENS! Voce subiu para o Nivel 4 \n"
                  << "*************************\n" << std::endl;
        nivel4 = true;
    }
}

void ControladorGamificacao::comunicarBadges() {
    std::cout << "--------------- NIVEIS ---------------" << std::endl;
    std::cout << "NIVEL 1 (1 HORA): "   << (badge1 ? "**COMPLETO**" : "**INCOMPLETO**") << std::endl;
    std::cout << "NIVEL 2 (5 HORAS): "  << (badge2 ? "**COMPLETO**" : "**INCOMPLETO**") << std::endl;
    std::cout << "NIVEL 3 (10 HORAS): " << (badge3 ? "**COMPLETO**" : "**INCOMPLETO**") << std::endl;
    std::cout << "NIVEL 4 (20 HORAS): " << (badge4 ? "**COMPLETO**" : "**INCOMPLETO**") << std::endl;

    std::cout << "--------------- BADGES ---------------" << std::endl;
    if (badge1) std::cout << "Calouro\n";
    if (badge2) std::cout << "Estudante\n";
    if (badge3) std::cout << "Veterano\n";
    if (badge4) std::cout << "Formando\n";
}