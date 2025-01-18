# Graph-Based Transportation Optimization

This project implements a graph-based system to model and optimize transportation networks. It supports buses, cars, and walking, allowing users to find the most optimal routes based on comfort, cost, or time.

## Features

- **Graph Representation**: Uses adjacency matrices to model the transportation network.
- **Optimization Criteria**:
  - Comfort: Prioritizes faster vehicle types.
  - Cost: Minimizes total travel expenses.
  - Time: Reduces total travel time.
- **Shortest Path Calculation**: Implements Dijkstra's algorithm to compute the optimal route.
- **Random Graph Generation**: Creates graphs with configurable sizes and parameters.

## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or later (e.g., GCC, Clang).

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/transport-optimization.git
   ```
2. Navigate to the project directory:
   ```bash
   cd transport-optimization
   ```
3. Compile the program:
   ```bash
   g++ -o transport main.cpp
   ```

### Usage

1. Run the compiled program:
   ```bash
   ./transport
   ```

2. Follow the on-screen instructions to:
   - Choose an optimization criterion: Comfort, Cost, or Time.
   - Input the start and end nodes for the shortest path calculation.

### Input Format

- The graph is randomly generated with 10,000 nodes by default.
- Users provide:
  - **Optimization Preference**: Select one of the three criteria (Comfort, Cost, or Time).
  - **Start and End Nodes**: Specify the nodes for the shortest path calculation.

### Output Example

**Sample Input**:
```
Choose your preference:
1. Comfort
2. Cost
3. Time
Enter your choice: 2
Enter start node: 1
Enter end node: 100
```

**Sample Output**:
```
Optimal route based on Cost:
Path: 1 -> 5 -> 20 -> 100
Total Cost: 25
Total Time: 15 minutes
```

## Project Structure

- `main.cpp`: The main implementation file containing the graph creation, optimization, and shortest path logic.
- `README.md`: Documentation for the project.

## Future Improvements

- Add support for additional optimization criteria (e.g., environmental impact).
- Integrate real-world data for more accurate simulations.
- Implement a graphical interface for better user interaction.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgments

- Algorithms inspired by standard graph theory concepts.
- Special thanks to contributors and reviewers for their feedback.

