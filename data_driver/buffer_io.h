#pragma once

#include <stdio.h>

namespace bufferio {

    const int IOBufferLength = 10000;
    char* io_buffer, * io_buffer_start = io_buffer, * io_buffer_end = io_buffer;

    void clear_buffer() {
        delete[] io_buffer;
        io_buffer = NULL;
        io_buffer_start = io_buffer;
        io_buffer_end = io_buffer;
    }

    // Return a single character, and load fp on io_buffer when it runs out.
    // Example:
    //     ch = _buffer_get(fp);
    char _buffer_get(FILE* fp = stdin) {
        if (io_buffer_start == io_buffer_end) {
            delete[] io_buffer;
            io_buffer = new char[IOBufferLength + 1];
            io_buffer_end = (io_buffer_start = io_buffer) + fread(io_buffer, 1, IOBufferLength, fp);
            if (io_buffer_start == io_buffer_end)
                return EOF;
        }
        return *io_buffer_start++;
    }

    // Read a number from fp, save to target_num.
    // Return 0 when reaching EOF.
    // This function just simply ignore any non-digit except for '-' between numbers, 
    // its ability to check input format is weak. Do make sure your Input is right.
    // Example:
    //     int number_to_input, info;
    //     FILE *fp = fopen("data.txt", "r");
    //     info = bufferio::read(number_to_input, fp);
    template <typename T> short read(T& target_num, FILE* fp = stdin) {
        char ch, sign = 1;
        for (ch = _buffer_get(fp); ch > '9' || ch < '0'; ch = _buffer_get(fp)) {
            if (ch == EOF)
                return 0;
            else if (ch == '-')
                sign = -1;
        }
        for (target_num = 0; ch >= '0' && ch <= '9'; ch = _buffer_get(fp))
            target_num = target_num * 10 + ch - '0';
        target_num *= sign;
        return 1;
    }

    // Read two numbers in a line from fp, save to num1 and num2.
    // Return 0 when reaching EOF, 2 when input format goes wrong, and 1 when everything goes well.
    // Character to split number can only be space or tab. 
    // If you have something input like this:
    //     1 
    //     2 
    //     3 4
    //     5 6
    //     ... (x y)
    // You can use this function like:
    //     int u, v, info;
    //     FILE *fp = fopen("data.txt", "r");
    //     info = bufferio::read(u, fp);
    //     info = bufferio::read(v, fp);
    //     while (info == 1)
    //         info = bufferio::read2(u, v, fp);
    template <typename T> short read2(T& num1, T& num2, FILE* fp = stdin) {
        char ch, sign = 1;
        for (ch = _buffer_get(fp); ch > '9' || ch < '0'; ch = _buffer_get(fp)) {
            if (ch == EOF)
                return 0; // good EOF
            else if (ch == '-')
                sign = -1;
            /*
            else if (ch == '\n')
                return 2;
            */
        }
        for (num1 = 0; ch >= '0' && ch <= '9'; ch = _buffer_get(fp))
            num1 = num1 * 10 + ch - '0';
        num1 *= sign;
        sign = 1;
        for (; ch > '9' || ch < '0'; ch = _buffer_get(fp)) {
            if (ch == EOF)
                return 2; // bad EOF -> bad input format
            else if (ch == '-')
                sign = -1;
            else if (ch == '\n')
                return 2; // wrong newline -> bad input format
        }
        for (num2 = 0; ch >= '0' && ch <= '9'; ch = _buffer_get(fp))
            num2 = num2 * 10 + ch - '0';
        num2 *= sign;
        do {
            if (ch == '\n')
                return 1; // right newline -> good input format
            else if (ch == EOF)
                return 1; // good EOF -> retain to next read
            else if (ch != ' ' && ch != '\t')
                return 2; // bad character -> bad input format
        } while (ch = _buffer_get(fp));
        return 2; // whatever else
    }

    // Read three numbers in a line from fp, save to num1, num2, and num3.
    // Return 0 when reaching EOF, 2 when input format goes wrong, and 1 when everything goes well.
    // Character to split number can only be space or tab. 
    // If you have something input like this:
    //     1000 100
    //     2 3 4
    //     3 4 5
    //     5 6 6
    //     ... (x y z)
    // You can use this function like:
    //     int u, v, w, info;
    //     FILE *fp = fopen("data.txt", "r");
    //     info = bufferio::read2(u, v, fp);
    //     while (info == 1)
    //         info = bufferio::read3(u, v, w, fp);
    template <typename T> short read3(T& num1, T& num2, T& num3, FILE* fp = stdin) {
        char ch, sign = 1;
        for (ch = _buffer_get(fp); ch > '9' || ch < '0'; ch = _buffer_get(fp)) {
            if (ch == EOF)
                return 0; // good EOF
            else if (ch == '-')
                sign = -1;
            /*
            else if (ch == '\n')
                return 2;
            */
        }
        for (num1 = 0; ch >= '0' && ch <= '9'; ch = _buffer_get(fp))
            num1 = num1 * 10 + ch - '0';
        num1 *= sign;
        sign = 1;
        for (; ch > '9' || ch < '0'; ch = _buffer_get(fp)) {
            if (ch == EOF)
                return 2; // bad EOF -> bad input format
            else if (ch == '-')
                sign = -1;
            else if (ch == '\n')
                return 2; // wrong newline -> bad input format
        }
        for (num2 = 0; ch >= '0' && ch <= '9'; ch = _buffer_get(fp))
            num2 = num2 * 10 + ch - '0';
        num2 *= sign;
        sign = 1;
        for (; ch > '9' || ch < '0'; ch = _buffer_get(fp)) {
            if (ch == EOF)
                return 2; // bad EOF -> bad input format
            else if (ch == '-')
                sign = -1;
            else if (ch == '\n')
                return 2; // wrong newline -> bad input format
        }
        for (num3 = 0; ch >= '0' && ch <= '9'; ch = _buffer_get(fp))
            num3 = num3 * 10 + ch - '0';
        num3 *= sign;
        do {
            if (ch == '\n')
                return 1; // right newline -> good input format
            else if (ch == EOF)
                return 1; // good EOF
            else if (ch != ' ' && ch != '\t')
                return 2; // bad character -> bad input format
        } while (ch = _buffer_get(fp));
        return 2; // whatever else
    }

}  // namespace bufferio
