#include "MainFunctions.h"

#include <SFML/Graphics.hpp>
#include "src/sfml_graphics/SnakeShape.h"
#include "src/sfml_graphics/AppleShape.h"
#include "src/sfml_graphics/FieldShape.h"

#include "src/core/SnakeGame.h"
#include "src/graphics/AsciiFunctions.h"

#include "src/SnakeBehaviorFactory.h"
#include "src/ReplaySnakeBehavior.h"
#include "MySnakeBehavior.h"

#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>


void run_snake_game(int fieldSize, int seed) {
    ISnakeBehavior* behavior;

    behavior = SnakeBehaviorFactory().constructSnakeBehavior();
    SnakeGame game(behavior, fieldSize, seed);

    float cellSize = 1280.0 / game.getField().getSize();

    FieldShape fieldShape(game.getField().getSize(), cellSize);
    SnakeShape snakeShape(game.getSnake(), game.getField().getSize(), cellSize);
    AppleShape appleShape(game.getField().getSize(), cellSize);
    AsciiCanvas canvas(game.getField().getSize(), game.getField().getSize());

    sf::RenderWindow window( sf::VideoMode(1280, 1280), "Snake" );

    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    // perform any file processing once before draw loop begins

    //  END  ANY FILE LOADING
    /////////////////////////////////////

    // create an event object once to store future events
    sf::Event event;

    sf::Clock timer;
    float nextUpdate = timer.getElapsedTime().asMilliseconds() + 1000.0 / 50;

    bool hasException = false;

    // while the window is open
    while( window.isOpen() ) {
        // clear any existing contents
        window.clear();

        /////////////////////////////////////
        // BEGIN DRAWING HERE

        window.draw(fieldShape);
        window.draw(snakeShape);
        if (!game.isFinished()) {
            appleShape.setLocation(game.getApple().getLocation());
            window.draw(appleShape);
        }

        //  END  DRAWING HERE
        /////////////////////////////////////

        if (!hasException && !game.isFinished() && timer.getElapsedTime().asMilliseconds() > nextUpdate) {
            nextUpdate += 1000.0 / 50;

            try {
                game.step();
            } catch(std::exception& e) {
                std::cerr << e.what() << std::endl;
                hasException = true;
            }
            
        }


        // display the current contents of the window
        window.display();

        /////////////////////////////////////
        // BEGIN EVENT HANDLING HERE
        // check if any events happened since the last time checked
        while( window.pollEvent(event) ) {
            // if event type corresponds to pressing window X
            if(event.type == sf::Event::Closed) {
                // tell the window to close
                window.close();
            }
            // check addition event types to handle additional events
        }
        //  END  EVENT HANDLING HERE
        /////////////////////////////////////
    }

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
    std::ofstream submissionFile("submission.txt");
    if (!submissionFile.is_open()) {
        throw std::runtime_error("Could not create submission.txt");
    }

    // run 20 games
    submissionFile << 20 << '\n';
    std::vector<Move> moves;
    for (int i = 0; i < 20; i++) {
        ISnakeBehavior* behavior = new MySnakeBehavior();
        SnakeGame game(behavior, 32, i);
        try {
            while(!game.isFinished()) {
                game.step();
                moves.push_back(game.getLastMove());
            }
        } catch (std::exception& e) {
            printf("Error: size 32, seed %d", i);
            submissionFile << "0\n";
            continue;
        }

        printf("Game %d: %d moves\n", i+1, (int) moves.size());
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

    std::ifstream submissionFile("submission.txt");
    if (!submissionFile.is_open()) {
        throw std::runtime_error("Could not create submission.txt");
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