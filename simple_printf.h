#pragma once
#include <stdarg.h>
#include <stdio.h>

#ifdef _WIN32
#include <windows.h> // Windows���е�ͷ�ļ�
#else
#include <unistd.h> // Linux���е�ͷ�ļ�
#endif

// ��ƽ̨д�뺯��
void simple_write(const char* str) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleA(hConsole, str, strlen(str), &written, NULL);
#else
    write(STDOUT_FILENO, str, strlen(str));
#endif
}

// ��ƽ̨�ļ򻯰�printf����
void simple_printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;
            switch (*format) {
            case 'd':
            case 'i': {
                int i = va_arg(args, int);
                char buffer[12];
                sprintf_s(buffer, sizeof(buffer), "%d", i);
                simple_write(buffer);
                break;
            }
            case 's': {
                const char* s = va_arg(args, const char*);
                simple_write(s);
                break;
            }
            case 'f': {
                double f = va_arg(args, double);
                char buffer[32];
                sprintf_s(buffer, sizeof(buffer), "%f", f);
                simple_write(buffer);
                break;
            }
            default:
                simple_write("%");
                simple_write(format);
                break;
            }
            format++;
        }
        else {
            char buffer[2] = { *format, 0 };
            simple_write(buffer);
            format++;
        }
    }

    va_end(args);
}
