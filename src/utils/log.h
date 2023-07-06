#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define _LOG_PIPE(stream, message, ...) do {   \
        fprintf(stream, message, ##__VA_ARGS__); \
    } while(0)

#define LOG(message, ...) do {                   \
        fprintf(stdout, "[INFO]: ");             \
        _LOG_PIPE(stdout, message, ##__VA_ARGS__); \
    } while(0)

#define LOG_FATAL(message, ...) do {             \
        fprintf(stderr, "[FATAL]: ");            \
        _LOG_PIPE(stderr, message, ##__VA_ARGS__); \
    } while(0)

#define LOG_ERROR(message, ...) do {             \
        fprintf(stderr, "[ERROR]: ");            \
        _LOG_PIPE(stderr, message, ##__VA_ARGS__); \
    } while(0)

#endif // LOG_H