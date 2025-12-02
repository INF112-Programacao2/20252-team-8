#include "TelaBase.h"
#include <iostream>
#include <limits> // Necessário para limpar o buffer do cin
#include <cstdlib> // Necessário para system()
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio> // Para getchar

void TelaBase::limparTela() {
    // Verifica o Sistema Operacional para usar o comando certo
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void TelaBase::mostrarCabecalho(std::string titulo) {
    limparTela();
    std::cout << "========================================" << std::endl;
    std::cout << "       " << titulo << "       " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
}

void TelaBase::mostrarMensagem(std::string mensagem) {
    std::cout << ">> " << mensagem << std::endl;
}

void TelaBase::mostrarErro(std::string erro) {
    std::cerr << "[ERRO] " << erro << std::endl;
    esperarEnter(); // Pausa para o usuário ler o erro
}

void TelaBase::esperarEnter() {
    std::cout << "\nPressione ENTER para continuar...";
    // Se houver lixo no buffer, ignora. Se não, espera input.
    if (std::cin.peek() == '\n') std::cin.ignore();
    std::cin.get();
}


int TelaBase::lerOpcao() {
    int opcao;
    std::cout << ">> Escolha uma opcao: ";
    
    // Tenta ler um inteiro
    while (!(std::cin >> opcao)) {
        // Se falhar (ex: usuário digitou "a"), entra aqui:
        std::cin.clear(); // Limpa a flag de erro do cin
        
        // Ignora o restante da linha inválida no buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::cout << "Entrada invalida! Digite apenas numeros: ";
    }
    
    // Limpa o buffer após ler o número (para não pular o próximo getline)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return opcao;
}

TelaBase::~TelaBase(){}

int TelaBase::exibir(Usuario* usuario) {
    // Implementação padrão caso a tela filha não tenha a sua própria.
    // Retorna 0 (geralmente usado para "Sair" ou "Voltar")
    return 0; 
}

int TelaBase::kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

char TelaBase::getch() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
    return (buf);
}