#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "security.h"
#include "storage.h"

#include <cstddef>
#include <string>


std::string masking(
    const std::string& text,
    std::size_t visible = 4
);


std::string fuzzing(const std::string& text);

void logging(const std::string& action);

#endif 