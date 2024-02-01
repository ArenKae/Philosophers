# Philosophers

<p align="center">
  <img src="https://github.com/ArenKae/42-badges/blob/main/philosopherse.png" alt="Philosophers by acosi">
</p>

One of the first graphical projects at 42 school, so_long is a small 2D game where a lost astronaut needs to collect energy cells to power up his ship. This project uses the school's graphical library, MiniLibX, in order to display a window, handle events, colors and textures.

---

## Status
Finished 01/02/2024.

Grade: 100/100

## Usage
To compile, use ```make``` or ```make all```.
Launch the program with the command : ```./philo arg1 arg2 arg3 arg4 arg5```
where :
arg1 = Number of philosophers
arg2 = The time (in milliseconds) it takes for a philosophers to die
arg3 = The time (in milliseconds) it takes for a philosophers to eat
arg4 = The time (in milliseconds) it takes for a philosophers to sleep
arg5 = The number of times each philosophers should eat. This argument is optional.

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