#include "MotorCubo.h"







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


Estado MotorCubo::moverD(const Estado& e) {
    Estado res = e;
    res.cubo[6] = e.cubo[4];
    res.cubo[7] = e.cubo[6];
    res.cubo[5] = e.cubo[7];
    res.cubo[4] = e.cubo[5];
    res.profundidade += 1;
    res.caminho_ate_aqui += "D ";
    return res;
}
Estado MotorCubo::moverD_linha(const Estado& e) {
    Estado res = e;
    res.cubo[4] = e.cubo[6];
    res.cubo[6] = e.cubo[7];
    res.cubo[7] = e.cubo[5];
    res.cubo[5] = e.cubo[4];
    res.profundidade += 1;
    res.caminho_ate_aqui += "D' ";
    return res;
}


Estado MotorCubo::moverL(const Estado& e) {
    Estado res = e;
    res.cubo[0] = e.cubo[4];
    res.cubo[0].orientacao = (res.cubo[0].orientacao + 1) % 3;
    res.cubo[4] = e.cubo[6];
    res.cubo[4].orientacao = (res.cubo[4].orientacao + 2) % 3;
    res.cubo[6] = e.cubo[2];
    res.cubo[6].orientacao = (res.cubo[6].orientacao + 1) % 3;
    res.cubo[2] = e.cubo[0];
    res.cubo[2].orientacao = (res.cubo[2].orientacao + 2) % 3;
    res.profundidade += 1;
    res.caminho_ate_aqui += "L ";
    return res;
}
Estado MotorCubo::moverL_linha(const Estado& e) {
    Estado res = e;
    res.cubo[4] = e.cubo[0];
    res.cubo[4].orientacao = (res.cubo[4].orientacao + 2) % 3;
    res.cubo[6] = e.cubo[4];
    res.cubo[6].orientacao = (res.cubo[6].orientacao + 1) % 3;
    res.cubo[2] = e.cubo[6];
    res.cubo[2].orientacao = (res.cubo[2].orientacao + 2) % 3;
    res.cubo[0] = e.cubo[2];
    res.cubo[0].orientacao = (res.cubo[0].orientacao + 1) % 3;
    res.profundidade += 1;
    res.caminho_ate_aqui += "L' ";
    return res;
}

Estado MotorCubo::moverB(const Estado& e) {
    Estado res = e;
    res.cubo[0] = e.cubo[1];
    res.cubo[0].orientacao = (res.cubo[0].orientacao + 1) % 3;
    res.cubo[4] = e.cubo[0];
    res.cubo[4].orientacao = (res.cubo[4].orientacao + 2) % 3;
    res.cubo[5] = e.cubo[4];
    res.cubo[5].orientacao = (res.cubo[5].orientacao + 1) % 3;
    res.cubo[1] = e.cubo[5];
    res.cubo[1].orientacao = (res.cubo[1].orientacao + 2) % 3;
    res.profundidade += 1;
    res.caminho_ate_aqui += "B ";
    return res;
}
Estado MotorCubo::moverB_linha(const Estado& e) {
    Estado res = e;
    res.cubo[1] = e.cubo[0];
    res.cubo[1].orientacao = (res.cubo[1].orientacao + 2) % 3;
    res.cubo[0] = e.cubo[4];
    res.cubo[0].orientacao = (res.cubo[0].orientacao + 1) % 3;
    res.cubo[4] = e.cubo[5];
    res.cubo[4].orientacao = (res.cubo[4].orientacao + 2) % 3;
    res.cubo[5] = e.cubo[1];
    res.cubo[5].orientacao = (res.cubo[5].orientacao + 1) % 3;
    res.profundidade += 1;
    res.caminho_ate_aqui += "B' ";
    return res;
}

std::vector<Estado> MotorCubo::gerarSucessores(const Estado& atual) {
    std::vector<Estado> sucessores;
    sucessores.reserve(6); 
    const std::string& cam = atual.caminho_ate_aqui;
    std::string ultimo = "";
    if (!cam.empty()) {
        size_t len = cam.length();
        if (len >= 3 && cam[len-2] == '\'') {
            ultimo = cam.substr(len-3, 2);
        } else if (len >= 2) {
            ultimo = cam.substr(len-2, 1);
        }
    }
    
    
    
    if (ultimo != "U'") sucessores.push_back(moverU(atual));
    if (ultimo != "U")  sucessores.push_back(moverU_linha(atual));
    if (ultimo != "R'") sucessores.push_back(moverR(atual));
    if (ultimo != "R")  sucessores.push_back(moverR_linha(atual));
    if (ultimo != "F'") sucessores.push_back(moverF(atual));
    if (ultimo != "F")  sucessores.push_back(moverF_linha(atual));
    return sucessores;
}
