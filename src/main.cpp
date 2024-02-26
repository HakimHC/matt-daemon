#include <iostream>

#include <unistd.h>

#include "TintinReporter.hpp"

int main() {
    if (geteuid() != 0)
        return 1;
    TintinReporter tr;
    tr.log("Started.", "INFO");
}