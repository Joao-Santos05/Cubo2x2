#ifndef FRONTEIRABUSCA_H
#define FRONTEIRABUSCA_H
#include "Estado.h"
#include <queue>
#include <stack>
#include <unordered_set>
#include <cstdint>
#include <cmath>
#include <algorithm>

class FronteiraBusca {
public:
    virtual ~FronteiraBusca() = default;
    
    virtual void adicionar(const Estado& e) = 0;
    virtual Estado remover() = 0;
    virtual bool vazia() const = 0;
};
class FilaBFS : public FronteiraBusca {
private:
    std::queue<Estado> fila;
    
    std::unordered_set<uint64_t> visitados;
    uint64_t codificarEstado(const Estado& e) const {
        uint64_t hash = 0;
        for (int i = 0; i < 8; ++i) {
            hash = (hash << 3) | (e.cubo[i].id & 0x7);
            hash = (hash << 2) | (e.cubo[i].orientacao & 0x3);
        }
        return hash;
    }
public:
    void adicionar(const Estado& e) override {
        uint64_t codigo = codificarEstado(e);
        
        if (visitados.insert(codigo).second) {
            fila.push(e);
        }
    }
    Estado remover() override {
        Estado e = fila.front();
        fila.pop();
        return e;
    }
    bool vazia() const override {
        return fila.empty();
    }
};
class PilhaDFS : public FronteiraBusca {
private:
    std::stack<Estado> pilha;
    int limite_profundidade;
public:
    explicit PilhaDFS(int limite) : limite_profundidade(limite) {}
    void adicionar(const Estado& e) override {
        
        if (e.profundidade <= limite_profundidade) {
            pilha.push(e);
        }
    }
    Estado remover() override {
        Estado e = pilha.top();
        pilha.pop();
        return e;
    }
    bool vazia() const override {
        return pilha.empty();
    }
};

class FilaPrioridadeAStar : public FronteiraBusca {
private:
    struct ComparadorAStar {
        bool operator()(const Estado& a, const Estado& b) const {
            int f_a = a.profundidade + calcularHeuristica(a);
            int f_b = b.profundidade + calcularHeuristica(b);
            if (f_a == f_b) {
                return a.profundidade < b.profundidade;
            }
            return f_a > f_b; 
        }
        static int calcularHeuristica(const Estado& e) {
            int dist_manhattan = 0;
            int custo_orientacao = 0;
            for (int i = 0; i < 8; ++i) {
                int id_atual = e.cubo[i].id;
                
                int x1 = i % 2;
                int y1 = (i < 4) ? 1 : 0;
                int z1 = ((i / 2) % 2 == 0) ? 1 : 0;
                
                int x2 = id_atual % 2;
                int y2 = (id_atual < 4) ? 1 : 0;
                int z2 = ((id_atual / 2) % 2 == 0) ? 1 : 0;
                dist_manhattan += std::abs(x1 - x2) + std::abs(y1 - y2) + std::abs(z1 - z2);
                if (e.cubo[i].orientacao != 0) {
                    custo_orientacao++;
                }
            }
            return std::max(dist_manhattan / 4, custo_orientacao / 4);
        }
    };
    std::priority_queue<Estado, std::vector<Estado>, ComparadorAStar> pq;
    std::unordered_set<uint64_t> visitados;
    uint64_t codificarEstado(const Estado& e) const {
        uint64_t hash = 0;
        for (int i = 0; i < 8; ++i) {
            hash = (hash << 3) | (e.cubo[i].id & 0x7);
            hash = (hash << 2) | (e.cubo[i].orientacao & 0x3);
        }
        return hash;
    }
public:
    void adicionar(const Estado& e) override {
        uint64_t codigo = codificarEstado(e);
        if (visitados.insert(codigo).second) {
            pq.push(e);
        }
    }
    Estado remover() override {
        Estado e = pq.top();
        pq.pop();
        return e;
    }
    bool vazia() const override {
        return pq.empty();
    }
};
#endif 
