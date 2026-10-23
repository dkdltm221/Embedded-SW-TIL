#if 1
#include "day3_lib.h"


// int arr[1100 이숫자는 의미없음]이라해도된다. 그러나 권장하진않음
void input_data(int* arr, int n){
    for(int i=0;i<n;i++){
        //scanf("%d",arr[i])  &*(arr+i) 이거와 같다 그러나
        // &*를 같이쓰면 컴파일러가 알아서 처리해주기에
        // 아래 내용과 똑같은 것이다.
        scanf("%d",arr + i);
    }
}

void print_data(int* arr, int n){
    for(int i=0;i<n;i++){
        printf("%d ",*(arr+i));
    }
    printf("\n");
}

int sum_data(int* arr,int n){
    int s=0;
    for(int i=0;i<n;i++){
        s+=*(arr+i);
    }
    return s;
}
double avg_data(int* arr,int n){
    return (double)sum_data(arr,n)/n;
}

void swap(int *pa,int *pb){
    int temp = *pa; 
    *pa = *pb;
    *pb = temp;
    
}
//큰값찾기
int findmax_ary(int* arr,int n){
    int max =0;
    for(int i=0;i<n;i++){
        if(*(arr+i)>max)
            max=*(arr+i);
    }
    return max;
}
//작은값 찾기
int findmin_ary(int* arr,int n){
    int min = *arr;
    for(int i=0;i<n;i++){
        if(*(arr+i)<min)
            min = *(arr+i);
    }
    return min;

}
//작은순 정렬
void sort_data(int*arr , int n){
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            if(*(arr+i)>*(arr+j)){
                swap(arr+i,arr+j);
            }
        }
    }
}



#endif
