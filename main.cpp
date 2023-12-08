#include "MainFunctions.h"

#include <iostream>
#include <cstdint>
#include <limits>
using namespace std;

int read_int() {
    int num = INT32_MIN;
    do {
        printf(": ");
        scanf("%d", &num);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (num == INT32_MIN);
    return num;
}

int main(int argc, char*argv[]) {
    enum ProgramType {
        GenerateSubmission,
        Test,
        Run,
        JudgeSubmission
    };

    ProgramType runType = Run;
    int fieldSize = 32;
    int seed = time(0);

    if (argc == 1) {
        // prompt user
        printf("Select an action to perform\n");
        printf("1) Generate Submission\n");
        printf("2) Debug MySnakeBehavior\n");
        printf("3) Run MySnakeBehavior\n");
        printf("4) Judge SnakeSubmission\n");
        int choice(0);
        do {
            choice = read_int();
        } while(choice < 1 || choice > 3);
        printf("\n");
        
        
        switch (choice) {
        case 1:
            runType = GenerateSubmission;
            break;
        case 2:
            runType = Test;
            break;
        case 3:
            runType = Run;
            break;
        case 4:
            runType = JudgeSubmission;
            break;
        }

        if (runType != GenerateSubmission) {
            printf("Enter the field size");
            do {
                fieldSize = read_int();
            } while (fieldSize <= 0);
            printf("Enter the seed");
            do {
                seed = read_int();
            } while (seed < 0);
        }

        printf("\n");

    } else {
        int i = 1;
        while (i < argc) {
            string argument = argv[i++];

            if (argument == "-h" || argument == "-help" || argument == "--help") {
                printf("CMD Options:\n-G generate submission to contest\n-T test SnakeBehavior\n-R run SnakeBehavior\n-J judge MySnakeBehavior\n\n-s <size> set the size of the field\n-r <seed> set the seed of the random number generator\n");
                return 0;
            } else if (argument == "-G") {
                runType = GenerateSubmission;
            } else if (argument == "-T") {
                runType = Test;
            } else if (argument == "-R") {
                runType = Run;
            } else if (argument == "-J"){
                runType = JudgeSubmission;
            } else if (argument == "-s") {
                if (i >= argc) {
                    throw runtime_error("Invalid argument. -s should have parameter [size].");
                }
                fieldSize = stoi(argv[i++]);
                if (fieldSize <= 0) {
                    throw runtime_error("Invalid argument. size should be non-negative.");
                }
            } else if (argument == "-r") {
                if (i >= argc) {
                    throw runtime_error("Invalid argument. -r should have parameter [seed].");
                }
                seed = stoi(argv[i++]);
                if (seed < 0) {
                    throw runtime_error("Invalid argument. seed should be non-negative");
                }
            }
        }
    }

    switch (runType)
    {
    case Run:
        run_snake_game(fieldSize, seed);
        break;
    case Test:
        test_snake(fieldSize, seed);
        break;
    case GenerateSubmission:
        generate_submission();
        break;
    case JudgeSubmission:
        judge_submission();
    default:
        break;
    }

    return 0;
}