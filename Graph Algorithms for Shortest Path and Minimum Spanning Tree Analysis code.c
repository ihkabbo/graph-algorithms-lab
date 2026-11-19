#include <stdio.h>
#include <limits.h>
#define MAX 100
#define MAXE 10000
#define INF LLONG_MAX

struct Edge {
    int u, v;
    long long w;
};

int parent[MAX];

int findParent(int x){
    if(parent[x] != x)
        parent[x] = findParent(parent[x]);

    return parent[x];
}

void unionSet(int a , int b){
    int x = findParent(a);
    int y = findParent(b);

    if(x != y)
        parent[y] = x;
}

void sortEdges(struct Edge edge[] , int m){
    struct Edge temp;

    for(int i=0 ; i < m-1 ; i++){
        for(int j=0 ; j < m-i-1 ; j++){
            if(edge[j].w > edge[j+1].w){
                temp = edge[j];
                edge[j] = edge[j+1];
                edge[j+1] = temp;
            }
        }
    }
}

void printPath(char name[] , int path[] , int count , long long cost){
    printf("%s: " , name);

    if(count == 0){
        printf("Not Possible\n");
        return;
    }

    for(int i=0 ; i < count ; i++){
        printf("%d" , path[i]);

        if(i < count-1)
            printf(" -> ");
    }

    printf(" (Cost: %lld)\n" , cost);
}

int dijkstra(long long graph[MAX][MAX] , int n , int src , int dest , int path[] , long long *cost){

    long long dist[MAX];
    int visited[MAX] = {0};
    int prev[MAX];

    for(int i=0 ; i < n ; i++){
        dist[i] = INF;
        prev[i] = -1;
    }

    dist[src] = 0;

    for(int i=0 ; i < n ; i++){
        int u = -1;

        for(int j=0 ; j < n ; j++){
            if(!visited[j] && (u == -1 || dist[j] < dist[u])){
                u = j;
            }
        }

        if(u == -1 || dist[u] == INF)
            break;

        visited[u] = 1;

        for(int j=0 ; j < n ; j++){
            if(graph[u][j] > 0 && !visited[j]){
                if(dist[u] + graph[u][j] < dist[j]){
                    dist[j] = dist[u] + graph[u][j];
                    prev[j] = u;
                }
            }
        }
    }

    if(dist[dest] == INF)
        return 0;

    int temp[MAX];
    int count = 0;
    int current = dest;

    while(current != -1){
        temp[count] = current;
        count++;
        current = prev[current];
    }

    for(int i=0 ; i < count ; i++){
        path[i] = temp[count-i-1];
    }

    *cost = dist[dest];

    return count;
}

int kruskal(int n , struct Edge edge[] , int m , long long tree[MAX][MAX]){

    struct Edge sorted[MAXE];
    int count = 0;

    for(int i=0 ; i < m ; i++){
        sorted[i] = edge[i];
    }

    sortEdges(sorted , m);

    for(int i=0 ; i < n ; i++){
        parent[i] = i;
    }

    for(int i=0 ; i < m ; i++){
        int u = sorted[i].u;
        int v = sorted[i].v;

        if(findParent(u) != findParent(v)){
            unionSet(u , v);

            tree[u][v] = sorted[i].w;
            tree[v][u] = sorted[i].w;

            count++;
        }

        if(count == n-1)
            break;
    }

    return count == n-1;
}

int prim(long long graph[MAX][MAX] , int n , long long tree[MAX][MAX]){

    long long key[MAX];
    int visited[MAX] = {0};
    int prev[MAX];

    for(int i=0 ; i < n ; i++){
        key[i] = INF;
        prev[i] = -1;
    }

    key[0] = 0;

    for(int i=0 ; i < n ; i++){
        int u = -1;

        for(int j=0 ; j < n ; j++){
            if(!visited[j] && (u == -1 || key[j] < key[u])){
                u = j;
            }
        }

        if(u == -1 || key[u] == INF)
            return 0;

        visited[u] = 1;

        for(int j=0 ; j < n ; j++){
            if(graph[u][j] > 0 && !visited[j] && graph[u][j] < key[j]){
                key[j] = graph[u][j];
                prev[j] = u;
            }
        }
    }

    for(int i=1 ; i < n ; i++){
        int p = prev[i];

        if(p == -1)
            return 0;

        tree[p][i] = graph[p][i];
        tree[i][p] = graph[p][i];
    }

    return 1;
}

int bfs(long long tree[MAX][MAX] , int n , int src , int dest , int path[] , long long *cost){

    int queue[MAX];
    int visited[MAX] = {0};
    int prev[MAX];

    int front = 0, rear = 0;

    for(int i=0 ; i < n ; i++){
        prev[i] = -1;
    }

    queue[rear] = src;
    rear++;
    visited[src] = 1;

    while(front < rear){
        int u = queue[front];
        front++;

        if(u == dest)
            break;

        for(int i=0 ; i < n ; i++){
            if(tree[u][i] > 0 && !visited[i]){
                visited[i] = 1;
                prev[i] = u;
                queue[rear] = i;
                rear++;
            }
        }
    }

    if(!visited[dest])
        return 0;

    int temp[MAX];
    int count = 0;
    int current = dest;

    *cost = 0;

    while(current != -1){
        temp[count] = current;
        count++;
        current = prev[current];
    }

    for(int i=0 ; i < count ; i++){
        path[i] = temp[count-i-1];
    }

    for(int i=0 ; i < count-1 ; i++){
        *cost += tree[path[i]][path[i+1]];
    }

    return count;
}

int main()
{
    FILE *fp = fopen("input.txt" , "r");

    if(fp == NULL){
        printf("File not found!\n");
        return 1;
    }

    int n, m;

    if(fscanf(fp, "%d %d" , &n , &m) != 2 ||
       n < 1 || n > MAX || m < 0 || m > MAXE){
        printf("Invalid input!\n");
        fclose(fp);
        return 1;
    }

    struct Edge edge[MAXE];
    struct Edge newEdge[MAXE];

    long long graph[MAX][MAX] = {0};
    long long kTree[MAX][MAX] = {0};
    long long pTree[MAX][MAX] = {0};
    long long newKTree[MAX][MAX] = {0};
    long long newPTree[MAX][MAX] = {0};

    for(int i=0 ; i < m ; i++){
        if(fscanf(fp, "%d %d %lld" , &edge[i].u , &edge[i].v , &edge[i].w) != 3){
            printf("Invalid edge input!\n");
            fclose(fp);
            return 1;
        }

        int u = edge[i].u;
        int v = edge[i].v;

        if(u < 0 || u >= n || v < 0 || v >= n || u == v || edge[i].w <= 0){
            printf("Invalid edge!\n");
            fclose(fp);
            return 1;
        }

        graph[u][v] = edge[i].w;
        graph[v][u] = edge[i].w;
    }

    int src, dest;

    if(fscanf(fp, "%d %d" , &src , &dest) != 2 ||
       src < 0 || src >= n || dest < 0 || dest >= n){
        printf("Invalid source or destination!\n");
        fclose(fp);
        return 1;
    }

    int removeU, removeV;

    if(fscanf(fp, "%d %d" , &removeU , &removeV) != 2 ||
       removeU < 0 || removeU >= n || removeV < 0 || removeV >= n){
        printf("Invalid edge to remove!\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    int path[MAX];
    int count;
    long long cost = 0;

    count = dijkstra(graph , n , src , dest , path , &cost);
    printPath("Shortest Path" , path , count , cost);

    if(kruskal(n , edge , m , kTree))
        count = bfs(kTree , n , src , dest , path , &cost);
    else
        count = 0;

    printPath("Kruskal Path" , path , count , cost);

    if(prim(graph , n , pTree))
        count = bfs(pTree , n , src , dest , path , &cost);
    else
        count = 0;

    printPath("Prim Path" , path , count , cost);

    printf("\nAfter Removing Edge (%d,%d):\n" , removeU , removeV);

    int found = 0;

    for(int i=0 ; i < m ; i++){
        if((edge[i].u == removeU && edge[i].v == removeV) ||
           (edge[i].u == removeV && edge[i].v == removeU)){
            found = 1;
        }
    }

    if(found){
        graph[removeU][removeV] = 0;
        graph[removeV][removeU] = 0;
    }

    int newM = 0;

    for(int i=0 ; i < m ; i++){
        if(found &&
           ((edge[i].u == removeU && edge[i].v == removeV) ||
            (edge[i].u == removeV && edge[i].v == removeU))){
            continue;
        }

        newEdge[newM] = edge[i];
        newM++;
    }

    count = dijkstra(graph , n , src , dest , path , &cost);
    printPath("Updated Shortest Path" , path , count , cost);

    if(kruskal(n , newEdge , newM , newKTree))
        count = bfs(newKTree , n , src , dest , path , &cost);
    else
        count = 0;

    printPath("Updated Kruskal Path" , path , count , cost);

    if(prim(graph , n , newPTree))
        count = bfs(newPTree , n , src , dest , path , &cost);
    else
        count = 0;

    printPath("Updated Prim Path" , path , count , cost);

    return 0;
}
