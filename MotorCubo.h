#ifndef MOTORCUBO_H
#define MOTORCUBO_H
#include "Estado.h"
#include <vector>
#include <string>
class MotorCubo {
public:
    static Estado moverU(const Estado& e);
    static Estado moverU_linha(const Estado& e);
    
    static Estado moverR(const Estado& e);
    static Estado moverR_linha(const Estado& e);
    
    static Estado moverF(const Estado& e);
    static Estado moverF_linha(const Estado& e);
    
    static Estado moverD(const Estado& e);
    static Estado moverD_linha(const Estado& e);
    static Estado moverL(const Estado& e);
    static Estado moverL_linha(const Estado& e);
    static Estado moverB(const Estado& e);
    static Estado moverB_linha(const Estado& e);
    
    static std::vector<Estado> gerarSucessores(const Estado& atual);
};
#endif 
