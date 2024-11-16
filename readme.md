# Notepad Application with Spell Check

This is a simple console-based notepad application developed in C++ using the `ncurses` library. It features a text editor with spell-check functionality powered by an AVL tree dictionary.

---

## Features

### Text Editor
- **Add Text:** Type characters to append to the text.
- **Delete Last Character:** Press `Backspace` to delete the last character in the text.
- **Save Text to File:** Press `Ctrl + S` to save the current text to a file named `save.txt`.
- **Load Text from File:** Press `Ctrl + L` to load text from `save.txt`.

### Spell Check
- **Word Validation:** Automatically checks the spelling of a word when a space is typed.
- **Suggestions:** If a word is not found in the dictionary, suggestions are displayed for:
  - Substitution of a letter
  - Omission of a letter
  - Insertion of a letter
  - Reversal of adjacent letters

---

## Key Bindings

| **Key**       | **Function**                              |
|---------------|-------------------------------------------|
| `ESC`         | Exit the application                      |
| `Backspace`   | Delete the last character                 |
| `Space`       | Perform spell check on the current word   |
| `Ctrl + S`    | Save the text to `save.txt`               |
| `Ctrl + L`    | Load text from `save.txt`                 |

---

## Dependencies

- `ncurses` library for terminal-based UI.
- C++ compiler with standard C++11 or later support.

---

## File Structure

- **`main.cpp`**: Contains the source code for the application.
- **`dictionary.txt`**: A text file containing the words used for the spell check dictionary.
- **`save.txt`**: The file used to save and load text content.

---

## Classes

### `LinkedList`
- Handles character storage for the text editor.
- **Methods**:
  - `append(char data)`: Adds a character to the end of the list.
  - `deleteAtEnd()`: Deletes the last character.
  - `display(int startRow)`: Displays the content on the screen starting at the specified row.

### `Queue`
- Stores characters for forming words during spell checking.
- **Methods**:
  - `enqueue(char data)`: Adds a character to the queue.
  - `dequeue()`: Removes the first character.
  - `dequeueAll()`: Clears the queue and returns the stored word.

### `AVLTree`
- Implements an AVL tree for the dictionary.
- **Methods**:
  - `insertValue(const string &value)`: Inserts a word into the tree.
  - `search(const string &value)`: Checks if a word exists in the dictionary.

---

## Spell Check Algorithms

1. **Substitute Letters**: Replaces each letter in the word with every other letter to find a valid word.
2. **Omit Letters**: Removes one letter at a time to check for valid words.
3. **Insert Letters**: Inserts letters at every position to find valid words.
4. **Reverse Letters**: Swaps adjacent letters to check for valid words.

---


