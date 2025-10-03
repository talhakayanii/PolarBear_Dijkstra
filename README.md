# Polar Bear Delivery Optimization System
## Description:

The Polar Bear Delivery Optimization System is a route planning algorithm implemented in C++ that optimizes delivery times for riders delivering orders from restaurants. The system uses Dijkstra's Algorithm to find the shortest paths on a grid, ensuring timely deliveries within the specified time limits.

## Features:

Optimized Delivery Routes: Uses Dijkstra's algorithm to calculate the shortest path for each delivery order.

Order Management: Handles multiple restaurants, each with several orders, ensuring timely delivery based on location and time constraints.

Dynamic Grid System: The system operates on a grid-based layout where each restaurant and order location is tracked.

Efficient Rider Routing: The rider picks up and delivers orders by choosing the nearest unvisited order based on the shortest path, ensuring efficiency.

## How it Works:

Input Data: The system reads the input from a file (polarbearinput.txt), which contains details such as grid size, rider and restaurant information, and order specifications.

Route Optimization: For each restaurant, the system calculates the shortest paths for riders to deliver orders within the specified delivery time limit.

Output: The system outputs the total time taken for all deliveries and the time for each order.

## Example Workflow:

The system reads input data for multiple test cases from a file.

For each test case:

It calculates the shortest delivery times for orders at various restaurants.

Displays if each order can be delivered on time, and if not, provides the details.

After processing all orders, the system outputs the total time taken for deliveries.

## Technologies Used:

C++: For implementing Dijkstra's Algorithm and managing input/output.

File I/O: Input and output handled via text files (polarbearinput.txt).

Windows APIs: Used for system calls like Sleep() to control animation timings.
