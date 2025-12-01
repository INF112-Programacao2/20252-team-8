#ifndef ITEM_AUDIO_H
#define ITEM_AUDIO_H

#include "Item.h"
#include <string>

class ItemAudio : public Item {
private:
    std::string caminhoArquivo;

public:
    ItemAudio(std::string nome, int valor, std::string caminhoArquivo);

    // Sobrescreve o método usar para tocar música
    void usar() override;
};

#endif