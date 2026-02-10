# 🍝 Philosophers - Dining Philosophers Problem

> **Note:** This README was created by AI

A multithreaded solution to the classic Dining Philosophers Problem, implemented in C using POSIX threads. This project is part of the 42 School curriculum, focusing on concurrent programming, thread synchronization, and avoiding deadlocks and data races.

## 📋 Table of Contents

- [About](#about)
- [The Problem](#the-problem)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Testing](#testing)
- [Project Structure](#project-structure)

## 🎯 About

The Dining Philosophers problem is a classic synchronization problem in computer science. It illustrates the challenges of resource allocation and deadlock avoidance in concurrent systems. This implementation ensures:

- No deadlocks occur
- No data races (verified with ThreadSanitizer)
- Philosophers die within 10ms of the expected time
- Proper synchronization using mutexes

## 🤔 The Problem

Five (or N) philosophers sit at a round table with a bowl of spaghetti in front of each. Between each pair of philosophers is a single fork. A philosopher needs two forks to eat.

Philosophers alternate between three states:
- **Eating**: Using two forks
- **Sleeping**: Digesting food
- **Thinking**: Waiting to eat again

The challenge is to prevent:
1. **Deadlock**: All philosophers grab one fork and wait forever for the second
2. **Starvation**: A philosopher never gets to eat
3. **Data races**: Unsynchronized access to shared resources

## ✨ Features

- ✅ Thread-safe implementation with proper mutex protection
- ✅ Accurate death detection (within milliseconds)
- ✅ Support for variable number of philosophers
- ✅ Optional meal count termination
- ✅ No data races (ThreadSanitizer clean)
- ✅ Deadlock prevention through fork ordering strategy
- ✅ Memory leak free

## 🚀 Installation

```bash
# Clone the repository
git clone <your-repo-url>
cd philisopher

# Compile the project
make

# The executable 'philo' will be created
```

### Compilation with Sanitizers (for testing)

```bash
# With Thread Sanitizer (detect data races)
make fclean
make CC="cc" CFLAGS="-Wall -Wextra -Werror -pthread -g -fsanitize=thread"

# With Address Sanitizer (detect memory leaks)
make fclean
make CC="cc" CFLAGS="-Wall -Wextra -Werror -pthread -g -fsanitize=address"
```

## 💻 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time in milliseconds until a philosopher dies without eating
- `time_to_eat`: Time in milliseconds a philosopher spends eating
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat`: (Optional) Simulation stops when all philosophers have eaten this many times

All times are in milliseconds. All parameters must be positive integers.

### Examples

```bash
# 5 philosophers, die after 800ms, eat for 200ms, sleep for 200ms
./philo 5 800 200 200

# Same as above, but stop after each philosopher eats 7 times
./philo 5 800 200 200 7

# Edge case: single philosopher (should die)
./philo 1 800 200 200

# Tight timing test (difficult scenario)
./philo 4 410 200 200

# Two philosophers (should never die)
./philo 2 410 200 200
```

## 🔧 Implementation Details

### Thread Architecture

- **Main thread**: Initializes data structures and manages cleanup
- **Philosopher threads**: One per philosopher, executes eat-sleep-think cycle
- **Monitor thread**: Checks for philosopher deaths and meal completion

### Synchronization Strategy

#### Fork Management
- Each fork is protected by a mutex
- Even-numbered philosophers pick right fork first, odd-numbered pick left first
- This ordering prevents circular wait conditions (deadlock prevention)

#### Data Race Prevention
- `last_meal` timestamp: Protected by per-philosopher `meal_mutex`
- `eat_count`: Protected by per-philosopher `meal_mutex`
- `someone_died` flag: Protected by global `death_mutex`
- Console output: Protected by global `print_mutex`

#### Key Mutexes
```c
pthread_mutex_t *forks;              // One per fork
pthread_mutex_t meal_mutex;          // Per philosopher (protects last_meal & eat_count)
pthread_mutex_t print_mutex;         // Global (protects output)
pthread_mutex_t death_mutex;         // Global (protects death flag)
```

### Timing Precision

- Monitor checks philosopher status every 100 microseconds
- Death detection accuracy: typically within 1-2ms
- Uses `gettimeofday()` for millisecond precision
- Custom `ft_usleep()` for more accurate sleep implementation

### Edge Cases Handled

1. **Single philosopher**: Dies immediately (only one fork available)
2. **Two philosophers**: Can alternate eating indefinitely
3. **Very tight timing**: Handles scenarios where `time_to_die` ≈ `time_to_eat` + `time_to_sleep`
4. **Even/odd staggering**: Even-numbered philosophers start eating with slight delay to prevent contention

## 🧪 Testing

### Basic Tests
```bash
# Should not die (enough time to eat and sleep)
./philo 5 800 200 200

# Should die quickly
./philo 5 400 200 200

# Edge cases
./philo 1 800 200 200     # Single philosopher dies
./philo 2 800 200 200     # Two philosophers alternate
./philo 200 800 200 200   # Many philosophers
```

### Stress Tests
```bash
# Very tight timing
./philo 4 310 200 100     # Dies at ~310ms

# Death immediately after eating
./philo 4 410 200 200

# Meal count completion
./philo 5 800 200 200 7   # Stops after 7 meals each
```

### Checking for Data Races
```bash
# Recompile with ThreadSanitizer
make fclean
make CC="cc" CFLAGS="-Wall -Wextra -Werror -pthread -g -fsanitize=thread"

# Run any test
./philo 4 410 200 200

# Should output "ThreadSanitizer: reported 0 warnings" (no data races)
```

### Memory Leak Check
```bash
# Using valgrind (install if needed)
valgrind --leak-check=full ./philo 5 800 200 200

# Or compile with AddressSanitizer
make fclean
make CC="cc" CFLAGS="-Wall -Wextra -Werror -pthread -g -fsanitize=address"
./philo 5 800 200 200
```

## 📁 Project Structure

```
.
├── Makefile              # Build configuration
├── README.md            # This file
├── philo                # Compiled executable
├── include/
│   └── philo.h          # Header file with structures and prototypes
├── src/
│   ├── main.c           # Entry point and argument parsing
│   ├── init.c           # Initialization of data structures and threads
│   ├── routine.c        # Philosopher thread routine
│   ├── monitor.c        # Monitor thread and death detection
│   ├── actions.c        # Eat, sleep, think actions
│   ├── time.c           # Time utilities and status printing
│   ├── utils.c          # Utility functions (atoi, validation)
│   └── cleanup.c        # Memory and mutex cleanup
└── obj/                 # Object files (generated)
```

## 🎓 Learning Objectives

This project teaches:
- **Multithreading**: Creating and managing POSIX threads
- **Synchronization**: Using mutexes to protect shared resources
- **Deadlock Prevention**: Strategies to avoid circular wait conditions
- **Data Races**: Understanding and preventing race conditions
- **Resource Management**: Proper allocation and cleanup of system resources
- **Timing and Precision**: Working with timestamps and accurate sleep implementations

## ⚙️ Technical Requirements

- **Language**: C
- **Compilation**: `cc` with `-Wall -Wextra -Werror -pthread`
- **Standard**: POSIX threads (pthread library)
- **External functions allowed**:
  - `memset`, `printf`, `malloc`, `free`, `write`, `usleep`
  - `gettimeofday`, `pthread_create`, `pthread_detach`
  - `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`
  - `pthread_mutex_lock`, `pthread_mutex_unlock`

## 🐛 Common Issues and Solutions

### Issue: Philosophers die when they shouldn't
**Solution**: Ensure timing parameters satisfy: `time_to_die > time_to_eat + time_to_sleep`

### Issue: No death detected when expected
**Solution**: Check monitor thread is running and usleep interval is small enough

### Issue: Data race detected
**Solution**: All shared variables must be protected with mutexes when accessed by multiple threads

### Issue: Deadlock (program hangs)
**Solution**: Verify fork acquisition order differs between even/odd philosophers

## 📝 License

This project is part of the 42 School curriculum. Feel free to study and learn from it, but please adhere to your school's policies on academic integrity.

---

**Made with ☕ and threads**
