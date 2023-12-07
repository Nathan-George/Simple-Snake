
#include "SnakeBehaviorFactory.h"

#include "SimpleSnakeBehavior.h"
#include "ExampleSnakeBehavior.h"
#include "../MySnakeBehavior.h"

#include <iostream>

ISnakeBehavior* SnakeBehaviorFactory::constructSnakeBehavior() const {
    std::cout << "Select Behavior\n";
    std::cout << "default) MySnakeBehavior\n";
    std::cout << "1) SimpleSnakeBehavior\n";
    std::cout << "2) ExampleSnakeBehavior\n";
    std::cout << ": ";
    switch (std::cin.get())
    {
    case '1':
        return new SimpleSnakeBehavior();
    case '2':
        return new ExampleSnakeBehavior();
    default:
        return new MySnakeBehavior();
    }

}