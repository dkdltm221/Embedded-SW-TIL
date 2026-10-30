# DAY 08 — 동적 메모리 할당

## 1. 동적 메모리 관리 함수

![동적 메모리 관리 함수](./img/15-0.png)

`<stdlib.h>`에 선언된 함수를 사용한다. 할당에 실패하면 `NULL`을 반환한다.

| 함수 | 역할 |
| --- | --- |
| `malloc(바이트 수)` | 공간만 확보하며, 저장된 값은 초기화하지 않음 |
| `calloc(개수, 원소 크기)` | 공간을 확보하고 모든 바이트를 0으로 초기화 |
| `realloc(기존 주소, 새 바이트 수)` | 기존 할당 공간의 크기를 변경 |
| `free(주소)` | 할당받은 공간 해제. `free(NULL)`은 아무 동작도 하지 않음 |

### 할당과 해제 예제

```c
#include <stdio.h>
#include <stdlib.h>

int *pi;
double *pd;

int main(void) {
    pi = (int *)malloc(10 * sizeof(int));
    if (pi == NULL) {
        printf("메모리 부족\n");
        exit(1);
    }

    pd = (double *)malloc(10 * sizeof(double));
    if (pd == NULL) {
        printf("메모리 부족\n");
        free(pi);
        exit(1);
    }

    printf("%p %p\n", (void *)pi, (void *)pd); // 할당받은 주소
    free(pi);
    free(pd);

    return 0;
}
```

## 2. 주소·값·크기 구분

**`int`가 4바이트라는 것은 저장 공간의 크기이며, 저장되는 값이 4라는 뜻이 아니다.**

| 표현 | 의미 | 현재 실습 환경 |
| --- | --- | --- |
| `pi` | 할당받은 공간의 주소 | `%p`로 출력 |
| `*pi`, `pi[0]` | 첫 번째 공간에 저장된 정숫값 | 사용하기 전에 직접 초기화해야 함 |
| `sizeof(*pi)` | 가리키는 `int` 하나의 크기 | 4바이트 |
| `sizeof(pi)` | 포인터 변수 자체의 크기 | 8바이트 |
| `10 * sizeof(int)` | 요청한 전체 할당 크기 | 40바이트 |
| `pi + 1` | 다음 `int`의 주소 | 4바이트 이동한 주소 |

`malloc`으로 확보한 공간은 초기화되지 않는다. 값을 저장하기 전에 읽으면 결과를 보장할 수 없다.

```c
// malloc 성공 후, free 전에 사용
*pi = 1;
printf("%d %zu\n", *pi, sizeof(*pi)); // 값은 1, 크기는 4
```

## 3. 해제 후 포인터를 `NULL`로 바꾸기

`free`는 메모리를 해제하지만 **포인터 변수에 저장된 주소까지 바꾸지는 않는다.** 해제 후 같은 포인터로 다시 해제하면 정의되지 않은 동작이다.

```c
// 할당에 성공한 arr를 정리하는 부분
free(arr);
arr = NULL;
free(arr); // free(NULL)이므로 안전
```

호출한 쪽의 `int *` 변수까지 `NULL`로 바꾸려면 주소를 받아야 하므로 `int **`를 사용한다.

```c
void free_mem(int **p) {
    if (p == NULL) return; // *p로 접근하기 전에 포인터 변수의 주소 확인
    free(*p);
    *p = NULL;
}
```

- `p == NULL`: 포인터 변수의 주소 자체가 널인지 검사한다.
- `*p = NULL`: 호출한 쪽 포인터를 널 포인터로 바꾼다. `free_mem(&pi)`로 호출한다.

## 4. `realloc`으로 크기 변경

![재할당 동작](./img/15-4.png)

**새 크기가 0보다 큰 경우**를 기준으로 한다.

- 기존 공간에서 크기를 조정하거나, 다른 공간으로 데이터를 옮긴 뒤 새 주소를 반환한다.
- 다른 공간으로 옮겨졌다면 **기존 공간은 `realloc`이 해제**하므로 직접 해제하지 않는다.
- 실패하면 `NULL`을 반환하고 기존 공간은 유지된다. 따라서 **임시 포인터로 받은 뒤 성공한 경우에만 원래 포인터를 갱신**한다.
- `realloc(NULL, 크기)`는 `malloc(크기)`처럼 새 공간을 할당한다. 늘어난 부분은 자동으로 0이 되지 않는다.

## 5. 실습 — 정수를 입력받으며 3칸씩 확장

[실습 코드](./src/8_C_Dynamic_Memory.c) · [해제 함수 구현](./src/lib/day8_lib.c)

처음에는 3칸을 확보하고, 공간이 부족하면 3칸씩 늘린다. 0 이하 또는 입력 실패 시 종료하고 저장한 값만 출력한다.

| 변수 | 의미 | `3 10 20 40 0` 입력 후 |
| --- | --- | --- |
| `N` | 저장 가능한 원소 개수(용량) | 6 |
| `count` | 실제 저장한 원소 개수 | 4 |

```c
#include "day8_lib.h"
#include "day3_lib.h"

int main(void) {
    int N = 3;
    int num = 0, count = 0;
    int *pi = (int *)calloc(N, sizeof(*pi));
    if (pi == NULL) {
        printf("메모리 부족\n");
        return 1;
    }

    printf("숫자를 입력해주세요\n");
    for (; scanf("%d", &num) == 1 && num > 0; count++) {
        if (count == N) {
            N += 3;
            int *temp = (int *)realloc(pi, N * sizeof(*pi));
            if (temp == NULL) {
                printf("메모리 부족\n");
                free_mem(&pi);
                return 1;
            }
            pi = temp;
        }
        pi[count] = num;
    }

    print_data(pi, count);
    free_mem(&pi);
    return 0;
}
```

**동적 할당한 원소 개수는 `SIZE(pi)`로 구할 수 없다.** 이 매크로는 현재 환경에서 `sizeof(포인터) / sizeof(int)`, 즉 `8 / 4 = 2`가 된다. 출력할 개수는 `count`로 관리한다.

## 6. 실습 — 파일에서 문자열 읽기

`freopen`으로 표준 입력 `stdin`을 `data.txt`에 연결한다. 파일의 첫 값은 문자열 개수 `N`, 이후 값은 공백으로 구분된 문자열이다.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int N;
    if (freopen("data.txt", "r", stdin) == NULL) return 1;
    if (scanf("%d", &N) != 1 || N <= 0) return 1;
    printf("%d\n", N);

    char (*arr)[21] = (char (*)[21])calloc(N, sizeof(*arr));
    if (arr == NULL) return 1;

    for (int i = 0; i < N; i++) {
        if (scanf("%20s", arr[i]) != 1) break;
        printf("%s\n", arr[i]);
    }

    free(arr);
    arr = NULL;
    return 0;
}
```

- `char (*arr)[21]`: `char` 21개짜리 행을 가리키는 포인터이다.
- `sizeof(*arr)`, `sizeof(char[21])`, `21 * sizeof(char)`는 모두 **21바이트**이다. `calloc`으로 그 행을 `N`개 확보한다.
- `arr[i]`는 i번째 행의 시작 주소이다. `%20s`로 최대 20바이트를 읽고 마지막 한 칸은 `\0`에 사용한다.

## 7. 실습 — 이중 포인터로 문자열 저장

문자열의 주소를 저장할 **포인터 배열**과, 실제 문자열을 저장할 **각각의 공간**을 따로 할당한다.

```text
parr → [주소] → "apple"
       [주소] → "banana"
       [주소] → "kiwi"
```

### 1. 할당하고 문자열 복사하기

[실습 코드](./src/8_C_Dynamic_Memory.c)

`data.txt`에서 문자열 개수 `N`을 먼저 읽는다. 아래 예제는 파일에 올바른 개수와 문자열이 들어 있다고 가정한다.

```c
#include "day8_lib.h"
#include "day7_lib.h"

int main(void) {
    int N;
    char str[21] = {0};
    char **parr = NULL;

    freopen("data.txt", "r", stdin);
    scanf("%d", &N);
    printf("%d\n", N);

    parr = (char **)calloc(N, sizeof(char *)); // 주소를 저장할 N칸
    if (parr == NULL) return 12;

    for (int i = 0; i < N; i++) {
        scanf("%20s", str);
        parr[i] = (char *)malloc(strlen(str) + 1); // 문자열과 '\0'의 공간
        if (parr[i] == NULL) {
            free_mem2((void ***)&parr, i); // 지금까지 할당한 i개 정리
            return 12;
        }
        strcpy(parr[i], str); // 주소가 아니라 내용을 복사
    }

    print_strdata(parr, N);
    free_mem2((void ***)&parr, N);
    printf("parr == NULL: %d\n", parr == NULL);
    return 0;
}
```

| 코드 | 역할 |
| --- | --- |
| `calloc(N, sizeof(char *))` | 문자열 주소를 저장할 포인터 N개 확보 |
| `malloc(strlen(str) + 1)` | 문자열 길이와 끝의 `\0`만큼 별도 공간 확보 |
| `strcpy(parr[i], str)` | 입력한 문자열 내용을 각 공간에 복사 |

**`parr[i] = str`은 주소만 복사**하므로 모든 원소가 같은 `str`을 가리킨다. 입력할 때마다 덮어쓰므로 마지막 문자열만 반복 출력된다.

### 2. 문자열부터 해제하고 포인터 배열 해제하기

[해제 함수 구현](./src/lib/day8_lib.c)

```c
void free_mem(void **p) {
    if (p == NULL) return;
    free(*p);
    *p = NULL;
}

void free_mem2(void ***p, int n) {
    if (p == NULL || *p == NULL) return;

    for (int i = 0; i < n; i++) {
        free_mem(&(*p)[i]); // 각 문자열 공간 해제 후 포인터를 NULL로 변경
    }
    free(*p);  // 포인터 배열 공간 해제
    *p = NULL; // 호출한 쪽의 parr를 NULL로 변경
}
```

- `free_mem`: 할당 공간 하나를 해제하고 해당 포인터를 `NULL`로 변경한다.
- `free_mem2`: 문자열들을 먼저 해제한 뒤 포인터 배열을 해제한다. **`free(parr)`만으로는 문자열 공간이 함께 해제되지 않는다.**
- `p == NULL`은 포인터 변수의 주소를 받았는지, `*p == NULL`은 포인터 배열이 이미 널인지 검사한다.

실습에서 사용한 `void ***` 강제 형 변환 표기는 유지했다. 다만 `char ***`와 `void ***`가 자동 호환되는 것은 아니며, 이 방식의 표준 C 이식성은 보장되지 않는다.

### 실행 결과

```text
3
apple banana kiwi
parr == NULL: 1
```

마지막 `1`은 `parr`가 `NULL`로 바뀌었다는 뜻이다.
