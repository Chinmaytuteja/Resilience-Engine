# Dynamic Infrastructure Resilience Engine

A highly optimized C++ systems simulator designed to evaluate physical network infrastructure (power grids, server farms, fiber-optic routes) for fault tolerance. The engine calculates the absolute minimum infrastructure backbone required to maintain connectivity and executes real-time diagnostics during simulated hardware failures (e.g., fiber-optic cuts).

## Core Engineering Mechanics

This project bypasses standard libraries to implement two advanced data structures from scratch:

1. **Disjoint Set Union (DSU / Union-Find):**
   - Engineered an optimized pointer-forest architecture utilizing both **Path Compression** and **Union by Rank**.
   - Achieves near O(α(V)) amortized time complexity (bounded by the Inverse Ackermann function) for component connectivity lookups, completely bypassing slow O(V + E) graph traversals during real-time network fracturing.
   
2. **Kruskal's Minimum Spanning Tree (MST):**
   - Utilizes the DSU to greedily construct the most cost-effective, cycle-free infrastructure skeleton across the network topology.

## Interactive Terminal Features
The engine features a stateful, event-driven command-line interface that allows for real-time infrastructure profiling:

* **Baseline Calculation:** Sorts active edges and prints the optimized MST routing configuration.
* **Network Diagnostics:** Scans the active grid to count the number of isolated components/islands.
* **Failure Simulation:** Allows the user to intentionally sever explicit cable IDs, triggering dynamic recalculations of network integrity.

## How to Run

1. Compile the C++ engine:
   `g++ resilience_engine.cpp -o resilience_engine`

2. Execute the simulation:
   `./resilience_engine`