#include "Loja.h"
#include "SistemaGamificacao.h"
#include <iostream>
#include <string>

Loja::Loja(int tempo_de_estudo_inicial) 
    : SistemaGamificacao(tempo_de_estudo_inicial)
{
    musica1_comprada = false;
    musica1_valor = 300;
    nomemusica1 = "Study Calm Lo-Fi";

    musica2_comprada = false;  
    musica2_valor = 700;
    nomemusica2 = "Sad Lo-Fi";

    musica3_comprada = false;
    musica3_valor = 1200;
    nomemusica3 = "Chill Night Lo-Fi";
}

void Loja::loja(){
    int escolha;
    int escolhamusica;


    while(true){
        std::cout << "-----------------BEM VINDO A LOJA---------------\n\n";
        
        std::cout << "Voce tem: " << pontos << " disponiveis\n";
        std::cout << "---------------------------------\n";
        
        std::cout << "Musica 1: " << nomemusica1 << " -------- 300 pontos --------"; 
        if(musica1_comprada) std::cout << "MUSICA JA COMPRADA\n"; else std::cout << "MUSICA DISPONIVEL PARA COMPRA\n";
        
        std::cout << "Musica 2: " << nomemusica2 << " -------- 700 pontos";
        if(musica2_comprada) std::cout << "MUSICA JA COMPRADA\n"; else std::cout << "MUSICA DISPONIVEL PARA COMPRA\n";

        std::cout << "Musica 3: " << nomemusica3 << " -------- 1200 pontos"; // Você tinha "Musica 2" aqui
        if(musica3_comprada) std::cout << "MUSICA JA COMPRADA\n"; else std::cout << "MUSICA DISPONIVEL PARA COMPRA\n";

        while(true){
            std::cout << "Aperte 1 para comprar alguma musica , 2 para voltar e ver as musicas disponiveis e 3 para sair da loja\n";
            std::cin >> escolha;
            if(escolha==1){
                std::cout << "Qual musica voce deseja comprar (1 para musica1 , 2 para musica 2 e assim por diante): ";
                std::cin >> escolhamusica;

                if(escolhamusica==1 && pontos >= musica1_valor){
                     std::cout << "PARABENS , VOCE COMPROU A MUSICA " << nomemusica1 << " !!";
                     musica1_comprada = true;
                     pontos -= musica1_valor;
                } 
                else if (escolhamusica==2 && pontos >= musica2_valor){
                     std::cout << "PARABENS , VOCE COMPROU A MUSICA " << nomemusica2 << " !!";
                     musica2_comprada = true;
                     pontos -= musica2_valor;
                } 
                else if (escolhamusica==3 && pontos >= musica3_valor){
                     std::cout << "PARABENS , VOCE COMPROU A MUSICA " << nomemusica3 << " !!";
                     musica3_comprada = true;
                     pontos -= musica3_valor;
                }
                else if(escolhamusica>3){
                    return;
                }
                else{
                    std::cout << "Seu saldo de " << pontos << " nao é suficiente para comprar essa musica!\n";
                }
            }
            else if(escolha==2 || escolha==3) break;
        }
        if(escolha==3) break;
    }
}

void Loja::musicas_compradas(){
    std::cout << "--- STATUS DAS SUAS MUSICAS ---" << std::endl;
    if(musica1_comprada) std::cout << nomemusica1 << " (COMPRADA)\n";
    if(musica2_comprada) std::cout << nomemusica2 << " (COMPRADA)\n";
    if(musica3_comprada) std::cout << nomemusica3 << " (COMPRADA)\n";
    std::cout << "---------------------------------" << std::endl;
}

bool Loja::isMusica1Comprada() {
    return musica1_comprada;
}

bool Loja::isMusica2Comprada() {
    return musica2_comprada;
}

bool Loja::isMusica3Comprada() {
    return musica3_comprada;
}

std::string Loja::getNomeMusica1() {
    return nomemusica1;
}
Loja::~Loja() {
}
