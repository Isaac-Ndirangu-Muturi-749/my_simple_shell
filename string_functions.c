#include "main.h"

// Custom _strcpy function
char *_strcpy(char *dest, const char *src);
// Custom _strcat function
char *_strcat(char *dest, const char *src);
// Custom _strcmp function
int _strcmp(char *s1, char *s2);
// Custom _strtok function
char *_strtok(char *str, const char *delim);
// Custom _strchr function
const char *_strchr(const char *s, char c);
// Custom _strlen function
int _strlen(const char *s);
// Custom _strdup function
char *_strdup(const char *s);
// Custom _atoi function
int _atoi(char *str);


// Custom _strcpy function
char *_strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    while ((*dest++ = *src++) != '\0');
    return original_dest;
}

// Custom _strcat function
char *_strcat(char *dest, const char *src) {
    char *original_dest = dest;
    while (*dest) {
        dest++;
    }
    while ((*dest++ = *src++) != '\0');
    return original_dest;
}

// Custom _strcmp function
int _strcmp(char *s1, char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

// Custom _strtok function
char *_strtok(char *str, const char *delim) {
    static char *last_str = NULL;
    if (str != NULL) {
        last_str = str;
    }
    if (last_str == NULL || *last_str == '\0') {
        return NULL;
    }
    char *start = last_str;
    while (*start != '\0' && _strchr(delim, *start) != NULL) {
        start++;
    }
    if (*start == '\0') {
        last_str = NULL;
        return NULL;
    }
    char *end = start + 1;
    while (*end != '\0' && _strchr(delim, *end) == NULL) {
        end++;
    }
    *end = '\0';
    last_str = end + 1;
    return start;
}

// Custom _strchr function
const char *_strchr(const char *s, char c) {
    while (*s != '\0') {
        if (*s == c)
            return s;
        s++;
    }
    if (*s == c)
        return s;
    return NULL;
}


// Custom _strlen function
int _strlen(const char *s) {
    int length = 0;
    while (*s != '\0') {
        length++;
        s++;
    }
    return (length);
}

// Custom _strdup function
char *_strdup(const char *s) {
    size_t len = _strlen(s) + 1; // +1 for the null terminator
    char *dup = (char *)malloc(len);
    if (dup == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    _strcpy(dup, s);
    return dup;
}

// Custom _atoi function
int _atoi(char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}