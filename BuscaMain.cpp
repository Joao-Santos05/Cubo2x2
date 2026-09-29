#include "BuscaMain.h"
#include "MotorCubo.h"
#include <vector>

std::string resolverCubo(const Estado& inicial, FronteiraBusca* fronteira, long long& estadosVisitados) {
    estadosVisitados = 0;
    
    // Adicionar estado inicial na estrutura
    fronteira->adicionar(inicial);
    
    // Enquanto a estrutura não estiver vazia:
    while (!fronteira->vazia()) {
        // Remover próximo estado da estrutura
        Estado estado = fronteira->remover();
        
        // Exatamente quando o estado é expandido (removido), contamos ele.
        estadosVisitados++; 
        
        // Avaliar estado (verificar se é o objetivo)
        // SE estado final -> mostrar solução e retornar
        if (estado.isObjetivo()) {
            return estado.caminho_ate_aqui;
        }
        
        // Adicionar estados seguintes (sucessores gerados) na estrutura
        std::vector<Estado> sucessores = MotorCubo::gerarSucessores(estado);
        for (const Estado& suc : sucessores) {
            fronteira->adicionar(suc); // O polimorfismo cuida do descarte (Closed Set / Limite)
        }
    }
    
    // Retornar "Sem solução"
    return "Sem solução";
}
