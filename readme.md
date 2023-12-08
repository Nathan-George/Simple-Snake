## Overview

This is a development pack for making an algorithm for playing the classic game of Snake. The intention of this project is to release it as a competition for individuals to create different Snake Algorithms and submit their generated submissions for ranking amongst the other contestants. For now, this is the first iteration.

Contestants will implement the ISnakeBehavior::getMove function in the MySnakeBehavior class with their own implementations for generating snake moves. They are given access to a Snake API which gives access to an ordered arrangement of the locations in the snake and a Field API which gives access to a 2d representation of the field.

## How to use

There are four modes this project can be run in

- Run mode
- Test mode
- Generate submission
- Judge submission

To test each of them out make
the project and run the FinalProject executable. 

```
./FinalProject.exe
```

I recommend stating off with with just the Run mode. Enter a size and a seed and select one of the algorithms. The simple snake will always win my just following a cycle. The example snake will use a breadth first search to find the apple, but this often gets it in trouble so you can see what happens when the program errors out. The Test mode is the exact same but with UTF-8 in the terminal. To convert powershell to UTF-8 you can run the following command in the powershell terminal.
```
> chcp 65001
``` 


Generating and judging submissions works with the submission.txt file. It will use MySnakeBehavior to run 20 games on 32 by 32 grids with the seeds in the range [0, 19]. Running in judge submission mode will read the submission file and output the average moves per apple over all games.

Each mode has command line arguments which can enable users to rapidly test their code without entering specifics. You can view the list of all options by running

```
> ./FinalProject.exe --help
```

### Run mode

```
> ./FinalProject.exe -R [-s <size=32>] [-r <seed=time(0)>]
```

This command executes the project in Run mode with an optional argument of the size of the game and the seed.

### Test mode

```
> ./FinalProject.exe -T [-s <size=32>] [-r <seed=time(0)>]
```

This command executes the project in Test mode with an optional argument of the size of the game and the seed.

### Generate Submission

```
> ./FinalProject.exe -G
```

This command generates a submission to the contest

### Judge Submission

```
> ./FinalProject.exe -J
```

This command judges a submission to the contest