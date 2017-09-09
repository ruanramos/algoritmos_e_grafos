#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<deque>
using namespace std;

vector<int>* AllocMatrix(int n) {
    vector<int>* adj = (vector<int>*) malloc(n * sizeof(vector<int>));
    for (int i = 0; i < n; i++) {
        adj[i] = vector<int>();
    }
    return adj;
}



void PrintMatrix(vector<int>* adj, int n) {
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < (int) adj[i].size(); j++) {
            printf("%3d", adj[i][j]);
        }
        printf("\n");
    }
}

void Bfs(vector<int>* adj, int n) {
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
            printf("%d : %d\n", v + 1, adj[v].size());
            breadth[v] = l++;
            
            for (int i = 0; i < (int) adj[v].size(); i++) {
                if (parent[adj[v][i]] == -1) {
                    q.push_back(adj[v][i]);
                    parent[adj[v][i]] = v;
                }
            }
        }
    }
    
    printf("\nResults:\n");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d \n", i + 1, parent[i]+1, breadth[i]);
    }
}

int nextDIn, nextDOut;
int Dfs(vector<int>* adj, int n, int r, int parent, int* dIn, int* dOut) {
    dIn[r] = nextDIn++;
    printf("Estou visitando o vertice %d\n", r + 1);
    int myP = r;
    int children = 0;
    for (int i = 0; i < (int) adj[r].size(); i++) {
        int v = adj[r][i];
        printf("Estou visitando a aresta %d - %d\n", r + 1, v + 1);
        if (parent != v && dIn[v] == -1) {
            // visito o vertice filho do vertice atual
            int p = Dfs(adj, n, v, r, dIn, dOut);
            children++;
            if (dIn[p] < dIn[myP]) {
                // checo se meu filho alcança um vertice mais alto que eu
                // consigo alcançar com no máximo uma aresta de retorno
                myP = p;
            } else if (dIn[p] >= dIn[r] && parent != r) {
                printf("%d is articulation\n", r + 1);
            }
        } else if (parent != v) {
            // aresta de retorno
            if (dIn[v] < dIn[myP]) {
                myP = v;
            }
        }
    }
    dOut[r] = nextDOut++;
    if (parent == r && children > 1) {
        printf("%d is articulation\n", r + 1);
    }
    return myP;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<int>* adj = AllocMatrix(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    PrintMatrix(adj, n);
    //Bfs(adj, n);
    nextDIn = 1;
    nextDOut = 1;
    int* dIn = (int*) malloc(n * sizeof(int));
    int* dOut = (int*) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dIn[i] = -1;
        dOut[i] = -1;
    }
    for (int r = 0; r < n; r++) {
        if (dIn[r] != -1) {
            continue;
        }
        Dfs(adj, n, r, r, dIn, dOut);
    }
        
    
    return 0;
}
