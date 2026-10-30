#include "day8_lib.h"
#include "day3_lib.h"
#include "day7_lib.h"


#if 1
struct student{
    int num;
    double grade;
    char name[20];
};
typedef struct student my_student;
void print_student(my_student a){
    printf("%d %.1f %s\n",a.num,a.grade,a.name);
}
void print_studentP(my_student*p){
    printf("%d %.1f %s\n",p->num,p->grade,p->name);
}
int main(void){
    struct student a = {1,4.3,"Soyoung Yoon"};
    my_student b;
    b=a;//복사!!
    b.num=2;
    print_student(b);
    print_studentP(&b);
  
    return 0;
}

#endif

// 숙제 - 큰 메모리를 한 번 할당받아 그 메모리에 주소 및 문자를 모두 저장
// 모두 저장 후, realloc을 사용해 불필요한 메모리 반환하여 보세요.
#if 0

char** get_data(int n) {
    char** parr = NULL;
    char str[21] = { 0 };
    parr = (char**)calloc(n, sizeof(char*));
    printf("%p\n", parr);
    if (parr == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; ++i) {
        scanf("%s", str);
        printf("%s\n", str);
        parr[i] = (char*)malloc(strlen(str) + 1);
        if (parr[i] == NULL) {
            free_mem2(&parr, i);
            return NULL;
        }
        strcpy(parr[i], str);
    }
    return parr;
}

int main(void) {
    int n;
    char str[21] = { 0 };
    char** parr = NULL;
    freopen("data.txt", "r", stdin);
    scanf("%d", &n);

    parr = (char**)malloc(1000);
    if (parr == NULL) {
        return 12;
    }
    parr[0] = (char*)parr + n;  // 시작주소 + sizeof(char*) * n
    printf("%p %p\n", parr, parr[0]);
    //for (int i = 0; i < n; ++i) {
    //    scanf("%s", parr[0]);

    //}
    return 0;
}

#endif


#if 0
//이중포인터 할당
typedef char c21[21];

int main(void){
    int N;
    char str[21] = {0};
    char** parr = NULL;
    freopen("data.txt", "r",stdin);
    scanf("%d",&N);
    printf("%d\n",N);
    parr = (char**)calloc(N,sizeof(char*)); //char*를 3개저장하고싶은거야 문자열을 저장하려고 문자열을 저장할공간을 이제 받아야겠지?
    if(parr == NULL){
        return 12;
    }

    for(int i=0;i<N;++i){
        scanf("%s",str);
        //parr[i]= str;// str의 주소를 넘기기때문에 결국다같은주소가 저장이된다.
        parr[i] = (char*)malloc(strlen(str)+1);
        if (parr[i] == NULL) {
            free_mem2((void***)&parr, i);   // 지금까지 할당한 i개만 해제
            return 12;
        }
        strcpy(parr[i],str);
    }
    print_strdata(parr,N);
    free_mem2((void***)&parr,N);
    printf("parr == NULL: %d\n", parr == NULL);
    return 0;
}


#endif


#if 0

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
