#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

#if 1

//인접행렬
#define MAX_N (100+2)
int arr[MAX_N][MAX_N];
int V,E;
int visited[MAX_N];
int Queue[MAX_N];
int rear; //삽입위치,삽입하고 1증가
int front; // 삭제위치,삭제하고 1증가

void enqueue(int no){
    Queue[rear++] =no;
}
int dequeue(){
    return Queue[front++];
}

void input_data(void){
    int v1,v2;
    scanf("%d %d",&V,&E);
    for(int i=0;i<E;i++){
        scanf("%d %d",&v1,&v2);
        arr[v1][v2] = 1;
        arr[v2][v1] = 1;
    }
}
void print_data(int (*arr)[MAX_N],int n){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            printf("%d",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void input_data2(void){
    int v1,v2;
    scanf("%d %d",&V,&E);
    for(int i=0;i<E;i++){
        scanf("%d %d",&v1,&v2);
        arr[v1][++arr[v1][0]] = v2;
        arr[v2][++arr[v2][0]] = v1;
    }
}
void print_adj1(int(*arr)[MAX_N],int v){
    for(int i=0;i<V;i++){
        if(arr[v][i]==1)
            printf("%d ",i);
    }
}
void print_adj(int(*arr)[MAX_N],int v){
    for(int i=1;arr[v][i];){
        printf("%d ",arr[v][i++]);
    }
    printf("\n");
}
int virus_BFS1(int start){
    front = rear = 0;
    enqueue(start);
    visited[start] = 1;
    while(front!=rear){
        int node = dequeue();
        for(int i=1;i<=V;i++){
            if(visited[i]) continue;
            if(!arr[node][i]) continue;
            visited[i]=1;
            enqueue(i);  
        }
    }
    return front-1;
}
int virus_BFS2(int start){
    front = rear = 0;
    enqueue(start);
    visited[start] = 1;
    while(front!=rear){
        int node = dequeue();
        for(int i=1;arr[node][i];i++){
            if(visited[arr[node][i]]) continue;
            visited[arr[node][i]]=1;
            enqueue(arr[node][i]);  
        }
    }
    return front-1;
}
int main(void){
    freopen("01_data.txt","r",stdin);
    input_data2();
    print_data(arr,V);
    // print_adj(arr,1);
    printf("%d\n",virus_BFS2(4));
}
#endif