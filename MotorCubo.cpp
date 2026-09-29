#include "MotorCubo.h"

// Mapeamento dos cantos (0 a 7):
// 0: UBL (Up-Back-Left)
// 1: UBR (Up-Back-Right)
// 2: UFL (Up-Front-Left)
// 3: UFR (Up-Front-Right)
// 4: DBL (Down-Back-Left)
// 5: DBR (Down-Back-Right)
// 6: DFL (Down-Front-Left)
// 7: DFR (Down-Front-Right)

// --- Movimentos U (Topo) ---
// Rotação no sentido horário afeta: 0 -> 1 -> 3 -> 2 -> 0
// Movimentos em U/D não alteram a orientação.
Estado MotorCubo::moverU(const Estado& e) {
    Estado res = e;
    res.cubo[1] = e.cubo[0];
    res.cubo[3] = e.cubo[1];
    res.cubo[2] = e.cubo[3];
    res.cubo[0] = e.cubo[2];
    
    res.profundidade += 1;
    res.caminho_ate_aqui += "U ";
    return res;
}

Estado MotorCubo::moverU_linha(const Estado& e) {
    Estado res = e;
    res.cubo[0] = e.cubo[1];
    res.cubo[1] = e.cubo[3];
    res.cubo[3] = e.cubo[2];
    res.cubo[2] = e.cubo[0];
    
    res.profundidade += 1;
    res.caminho_ate_aqui += "U' ";
    return res;
}

// --- Movimentos R (Direita) ---
// Rotação no sentido horário afeta: 3 -> 1 -> 5 -> 7 -> 3
// Altera as orientações de acordo com a torção (+1 ou +2 módulo 3).
Estado MotorCubo::moverR(const Estado& e) {
    Estado res = e;
    res.cubo[1] = e.cubo[3];
    res.cubo[1].orientacao = (res.cubo[1].orientacao + 1) % 3;
    
    res.cubo[5] = e.cubo[1];
    res.cubo[5].orientacao = (res.cubo[5].orientacao + 2) % 3;
    
    res.cubo[7] = e.cubo[5];
    res.cubo[7].orientacao = (res.cubo[7].orientacao + 1) % 3;
    
    res.cubo[3] = e.cubo[7];
    res.cubo[3].orientacao = (res.cubo[3].orientacao + 2) % 3;
    
    res.profundidade += 1;
    res.caminho_ate_aqui += "R ";
    return res;
}

Estado MotorCubo::moverR_linha(const Estado& e) {
    Estado res = e;
    res.cubo[3] = e.cubo[1];
    res.cubo[3].orientacao = (res.cubo[3].orientacao + 2) % 3;
    
    res.cubo[1] = e.cubo[5];
    res.cubo[1].orientacao = (res.cubo[1].orientacao + 1) % 3;
    
    res.cubo[5] = e.cubo[7];
    res.cubo[5].orientacao = (res.cubo[5].orientacao + 2) % 3;
    
    res.cubo[7] = e.cubo[3];
    res.cubo[7].orientacao = (res.cubo[7].orientacao + 1) % 3;
    
    res.profundidade += 1;
    res.caminho_ate_aqui += "R' ";
    return res;
}

// --- Movimentos F (Frente) ---
// Rotação no sentido horário afeta: 2 -> 3 -> 7 -> 6 -> 2
// Altera as orientações de acordo com a torção (+1 ou +2 módulo 3).
Estado MotorCubo::moverF(const Estado& e) {
    Estado res = e;
    res.cubo[3] = e.cubo[2];
    res.cubo[3].orientacao = (res.cubo[3].orientacao + 1) % 3;
    
    res.cubo[7] = e.cubo[3];
    res.cubo[7].orientacao = (res.cubo[7].orientacao + 2) % 3;
    
    res.cubo[6] = e.cubo[7];
    res.cubo[6].orientacao = (res.cubo[6].orientacao + 1) % 3;
    
    res.cubo[2] = e.cubo[6];
    res.cubo[2].orientacao = (res.cubo[2].orientacao + 2) % 3;
    
    res.profundidade += 1;
    res.caminho_ate_aqui += "F ";
    return res;
}

Estado MotorCubo::moverF_linha(const Estado& e) {
    Estado res = e;
    res.cubo[2] = e.cubo[3];
    res.cubo[2].orientacao = (res.cubo[2].orientacao + 2) % 3;
    
    res.cubo[3] = e.cubo[7];
    res.cubo[3].orientacao = (res.cubo[3].orientacao + 1) % 3;
    
    res.cubo[7] = e.cubo[6];
    res.cubo[7].orientacao = (res.cubo[7].orientacao + 2) % 3;
    
    res.cubo[6] = e.cubo[2];
    res.cubo[6].orientacao = (res.cubo[6].orientacao + 1) % 3;
    
    res.profundidade += 1;
    res.caminho_ate_aqui += "F' ";
    return res;
}

// --- Gerador de Sucessores ---
std::vector<Estado> MotorCubo::gerarSucessores(const Estado& atual) {
    std::vector<Estado> sucessores;
    sucessores.reserve(6); // Max 6 movimentos
    
    const std::string& cam = atual.caminho_ate_aqui;
    std::string ultimo = "";
    
    // Extrai o último movimento (ex: "U", "U'", "R") otimizadamente para evitar cópias de string
    if (!cam.empty()) {
        size_t len = cam.length();
        if (len >= 3 && cam[len-2] == '\'') {
            ultimo = cam.substr(len-3, 2); // Caso inverso, ex: "U'"
        } else if (len >= 2) {
            ultimo = cam.substr(len-2, 1); // Caso horário, ex: "U"
        }
    }
    
    // Filtro contra retornos imediatos na árvore de busca
    if (ultimo != "U'") sucessores.push_back(moverU(atual));
    if (ultimo != "U")  sucessores.push_back(moverU_linha(atual));
    
    if (ultimo != "R'") sucessores.push_back(moverR(atual));
    if (ultimo != "R")  sucessores.push_back(moverR_linha(atual));
    
    if (ultimo != "F'") sucessores.push_back(moverF(atual));
    if (ultimo != "F")  sucessores.push_back(moverF_linha(atual));
    
    return sucessores;
}
