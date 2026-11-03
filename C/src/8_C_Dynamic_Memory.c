#include "day8_lib.h"
#include "day3_lib.h"
#include "day7_lib.h"

//포인터 배열도 동적할당, 배열의 멤버도 동적할당 받는 코드 작성
// 아래놈이 해당 상수들의 주소를 가지고있다가 구조체에다가 넣어주는거여


#if 1
char* colors[] = { "white", "black", "blue", "red", "orange", "pink", "green", "grey" };
typedef struct _profile {
    int age;
    char **color;
    char *name;  // 이름이 나중에(사용중) 변경 가능하다고 가정함
}profile;

typedef struct _student {
    int num;
    double grade;
    profile prof;
}student;

int compareString(char* c){
    for(int i=0;i<SIZE(colors);i++){
        if(strcmp(c,colors[i])==0){
            return i;
        }
    }
    return -1;
}

student* init_student(int n) {
    student* st = (student*)calloc(n,sizeof(student));
    if(st==NULL)
        return NULL;
    for(int i=0;i<n;i++){
        student stu = {0};
        int m = 0;
        scanf("%d %lf %d %d",&stu.num,&stu.grade,&stu.prof.age,&m);
        stu.prof.color = calloc(m,sizeof(char*));
        for(int j=0;j<m;j++){
            char c[100];
            scanf("%s",c);
            int compN = compareString(c);
            if(compN==-1){
                printf("wrong data");
                return NULL;
            }
            stu.prof.color[j] = colors[compN];
        }
        st[i] = stu;
    }
    return st;
}
// typedef struct _student_m{
//     student* stu;
//     int n;
// }student_mng;
void free_student(student** st,int n){
    if(st==NULL || *st==NULL) return;
    for(int i=0;i<n;i++){
        free((*st)[i].prof.color);
    }
    free(*st);
    *st=NULL;
}
int main(void) {
    student *stu = { 0 };
    int n;
    freopen("student3.txt", "r", stdin);
    scanf("%d",&n);
    stu = init_student(n);
    if(stu=NULL) return 12;
    print_student(stu, n);
    free_student(&stu,n); // 어떤것을 사용할지 찾기
    return 0;
}
#endif
#if 0
typedef struct _profile {
    int age;
    char *color[3];
    char name[20]; //이름이 나중에(사용중) 변경 가능하다고 가정함
}profile;

typedef struct _student {
    int num;
    double grade;
    profile prof;
}student;

void init_student(student* p, int n) {
    for (int i = 0; i < n; ++i) {
        scanf("%d %lf %d", &p[i].num, &p[i].grade, &p[i].prof.age);
        char (*arr)[10] = (char(*)[10])calloc(3, sizeof(char[10]));
        p[i].prof.color[0] = arr[0];
        p[i].prof.color[1] = arr[1];
        p[i].prof.color[2] = arr[2];
        scanf("%s %s %s", p[i].prof.color[0], p[i].prof.color[1], p[i].prof.color[2]);
        scanf("%s", p[i].prof.name);
    }
}

void print_student(student* p, int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d %.1f %d ", p[i].num, p[i].grade, p[i].prof.age);
        printf("%s %s %s ", p[i].prof.color[0], p[i].prof.color[1], p[i].prof.color[2]);
        printf("%s\n", p[i].prof.name);
    }
}

void free_mem3(student* p, int n) {
    if (p == NULL) return;
    for (int i = 0; i < n; ++i) {
        free(p[i].prof.color[0]);
        p[i].prof.color[0] = 0;
        p[i].prof.color[1] = 0;
        p[i].prof.color[2] = 0;
    }
}

int main(void) {
    student stu[3] = { 0 };
    freopen("student2.txt", "r", stdin);
    init_student(stu, SIZE(stu));
    print_student(stu, SIZE(stu));
    free_mem3(stu, 3);
    return 0;
}

#endif

#if 0
char** get_data(int n) {
    char str[21] = { 0 };
    int used = n * sizeof(char*);
    int BIG_SIZE = used + n * SIZE(str);

    char* mem = (char*)malloc(BIG_SIZE);
    if (mem == NULL) return NULL;

    char** parr = (char**)mem;
    for (int i = 0; i < n; ++i) {
        scanf("%s", str);
        parr[i] = mem + used;
        strcpy(parr[i], str);
        used += strlen(str) + 1;
    }
    // 불필요한 메모리 반환 (메모리 축소 - 항상 성공 및 주소 유지를 보장하지 않음)
    mem = (char*)realloc(mem, used);  
    if (mem == NULL) {
        free(parr);
        return NULL;
    }
    // 혹시 초기의 mem이 변경된 경우 parr[i]에 있는 주소도 모두 변경
    if ((char**)mem != parr) {
        parr = (char**)mem;        
        char* p = mem + n * sizeof(char*);
        for (int i = 0; i < n; ++i) {
            parr[i] = p;
            p += strlen(p) + 1;
        }
    }

    printf("사용한 메모리: %d / %d바이트\n", used, BIG_SIZE);
    return parr;
}

int main(void) {
    int n;
    char** parr = NULL;
    freopen("data.txt", "r", stdin);
    scanf("%d", &n);
    parr = get_data(n);
    if (parr == NULL) return 12;
    print_strdata(parr, n);
    free_mem((void**)&parr);
    printf("%p\n", parr);
    return 0;
}
#endif



#if 0
typedef struct _profile {
    int age;
    char *color[3];
    char name[20];
}profile;

typedef struct _student {
    int num;
    double grade;
    profile prof;
}student;

void print_student(student*p,int n){
    for(int i=0;i<n;i++){
        printf("%d %.1f %d %s %s %s %s\n",p[i].num,p[i].grade,p[i].prof.age
            ,p[i].prof.color[0],p[i].prof.color[1],p[i].prof.color[2],p[i].prof.name);
    }
}
void init_student(student *p,int n){
    char str[20] = {0}; 
   
    for(int i=0;i<n;i++){
      
        scanf("%d %lf %d",&p[i].num,&p[i].grade,&p[i].prof.age);

        for(int j=0;j<3;j++){
            scanf("%s",str);
            p[i].prof.color[j] = (char*)malloc(strlen(str) + 1);
            strcpy(p[i].prof.color[j], str);
        }
        scanf("%s",p[i].prof.name);

    }
}


int main(void) {
    freopen("student2.txt", "r", stdin);
    student stu[3] = {0};
    init_student(stu,SIZE(stu));
    print_student(stu,SIZE(stu));
    for(int i=0;i<SIZE(stu);i++){
        for(int j=0;j<3;j++){
            free_mem((void**)&stu[i].prof.color[j]);
        }
    }
    return 0;
}
#endif



#if 0

typedef struct student{
    int num;
    double grade;
    char name[20];
}my_student;

void print_student(my_student*p,int n){
    for(int i=0;i<n;i++){
        printf("%d %.1f %s\n",p[i].num,p[i].grade,p[i].name);
    }
}
void init_student(my_student *p,int n){
    
    for(int i=0;i<n;i++){
        scanf("%d %lf %s",&p[i].num,&p[i].grade,p[i].name);
    }
}

int main(void){
    freopen("student.txt", "r", stdin);
    my_student sarry[4] = {0};
    init_student(sarry,SIZE(sarry));
    print_student(sarry,SIZE(sarry));
    return 0;
}

#endif

#if 0
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
