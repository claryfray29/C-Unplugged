# C Unplugged: Music Library Management System

**C Unplugged** is a CLI-based music management application written in C. It allows users to manage a personal song library, create custom playlists, organize songs into albums, and maintain a log of their activity. The system uses **doubly linked lists** for efficient navigation and file I/O for persistent data storage.

---

## Features

### 1. Library & Playlist Management
* **List Library**: View all available songs stored in `songs.txt`.
* **Custom Playlists**: Add songs to a dynamic playlist or delete them by specific position.
* **Playback Navigation**: "Play" your playlist with `begin`, `next`, and `prev` commands to navigate through songs bidirectionally.

### 2. Album Organization
* **Album Creation**: Create named albums to group your music (spaces are replaced with underscores).
* **Album Content**: Add or delete specific songs within an album.
* **Persistence**: Albums and their contents are automatically saved to `albums.txt` and restored when the program starts.

### 3. Command History
* **Activity Log**: Every command entered is recorded in `command_log.txt`.
* [**View Logs**: Users can view their full command history directly within the application.

---

## Project Structure

| File | Description |
| :--- | :--- |
| `main.c` | The core engine handling the user menu, command processing, and data restoration. |
| `list.c` | Logic for general playlist management, library reading, and command logging. |
| `album.c` | Logic for creating, managing, and saving/loading albums and their associated songs. |
| `functions.h` | Header file containing structure definitions (`playlist`, `album`, `albumofalbum`) and all function prototypes. |
| `Makefile` | Build instructions for the GCC compiler to generate the `c_unplugged` executable. |

---

## Technical Details

* **Data Structures**: The project utilizes **Doubly Linked Lists** for both playlists and albums, enabling features like moving to a "previous" song.
* **Compilation**: The project is compiled using `gcc` with the `-Wall` (all warnings) and `-g` (debugging information) flags.
* **Storage**:
    * `songs.txt`: The source library database used to find songs to add.
    * `albums.txt`: Stores serialized album and song data for cross-session persistence.
    * `command_log.txt`: A text-based audit trail of user inputs and actions.

---

## How to Run

### Build the Project
Use the provided `Makefile` to compile the source code:
```bash
make
