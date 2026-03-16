_This project has been created as part of the 42 curriculum by nhoussie._

---

### Table of Contents

- [Description](#description)
- [Instructions](#instructions)
  - [Usage](#usage)
- [Resources](#resources)

---

## Description

This project's goal is to learn to create threads and to use mutexes while tackling the Dining Philosophers problem.

The key things to know about the problem are:

- One or more philosophers sit at a round table. There is a bowl of spaghetti in the middle of the table.
- The philosophers take turns eating, thinking, and sleeping. While they are eating, they are not thinking nor sleeping. While thinking, they are not eating nor sleeping. While sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- A philosopher must pick up two forks before eating.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again.
- The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers do not communicate with each other.
- Philosophers do not know if another philosopher is about to die.
- Philosophers should avoid dying.

For the mandatory part, there is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, they will have access to just one fork.

A philosopher must pick up both the fork to their right and the fork to their left before eating.

## Instructions

1. Go to the `philo` directory

```
cd philo
```

2. Build the program:

```
make
```

3. Execute the program:

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

For informations about the program's arguments, you can read the [usage section](#usage).

### Usage

The program must be called in the following format:

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

The arguments are:

- `number_of_philosophers`: The number of philosophers and also the number of forks.
- `time_to_die` (in milliseconds): If a philosopher has not started eating within `time_to_die` milliseconds since the start of their last meal or the start of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional argument): If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

## Resources

This [Wikipedia article](https://en.wikipedia.org/wiki/Dining_philosophers_problem) describes the Dining philosophers problem in more depth.

For learning about threads and mutexes, the [Advanced Programming in the UNIX® Environment book](http://www.apuebook.com/) and this [article](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/) from a former 42 student were very useful resources.

AI was used for testing and for debugging tricky issues.
