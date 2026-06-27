
# 📚 Student Grade Book System

An interactive desktop utility designed to manage, track, and analyze student academic records cleanly through a terminal window. The application allows users to handle course grades for up to 50 students across 8 distinct subjects, perform quick student profile lookups, rank records automatically, and export summarized analytical performance sheets.

---

## 🕹️ Key Features

* **Complete Record Management:** Create, view, update, and remove student academic entries smoothly.
* **Integrated Class Tracking:** Records distinct performance values for 8 subjects (including Core Theory lectures and corresponding Practical Labs).
* **Automated Performance Math:** Automatically aggregates total student marks, calculates percentage distributions, computes GPA curves, and assigns clean letter grades (A through F).
* **Rankings Board Sorting:** Instantly sorts and re-orders the active student lists from highest to lowest GPA performance metrics.
* **Persistent File Saving:** Reads records automatically from storage on startup and writes updates back to a local flat file securely before exiting.
* **Analytical File Exporting:** Compares active rosters to instantly track class toppers, passed/failed ratios, and overall class average scores across all subjects into a secondary text summary.

---

## 🚀 Tracked Course Subjects

The application automatically records scores for:
1. Programming Fundamentals
2. PF LAB
3. Applied Physics
4. Physics LAB
5. Introduction to ICT (AICT)
6. AICT LAB
7. Calculus - 1
8. Discrete Mathematics

---

## ⚙️ How to Setup and Run

### Step-by-Step Execution

1. Open your computer's terminal, Command Prompt, or terminal emulator application.
2. Navigate directly into the specific folder containing your `main.cpp` source file.
3. Compile the application using a standard C++ compiler:
   ```bash
   g++ main.cpp -o student_gradebook
