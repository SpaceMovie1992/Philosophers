# Philosophers

## Overview

The Philosophers project simulates a classic synchronization problem where philosophers sit at a round table with a bowl of spaghetti in the center. The philosophers alternate between eating, thinking, and sleeping. The challenge is to manage resource allocation (forks) such that no philosopher starves.

## Rules

- One or more philosophers sit at a round table.
- There is a large bowl of spaghetti in the middle of the table.
- Philosophers alternate between eating, thinking, and sleeping:
  - While eating, they are not thinking or sleeping.
  - While thinking, they are not eating or sleeping.
  - While sleeping, they are not eating or thinking.
- There are as many forks as philosophers.
  - A philosopher needs two forks to eat, one in each hand.
  - When done eating, they put the forks back and start sleeping.
  - After sleeping, they start thinking.
- The simulation stops when a philosopher dies of starvation.
- Philosophers don’t communicate or know if another is about to die.
- Philosophers should avoid dying from starvation.

## Program Requirements

### Arguments

The program takes the following command-line arguments:

1. `number_of_philosophers`: The number of philosophers and forks.
2. `time_to_die` (in milliseconds): Time limit for a philosopher to start eating after the last meal. Otherwise, they die.
3. `time_to_eat` (in milliseconds): Duration a philosopher spends eating.
4. `time_to_sleep` (in milliseconds): Duration a philosopher spends sleeping.
5. `[number_of_times_each_philosopher_must_eat]` (optional): If provided, the simulation stops when each philosopher has eaten this many times. If not provided, the simulation stops when a philosopher dies.

### Log Format

State changes of a philosopher are logged in the following format:

- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

Replace `timestamp_in_ms` with the current timestamp in milliseconds and `X` with the philosopher's number.

### Rules for Logs

- State messages should not overlap.
- Death messages should be displayed within 10 ms of the philosopher's death.
- Avoid data races in the program.

## Compilation and Execution

### Compiling

To compile the program, run:

```sh
make

Running the Program
To run the program, use:

./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
Example: ./philosophers 5 800 200 200 7
This command runs the simulation with 5 philosophers, each having 800 ms to live without eating, 200 ms to eat, 200 ms to sleep, and the simulation stops after each philosopher has eaten 7 times.

Error Handling
If an error occurs, the program should handle it gracefully and print an appropriate message.

Author
This project was created by Ana Husic.

