#ifndef ESTADO_H
#define ESTADO_H
#include <string>
#include <functional>
#include <cstdint>
struct Peca {
    int id;         
    int orientacao; 
    bool operator==(const Peca& outra) const {
        return id == outra.id && orientacao == outra.orientacao;
    }
};
struct Estado {
    Peca cubo[8];
    std::string caminho_ate_aqui;
    int profundidade;
    
    Estado() : caminho_ate_aqui(""), profundidade(0) {
        for (int i = 0; i < 8; ++i) {
            cubo[i].id = i;
            cubo[i].orientacao = 0;
        }
    }
    
    bool operator==(const Estado& outro) const {
        for (int i = 0; i < 8; ++i) {
            if (!(cubo[i] == outro.cubo[i])) {
                return false;
            }
        }
        return true;
    }
    
    bool isObjetivo() const {
        for (int i = 0; i < 8; ++i) {
            if (cubo[i].id != i || cubo[i].orientacao != 0) {
                return false;
            }
        }
        return true;
    }
};


struct HashEstado {
    std::size_t operator()(const Estado& e) const {
        uint64_t hash = 0;
        
        for (int i = 0; i < 8; ++i) {
            hash = (hash << 3) | (e.cubo[i].id & 0x7);
            hash = (hash << 2) | (e.cubo[i].orientacao & 0x3);
        }
        return std::hash<uint64_t>()(hash);
    }
};
#endif 
