#include "src/core/SnakeGame.h"
#include "src/graphics/AsciiFunctions.h"

#include "src/SnakeBehaviorFactory.h"
#include "src/ReplaySnakeBehavior.h"
#include "MySnakeBehavior.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>

#include <stdlib.h>

using namespace std;

void run_snake_game(int fieldSize, int seed) {
    ISnakeBehavior* behavior;

    behavior = SnakeBehaviorFactory().constructSnakeBehavior();

    SnakeGame game(behavior, fieldSize, seed);
    AsciiCanvas canvas(game.getField().getSize(), game.getField().getSize());
    
    int i = 0;
    while(!game.isFinished()) {

        if (++i == 1) {
            canvas.clear();
            draw_snake(canvas, game.getSnake());
            draw_apple(canvas, game.getApple());
            canvas.draw();
            i=0;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        game.step();
    }

    canvas.clear();
    draw_snake(canvas, game.getSnake());
    canvas.draw();

    delete behavior;
}

void test_snake(int fieldSize, int seed) {
    ISnakeBehavior* behavior;

    behavior = SnakeBehaviorFactory().constructSnakeBehavior();

    SnakeGame game(behavior, fieldSize, seed);
    AsciiCanvas canvas(game.getField().getSize(), game.getField().getSize());
    
    int i = 0;
    while(!game.isFinished()) {

        if (++i == 1) {
            canvas.clear();
            draw_snake(canvas, game.getSnake());
            draw_apple(canvas, game.getApple());
            canvas.draw();
            i=0;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        game.step();
    }

    canvas.clear();
    draw_snake(canvas, game.getSnake());
    canvas.draw();

    delete behavior;
}

void generate_submission() {
    ofstream submissionFile("submission.txt");
    if (!submissionFile.is_open()) {
        throw runtime_error("Could not create submission.txt");
    }

    // run 20 games
    submissionFile << 20 << '\n';
    vector<Move> moves;
    for (int i = 0; i < 20; i++) {
        ISnakeBehavior* behavior = new MySnakeBehavior();
        SnakeGame game(behavior, 32, i);
        try {
            while(!game.isFinished()) {
                game.step();
                moves.push_back(game.getLastMove());
            }
        } catch (exception& e) {
            printf("Error: size 32, seed %d", i);
            submissionFile << "0\n";
            continue;
        }

        printf("Game %d: %lu moves\n", i+1, moves.size());
        submissionFile << moves.size() << '\n';
        for (Move move : moves) {
            switch (move)
            {
            case Move::Right:
                submissionFile << 'r';
                break;
            case Move::Up:
                submissionFile << 'u';
                break;
            case Move::Left:
                submissionFile << 'l';
                break;
            case Move::Down:
                submissionFile << 'd';
                break;
            
            default:
                break;
            }
        }
        submissionFile << '\n';

        moves.clear();
    }

    submissionFile.close();
}

void judge_submission() {
    printf("Judging Submission...\n");

    ifstream submissionFile("submission.txt");
    if (!submissionFile.is_open()) {
        throw runtime_error("Could not create submission.txt");
    }

    int total_moves = 0;
    int total_apples = 0;

    // run 20 games
    int num_games;
    submissionFile >> num_games;
    if (num_games != 20) {
        throw std::invalid_argument("Num games should be [20]");
    }

    bool invalid_submission = false;
    for (int i = 0; i < 20; i++) {
        printf("Game %d...\n", i);
        fflush(stdout);
        int num_moves;
        submissionFile >> num_moves;
        if (num_moves == 0) {
            invalid_submission = true;
            printf("Snake failed to complete round with seed %d", i);
            continue;
        }

        std::string moves_string;
        submissionFile >> moves_string;

        if (moves_string.length() != (size_t) num_moves) {
            throw std::invalid_argument("Bad file format: moves_string.length() != num_moves");
        }

        ISnakeBehavior* behavior;
        behavior = new ReplaySnakeBehavior(moves_string);
        SnakeGame game(behavior, 32, i);
        while(!game.isFinished()) {
            game.step();
        }

        delete behavior;

        total_moves += num_moves;
        total_apples += 32*32;
    }

    submissionFile.close();

    if (invalid_submission) {
        if (total_apples == 0) {
            printf("Invalid Score: inf\n");
        } else {
            printf("Invalid Score: %f.3\n", (double)total_moves/total_apples);
        }
    } else  {
        printf("Score: %.3f\n", (double)total_moves/total_apples);
    }
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
            printf(": ");
            scanf("%d", &choice);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                printf(": ");
                scanf("%d", &fieldSize);
            } while (fieldSize <= 0);
            printf("Enter the seed");
            do {
                printf(": ");
                scanf("%d", &seed);
            } while (seed < 0);
        }

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