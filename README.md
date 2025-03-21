# Philosophers

<p align="center">
  <img src="https://github.com/ArenKae/ArenKae/blob/main/42%20badges/philosopherse.png" alt="'Philosophers 42 project badge">
</p>

Philosophers is a project designed around Edsger Dijkstra's famous [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem). For this project, we must learn about concurrent programming. For the project's mandatory part, we must find a solution to the problem using only threads and mutexes.

---

## Status
✅ Completed on: 01/02/2024
</br>
🏆 Grade: 100/100

## Usage
To compile, use ```make``` or ```make all```.
Launch the program with the command : 
```bash
./philo <arg1> <arg2> <arg3> <arg4> <arg5>
```
where :
- arg1 = Number of philosophers
- arg2 = The time (in milliseconds) it takes for a philosophers to die
- arg3 = The time (in milliseconds) it takes for a philosophers to eat
- arg4 = The time (in milliseconds) it takes for a philosophers to sleep
- arg5 = The number of times each philosophers should eat. This argument is optional.

### Notes
- The project was done on Ubuntu 22.04.3 and was also tested on MacOS.
- Data races have been thoroughly checked with Valgrind :
```
valgrind --tool=drd ./philo ...
```
or
```
valgrind --tool=helgrind ./philo ...
```
</br>

> [!TIP]
> The flag "-fsanitize=thread" can also be used to compile with ThreadSanitizer and check for additional thread errors.
