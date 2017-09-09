#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<deque>
using namespace std;

int** AllocMatrix(int n) {
    int **adj = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        adj[i] = (int*) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            adj[i][j] = 0;
        }
    }
    return adj;
}



void PrintMatrix(int** adj, int n) {
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d", adj[i][j]);
        }
        printf("\n");
    }
}

void Bfs(int** adj, int n) {
    int* breadth = (int*) malloc(n * sizeof(int));
    int* parent = (int*) malloc(n * sizeof(int));
    int l = 1;
    for (int i = 0; i < n; i++) {
        parent[i] = -1;
    }
    
    deque<int> q;
    for (int r = 0; r < n; r++) {
        if (parent[r] != -1) {
            continue;
        }
        q.push_back(r);
        parent[r] = r;
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            printf("%d\n", v + 1);
            breadth[v] = l++;
            
            for (int i = 0; i < n; i++) {
                if (adj[v][i] && parent[i] == -1) {
                    q.push_back(i);
                    parent[i] = v;
                }
            }
        }
    }
    
    printf("\nResults:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d \n", i + 1, parent[i]+1, breadth[i]);
    }
}

int main() {
    int n, m;
    int** adj;
    scanf("%d %d", &n, &m);
    adj = AllocMatrix(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }
    
    Bfs(adj, n);
    return 0;
}
