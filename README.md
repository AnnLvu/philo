 # 🍽️ Philosophers

## 🌟 Overview

The **Philosophers** project is a simulation of the classic dining philosophers problem, which is a synchronization and concurrency problem in computer science. This project aims to demonstrate the application of thread management and synchronization using **mutexes** and **semaphores** in **C**.

In this simulation, a certain number of philosophers are seated at a table, each with a fork on either side. They alternate between thinking and eating. To eat, a philosopher must acquire both forks, and they must return the forks after eating. The goal is to avoid deadlocks and ensure that all philosophers can eat without starvation.

## 🚀 Features

- **Concurrency**: Implemented using `pthread` to simulate multiple philosophers acting concurrently.
- **Synchronization**: Proper synchronization of shared resources (forks) using mutexes to prevent race conditions and deadlocks.
- **Deadlock Prevention**: Strategies implemented to avoid deadlock situations, ensuring all philosophers can eat.
- **Starvation Avoidance**: Mechanisms to ensure no philosopher is left starving forever.
- **Customizable**: The number of philosophers and the simulation time can be adjusted.

## 📋 Requirements

- **Language**: C
- **Libraries**: `pthread.h`, `unistd.h`, `stdlib.h`, `stdio.h`
- **Compiler**: `gcc` with the following flags:
  - `-pthread` (for thread support)
- **Operating System**: Linux or MacOS (any system that supports POSIX threads)

## 💻 Installation

To compile and test the **Philosophers** project, follow these steps:

1. Clone the repository:
   ```bash   
   git clone git@github.com:AnnLvu/philosophers.git
   cd philosophers
   ```   

2. Compile the project:
   ```bash   
   make
   ```   

3. Run the simulation:
   ```bash   
   ./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [optional: <number_of_times_each_philosopher_must_eat>]
   ```  

---

## 🚨 Usage

You can adjust the following parameters when running the simulation:

- `number_of_philosophers`: The total number of philosophers sitting at the table.
- `time_to_die`: The time in milliseconds after which a philosopher will die if they haven't eaten.
- `time_to_eat`: The time in milliseconds that a philosopher spends eating.
- `time_to_sleep`: The time in milliseconds that a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): The number of times each philosopher must eat before the simulation ends. If omitted, philosophers will continue indefinitely.

## 🧠 How It Works

### Philosopher States
Each philosopher can be in one of three states:

- **Thinking**: The philosopher is thinking and not interacting with the forks.
- **Hungry**: The philosopher wants to eat and is waiting for the forks to be available.
- **Eating**: The philosopher has acquired the forks and is eating.

### Forks
Each philosopher needs two forks to eat. The forks are shared resources and are protected using mutexes to prevent multiple philosophers from eating simultaneously with the same fork.

### Thread Synchronization
Each philosopher is represented by a separate thread. The simulation uses mutexes and condition variables to coordinate access to forks and ensure no two philosophers pick up the same fork at the same time.

---

## ⚠️ Known Issues

### Deadlock Handling
While the simulation prevents deadlock using a basic approach, there may still be edge cases under certain configurations that could cause inefficiencies.

### Starvation
Philosophers may still experience starvation if the simulation time is too short or if the number of philosophers is too high.

---

## 🎯 Conclusion
This project demonstrates key concepts of multithreading, synchronization, and concurrency in C. The **Philosophers** problem is a classic example used to teach these concepts, and this project provides a hands-on implementation of that problem.
