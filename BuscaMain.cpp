#include "BuscaMain.h"
#include "MotorCubo.h"
#include <vector>
std::string resolverCubo(const Estado& inicial, FronteiraBusca* fronteira, long long& estadosVisitados) {
    estadosVisitados = 0;
    
    fronteira->adicionar(inicial);
    
    while (!fronteira->vazia()) {
        Estado estado = fronteira->remover();
        
        estadosVisitados++; 
        
        if (estado.isObjetivo()) {
            return estado.caminho_ate_aqui;
        }
        
        std::vector<Estado> sucessores = MotorCubo::gerarSucessores(estado);
        for (const Estado& suc : sucessores) {
            fronteira->adicionar(suc); 
        }
    }
    
    return "Sem solução";
}
