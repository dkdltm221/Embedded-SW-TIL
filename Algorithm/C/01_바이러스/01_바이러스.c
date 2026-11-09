#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE(x) (sizeof(x) / sizeof((x)[0]))



//  인접리스트 - 시험버전
#if 0

#define MAX_N (100+2)
int arr[MAX_N][MAX_N];
int V, E;
// Queue의 타입 : 저장할 내용의 타입 - 컴퓨터 번호 - int
// Queue의 개수 : 저장할 데이터의 최대 수 - 컴퓨터의 최대 수 - 100개
int Queue[MAX_N];
int rear; // 삽입위치, 삽입하고 1증가
int front;// 삭제위치, 삭제하고 1증가

void input_data(void) {
    int v1, v2;
    scanf("%d %d", &V, &E);
    for (int i = 0; i < E; ++i) {
        scanf("%d %d", &v1, &v2);
        arr[v1][++arr[v1][0]] = v2;
        arr[v2][++arr[v2][0]] = v1;
    }
}

// 디버깅 용도로 꼭 사용할 것
void print_data(int (*arr)[MAX_N], int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// start와 연결된 정점의 개수를 반환하는 함수
// 1. 시작점을 큐에 넣고, 방문표시
// 2. 큐에 정점이 있는 동안 반복
//   2-1. 큐에서 정점을 꺼냄
//   2-2. 꺼낸 정점과 연결된 정점을 찾아 방문하지 않은 정점을 큐에 넣고 방문표시

int virus_BFS(int start) {
    int visited[MAX_N] = { 0 };

    front = rear = 0;  // Queue 초기화
    Queue[rear++] = start;
    visited[start] = 1;

    while (front != rear) {
        int u = Queue[front++];
        int cnt = arr[u][0];
        for (int i = 1; i <= cnt; i++) {
            int v = arr[u][i];
            if (visited[v]) continue;
            Queue[rear++] = v;
            visited[v] = 1;
        }
    }
    return rear - 1;
}

int main(void) {
    //freopen("01_data.txt", "r", stdin);
    input_data();
    //print_data(arr, V);
    printf("%d\n", virus_BFS(1));
    return 0;
}
#endif

#if 0

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

#if 0
#include <stdio.h>
#define MAX 1000

int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

typedef struct _node {
    int nr, nc, day;
} node;

typedef struct _q {
    node que[MAX * MAX];
    int rear, front;
} q;

int map[MAX][MAX];
q queue;

int main(void) {
    int n, m;
    int max_day = 0;
    int tomato = 0;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &map[i][j]);
            if(map[i][j]==0)
                tomato++;
            if (map[i][j] == 1) {
                node nd = {i, j, 0};
                queue.que[queue.rear++] = nd;
            }
            
        }
    }

    while (queue.front != queue.rear) {
        node cur = queue.que[queue.front++];
        max_day = cur.day;

        for (int i = 0; i < 4; i++) {
            int r = cur.nr + dr[i];
            int c = cur.nc + dc[i];

            if (r < 0 || r >= n || c < 0 || c >= m) continue;
            if (map[r][c] != 0) continue;

            map[r][c] = 1;
            node next = {r, c, cur.day + 1};
            tomato--;
            queue.que[queue.rear++] = next;
        }
    }

    if(tomato!=0){
        printf("-1\n");
        return 0;
    }

    printf("%d\n", max_day);
    return 0;
}

#endif

#if 01
#include <stdio.h>

int map[30001];
int visited[3001];

int main(void) {
    int N, d, k, c;
    scanf("%d %d %d %d", &N, &d, &k, &c);

    for (int i = 0; i < N; i++) {
        scanf("%d", &map[i]);
    }

    int count = 1;
    int cnt = 0;

    // 쿠폰 초밥은 항상 포함
    visited[c] = 1;

    // 최초 윈도우 생성
    for (int i = 0; i < k; i++) {
        int sushi = map[i];

        if (visited[sushi] == 0)
            count++;

        visited[sushi]++;
    }

    cnt = count;

    // 슬라이딩 윈도우
    for (int i = 0; i < N - 1; i++) {

        // 1. 맨 앞 초밥 제거
        int remove = map[i];
        visited[remove]--;

        if (visited[remove] == 0)
            count--;

        // 2. 새로운 초밥 추가
        int add = map[(i + k) % N];

        if (visited[add] == 0)
            count++;

        visited[add]++;

        // 3. 최댓값 갱신
        if (count > cnt)
            cnt = count;
    }

    printf("%d\n", cnt);

    return 0;
}

#endif

#if 0

#include <stdio.h>

int cnt;


int main(void){
    int N,d,k,c;
    scanf("%d %d %d %d",&N,&d,&k,&c);
    int map[30001];
    for(int i=0;i<N;i++){
        scanf("%d",&map[i]);
    }
    for(int i=0;i<N;i++){
        int visited[3001] = {0};
        visited[c]=1;
        int count=1;
        for(int j=0;j<k;j++){
            int m =(i+j)%N;
            if(visited[map[m]]) continue;
            
            visited[map[m]]++;
            count++;
        }
        if(count>cnt) cnt=count;
    }
    printf("%d",cnt);
}

#endif

#if 0

typedef struct _stack{
    int front,rear;
}Stack;

Stack stack;

int solution(char* c){
    int pice = 0;
    stack.front = stack.rear = 0;
    for(int i=0;c[i]!='\0';i++){
        if(c[i]=='(' && c[i+1]==')'){
            pice += stack.rear - stack.front;
            i++;
            continue;
        }
        if(c[i]=='(')
            stack.rear++;
        else if(stack.front != stack.rear){
            pice++;
            stack.front++;
        }

    }
    return pice;
}


int main(void){
    char c[100001];
    scanf("%s",c);
    printf("%d\n",solution(c));
    return 0;

}
#endif

#if 0

#include <stdio.h>
#define N 5

typedef struct _node{
    int r,c
}node;

node arr[N*N+1];
int R[N+1];
int C[N+1];
int dl; //대각선 왼오
int dr; //대각선 오왼
int bingo_cnt;

void init(){
    for (int i = 1; i <= 5 ; i++) {
        for (int j = 1; j <= 5; j++) {
            int tmp;
            scanf("%d", &tmp);
            arr[tmp] = (node){i,j};
        }
    }
}

void check(int i,int j){
    if(++R[i]==5){
        bingo_cnt++;
    }
    if(++C[j]==5){
        bingo_cnt++;
    }
    if(i==j && ++dl==5){
        bingo_cnt++;
    }
    if(i+j==6 && ++dr==5){
        bingo_cnt++;
    }
}

void bingo(){
    int index=1;
    for(;index<=25;index++){
        int n;
        scanf("%d",&n);
        check(arr[n].r,arr[n].c);
        if(bingo_cnt>=3){ printf("%d",index); return;}
    }
}

int main(void) {
    init();
    bingo();
    return 0;
}

#endif


#if 0
#include <stdio.h>

typedef struct _node{
    int r,c;
}node;

#define N 5
int R[N+1];
int C[N+1];
node nums[N*N+1];
int visitedCrosR;
int visitedCrosC;
int bingo;


void check(int i,int j){
    if(++R[i]==5){
        bingo++;
    }
    if(++C[j]==5){
        bingo++;
    }
    if(i==j && ++visitedCrosR==5){
        bingo++;
    }
    if(i+j==6 && ++visitedCrosC==5){
        bingo++;
    }
}

int main(void){
    int index=1;
    bingo = 0;
    for(int i=1;i<6;i++){
        for(int j=1;j<6;j++){
            int n;
            scanf("%d",&n);
            nums[n] = (node){i,j};
        }
    }
    for(;index<26;index++){
        int n;
        scanf("%d",&n);
        check(nums[n].r,nums[n].c);
        if(bingo>=3){
            printf("%d",index);
            break;
        }
    }
    return 0;
}

#endif

#if 0
#include <stdio.h>
#define MAX 1000

int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

int N;
int mountN,mountM;
int map[MAX][MAX];
int cost_map[MAX][MAX];

typedef struct _node {
    int nr, nc,climing;
} node;

typedef struct _q {
    node que[MAX * MAX];
    int rear, front;
} q;

q queue;



void initMap(){
    scanf("%d %d %d",&N,&mountN,&mountM);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &map[i][j]);
            if(i==1 || i==N || j ==1 || j==N){
                node nd = {i, j,map[i][j]};
                cost_map[i][j] = map[i][j];
                queue.que[queue.rear++] = nd;
            }else{
                cost_map[i][j] = MAX*MAX;
            }
        }
    }
}
int compareCost(node nod , int nr,int nc){
    if(nod.climing == map[nr][nc]){
        return nod.climing;
    }else if( nod.climing > map[nr][nc]){
        return nod.climing-map[nr][nc];
    }else{
        int num = map[nr][nc] - nod.climing;
        return num*num;
    }
}
void bfs(){
    while (queue.front != queue.rear) {
        node cur = queue.que[queue.front++];
        for (int i = 0; i < 4; i++) {
            int r = cur.nr + dr[i];
            int c = cur.nc + dc[i];

            if (r < 1 || r > N || c < 1 || c > N) continue;
            int cost = cost_map[cur.nr][cur.nc]+compareCost(cur,r,c);
            if(cost >= cost_map[r][c]) continue;
            cost_map[r][c] = cost;
            node next = {r, c,cost};
            queue.que[queue.rear++] = next;
        }
    }
}
int main(void) {
   
    initMap();
    bfs();
    printf("%d",cost_map[mountN][mountM]);
    return 0;
}

#endif
