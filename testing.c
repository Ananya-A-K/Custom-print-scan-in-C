#include <unistd.h>
#include <stdlib.h>
#include "custom_printf.h"
#include "custom_scanf.h"

// Custom putchar
void custom_putchar(char c) {
    write(1, &c, 1); //write() system call
}

// Custom puts
void custom_puts(const char *str) {
    while (*str) {
        custom_putchar(*str++);
    }
}

// Custom putint
void custom_putint(int num) {
    if (num < 0) {
        custom_putchar('-');
        num = -num;
    }
    if (num / 10) {
        custom_putint(num / 10);
    }
    custom_putchar(num % 10 + '0');
}

// Custom printf
void custom_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'd') {
                int num = va_arg(args, int);
                custom_putint(num);
            } else if (*format == 's') {
                const char *str = va_arg(args, const char *);
                custom_puts(str);
            }
        } else {
            custom_putchar(*format);
        }
        format++;
    }
    
    va_end(args);
}

// Custom getchar
int custom_getchar() {
    char c;
    if (read(0, &c, 1) <= 0) { // read() system call
        return -1; // Error or EOF
    }
    return c;
}

// Custom scanf
void custom_scanf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'd') {
                int *num = va_arg(args, int *);
                char buffer[1024];
                int i = 0;
                char c;
                
                // Read until whitespace
                while ((c = custom_getchar()) != -1 && c != ' ' && c != '\n') {
                    buffer[i++] = c;
                }
                buffer[i] = '\0';
                *num = atoi(buffer); // Convert string to integer
            } 
            else if (*format == 's') {
                char *str = va_arg(args, char *);
                char c;
                int i = 0;
                
                // Read until whitespace
                while ((c = custom_getchar()) != -1 && c != ' ' && c != '\n') {
                    str[i++] = c;
                }
                str[i] = '\0';
            }
        }
        format++;
    }
    
    va_end(args);
}

int main() {
    int number;
    char name[100];

    custom_printf("Enter your name: ");
    custom_scanf("%s", name);
    custom_printf("Enter your age: ");
    custom_scanf("%d", &number);
    
    custom_printf("Hello, %s! You are %d years old.\n", name, number);
    
    return 0;
}
