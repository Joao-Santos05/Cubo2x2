#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include "Estado.h"
#include "MotorCubo.h"
#include "FronteiraBusca.h"
#include "BuscaMain.h"

using namespace std;

// Ponte para o motor visual (colega de trabalho)
void mapearParaInterface(const Estado& e, char adesivos[24]) {
    for (int pos = 0; pos < 8; ++pos) {
        int id = e.cubo[pos].id;
        int ori = e.cubo[pos].orientacao;
        
        char c[3];
        // Cores base para as 3 faces (Primária, Sec1, Sec2)
        switch(id) {
            case 0: c[0] = 'W'; c[1] = 'B'; c[2] = 'O'; break; // UBL
            case 1: c[0] = 'W'; c[1] = 'B'; c[2] = 'R'; break; // UBR
            case 2: c[0] = 'W'; c[1] = 'G'; c[2] = 'O'; break; // UFL
            case 3: c[0] = 'W'; c[1] = 'G'; c[2] = 'R'; break; // UFR
            case 4: c[0] = 'Y'; c[1] = 'B'; c[2] = 'O'; break; // DBL
            case 5: c[0] = 'Y'; c[1] = 'B'; c[2] = 'R'; break; // DBR
            case 6: c[0] = 'Y'; c[1] = 'G'; c[2] = 'O'; break; // DFL
            case 7: c[0] = 'Y'; c[1] = 'G'; c[2] = 'R'; break; // DFR
        }
        
        if (ori == 0) {
            adesivos[pos * 3 + 0] = c[0];
            adesivos[pos * 3 + 1] = c[1];
            adesivos[pos * 3 + 2] = c[2];
        } else if (ori == 1) { // Rotação horária
            adesivos[pos * 3 + 0] = c[2];
            adesivos[pos * 3 + 1] = c[0];
            adesivos[pos * 3 + 2] = c[1];
        } else if (ori == 2) { // Rotação anti-horária
            adesivos[pos * 3 + 0] = c[1];
            adesivos[pos * 3 + 1] = c[2];
            adesivos[pos * 3 + 2] = c[0];
        }
    }
}

void faceU (char c0, char c1, char c2, char c3){
	printf("\t\t\t\t\t\t\t _________ _________\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|    %c    |    %c    |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|_________|_________|\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|    %c    |    %c    |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|_________|_________|\n\n\t\t\t\t\t\t           |     |\n\t\t\t\t\t\t           |     |\n\t\t\t\t\t\t           |     |\n\t\t\t\t\t\t           |_____|\n\n", c0, c1, c2, c3);
}

void faceLRFB (char l0, char l1, char l2, char l3, char l4, char l5, char l6, char l7, char l8, char l9, char l10, char l11, char l12, char l13, char l14, char l15){
	printf("\t _________ _________     _________ _________     _________ _________     _________ _________\n\t|         |         |   |         |         |   |         |         |   |         |         |\n\t|    %c    |    %c    |   |    %c    |    %c    |   |    %c    |    %c    |   |    %c    |    %c    |\n\t|         |         |   |         |         |   |         |         |   |         |         |\n\t|_________|_________|   |_________|_________|   |_________|_________|   |_________|_________|\n\t|         |         |   |         |         |   |         |         |   |         |         |   |         |         |\n\t|    %c    |    %c    |   |    %c    |    %c    |   |    %c    |    %c    |   |    %c    |    %c    |\n\t|         |         |   |         |         |   |         |         |   |         |         |\n\t|_________|_________|   |_________|_________|   |_________|_________|   |_________|_________|\n\n\t        |                       _____                   _____                   _____\n\t        |                       |___                    |___/                   |___/\n\t        |                       |                       |\\                      |   \\\n\t        |_____                  |                       | \\                     |___|\n\n", l0, l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15);
}

void faceD (char d0, char d1, char d2, char d3){
	printf("\t\t\t\t\t\t\t _________ _________\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|    %c    |    %c    |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|_________|_________|\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|    %c    |    %c    |\n\t\t\t\t\t\t\t|         |         |\n\t\t\t\t\t\t\t|_________|_________|\n\n\t\t\t\t\t\t           ______\n\t\t\t\t\t\t           |     |\n\t\t\t\t\t\t           |     |\n\t\t\t\t\t\t           |_____/\n\n", d0, d1, d2, d3);
}

void imprimirCubo(const Estado& e) {
	char adesivos[24];
	mapearParaInterface(e, adesivos);
	
	faceU(adesivos[0], adesivos[3], adesivos[6], adesivos[9]);
	faceLRFB(adesivos[2], adesivos[8], adesivos[7], adesivos[10], adesivos[11], adesivos[5], adesivos[4], adesivos[1], adesivos[14], adesivos[20], adesivos[19], adesivos[22], adesivos[23], adesivos[17], adesivos[16], adesivos[13]);
	faceD(adesivos[18], adesivos[21], adesivos[12], adesivos[15]);
}

int main() {
    Estado cuboAtual; // Construtor padrão deixa o cubo resolvido
    int opcao = 0;
    
    while(opcao != 5) {
        cout << "\n=== Simulador e Solucionador de Cubo 2x2x2 ===\n";
        cout << "1. Jogar Manualmente / Embaralhar\n";
        cout << "2. Resolver com BFS (Busca em Largura)\n";
        cout << "3. Resolver com DFS Iterativa\n";
        cout << "4. Resolver com A* (Heuristica Admissivel)\n";
        cout << "5. Sair\n";
        cout << "Escolha: ";
        
        if (!(cin >> opcao)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        
        if (opcao == 1) {
            while (true) {
                // Clear screen cross-platform
                cout << "\033[2J\033[1;1H";
                
                imprimirCubo(cuboAtual);
                
                cout << "Movimentos disponiveis: U, U', R, R', F, F'\n";
                cout << "Digite um movimento ou 'voltar' para sair: ";
                string mov;
                cin >> mov;
                
                for (char &c : mov) {
                    c = toupper(c);
                }
                
                if (mov == "VOLTAR") {
                    break;
                }
                
                if (mov == "U") cuboAtual = MotorCubo::moverU(cuboAtual);
                else if (mov == "U'") cuboAtual = MotorCubo::moverU_linha(cuboAtual);
                else if (mov == "R") cuboAtual = MotorCubo::moverR(cuboAtual);
                else if (mov == "R'") cuboAtual = MotorCubo::moverR_linha(cuboAtual);
                else if (mov == "F") cuboAtual = MotorCubo::moverF(cuboAtual);
                else if (mov == "F'") cuboAtual = MotorCubo::moverF_linha(cuboAtual);
                
                // Limpa o caminho e profundidade para não influenciar buscas futuras
                cuboAtual.caminho_ate_aqui = ""; 
                cuboAtual.profundidade = 0;
            }
        }
        else if (opcao == 2) {
            FilaBFS bfs;
            long long visitados = 0;
            cout << "\nResolvendo com BFS...\n";
            string solucao = resolverCubo(cuboAtual, &bfs, visitados);
            cout << "Solucao: " << (solucao.empty() ? "Nenhuma (ja resolvido)" : solucao) << "\n";
            cout << "Estados visitados: " << visitados << "\n";
        }
        else if (opcao == 3) {
            cout << "\nResolvendo com DFS Iterativa...\n";
            long long totalVisitados = 0;
            string solucao = "Sem solução";
            
            // O máximo de movimentos para resolver um 2x2x2 é 14
            for (int limite = 1; limite <= 14; limite++) {
                PilhaDFS dfs(limite);
                long long visitadosParcial = 0;
                string res = resolverCubo(cuboAtual, &dfs, visitadosParcial);
                
                totalVisitados += visitadosParcial;
                
                if (res != "Sem solução") {
                    solucao = res;
                    break;
                }
            }
            if (cuboAtual.isObjetivo()) solucao = ""; 
            
            cout << "Solucao: " << (solucao.empty() ? "Nenhuma (ja resolvido)" : solucao) << "\n";
            cout << "Total de estados visitados (acumulado): " << totalVisitados << "\n";
        }
        else if (opcao == 4) {
            FilaPrioridadeAStar astar;
            long long visitados = 0;
            cout << "\nResolvendo com A*...\n";
            string solucao = resolverCubo(cuboAtual, &astar, visitados);
            cout << "Solucao: " << (solucao.empty() ? "Nenhuma (ja resolvido)" : solucao) << "\n";
            cout << "Estados visitados: " << visitados << "\n";
        }
    }
    
    return 0;
}