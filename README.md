# curlsmith

`curl` command builder written in **C++**.

`curlsmith` provides a simple terminal user interface (TUI) for constructing `curl` commands. Built for lazybones :)

## Features

- Terminal-based UI using **FTXUI**
- Build and preview `curl` commands interactively

## Dependencies

Dependencies are automatically fetched via CMake:

- [FTXUI](https://github.com/ArthurSonzogni/ftxui)

No system-wide installs are required.

## Build

```bash
git clone https://github.com/yourusername/curlsmith.git
cd curlsmith
mkdir build
cd build
cmake ..
cmake --build .
