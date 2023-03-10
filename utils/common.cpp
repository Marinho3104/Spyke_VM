#include "common.h"

#include <iostream>
#include <string.h>
#include <fstream>

char* utils::get_string_copy(char* __to_copy) {

    if (!__to_copy) return 0;

    char* __new = (char*) malloc(strlen(__to_copy) + 1);

    strcpy(
        __new,
        __to_copy
    );

    return __new;

}

char* utils::get_string_copy_n(char* __to_copy, size_t __size) {

    if (!__to_copy) return 0;

    char* __new = (char*) malloc(__size + 1);

    __new[__size] = '\0';

    if (__size)
    
        strncpy(
            __new,
            __to_copy,
            __size
        );

    return __new;

}

bool utils::file_exists(char* __path) {

    FILE *_file = fopen(__path, "r");

    bool _exists = _file;

    if (_exists) fclose(_file);

    return _exists;

}

char* utils::get_file_content(char* __path) {

    if (!file_exists(__path)) return 0;

    std::ifstream ifs(__path);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
        (std::istreambuf_iterator<char>()    ) );

    char* _file_content = (char*) malloc(strlen(content.c_str()) + 1);

    strcpy(_file_content, (char*) content.c_str());

    return _file_content;

} 
