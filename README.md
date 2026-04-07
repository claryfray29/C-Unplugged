# C Unplugged: Music Library Management System

[cite_start]**C Unplugged** is a CLI-based music management application written in C[cite: 1, 18]. [cite_start]It allows users to manage a personal song library, create custom playlists, organize songs into albums, and maintain a log of their activity. [cite_start]The system uses **doubly linked lists** for efficient navigation and file I/O for persistent data storage[cite: 7, 16, 17].

---

## Features

### 1. Library & Playlist Management
* [cite_start]**List Library**: View all available songs stored in `songs.txt`[cite: 10, 20].
* [cite_start]**Custom Playlists**: Add songs to a dynamic playlist or delete them by specific position[cite: 12, 13, 20].
* [cite_start]**Playback Navigation**: "Play" your playlist with `begin`, `next`, and `prev` commands to navigate through songs bidirectionally[cite: 13, 14, 21].

### 2. Album Organization
* [cite_start]**Album Creation**: Create named albums to group your music (spaces are replaced with underscores)[cite: 8, 22].
* [cite_start]**Album Content**: Add or delete specific songs within an album[cite: 3, 4, 24].
* [cite_start]**Persistence**: Albums and their contents are automatically saved to `albums.txt` and restored when the program starts[cite: 7, 18, 25].

### 3. Command History
* [cite_start]**Activity Log**: Every command entered is recorded in `command_log.txt`[cite: 16].
* [cite_start]**View Logs**: Users can view their full command history directly within the application[cite: 16, 25].

---

## Project Structure

| File | Description |
| :--- | :--- |
| `main.c` | [cite_start]The core engine handling the user menu, command processing, and data restoration[cite: 18, 25, 26]. |
| `list.c` | [cite_start]Logic for general playlist management, library reading, and command logging[cite: 16, 17]. |
| `album.c` | [cite_start]Logic for creating, managing, and saving/loading albums and their associated songs[cite: 8, 9]. |
| `functions.h` | [cite_start]Header file containing structure definitions (`playlist`, `album`, `albumofalbum`) and all function prototypes[cite: 17]. |
| `Makefile` | [cite_start]Build instructions for the GCC compiler to generate the `c_unplugged` executable[cite: 1]. |

---

## Technical Details

* [cite_start]**Data Structures**: The project utilizes **Doubly Linked Lists** for both playlists and albums, enabling features like moving to a "previous" song[cite: 8, 16, 17].
* [cite_start]**Compilation**: The project is compiled using `gcc` with the `-Wall` (all warnings) and `-g` (debugging information) flags[cite: 1].
* **Storage**:
    * [cite_start]`songs.txt`: The source library database used to find songs to add[cite: 3, 11].
    * [cite_start]`albums.txt`: Stores serialized album and song data for cross-session persistence[cite: 7].
    * [cite_start]`command_log.txt`: A text-based audit trail of user inputs and actions[cite: 16].

---

## How to Run

### Build the Project
[cite_start]Use the provided `Makefile` to compile the source code[cite: 1]:
```bash
make
