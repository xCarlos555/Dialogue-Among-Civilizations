# Dialogue Among Civilizations

**Dialogue Among Civilizations** is an international relations theory introduced by Mohammad Khatami, former president of Iran. Its central idea is to promote universal dialogue between nations, aiming to transform conflicts into peaceful relations. (https://en.wikipedia.org/wiki/Dialogue_Among_Civilizations)

In this project, this concept is modeled as a **weighted complete graph**, where:

- **Vertices** represent civilizations or nations.
- **Edge weights** represent the relationship level between two civilizations:
  - **Positive values** indicate friendly relations.
  - **Negative values** indicate conflict.

The program’s goal is to find a **sequence of dialogues initiated by Civilization 1** with the other civilizations that transforms all relations into **positive values**, thus achieving universal peace.  
If no such sequence exists, the program states that **peace cannot be reached**.

---

## How to Compile and Run

### Compile

```bash
gcc main.c -o dialogue
```

### Run

```bash
./dialogue
```

Ensure that the file **input.txt** is present in the same directory as the executable.

## Input Format

The `input.txt` file must contain:

1. The number of civilizations **N**.
2. An **N x N** matrix representing the relationships between civilizations.

### Rules

- The diagonal values must be `0`.
- Matrix must be **symmetric**.
- Values must be in the range `[-100, 100]`:
  - **Positive values** = friendly relations.
  - **Negative values** = conflicts.

---

### Example Input
```diff
4
0 10 -20 10
10 0 30 5
-20 30 0 -5
10 5 -5 0
```

## Output

- Displays the initial relations matrix.
- Processes possible dialogue sequences.
- Shows whether peace is achieved or not.
- Generates two graph images:
  - **graph_initial.png** – initial relations.
  - **graph_final.png** – final relations after dialogue.

---

## Graph Visualization

The project includes **Python scripts** to visualize relationships as graphs:

- `gerar_grafo_inicial.py` generates the initial graph.
- `gerar_grafo_final.py` generates the final graph.

Graphs use:
- **Green edges** for friendly relations.
- **Red edges** for conflicts.
- Edge labels display the numerical relationship values.