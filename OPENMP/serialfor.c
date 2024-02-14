#include <stdio.h>

#define N 100000000LL

long long int serialLoop() {
    long long int result = 0;

    for (long long int i = 0; i < N; ++i) {
        result += i;
    }

    printf("Serial Result: %lld\n", result);

    return result;
}

int main() {
    printf("Serial Loop:\n");
    long long int serial_result = serialLoop();

    return 0;
}
