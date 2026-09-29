#ifndef FRONTEIRABUSCA_H
#define FRONTEIRABUSCA_H

#include "Estado.h"
#include <queue>
#include <stack>
#include <unordered_set>
#include <cstdint>
#include <cmath>
#include <algorithm>

// A "Regra de Ouro": Interface base estrita que garante o laço imutável.
class FronteiraBusca {
public:
    virtual ~FronteiraBusca() = default;
    
    // Todos recebem a mesma interface. As classes filhas implementarão
    // suas próprias regras e filtragens por trás dos panos.
    virtual void adicionar(const Estado& e) = 0;
    virtual Estado remover() = 0;
    virtual bool vazia() const = 0;
};

class FilaBFS : public FronteiraBusca {
private:
    std::queue<Estado> fila;
    // O Closed Set armazena um inteiro 64-bits com a codificação perfeita do cubo (40 bits necessários).
    // Zero colisões garantidas sem a necessidade de instanciar ou comparar a classe Estado.
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
        
        // set::insert retorna um pair. O .second é true se foi inserido com sucesso (novo estado).
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
        // Closed Set local baseado no limite!
        // Oculta a rejeição mantendo o laço de busca perfeitamente inalterado.
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

// Fronteira A* (Fase 4)
class FilaPrioridadeAStar : public FronteiraBusca {
private:
    struct ComparadorAStar {
        bool operator()(const Estado& a, const Estado& b) const {
            int f_a = a.profundidade + calcularHeuristica(a);
            int f_b = b.profundidade + calcularHeuristica(b);
            // Em caso de empate, prioriza o estado mais profundo (maior g(n)) para resolver mais rápido
            if (f_a == f_b) {
                return a.profundidade < b.profundidade;
            }
            return f_a > f_b; // Menor f(n) no topo da max-heap do C++
        }

        static int calcularHeuristica(const Estado& e) {
            int dist_manhattan = 0;
            int custo_orientacao = 0;

            for (int i = 0; i < 8; ++i) {
                int id_atual = e.cubo[i].id;
                
                // Coordenadas 3D atuais (i)
                int x1 = i % 2;
                int y1 = (i < 4) ? 1 : 0;
                int z1 = ((i / 2) % 2 == 0) ? 1 : 0;

                // Coordenadas 3D alvo (id_atual)
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

#endif // FRONTEIRABUSCA_H
