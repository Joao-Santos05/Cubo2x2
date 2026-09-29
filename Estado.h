#ifndef ESTADO_H
#define ESTADO_H

#include <string>
#include <functional>
#include <cstdint>

struct Peca {
    int id;         // Identificador da peça (0 a 7)
    int orientacao; // Orientação em relação ao eixo principal (0, 1 ou 2)

    bool operator==(const Peca& outra) const {
        return id == outra.id && orientacao == outra.orientacao;
    }
};

struct Estado {
    Peca cubo[8];
    std::string caminho_ate_aqui;
    int profundidade;

    // Construtor padrão que inicializa no estado objetivo
    Estado() : caminho_ate_aqui(""), profundidade(0) {
        for (int i = 0; i < 8; ++i) {
            cubo[i].id = i;
            cubo[i].orientacao = 0;
        }
    }

    // Operador de igualdade para checagem rápida (usado pelo Closed Set)
    bool operator==(const Estado& outro) const {
        for (int i = 0; i < 8; ++i) {
            if (!(cubo[i] == outro.cubo[i])) {
                return false;
            }
        }
        return true;
    }
    
    // Função exigida para avaliar se é o objetivo
    bool isObjetivo() const {
        for (int i = 0; i < 8; ++i) {
            if (cubo[i].id != i || cubo[i].orientacao != 0) {
                return false;
            }
        }
        return true;
    }
};

// Estrutura customizada de Hash para otimizar o uso de memória e CPU
// com std::unordered_set. A ideia é compactar as 8 peças (IDs e Orientações)
// em um único uint64_t garantindo colisões zero para estados perfeitamente iguais.
struct HashEstado {
    std::size_t operator()(const Estado& e) const {
        uint64_t hash = 0;
        // Cada id precisa de 3 bits (0 a 7).
        // Cada orientacao precisa de 2 bits (0 a 2).
        // Um total de 5 bits por peça. 8 * 5 = 40 bits no total.
        for (int i = 0; i < 8; ++i) {
            hash = (hash << 3) | (e.cubo[i].id & 0x7);
            hash = (hash << 2) | (e.cubo[i].orientacao & 0x3);
        }
        return std::hash<uint64_t>()(hash);
    }
};

#endif // ESTADO_H
