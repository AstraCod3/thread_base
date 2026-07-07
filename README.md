# Thread Base

`⚙️ Build Debug: passing`<br>
`🚀 Build Release: passing`<br>
`📄 License: GPLv3`<br>
`📝 Language: C++`<br>
`💻 OS: Windows | Linux`

---

A multi-platform (Linux/Unix, Windows) header-only developed with the Standard Template Library (STL). It provides robust support for managing and synchronizing all your custom threads, offering an efficient solution for implementing real-time systems.

---

## 🚀 How to use

Follow these steps to integrate and manage threads in your application:

1. **Include the Header File**
   Start by including the main header file:
   ```cpp
   #include "cthread_base.hpp"
   ```

2. **Create a Subclass**
   Create a custom class that inherits from the abstract class:
   ```cpp
   class my_thread : public ns_thread_base::cthread_base {
   ...
   ```

3. **Implement the Virtual Function**
   Override the pure virtual function where your thread logic will live:
   ```cpp
   void my_thread::thread_function() override {
      // to do something
   }
   ```

4. **Create the Thread**
   Call the `create()` function to initialize the thread. 
   > ⚠️ **Note:** This function must be called first and is **BLOCKING**.

5. **Run the Thread**
   Call the `run()` function when you are ready to start execution.
   ```cpp
   my_thread obj_my_thread;
   obj_my_thread.run();
   ```
   > ⚡ **Note:** This function is **NON-BLOCKING**.

6. **Destroy the Thread**
   After calling `run()`, you must call `destroy()` to clean up resources. 
   ```cpp
   obj_my_thread.destroy();
   ```
   > ⚠️ **Note:** This function is **BLOCKING**.
   * Failing to call `destroy()` after `run()` will raise an exception.
   * You can call `destroy()` to terminate the thread, but ensure it happens *after* `create()`, otherwise an exception will be thrown.

---

### 💡 Examples
For a practical implementation, please check the `ns_quick_sort` namespace inside the **`test/example/quick_sort.cpp`** file.

---

## 📂 Project Structure

```text
├── examples/ ................. # Example implementations and client scripts
│   ├── quick_sort.cpp ............. # Quick sor algorithm with multi-threads
│   └── CMakeLists.txt ..............# CMake configuration for examples
├── scripts/ .................. # Cross-platform automation and build tools (see details below)
├── tests/ ......................... # Testing environment (GoogleTest)
│   ├── integration/ ............... # Source code of the integration tests
│   ├── unit/ ...................... # Source code of the unit tests
│   ├── CMakeLists.txt ............. # CMake configuration for tests
│   └── README.md .................. # Tests documentation file
├── thread_base/ .............. # Source code of the library
└── README.md ................. # Project documentation file
```

---

## 🛠️ Automation Scripts

The project provides automation tools inside the `scripts/` directory to standardize your workflow.

| Feature | Windows (`.cmd`) | Linux/macOS (`.sh`) | Description |
| :--- | :--- | :--- | :--- |
| **Orchestration** | `build.cmd` | `build.sh` | Main script to compile GoogleTest, build project tests, or generate Doxygen documentation. |
| **Execution** | `run.cmd` | `run.sh` | Runs the compiled test binaries locally. |
| **Cleanup** | `clean.cmd` | `clean.sh` | Deep cleans the workspace, wiping build caches and generated documentation. |
| **Environment** | `env.cmd` | `env.sh` | Centralizes variables, compiler flags, and local paths shared across scripts. |
| **Profiling** | *N/A* | `run_valgrind.sh` | Launches the test suite through **Valgrind** to track down memory leaks. |

---

## 🧪 Testing

Follow these steps to build and run the test suite:

1. **Add your test files**  
   Place your source files inside the `src/` directory and ensure your main entry point is added to `src/test.cpp`.

2. **Build the project**  
   Run the appropriate script for your operating system from the root folder:
   * **Linux/Unix:** `./scripts/build.sh`
   * **Windows:** `.\scripts\build.cmd`
   
   > ℹ️ *Note: The `CMakeLists.txt` file automatically loops through all source files in the `src/` directory and builds a separate executable for each one.*

3. **Run the tests**  
   Execute the run scripts to test your code:
   * **Linux/Unix:** `./scripts/run.sh` or `./scripts/run_valgrind.sh`
   * **Windows:** `.\scripts\run.cmd`
   
   > 🛡️ *Note: On Linux, `run_valgrind.sh` will automatically run Valgrind memory analysis on every executable found inside the `bin/` folder.*

---

### 🔨 Dynamically Generated Items (After Build/Run)


```text
├── bin/ ....................... # Created after build; contains the compiled executables
├── build/ ..................... # Created after build; contains temporary CMake objects
├── deps/ ...................... # Created after build; contains external dependencies
└── log/ ....................... # Created after running run_valgrind.sh; contains Valgrind logs
```

---

## 📄 License

This project is licensed under the **GNU General Public License v3.0** - see the [LICENSE](LICENSE) file for details.
