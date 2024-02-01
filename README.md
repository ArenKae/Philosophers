# Philosophers

<p align="center">
  <img src="https://github.com/ArenKae/42-badges/blob/main/philosopherse.png" alt="Philosophers by acosi">
</p>

Philosophers is a 42 school project designed around Edsger Dijkstra's famous dining philosophers problem. For this project, we must learn about concurrent programming. For the project's mandatory part, we must find a solution to the problem using only threads and mutexes.

---

## Status
Finished 01/02/2024.

Grade: 100/100

## Usage
To compile, use ```make``` or ```make all```.
Launch the program with the command : ```./philo arg1 arg2 arg3 arg4 arg5```
where :
- arg1 = Number of philosophers
- arg2 = The time (in milliseconds) it takes for a philosophers to die
- arg3 = The time (in milliseconds) it takes for a philosophers to eat
- arg4 = The time (in milliseconds) it takes for a philosophers to sleep
- arg5 = The number of times each philosophers should eat. This argument is optional.

### Notes
- The project was done on Ubuntu 22.04.3 and was also tested on MacOS.
- Memory leaks have been thoroughly checked with Valgrind :
```
valgrind --leak-check=full ./philo arg1 arg2 arg3 arg4 arg5
```
- Valgrind was also used to check for data races :
```
valgrind --tool=drd
```
or
```
valgrind --tool=helgrind
```
- The flag "-fsanitize=thread" can also be used to compile with ThreadSanitizer and check for additional thread errors.