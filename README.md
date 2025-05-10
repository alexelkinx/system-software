# System Software (C Programming Projects)

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue" alt="C"/>
  <img src="https://img.shields.io/badge/Build-Makefile-informational" alt="Makefile"/>
  <img src="https://img.shields.io/badge/Build-CMake-informational" alt="CMake"/>
  <img src="https://img.shields.io/badge/Scripting-Python-yellowgreen" alt="Python"/>
  <img src="https://img.shields.io/badge/Data-CSV-orange" alt="CSV"/>
</p>

## Overview

This repository contains the projects and solutions for the **System Software** course, which spans a semester and covers various aspects of system software development, including file handling, data processing, and simulation systems. The course focuses on programming in C, and each lab is designed to strengthen the understanding of fundamental concepts such as data structures, memory management, and hardware interaction.

## Topics Covered

- File I/O and data persistence in C
- Structs, arrays, and memory management
- Data smoothing and filters (Moving Average, Low-Pass)
- Basic CMake and Makefile usage
- Python scripting for data processing and visualization
- State machines and simulation of control systems

The course includes three primary labs that involve the development of:

1. A **Library Manager** application for managing book records with file I/O operations.
2. A **Moving Average Filter** to process temperature data from CSV files using smoothing techniques.
3. A **Traffic Light Controller** that simulates traffic light operations with various states and pedestrian request handling.

## Table of Contents

- [Lab 1: Library Manager](#lab-1-library-manager)
- [Lab 2: Moving Average Filter](#lab-2-moving-average-filter)
- [Lab 3: Traffic Light Controller](#lab-3-traffic-light-controller)
- [Building the Projects](#building-the-projects)

## Lab 1: Library Manager

### Project Overview

In **Lab 1**, I developed a simple **Library Manager** application in C to manage a collection of books. The program allows the user to perform various actions such as adding, deleting, and loaning books, as well as listing available books and searching for a book by ID. It also includes file operations to save the state of the library to a file.

### Key Features:

- Add, delete, loan, and search for books
- Save and load library data from a file
- Built with a **Makefile** for managing the build process

**[See Lab 1 Details](lab-01-library-manager/README.md)**

---

## Lab 2: Moving Average Filter

### Project Overview

In **Lab 2**, I created a program to apply **Moving Average** and **Low-Pass Filters** to temperature data stored in CSV files. The program processes temperature data for a specified location and applies smoothing techniques to the data. The filtered results are saved in a new CSV file.

### Key Features:

- Applies **Moving Average** and **Low-Pass Filters**
- Fetches real-time temperature data from a weather API
- Plots original and filtered data using Python scripts

**[See Lab 2 Details](lab-02-moving-average-filter/README.md)**

---

## Lab 3: Traffic Light Controller

### Project Overview

In **Lab 3**, I developed a traffic light simulation system that manages the states of a traffic light, including **RED**, **YELLOW**, **GREEN**, and special periods like **BLINKING YELLOW** and **OFF** during the night. The system also responds to pedestrian requests by changing to the **GREEN** light for pedestrian crossings.

### Key Features:

- Simulates **traffic light state transitions**
- Handles **pedestrian requests** (button press)
- Supports **night period** and **blinking yellow transitions**

**[See Lab 3 Details](lab-03-traffic-light-controller/README.md)**

---

## Building the Projects

For build and run instructions, refer to each lab’s dedicated `README.md` file.

---

Feel free to explore each lab's folder for more detailed documentation and source code.
