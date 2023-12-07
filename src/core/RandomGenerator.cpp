

#include "RandomGenerator.h"

RandomGenerator::RandomGenerator() : RandomGenerator(0) {}
RandomGenerator::RandomGenerator(unsigned int seed) {
    _r = seed;
}

unsigned int RandomGenerator::get() {
    return _r = 22695477*_r+1;
}