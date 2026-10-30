#include "day8_lib.h"
#include "day3_lib.h"


#if 1

int main(void){
    int N;
    freopen("data.txt", "r",stdin);
    scanf("%d",&N);
    printf("%d\n",N);
    char (*arr)[21] = (char(*)[21])calloc(N,sizeof(char)*21);
    for(int i=0;i<N;++i){
        scanf("%s",arr[i]);
        printf("%s\n",arr[i]);
    }
    free(arr);
    arr = NULL;
    return 0;
}


#endif

#if 0

// n을 3으로 시작해,필요시 3씩 증가하는 크기를 가진 배열 구현
// 사용자에게 숫자를 입력받고 0보다 큰 양의 정수일 때 반복입력
// 0 이하의 숫자일때 종료하고 입력 받은 것을 출력하는 프로그램 작성
void free_mem(int **p) {
    if (p == NULL) return; // 아래의 *p 동작이 있어,p가  null인것을 검사
    free(*p);
    *p = NULL;
}

int main(void){
    typedef int* intP;
    int N=3;
    int num =0;
    int count=0;
    intP pi,temp;
    pi = (int*)calloc(N,sizeof(int));
    if(pi == NULL){
        printf("메모리부족\n");
        return 0;
    }
    printf("숫자를 입력해주세요\n");
    for(;scanf("%d",&num)==1 && num>0;count++){
        if(count == N){
            N+=3;
            temp = (int*)realloc(pi,sizeof(int)*N);
            if(temp==NULL){
                printf("메모리 부족\n");
                free_mem(&pi);
                exit(1);
            }
            pi = temp;
        }
        pi[count] = num;
    }
    
    print_data(pi,count);
    free_mem(&pi);
    return 0;
}

#endif





#if 0
int main(void){
    int n= 10;
    int* arr = (int*)malloc(sizeof(int)*n);
    if(arr==NULL) return 12;
    int* temp = (int*)realloc(arr,n*sizeof(int));
    if(temp = NULL) return 12;
    if(temp!=arr) arr =temp;

}

#endif

#if 0

int* pi;
double* pd;
int main(void){
    pi = (int*)malloc(10*sizeof(int));
    if (pi == NULL){
        printf("메모리부족");
        exit(1);
    }
    pd = (double*)malloc(10*sizeof(double));
    if(pd==NULL){
        printf("메모리 부족");
        exit(1);
    }
    printf("%p %p\n",pi,pd);
    free(pi); free(pd);

    return 0;
}



#endif
