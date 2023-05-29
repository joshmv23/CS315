//Josh Morfin-Vazquez -- Assignment 2 CS 315

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Hendrix college website on topological sort helped me get insight on how to go about doing the topological sort function and what type of variables I needed to complete this.

#define MAX_N 1000
#define INF 1000000000

int n, m; // n is number of nodes, m is number of edges
int adj[MAX_N][MAX_N]; // adjacency matrix
int indegree[MAX_N]; // indegree of nodes
int dp[MAX_N]; // dynamic programming array
int cnt[MAX_N]; // count of longest paths
int longest; // length of longest path

//function to find the max of two integers
int max(int a, int b) {
    return a > b ? a : b;
}

void topological_sort() {
    int queue[MAX_N], front = 0, rear = 0; //make Queue
    for (int i = 1; i <= n; i++) { //loop over n nodes
        if (indegree[i] == 0) { //indegree 0 case
            queue[rear++] = i; //enqueue the index of the node
            dp[i] = 0; //
        } else {
            dp[i] = -INF;
        }
    }
    while (front != rear) { // while front does not equal the rear of queue
        int u = queue[front++];
        for (int v = 1; v <= n; v++) { //loop over nodes again
            if (adj[u][v] != -1) {
                indegree[v]--; //travsersed a directed edge at index v
                if (indegree[v] == 0) { //no directed edges pointing at that node
                    queue[rear++] = v; //enqueue v
               }
                dp[v] = max(dp[v], dp[u] + adj[u][v]); //get max and store in dp[v]
            }
        }
    }
    longest = dp[n]; //store longest path in longest variable
}

//function counts number of paths
void count_paths() {
    cnt[1] = 1;
    for (int i = 2; i <= n; i++) { //loop over number of nodes
        for (int j = 1; j <= n; j++) {
            if (adj[j][i] != -1 && dp[j] + adj[j][i] == dp[i]) {
                cnt[i] += cnt[j]; //increment count to the number of longest paths
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);// scan first two numbers to get values for n and m
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = -1; //form the empty matrix
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w); //get the values for the rest of the file
        adj[u][v] = w; //make the adjacency matrix
        indegree[v]++;
    }
    topological_sort(); //topological sort, pseudocode online
    count_paths(); //function meant only to count number of paths
    printf("longest path: %d\n", longest);
    printf("number of longest paths: %d\n", cnt[n]);
    return 0;
}
