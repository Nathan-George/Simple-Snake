#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

class RandomGenerator {
public:
    RandomGenerator();
    RandomGenerator(unsigned int seed);

    unsigned int get();
private:
    unsigned int _r;
};

#endif