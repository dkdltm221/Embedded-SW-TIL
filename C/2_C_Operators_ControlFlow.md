# DAY 02 — C 연산자와 제어 흐름

## 1. 특정 비트 연산

비트 위치는 **오른쪽 끝을 0번**으로 센다. `1U << bitPosition`으로 해당 위치만 1인 마스크를 만든다.

| 동작 | 연산자 | 의미 |
| --- | --- | --- |
| 설정 | `\|` (OR) | 해당 비트를 1로 설정 |
| 해제 | `& ~` (AND와 NOT) | 해당 비트를 0으로 설정 |
| 반전 | `^` (XOR) | 해당 비트를 0 ↔ 1로 변경 |

`~`는 모든 비트를 뒤집고, `1U`는 부호 없는 정수 상수이다.

```c
#include <stdio.h>

// 특정 비트를 해제
unsigned int clearBit(unsigned int num, int bitPosition) {
    return num & ~(1U << bitPosition);
}

// 특정 비트를 설정
unsigned int setBit(unsigned int num, int bitPosition) {
    return num | (1U << bitPosition);
}

// 특정 비트를 반전
unsigned int toggleBit(unsigned int num, int bitPosition) {
    return num ^ (1U << bitPosition);
}

int main(void) {
    unsigned int num = 0xAU; // 2진수 1010
    num = setBit(num, 2); 
    printf("num=%X\n", num);
    num = clearBit(num, 1);
    printf("num=%X\n", num);
    num = toggleBit(num, 3);
    printf("num=%X\n", num);

    return 0;
}
```

## 2. 특정 위치부터 여러 비트 연산

시작 위치 `s`부터 연속된 `n`개의 비트를 조작한다.

1. `(1U << n) - 1U`로 하위 `n`개 비트가 1인 값을 만든다.
2. 이를 `s`만큼 왼쪽으로 이동해 마스크를 만든다.
3. 설정은 OR, 해제는 AND와 NOT, 반전은 XOR을 사용한다.

예를 들어 `s = 2`, `n = 3`이면 마스크는 `0001 1100`이다. **C에서 `^`는 거듭제곱이 아니라 XOR이다.**

```c
#include <stdio.h>

 
//특정 위치부터 특정 개수의 비트를 설정
unsigned int setBits(unsigned int num, int s, int n) {
    return num | (((1U << n) - 1U) << s);
}

//특정 위치부터 특정 개수의 비트를 해제
unsigned int clearBits(unsigned int num, int s, int n) {
    return num & ~(((1U << n) - 1U) << s);
}

//특정 위치부터 특정 개수의 비트를 반전
unsigned int toggleBits(unsigned int num, int s, int n) {
    return num ^ (((1U << n) - 1U) << s);
}

int main(void) {
    unsigned int num = 0xAAU; // 2진수 1010 1010
    num = setBits(num, 2, 3);
    printf("num=%X\n",num);
    num = clearBits(num, 4, 2);
    printf("num=%X\n",num);
    num = toggleBits(num, 1, 5);
    printf("num=%X\n",num);

    return 0;
}
```

`%X`는 대문자 16진수 출력이다. 첫 예제는 E → C → 4, 두 번째 예제는 BE → 8E → B0 순서로 출력된다.

### 사용 조건

- 단일 비트 위치는 0 이상이고 `unsigned int`의 비트 폭보다 작아야 한다.
- 위 여러 비트 연산식은 `s >= 0`, `1 <= n < 비트 폭`, `s < 비트 폭`, `s + n <= 비트 폭`인 범위에서 사용한다.
- 두 코드 블록은 각각 독립적으로 실행한다.

## 3. 비트를 2진수로 출력하기

값을 오른쪽으로 이동한 뒤 `& 1U`로 마지막 비트만 추출하면, 각 비트를 0 또는 1로 출력할 수 있다.
### 3.1 BitCheck 함수
```c
static unsigned int isBitSet(unsigned int num,int bitPosition){
    return (num>>bitPosition) & 1U;
}
```

```c
#include <stdio.h>
#include <limits.h>

void printBits(unsigned int num) {
    for (int i = sizeof(num) * CHAR_BIT - 1; i >= 0; --i) {
        printf("%u", (num >> i) & 1U);
    }
    putchar('\n');
}

int main(void) {
    unsigned int num = 10U;
    printBits(num);
    return 0;
}
```

`unsigned int`가 32비트인 환경의 출력:

```text
00000000000000000000000000001010
```

### 반복문 해석

| 코드 | 의미 |
| --- | --- |
| `sizeof(num)` | `num`의 크기를 바이트 단위로 구함. 보통 4바이트 |
| `CHAR_BIT` | 한 바이트의 비트 수. `<limits.h>`에 정의되며 보통 8 |
| `sizeof(num) * CHAR_BIT` | 저장 공간의 전체 비트 수. 4 × 8이면 32 |
| `- 1` | 비트 위치는 0부터 세므로 가장 높은 위치는 31 |
| `i >= 0` | 0번 비트까지 출력하고 종료 |
| `--i` | 다음에는 한 칸 낮은 위치의 비트를 확인 |

따라서 32비트 환경에서는 `i`가 **31 → 30 → … → 1 → 0** 순서로 바뀌며, 왼쪽의 높은 비트부터 출력한다. 마지막에는 `i`가 -1이 되어 반복이 끝나므로 여기서는 부호 있는 `int`를 사용한다.

### `(num >> i) & 1U` 해석

1. `num >> i`: 확인할 i번 비트를 맨 오른쪽인 0번 위치로 옮긴다.
2. `& 1U`: 맨 오른쪽 비트만 남기고 나머지는 모두 0으로 만든다.
3. `printf("%u", ...)`: 추출한 0 또는 1을 줄바꿈 없이 이어서 출력한다.

`num = 10`일 때 하위 4비트만 따라가면 다음과 같다.

| `i` | `num >> i`의 하위 4비트 | `& 0001` 결과 | 출력 |
| --- | --- | --- | --- |
| 3 | `0001` | `0001` | 1 |
| 2 | `0010` | `0000` | 0 |
| 1 | `0101` | `0001` | 1 |
| 0 | `1010` | `0000` | 0 |

따라서 `1010`이 출력된다. `num >> i`는 계산한 값을 사용할 뿐, 원래 `num`을 바꾸지는 않는다. 반복문 뒤의 `putchar('\n')`은 모든 비트를 출력한 뒤 한 번 줄바꿈한다.

하위 8비트만 확인하려면 반복문의 시작을 `int i = 7`로 바꾼다. 이 예제도 앞의 코드 블록들과 독립적으로 실행한다.


### 