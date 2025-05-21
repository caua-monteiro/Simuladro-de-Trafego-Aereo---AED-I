#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

//O codigo foi desenvolvido pensando apenas em usos em Windows!!!!!!

struct no {
    int id;
    int prioridade;
    int tempo_espera;
};

bool operator<(no a, no b) {
    return a.prioridade > b.prioridade;
}

class FilaDePrioridade {
private:
    priority_queue<no> fila;

public:
    
    void inserir(int id, int prioridade) {
        fila.push({id, prioridade, 0});
    }

    no retirar() {
        if (!fila.empty()){
            no topo = fila.top();
            fila.pop();
            return topo;
        }
        else {
            throw runtime_error("Fila vazia!");
        } 

    }

    void incrementar_espera() {
        vector<no> temp;
        while (!fila.empty()) {
            no atual = fila.top();
            fila.pop();
            atual.tempo_espera++;
            temp.push_back(atual);
        }
        for (auto item : temp) {
            fila.push(item);
        }
    }

    void exibir() {
        vector<no> temp;
        cout << "[";
        while (!fila.empty()) {
            no atual = fila.top();
            fila.pop();
            cout << "(ID: " << atual.id << ", Prioridade: " << atual.prioridade
                 << ", Espera: " << atual.tempo_espera << ") ";
            temp.push_back(atual);
        }
        cout << "]" << endl;
        for (auto item : temp) {
            fila.push(item);
        }
    }

    bool vazia() {
        return fila.empty();
    }
};

int main() {
    FilaDePrioridade FP_pouso, FP_Decolagem;
    int tempo = 0, contador_id = 1, max_voos = 50, pista1_tempo_restante = 0, pista2_tempo_restante = 0;
    no AviaoPistaPouso = {-1, -1, -1}, AviaoPistaDecolagem = {-1, -1, -1};

    srand(time(NULL));

    while (contador_id <= max_voos || !FP_pouso.vazia() || !FP_Decolagem.vazia()) {
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

        cout << "Tempo: " << tempo << endl << endl;

        if (contador_id <= max_voos) {
            for (int i = 0; i < 5 && contador_id <= max_voos; i++) {
                int tipo = rand() % 2; 
                int prioridade = rand() % 2 + 1;
                if (tipo == 0) {
                    FP_pouso.inserir(contador_id++, prioridade);
                    cout << "Novo pedido de POUSO (ID: " << contador_id - 1 << ", Prioridade: " << prioridade << ")" << endl;
                } else {
                    FP_Decolagem.inserir(contador_id++, prioridade);
                    cout << "Novo pedido de DECOLAGEM (ID: " << contador_id - 1 << ", Prioridade: " << prioridade << ")" << endl;
                }
            }
        }

        cout << endl;

        if (pista1_tempo_restante == 0) {
            if (!FP_pouso.vazia()) {
                AviaoPistaPouso = FP_pouso.retirar();
                pista1_tempo_restante = 2;
                cout << "Pista 1: POUSO autorizado (ID: " << AviaoPistaPouso.id << ")" << endl;
            } else {
                cout << "Pista 1: Sem voos pendentes" << endl;
            }
        } else {
            cout << "Pista 1: Ocupada (ID: " << AviaoPistaPouso.id << ", Tempo restante: " << pista1_tempo_restante << ")" << endl;
            pista1_tempo_restante--;
        }

        if (pista2_tempo_restante == 0) {
            if (!FP_Decolagem.vazia()) {
                AviaoPistaDecolagem = FP_Decolagem.retirar();
                pista2_tempo_restante = 3; 
                cout << "Pista 2: DECOLAGEM autorizada (ID: " << AviaoPistaDecolagem.id << ")" << endl;
            } else {
                cout << "Pista 2: Sem voos pendentes" << endl;
            }
        } else {
            cout << "Pista 2: Ocupada (ID: " << AviaoPistaDecolagem.id << ", Tempo restante: " << pista2_tempo_restante << ")" << endl;
            pista2_tempo_restante--;
        }

        
        cout << endl << "Fila de POUSOS: ";
        FP_pouso.exibir();

        cout << endl << "Fila de DECOLAGENS: ";
        FP_Decolagem.exibir();

        FP_pouso.incrementar_espera();
        FP_Decolagem.incrementar_espera();

         cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        tempo++;
        system("pause");
        //system("cls");
    }

    return 0;
}
