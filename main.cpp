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


const int cwOrder[8][3] = {
    {0, 2, 1},  
    {0, 1, 2},  
    {0, 1, 2},  
    {0, 2, 1},  
    {0, 1, 2},  
    {0, 2, 1},  
    {0, 2, 1},  
    {0, 1, 2},  
};

char getStickerColor(int pieceId, int ori, int pos, int axis) {
    
    char c[3];
    
    switch(pieceId) {
        case 0: c[0]='Y'; c[1]='G'; c[2]='O'; break;
        case 1: c[0]='Y'; c[1]='G'; c[2]='R'; break;
        case 2: c[0]='Y'; c[1]='B'; c[2]='O'; break;
        case 3: c[0]='Y'; c[1]='B'; c[2]='R'; break;
        case 4: c[0]='W'; c[1]='G'; c[2]='O'; break;
        case 5: c[0]='W'; c[1]='G'; c[2]='R'; break;
        case 6: c[0]='W'; c[1]='B'; c[2]='O'; break;
        case 7: c[0]='W'; c[1]='B'; c[2]='R'; break;
    }
    char cwColors[3];
    for (int i = 0; i < 3; i++) {
        cwColors[i] = c[cwOrder[pieceId][i]];
    }
    char twistedCW[3];
    for (int i = 0; i < 3; i++) {
        if (ori == 0) twistedCW[i] = cwColors[i];
        else if (ori == 1) twistedCW[i] = cwColors[(i + 2) % 3];
        else twistedCW[i] = cwColors[(i + 1) % 3];
    }
    for (int i = 0; i < 3; i++) {
        if (cwOrder[pos][i] == axis) {
            return twistedCW[i];
        }
    }
    return '?';
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
    char u0 = getStickerColor(e.cubo[0].id, e.cubo[0].orientacao, 0, 0);
    char u1 = getStickerColor(e.cubo[1].id, e.cubo[1].orientacao, 1, 0);
    char u2 = getStickerColor(e.cubo[2].id, e.cubo[2].orientacao, 2, 0);
    char u3 = getStickerColor(e.cubo[3].id, e.cubo[3].orientacao, 3, 0);
    
    
    char d0 = getStickerColor(e.cubo[6].id, e.cubo[6].orientacao, 6, 0);
    char d1 = getStickerColor(e.cubo[7].id, e.cubo[7].orientacao, 7, 0);
    char d2 = getStickerColor(e.cubo[4].id, e.cubo[4].orientacao, 4, 0);
    char d3 = getStickerColor(e.cubo[5].id, e.cubo[5].orientacao, 5, 0);
    
    char l0 = getStickerColor(e.cubo[0].id, e.cubo[0].orientacao, 0, 2);
    char l1 = getStickerColor(e.cubo[2].id, e.cubo[2].orientacao, 2, 2);
    char l2 = getStickerColor(e.cubo[4].id, e.cubo[4].orientacao, 4, 2);
    char l3 = getStickerColor(e.cubo[6].id, e.cubo[6].orientacao, 6, 2);
    
    char f0 = getStickerColor(e.cubo[2].id, e.cubo[2].orientacao, 2, 1);
    char f1 = getStickerColor(e.cubo[3].id, e.cubo[3].orientacao, 3, 1);
    char f2 = getStickerColor(e.cubo[6].id, e.cubo[6].orientacao, 6, 1);
    char f3 = getStickerColor(e.cubo[7].id, e.cubo[7].orientacao, 7, 1);
    
    char r0 = getStickerColor(e.cubo[3].id, e.cubo[3].orientacao, 3, 2);
    char r1 = getStickerColor(e.cubo[1].id, e.cubo[1].orientacao, 1, 2);
    char r2 = getStickerColor(e.cubo[7].id, e.cubo[7].orientacao, 7, 2);
    char r3 = getStickerColor(e.cubo[5].id, e.cubo[5].orientacao, 5, 2);
    
    char b0 = getStickerColor(e.cubo[1].id, e.cubo[1].orientacao, 1, 1);
    char b1 = getStickerColor(e.cubo[0].id, e.cubo[0].orientacao, 0, 1);
    char b2 = getStickerColor(e.cubo[5].id, e.cubo[5].orientacao, 5, 1);
    char b3 = getStickerColor(e.cubo[4].id, e.cubo[4].orientacao, 4, 1);
	faceU(u0, u1, u2, u3);
	faceLRFB(l0, l1, f0, f1, r0, r1, b0, b1, l2, l3, f2, f3, r2, r3, b2, b3);
	faceD(d0, d1, d2, d3);
}
int main() {
    Estado cuboAtual; 
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
                cout << "\033[2J\033[1;1H";
                imprimirCubo(cuboAtual);
                cout << "Movimentos disponiveis: U, U', R, R', F, F'\n";
                cout << "(Dica: use apostrofo ou 'i'/'2' para inverso, ex: Ui)\n";
                cout << "Digite um movimento ou 'voltar' para sair: ";
                string mov;
                cin >> mov;
                
                string movClean = "";
                for (char c : mov) {
                    if (c >= 'a' && c <= 'z') c = toupper(c);
                    if (c == '\'' || c == 'I' || c == '2' || (unsigned char)c > 127) {
                        if (movClean.length() > 0 && movClean.back() != '\'') {
                            movClean += '\'';
                        }
                    } else if (c >= 'A' && c <= 'Z') {
                        movClean += c;
                    }
                }
                if (movClean == "VOLTAR") {
                    break;
                }
                if (movClean == "U") cuboAtual = MotorCubo::moverU(cuboAtual);
                else if (movClean == "U'") cuboAtual = MotorCubo::moverU_linha(cuboAtual);
                else if (movClean == "R") cuboAtual = MotorCubo::moverR(cuboAtual);
                else if (movClean == "R'") cuboAtual = MotorCubo::moverR_linha(cuboAtual);
                else if (movClean == "F") cuboAtual = MotorCubo::moverF(cuboAtual);
                else if (movClean == "F'") cuboAtual = MotorCubo::moverF_linha(cuboAtual);
                
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
