#include "ControladorGamificacao.h"

ControladorGamificacao::ControladorGamificacao(Usuario* usuario, RepositorioGamificacao* repo)
    : usuarioAtual(usuario), repositorio(repo) {
    // A 'tela' é criada automaticamente aqui pelo compilador
}

// Mostra o perfil usando a classe de Tela
void ControladorGamificacao::executar() {
    tela.mostrarPerfil(usuarioAtual);
}

void ControladorGamificacao::adicionarXP(int quantidade) {
    if (!usuarioAtual || quantidade <= 0) return;

    // 1. Atualiza Memória
    usuarioAtual->adicionarXp(quantidade);
    
    // 2. Atualiza Arquivo
    if (repositorio) {
        repositorio->setPontos(usuarioAtual->getXp());
    }

    // 3. Manda a tela mostrar o ganho
    tela.mostrarGanhoRecursos(quantidade, 0);
    
    // 4. Verifica se subiu de nível
    verificarEvolucao();
}

void ControladorGamificacao::verificarEvolucao() {
    int xpTotal = usuarioAtual->getXp();
    // Usa o #define XP_POR_NIVEL
    int nivelCalculado = xpTotal / XP_POR_NIVEL; 
    
    // Pega o nível que está salvo no arquivo para comparar
    int nivelNoArquivo = repositorio->getNivel();

    if (nivelCalculado > nivelNoArquivo) {
        // --- LEVEL UP ---
        int niveisSubidos = nivelCalculado - nivelNoArquivo;
        int moedasGanhas = niveisSubidos * RECOMPENSA_MOEDAS;
        
        // Dá as moedas
        adicionarMoedas(moedasGanhas);

        // Define a nova badge
        std::string nomeBadge = calcularNomeBadge(nivelCalculado);
        std::string badgeAntiga = usuarioAtual->getBadge();
        usuarioAtual->setBadge(nomeBadge); 

        // Salva tudo no arquivo
        repositorio->setNivel(nivelCalculado);
        repositorio->setBadge(calcularIdBadge(nivelCalculado));

        // Manda a tela exibir os Parabéns
        // Só mostra badge na tela se ela mudou de fato
        std::string badgeParaMostrar = (nomeBadge != badgeAntiga) ? nomeBadge : "";
        tela.mostrarLevelUp(nivelCalculado, moedasGanhas, badgeParaMostrar);
    }
}

void ControladorGamificacao::adicionarMoedas(int quantidade) {
    if (!usuarioAtual) return;

    usuarioAtual->adicionarMoedas(quantidade);
    
    if (repositorio) {
        repositorio->setMoedas(usuarioAtual->getMoedas());
    }
    
    // Nota: Se a moeda vier do LevelUp, o aviso de LevelUp já mostra o ganho.
    // Se quiser mostrar ganho avulso (ex: vendeu item), descomente abaixo:
    // if (quantidade > 0) tela.mostrarGanhoRecursos(0, quantidade);
}

void ControladorGamificacao::salvarTudo() {
    if (repositorio && usuarioAtual) {
        repositorio->setPontos(usuarioAtual->getXp());
        repositorio->setMoedas(usuarioAtual->getMoedas());
    }
}

// --- Auxiliares ---

std::string ControladorGamificacao::calcularNomeBadge(int nivel) {
    if (nivel >= 20) return "Lenda";
    if (nivel >= 10) return "Veterano";
    if (nivel >= 5)  return "Estudante";
    if (nivel >= 2)  return "Calouro";
    return "Iniciante";
}

int ControladorGamificacao::calcularIdBadge(int nivel) {
    if (nivel >= 20) return 4; 
    if (nivel >= 10) return 3; 
    if (nivel >= 5)  return 2; 
    if (nivel >= 1)  return 1; 
    return 0;
}

// --- Getters ---

Usuario* ControladorGamificacao::getUsuario() const { return usuarioAtual; }
int ControladorGamificacao::getXP() const { return usuarioAtual ? usuarioAtual->getXp() : 0; }

// Calcula nível dinamicamente (XP / 100)
int ControladorGamificacao::getNivel() const {
    if (!usuarioAtual) return 0;
    return usuarioAtual->getXp() / XP_POR_NIVEL;
}

int ControladorGamificacao::getMoedas() const { return usuarioAtual ? usuarioAtual->getMoedas() : 0; }
std::string ControladorGamificacao::getBadge() const { return usuarioAtual ? usuarioAtual->getBadge() : ""; }