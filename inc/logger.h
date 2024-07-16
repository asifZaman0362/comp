#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __FILE_NAME__
#define __FILENAME__ __FILE_NAME__
#else
#define __FILENAME__ "__FILE_NAME__not_defined"
#endif

typedef enum { INFO = 0, DEBUG, WARN, ERROR } log_level_t;

#ifdef __cplusplus
extern "C" {
#endif

extern void init_logger(FILE *target, log_level_t level);
static void log(log_level_t level, const char *fmt, ...);

#define _QUOTES(a) #a
#define STR(a) _QUOTES(a)
#define LINE STR(__LINE__)

#define LOCATION __FILE_NAME__ ":" LINE

#define LOG(level, fmt, ...) log(level, LOCATION " " fmt, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...) LOG(log_level_t::INFO, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) LOG(log_level_t::DEBUG, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) LOG(log_level_t::WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG(log_level_t::ERROR, fmt, ##__VA_ARGS__)


#ifdef __cplusplus
}
#endif

#ifdef LOGGER_IMPLEMENTATION

FILE *OUTFILE;
log_level_t LEVEL = log_level_t::ERROR;

void init_logger(FILE *target, log_level_t level) {
    if (target == NULL || target == stdout)
        OUTFILE = NULL;
    else
        OUTFILE = target;
    LEVEL = level;
}

static void log(log_level_t level, const char *fmt, ...) {
    va_list list;
    va_start(list, fmt);
    const char *level_str[] = {"INFO", "DEBUG", "WARN", "ERROR"};
    time_t t = time(NULL);
    struct tm *local = localtime(&t);
    assert(local && "Failed to get local time!");
    char timestr[32] = {0};
    assert(strftime(timestr, sizeof(timestr), "%F %H:%M:%S", local) &&
           "Failed to format time string!");
    char *new_fmt = (char *)malloc(strlen(fmt) + strlen("1970-01-01 00:00:00 ") + 10);
    sprintf(new_fmt, "%s %s %s\n", level_str[level], timestr, fmt);
    if (OUTFILE != NULL) vfprintf(OUTFILE, new_fmt, list);
    if (level >= LEVEL) vfprintf(stdout, new_fmt, list);
    va_end(list);
}

#endif // LOGGER_IMPLEMENTATION
#endif // LOGGER_HPP
