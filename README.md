# Artificial Intelligence and Knowledge Engineering

Projects developed as part of the *Artificial Intelligence and Knowledge Engineering* course.

---

## Repository Structure

- `Lista1/` – Python (graph algorithms, GTFS data)
- `Lista2/` – C++ (MiniMax, Alpha-Beta, Breakthrough)

---

## Task 1 – Dijkstra, A* and Tabu Search for railway routing

The project focuses on:
- loading data in **GTFS format**
- building a graph of railway stops
- finding optimal routes between them

### Technologies
- Python

### Implemented Algorithms

#### Dijkstra
<img width="1485" height="819" alt="image" src="https://github.com/user-attachments/assets/2107a567-e928-412a-9669-c6ba2ef7005d" />

#### A* (time criterion)
<img width="1676" height="1096" alt="image" src="https://github.com/user-attachments/assets/a1939f9f-480a-44d8-b773-7eaa1ba4eb0b" />

#### A* (transfer criterion)
<img width="1684" height="1089" alt="image" src="https://github.com/user-attachments/assets/d8ad9e26-e403-4b33-b662-0a6ccb382fb2" />

#### Tabu Search (time criterion)
<img width="1531" height="330" alt="image" src="https://github.com/user-attachments/assets/e2d8d805-d2a4-45cb-9039-5a030434c3cf" />

#### Tabu Search (transfer criterion)
<img width="1563" height="327" alt="image" src="https://github.com/user-attachments/assets/bb860fa4-846a-43f2-ab65-8939c93c34dc" />


### ⚙️ Usage

```bash
git clone https://github.com/Micek2021/AI
cd Lista1/src
python main.py --help
```

### Criterion
- `t` – time minimalization
- `p` – transfers minimalization
- 
### Example usage
```
python main.py dijkstra --start "Rawicz" --end "Kłodzko główne" --time 12:30
python main.py astar --criteria t --start "Rawicz" --end "Dresden" --time 12:30 --date 20260301
python main.py astar --criteria t --start "Kłodzko" --end "Zielona Góra Główna" --time 12:30 --date 20260301
python main.py tabu_search --start Rawicz --targets "Wrocław Główny;Gryfów;Lubań;Kłodzko;Łososiowice" --criteria p --time 08:00 --date 20260727 
```
## Assignment 2 – MiniMax + AlphaBeta Algorithm for the Breakthrough Game

The project involves:
- implementing the game board for Breakthrough  
- defining heuristics in the form of an evaluation function  
- finding the best move  
- tuning strategy weights using a genetic algorithm  

### Technologies
- C++

### Implemented Algorithms
- AlphaBeta  
- Minimax  

### Instructions
The program does not include a CLI interface.  
Test parameters (e.g., board state, search depth) should be set directly in the `main.cpp` file.

```bash
git clone https://github.com/Micek2021/AI
cd Lista2/src
g++ main.cpp
./a.outt
```

### Conducted tests
- Tournament of several strategies
<img width="526" height="279" alt="image" src="https://github.com/user-attachments/assets/0469b00c-f6e0-4296-a57a-c9c95f5fb66e" />

- Single game
<img width="348" height="268" alt="image" src="https://github.com/user-attachments/assets/0519646e-421b-45df-b401-7907d4813432" />

- Benchmark
<img width="182" height="177" alt="image" src="https://github.com/user-attachments/assets/4f9b4b26-783e-47da-8eeb-beafaf7df043" />

- Genetic algorithm
<img width="369" height="264" alt="image" src="https://github.com/user-attachments/assets/aa185c31-9ff1-49a7-b3b0-3dead4e7dc1b" />
