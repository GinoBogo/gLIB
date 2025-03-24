# **gLIB**

Collection of C++17 classes designed to be _fast_, _compact_ and _multi-platform_.

## **List of classes** ##

**GBuffer**

The `GBuffer` class is a utility for managing a dynamically allocated memory buffer. It provides methods for clearing, zeroing, reading, writing, and managing the state of the buffer. The class ensures efficient memory operations and includes error handling for invalid arguments. It is suitable for scenarios requiring temporary storage or data manipulation in a controlled memory space.

**GCircularBuffer**

The `GCircularBuffer` class is a templated circular buffer implementation designed for efficient storage and retrieval of elements in a fixed-size buffer. It supports operations such as adding elements, removing elements, checking for containment, and resizing the buffer. The class ensures that the buffer size is a power of two for optimized indexing and provides methods to query its state, such as whether it is full or empty, its current count, and its capacity.

**GConfig**

The `GConfig` class is a configuration management utility that facilitates reading and writing configuration files. It provides methods to load options from a file and save them back to a specified file. The class includes logging for success, errors, and warnings, and can generate a default configuration file if loading fails.

**GFFT**

The `GFFT` class is a templated Fast Fourier Transform (FFT) utility built on the FFTW library. It supports forward and backward FFT operations on a fixed number of elements and provides options for scaling and shifting the results. The class allows setting input signals, executing FFT operations with different modes, and retrieving the transformed results. It is designed for efficient and flexible frequency-domain analysis.

**GFifo**

The `GFifo` class is a thread-safe First-In-First-Out (FIFO) buffer designed for managing fixed-size data blocks. It supports operations to push data into the buffer, pop data from it, and clear or reset its state. The class includes overflow and underflow metrics for monitoring usage and ensures safe concurrent access using mutex locks. It is suitable for scenarios requiring efficient and synchronized data queuing.

**GFilePipe**

The `GFilePipe` class is a file streaming utility that facilitates reading from and writing to files in chunks. It uses a ping-pong buffering mechanism to handle data efficiently and supports both reader and writer modes. The class integrates with worker functions for file operations and provides error handling for invalid configurations. It is suitable for scenarios requiring high-performance file I/O with chunked data processing.

**GLogger**

The `GLogger` class is a logging utility that provides functionality for writing log messages with timestamps, severity levels, and source file information. It supports logging to both the console and a file, with automatic file initialization if not already open. The class includes methods for formatting log entries and aligning text, making it suitable for structured and detailed logging in applications.

**GMeasure**

The `GMeasure` struct is a utility for measuring the execution time of functions. It provides static methods to measure durations in milliseconds, microseconds, and nanoseconds. By accepting a callable and its arguments, it calculates the elapsed time using the system clock, making it useful for performance benchmarking and profiling.

**Gmseq**

The `Gmseq` class is a templated implementation of a maximum-length sequence (m-sequence) generator. It uses linear feedback shift registers (LFSRs) to produce pseudo-random binary sequences based on a specified degree and polynomial taps. The class provides methods to reset the generator and update the sequence, making it suitable for applications in communications, cryptography, and signal processing.

**GOptions**

The `GOptions` class is a configuration management utility that provides functionality for reading, writing, and manipulating key-value pairs from configuration files. It supports parsing data into structured sections, converting between different data types, and merging configurations. The class includes utilities for splitting and joining strings, as well as robust error handling for invalid or missing files, making it suitable for managing application settings.

**GPingPong**

The `GPingPong` class is a multi-threaded data buffering utility that implements a ping-pong mechanism for efficient data processing. It alternates between two buffers to handle data streams, supporting both reading and writing operations. The class integrates worker functions for custom processing, manages thread priorities, and ensures thread-safe operations using mutexes and condition variables. It is ideal for scenarios requiring synchronized producer-consumer workflows.

**GPtr**

The `GPtr` class is a lightweight smart pointer utility designed to manage the lifetime of dynamically allocated objects or arrays. It uses template specialization to differentiate between single objects and arrays, ensuring proper deletion. The class provides overloaded operators for pointer-like behavior, such as dereferencing and member access, making it a simple and efficient tool for managing raw pointers safely.

**GThreadPriority**

The `GThreadPriority` namespace provides utilities for managing thread priorities in a POSIX-compliant environment. It includes functions to get and set the priority of the current thread or a specific thread, as well as retrieve the priority range for a given scheduling policy. These tools are useful for fine-tuning thread execution order in multi-threaded applications.

**GUdpClient**

The `GUdpClient` class is a UDP client utility designed for sending and receiving data over a network. It provides methods to send and receive data using raw buffers or a `GBuffer` object. The class handles socket initialization, connection setup, and error logging, ensuring robust communication. It is suitable for lightweight and efficient UDP-based networking applications.

**GUdpServer**

The `GUdpServer` class is a UDP server utility designed for receiving and sending data over a network. It initializes a socket bound to a specified local address and port, manages incoming and outgoing data using raw buffers or a `GBuffer` object, and provides error logging for robust communication. The class is suitable for lightweight and efficient UDP-based server applications.

**GUdpLink**

The `GUdpLink` class is a templated utility that abstracts UDP communication for master-slave architectures. It uses `GUdpClient` for the master mode and `GUdpServer` for the slave mode. The class provides methods for sending queries and waiting for replies in master mode, as well as waiting for queries and sending replies in slave mode. It ensures type-safe operations and includes error logging for invalid calls, making it suitable for structured UDP-based communication systems.

**GUtils**

The `GUtils` module provides low-level utility functions for memory operations, including `gb_memcpy`, `gb_memset`, and `gb_zeros`. These functions use optimized techniques like Duff's Device for loop unrolling to enhance performance. The module is designed for scenarios requiring efficient manipulation of memory blocks, making it suitable for performance-critical applications.

**XCorr**

The `GXCorr` class is a templated cross-correlation utility built on the FFTW library. It computes the cross-correlation of two input signals using the Fast Fourier Transform (FFT) for efficient processing. The class supports operations in both normal and shifted modes, provides methods to set input signals, retrieve results, and identify the maximum peak in the correlation. It is ideal for signal processing tasks requiring fast and accurate cross-correlation computations.