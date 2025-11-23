#ifndef TOCARMUSICA_H
#define TOCARMUSICA_H

#include "Loja.h" 
// Lembre-se: #define MINIAUDIO_IMPLEMENTATION NÃO deve ficar aqui!

#include "miniaudio.h" 

class TocarMusicas : public Loja {
public:
    // O construtor repassa o tempo de estudo para a classe-pai (Loja)
    TocarMusicas(int tempo_de_estudo_inicial);

    // O destrutor é crucial para limpar a engine de áudio
    ~TocarMusicas();

    // O método principal que o usuário vai chamar
    void mostrarMenuMusicas();

private:
    // Métodos auxiliares privados (só a classe usa)
    void tocar(const std::string& caminhoMusica);
    void descarregarMusica(); // <-- Sua antiga função 'parar()'
    void pausarMusica();      // <-- Nova função
    void resumirMusica();     // <-- Nova função

    // Membros da biblioteca miniaudio
    ma_engine engine;
    ma_sound musicaAtual;
    bool musicaEstaCarregada; 
};

#endif // TOCARMUSICA_H