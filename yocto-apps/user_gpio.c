#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

#define GPIO_SIZE 0xB4
#define GPSET0    7
#define GPCLR0    10


int main()
{
    int fd = open("/dev/gpio_led", O_RDWR);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    volatile uint32_t *gpio =
        mmap(NULL, GPIO_SIZE, PROT_READ | PROT_WRITE,
             MAP_SHARED, fd, 0);

    if (gpio == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("Turning LED ON\n");
    gpio[GPSET0] = (1 << 21);
    sleep(1);

    printf("Turning LED OFF\n");
    gpio[GPCLR0] = (1 << 21);
    sleep(1);

    munmap((void *)gpio, GPIO_SIZE);
    close(fd);

    return 0;
}
