#ifndef MOTORCUBO_H
#define MOTORCUBO_H

#include "Estado.h"
#include <vector>
#include <string>

class MotorCubo {
public:
    // Movimentos da face Topo (Up)
    static Estado moverU(const Estado& e);
    static Estado moverU_linha(const Estado& e);

    // Movimentos da face Direita (Right)
    static Estado moverR(const Estado& e);
    static Estado moverR_linha(const Estado& e);

    // Movimentos da face Frente (Front)
    static Estado moverF(const Estado& e);
    static Estado moverF_linha(const Estado& e);

    // Gera os próximos estados possíveis a partir do estado atual
    static std::vector<Estado> gerarSucessores(const Estado& atual);
};

#endif // MOTORCUBO_H
