# 🟡 so_long

A simple 2D game built in C using MiniLibX (42 project).  
Your goal is to collect all items and reach the exit without dying 👻

---

## 🧰 Requirements

- Linux or macOS
- `gcc` or `clang`
- `make`
- X11 libraries (Linux only)

To install dependencies on Linux:
```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

🚀 How to Run
    1- Clone the repo 
        git clone https://github.com/aboodjabr0/so_long.git
        cd so_long
    2- Build the project
        make
    3- Run the game
        ./so_long maps/map.ber

🕹️ Controls
    | Key   | Action     |
    | ----- | ---------- |
    | W / ↑ | Move up    |
    | A / ← | Move left  |
    | S / ↓ | Move down  |
    | D / → | Move right |
    | ESC   | Quit game  |

📸 Preview
    Here’s a sneak peek of the game 👇
    ![Gameplay screenshot](assets/Gameplay.png)

💡 Notes

    . The mlx/ directory already includes the MiniLibX library — no installation needed.

    . If the window doesn’t open, ensure your system supports X11.

    . Tested on Ubuntu 22.04 and macOS.

👨‍💻 Author
. Abdullah Sauafth

    📧 [jabr.abood@yahoo.com]
