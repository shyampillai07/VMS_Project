
# Karnataka State Voter Management System (VMS)

**Version:** 3.0 (Stable)
**Author:** Shyam Pillai
**Course:** MCA – 1st Semester
**Case Study:** C Programming Case Study
**Institution:** VTU CPGS, Mysuru
**Organization (Case Study):** Karnataka State Election Commission (SEC)
**Programming Language:** C (Standard C99/C11)

---

## 1. Project Overview

The **Karnataka State Voter Management System (VMS)** is a console-based C application developed as part of the **C Programming Case Study** under **VTU CPGS, Mysuru**.

The project simulates a real-world voter registration and election data management system for the Karnataka State Election Commission. It focuses on structured programming concepts, file handling, data validation, and analytical processing using the C language.

The system provides a reliable solution for managing voter records, enforcing age eligibility rules, preventing duplicate voting, and generating election-related statistics using persistent CSV-based storage.

---

## 2. Key Features

### Core Functionalities

* **Voter Registration:** Secure manual entry of voter details with input validation.
* **Automated Age Verification:** Age is calculated automatically from Date of Birth (DOB) and eligibility is restricted to voters aged 18 and above.
* **Unique Voter ID Generation:** System-generated unique alphanumeric Voter IDs (e.g., `KA-SEC-1001`) ensure record uniqueness.
* **Persistent Storage:** Voter data is stored in a CSV file (`sec_database.csv`) and retained across program executions.

### Advanced Modules

* **Bulk Data Generator:** Generates 250+ realistic voter records with Karnataka-based names and addresses for testing and analytics.
* **Election Analytics Engine:** Produces detailed reports including:

  * Voter turnout percentage
  * Age group distribution (Youth, Adult, Senior)
  * Gender ratio analysis
* **Polling Station Mode:** Marks voters as *Voted* and prevents multiple voting attempts.
* **Administrative Controls:** Supports database reset and individual record deletion.

---

## 3. Technical Specifications

* **Programming Language:** C
* **C Standard:** C99 / C11
* **Libraries Used:**

  * `stdio.h`
  * `stdlib.h`
  * `string.h`
  * `time.h`
  * `ctype.h`
* **Data Storage:** CSV-based flat file system
* **User Interface:** Command Line Interface (CLI)

### Time Complexity

* **Search Operations:** O(N)
* **Analytics Computation:** O(N)
* **Record Insertion:** O(1)

---

## 4. Installation and Execution

### Prerequisites

* GCC Compiler (MinGW on Windows or GCC on Linux/macOS)
* Any standard C development environment (VS Code, Code::Blocks, Dev-C++, or Terminal)

### Build Instructions

#### Windows (Command Prompt / PowerShell)

```bash
gcc vms_final.c -o vms_final.exe
vms_final.exe
```

#### Linux / macOS (Terminal)

```bash
gcc vms_final.c -o vms_final
./vms_final
```

---

## 5. Usage Guide

When the application starts, it automatically loads existing voter data from `sec_database.csv`. The main menu provides the following options:

1. **Register New Voter**
   Input Name, Father’s Name, Gender, Date of Birth, and Address. The system calculates age and validates eligibility.

2. **Generate Sample Data**
   Generates a user-defined number of dummy voter records for testing and performance evaluation.

3. **Cast Vote**
   Marks a voter as having voted using their Voter ID. Duplicate voting is strictly blocked.

4. **Election Analytics**
   Displays real-time election statistics and demographic insights.

5. **Reset Database**
   Deletes all voter records permanently. Intended for administrative or testing purposes only.

---

## 6. Project Structure

```
/Project_Root
│
├── vms.c                # Main C source code
├── sec_database.csv     # CSV database (auto-created)
├── README.md            # Project documentation
└── vms.exe              # Compiled executable (Windows)
```

---

## 7. Learning Outcomes

This case study demonstrates practical application of:

* Structured programming in C
* File handling using CSV
* String manipulation and validation
* Modular program design
* Real-world system simulation using CLI

---

## 8. Future Enhancements

* Migration from CSV to binary file handling for improved security
* Implementation of optimized search algorithms
* Integration with a SQL-based backend for large-scale voter data
* Role-based access control for administrative functions

---

## 9. Academic Declaration

This project is developed as part of the **C Programming Case Study** for **MCA 1st Semester** at **VTU CPGS, Mysuru**, and is intended strictly for academic and educational purposes.

---

**Confidentiality Notice:**
This software is a simulated prototype created solely for academic case study evaluation and does not represent an official election system.

---
