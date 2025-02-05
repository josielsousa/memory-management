#include <stdio.h>

int max_sneklang_memory(int max_threads, int memory_per_thread) {
    return max_threads * memory_per_thread;
}

void init_sneklang(int max_threads, int memory_per_thread) {
    printf("Initializing sneklang\n");
    printf("Max threads: %d\n", max_threads);
    printf("Memory per thread: %d\n", memory_per_thread);

    int max_memory = max_sneklang_memory(max_threads, memory_per_thread);
    printf("Max memory: %d\n", max_memory);
    printf("====================================\n");
}

// cc boot-dev/c/lesson_12.c -o out/lesson_12.o && ./out/lesson_12.o
int main() {
    init_sneklang(4, 512);
    init_sneklang(8, 1024);
    init_sneklang(16, 2048);
}
