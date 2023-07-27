# Rubik's Cube Solving Algorithms

This project aims to analyze and compare various Rubik's Cube solving algorithms to determine their efficiency in terms of time and space complexities. The project will implement and evaluate four well-known algorithms: Kociemba’s Algorithm, Korf’s Algorithm, Tomas Rokicki’s Algorithm, and Thistlethwaite’s Algorithm. Additionally, a Markov-chain Algorithm will be used for scrambling the Rubik's Cube.

## Introduction
The Rubik's Cube, invented by Ernő Rubik in 1974, is a popular 3-dimensional combination puzzle. Its complex nature and vast number of possible combinations make it an intriguing subject for research and development in various fields, including Mathematics and Artificial Intelligence. This project aims to explore and analyze the efficiency of different Rubik's Cube solving algorithms to find optimal solutions.

## Algorithms
The four algorithms under consideration are:

### Kociemba’s Algorithm
Kociemba’s Algorithm is a two-phase approach that employs group theory and iterative search to find an optimal solution. It reduces the number of needed subgroups to two, using advanced implementation of IDA* (Iterative Deepening A*). This algorithm aims to solve the Rubik's Cube close to the shortest number of moves possible.

### Korf’s Algorithm
Korf’s Algorithm utilizes A* search combined with pattern databases to efficiently find solutions. It can solve any scrambled cube in 20 moves or fewer. This algorithm divides the problem into cosets, each containing related configurations, to push the upper bound to 22 moves, ensuring a solution from any initial scrambled configuration.

### Tomas Rokicki’s Algorithm
Tomas Rokicki’s Algorithm exploits the initial pathways computed by Kociemba’s Algorithm, realizing that they are solutions to a large set of related configurations. This algorithm divides the problem into cosets, containing around 20 billion related configurations each. It achieves an upper bound of 22 moves to solve the Rubik's Cube from any scrambled state.

### Thistlethwaite’s Algorithm
Thistlethwaite’s Algorithm divides the solving process into four stages, each with increasing complexity. The four stages involve solving corners, edges with half-turn metric, corners and edges with full-turn metric, and orienting the last layer's edges and corners. This algorithm guarantees an upper bound of 52 moves to solve any scrambled cube.

## Scrambling Algorithm
The Markov-chain Algorithm is used to scramble the Rubik's Cube, creating a random configuration for testing the solving algorithms. This algorithm involves applying random sequences of moves to the solved cube, producing a wide variety of scrambled states.

## Testing Parameters
The algorithms will be evaluated based on the following testing parameters:
1. Number of Moves: The number of moves each algorithm takes to solve the scrambled Rubik's Cube.
2. Time Complexity: The computational time required by each algorithm to solve the Rubik's Cube.
3. Space Complexity: The additional memory or storage space required by each algorithm during the solving process.
4. Line of Code: The length and complexity of the code required to implement each algorithm.

## License
This project is licensed under the [MIT License](LICENSE). Feel free to use and modify the code as per the license terms.
