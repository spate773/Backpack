Elementary Cellular Automaton Simulator (C)

Overview
This project is a C-based simulation of an elementary cellular automaton, a simple computational model that evolves over time based on a set of rules. Given a rule number (0–255), 
the program generates and displays how a one-dimensional world of cells changes across multiple generations.
I built this project to better understand low-level programming concepts in C, including arrays, structs, and state-based simulations.
How It Works
The user inputs a rule number (0–255), which defines how cells evolve.
The program converts this rule into an 8-bit binary representation.
Each cell updates its state based on its left neighbor, itself, and its right neighbor.
The simulation starts with a single active cell in the center.
The world evolves over a user-defined number of generations.
 
Features
Rule-based simulation using elementary cellular automata logic
Circular (wrap-around) world behavior
Visual output of each generation using characters:
o = active cell
' = inactive cell
Running total of how many times each cell was active
Input validation for rule number and generation count
Tech Stack
Language: C
Concepts: Structs, arrays, loops, conditionals, bit manipulation
Program Structure
cell struct stores:
Neighbor states (left, self, right)
Current activity state
Total active count over time
setBitArray() converts rule number into binary
stateToIndex() maps cell states to rule index
setStates() updates neighbor states for all cells
evolveWorld() computes the next generation

...
(Each row represents a new generation, followed by the number of active cells.)
Challenges & What I Learned
Implementing wrap-around logic for edge cells required careful indexing
Converting rule numbers into binary arrays helped reinforce bitwise thinking
Managing state updates separately 
Tracking cumulative activity introduced more complex state management
