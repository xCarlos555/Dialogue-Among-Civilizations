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