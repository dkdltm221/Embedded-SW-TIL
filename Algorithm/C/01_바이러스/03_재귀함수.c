#include <stdio.h>

#if 0

int factorial(int n){
    static int memo[100] = {0}; // memo[5] -> factorial(5)
    if(n == 0 || n == 1) return 1;
    if(memo[n] != 0) return memo[n];
    memo[n] = n * factorial(n-1);
    return memo[n];
}

int main(void){
    printf("%d \n", factorial(5));
}
#endif

#if 0

int N=3;
int sol[10]; //sol[1] = 처음 선택 결과,내ㅣ[2] 두번째 선택결과
void printList(int* arr, int n){
    for(int i=1;i<=N;i++){
        printf("%d", arr[i]);
    }
    printf("\n");
}
void test07_R(int L){
    if( L>N){
        printList(sol,N);
        return;
    }
    for(int i=1;i<=6;i++){
        sol[L] = i;
        test07_R(L+1);
    }
}

int main(void){
    test07_R(1);
}


#endif

#if 0
int N=3;
int sol[10]; //sol[1] = 처음 선택 결과,내ㅣ[2] 두번째 선택결과
void printList(int* arr, int n){
    for(int i=1;i<=N;i++){
        printf("%d", arr[i]);
    }
    printf("\n");
}
void test08(int L,int start){
    if(L>N){
        printList(sol,N);
        return;
    }
    for(int i=start;i<=6;i++){
        sol[L]=i;
        test08(L+1,i+1);
    }
}
N: 몇개 던질건지
L: 현재 몇번째 주사위인지 안내하는 순서 
i: 주사위 눈의 수
start: 한번의 던짐에 중ㄴ복이 생기지 않도록 시작 지점을 지정
test08 이란 사용자가 주사위 던질 횟수 와 시작 지점을 정해주었을때
한번의 던짐에 따른 중복이 나오지않는 가능성들을 제시해준다.
int main(void){
    test08(1,1);
    return 0;
}

#endif



#if 0
// 해밀턴 순환회로 백트랙킹 방식 사용

// 1. parameter: 비용,현재 몇번째 이동인지,이전 장소
// 2. 종료 : 현재 비용이 지금까지 측정한 비용보다 크면 종료
// 지금 이동횟수가 장소의 개수가 같을때 지금까지의 비용과 돌아가능비용의합이
// 지금까지의 측정한 최솟값보다 작을때 업데이트한다.
//3.행동선택 : 방문한곳은 다시 방문하지않는다 자기자신의 장소에 방문하지않는다.
// 다음 장소를 선택한후 지금의 장소와 비용을 계산해서 파라미터로 넘긴다.
// 그 후에 방문한곳을 취소한다.
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
int N;
int visited[14] = {0};
int map[100][100];
int min = 1000000000;

void dp(int distance, int cur, int num) {
    if (distance > min)
        return;

    if (N == cur) {
        if (map[num][0] != 0) {
            min = MIN(min, distance + map[num][0]);
        }
        return;
    }

   
    for (int i = 0; i < N; i++) {
        if (visited[i] != 0 || map[num][i] == 0)
            continue;
        visited[i] = 1;
        dp(distance + map[num][i],cur + 1, i);
        visited[i] = 0;
    }
}

int main(void) {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &map[i][j]);
        }
    }

    visited[0] = 1;
    dp(0, 1, 0);
    printf("%d", min);

    return 0;
}

#endif

#if 0
//N queen 문제
#define MAX (13+2)
int queenN[2*MAX];
int queenM[2*MAX];
int cor[MAX];
int map[MAX][MAX];
int N;
int count;


void dfs(int row,int c){
    if(row>N){
        count+=1;
    }
    for(int i=1;i<=N;i++){
        if(queenN[row+i]!=0 || queenM[N-(row-i)]!=0 || cor[i]!=0) continue;
        queenN[row+i] = 1; queenM[N-(row-i)] = 1; cor[i] =1;
        dfs(row+1,i);
        queenN[row+i] = 0; queenM[N-(row-i)] = 0; cor[i] =0;
    }

}
int main(void){
    scanf("%d",&N);
    count=0;
    dfs(1,1);
    printf("%d",count);

}
#endif

#if 01 


#include <stdio.h>

int map[7][7];
int visitedR[7];
int visitedC[7];
int visitedCrosR;
int visitedCrosC;
int bingo;


void check(int i,int j){
    if(++visitedR[i]==5){
        bingo++;
    }
    if(++visitedC[j]==5){
        bingo++;
    }
    if(i==j && ++visitedCrosR==5){
        bingo++;
    }
    if(i+j==6 && ++visitedCrosC==5){
        bingo++;
    }
}

int checkBingo(int n){
    for(int i=1;i<6;i++){
        for(int j=1;j<6;j++){
            if(map[i][j]==n){
                check(i,j);
                map[i][j]=0;
                return bingo>=3;
            }
        }
    }
    return bingo>=3;
}



int main(void){
    int index=1;
    bingo = 0;
    for(int i=1;i<6;i++){
        for(int j=1;j<6;j++){
            scanf("%d",&map[i][j]);
        }
    }
    for(;index<26;index++){
        int n;
        scanf("%d",&n);
        if(checkBingo(n)){
            return index;
        }
    }
    return 0;
}

#endif
