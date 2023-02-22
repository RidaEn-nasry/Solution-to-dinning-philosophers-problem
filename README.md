# Solution-to-dinning-philosophers-problem


The Dining Philosophers problem is a classic problem in computer science that involves five philosophers who must alternate between thinking and eating without blocking each other. In this project, mutexes and condition variables were used to ensure that the philosophers could eat without blocking each other. A deadlock detection mechanism was also implemented to prevent the program from hanging. Threads were used to represent the philosophers, and their actions were coordinated using mutexes and condition variables. This project provided a good opportunity to learn more about concurrent programming and the challenges of managing multiple threads.

![dpp](https://user-images.githubusercontent.com/65143740/220583456-ff0ee8dd-8133-47d0-bcd6-cc958d727e79.png)


• One or more philosophers sit at a round table.<br>
There is a large bowl of spaghetti in the middle of the table.<br>
• The philosophers alternatively eat, think, or sleep.<br>
While they are eating, they are not thinking nor sleeping;<br>
while thinking, they are not eating nor sleeping;<br>
and, of course, while sleeping, they are not eating nor thinking.<br>
• There are also forks on the table. There are as many forks as philosophers.<br>
• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.<br>
• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.<br>
• Every philosopher needs to eat and should never starve.<br>
• Philosophers don’t speak with each other.<br>
• Philosophers don’t know if another philosopher is about to die.<br>
• No need to say that philosophers should avoid dying!<br>



# About Directories:
- First directory "mandory" is a solution using <b>mutexes</b>.
- Second directory "bonus" is a solution using <b>semaphores</b>.


# How to use:

to use <b>mutexes</b> solution:<br>
```
$ make
```
to use <b>semaphores</b> solution <br>
```
$ make bonus
```
then <br>
```
$ ./philo <number of philosophers> <time_to_die> <time_to_eat> <time_to_eat> <number_of_times_each_philosopher_must_eat>
```

 or alternatively <br> 
 ```
$ ./philo_bonus <number of philosophers> <time_to_die> <time_to_eat> <time_to_eat> <number_of_times_each_philosopher_must_eat>
```
<br>
The program will run until a philosopher die or each philosopher eat <number_of_times_each_philosopher_must_eat> times.
 <br>

  
