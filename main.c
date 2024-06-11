#include <stdio.h>

#define MAX_EMPLOYEES 1000

int parent[MAX_EMPLOYEES]; // "Pai" de cada elemento
int rank[MAX_EMPLOYEES];

void initialize(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i; // Todo elemento é seu próprio pai
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Compressão de caminho
    }
    return parent[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        // União por ranking
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        }
        else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        }
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int sameDepartment(int emp1, int emp2) { return find(emp1) == find(emp2); }

int main() {
    int n = 20; // Número de empregados
    initialize(n);

    // Inicialização manual de dois departamentos com 5 empregados cada
    for (int i = 0; i < 5; i++) {
        unionSets(i, 0);
    }

    for (int i = 6; i < 10; i++) {
        unionSets(i, 5);
    }

    printf("Estrutura inicial (antes de utilizarmos union):\n");
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("Empregado %d está no departamento %d\n", i, find(i));
    }
    printf("\n");

    unionSets(1, 2);
    unionSets(3, 4);
    unionSets(2, 4);
    unionSets(2, 4);
    unionSets(17, 18);

    printf("Estrutura depois de utilizarmos union:\n");
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("Empregado %d está no departamento %d\n", i, find(i));
    }
    printf("\n");

    printf("Empregados 1 e 3 estão no mesmo departamento? %s\n",
        sameDepartment(1, 3) ? "Sim" : "Nao");
    printf("Empregados 1 e 5 estão no mesmo departamento? %s\n",
        sameDepartment(1, 5) ? "Sim" : "Nao");
    printf("Empregados 3 e 4 estão no mesmo departamento? %s\n",
        sameDepartment(3, 4) ? "Sim" : "Nao");
    printf("Empregados 17 e 18 estão no mesmo departamento? %s\n",
        sameDepartment(17, 18) ? "Sim" : "Nao");

    return 0;
}
