# 🎓 Student Progress Tracker (C++ / FLTK)

> A robust, self-contained desktop application for tracking academic performance, built with modern C++ and the FLTK GUI toolkit.

![Project Status](https://img.shields.io/badge/status-active-success.svg)
![C++](https://img.shields.io/badge/C++-17-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

## 📖 Overview

The **Student Progress Tracker** is an Object-Oriented C++ application designed to bridge the gap between teachers and students. It provides a secure, local environment where:
* **Teachers** can manage student rosters, create subjects, and record detailed assessments (grades & feedback).
* **Students** can visualize their academic growth through interactive charts and review feedback.

The project emphasizes clean **OOP Architecture** (Polymorphism, Composition, Aggregation), **Data Persistence** (custom file-based database), and **Zero-Dependency Deployment** (FLTK is fetched automatically).

---

## ✨ Key Features

### 👨‍🏫 For Teachers
* **Roster Management:** Add new students dynamically via the dashboard.
* **Subject Management:** Create global subjects (e.g., "Mathematics", "Computer Science") available for assignment.
* **Assessment Tracking:**
    * Record grades, total marks, and qualitative feedback.
    * **Update Capability:** Correct mistakes in previous assessments easily.
* **Data Isolation:** Multiple teachers can teach the same subject name to the same student without data collision. (e.g., *Math (Mr. Smith)* vs *Math (Ms. Doe)*).

### 👨‍🎓 For Students
* **Visual Dashboard:** View performance bar charts for every enrolled subject.
* **Feedback View:** Read detailed comments from teachers for specific assignments.
* **GPA/Average Calculation:** Real-time calculation of overall performance percentages.

### 🛠 Technical Highlights
* **Self-Contained Database:** Uses a structured file system (`data/` folder) instead of SQL, making it portable and easy to debug.
* **Modern CMake Build:** Uses `FetchContent` to download and compile FLTK on the fly—no manual library installation required.
* **Robust Error Handling:** Safe inputs for numerical fields and corruption-resistant file loading.

---

## 🏗️ System Architecture

![System Architecture UML]((https://www.plantuml.com/plantuml/svg/lLXFSzk-4RtpKs3IcLyaHNBJgyVLHF4VHpEAxB6KoVJaWSWrXHe4E00OrKtJpzwbk10eagAT7dw-YCG-B7RtFIm8VxAE6rTaChBFGkNSy8p5abixSyw8JU5W7ckr4ly6zh46aKA1Uyc1QUEsEdB2IM0hLoIW7BitEZLWBLiR7Z-3OHDs8nINR6RYhN0Gky905Bt_-yc_w3rZbtSFr-ngjfwnnTtj_B8N7l6DTRYOgs9dzs2iLkndnF3lBqpn3DWvGuXGAOr1neLi3kOuUQTDqXmNvOXGRl_wWTmFHB8V7E_z-ndZodDuzJxzo92SfE3coM3e7Vkn9Vh2KOyEXklIRQVbdbPe6otvgmTOWdveaNY8znp2xWA5HSfyJi1-UXf-iKJONFANkNhIWmFgLnHL_Coi1MipK8uuch1AGjun3TfOctBmIMhkF50xBhzoysmRXYU0P8E2Qpf9k8DcOK800nUeikHmp5nsU7mAzYuErnXtDs4h3Bwo-2Zzb4C6NTORIgFJvnLtqAq1C34enzFsYjQ7ujDhaLkFo6MdK26oGqdQpAwApJyX3hIsjnuoo0r6V6juqk8MUBm5Cwzjjp2wx7353ppQCXHSMPkBGEwKWgUe1YfmMGKH29_xpUoMzStoXesv3kbqiaqv-RtUDftq7191fVJbnvEafcX-7lGTQEpmEbSEZE9o85G2_yBWAdW0Z6XMp6LSIEvWzWCCJxloL6Xmi2goZ9kNUZP16dGyU6dOYfGQSKJJQEhPhLP3RJzfat4LGsDPSlaRdRX9x7-zYs4efLSBWdr4xIgI9H3JYl_ridLsIJ8XAi7Tpc-Cpcw4XARTOd5A-reVMKEvILoXt5MYzN9N8pvSF-F_hIOLZ-g9Dk-_NJooKF6weq7t8bLrBWWmBfLpaXe3iJPXDxHdBe-IwjihHLuU7Mzs9P9g2ushOokqbhAv7jxyATLzX9uwDr__M5gk7-uMY-i7zWVxjfulvkj_zCuXaPJQ-SeLJy6mYujlJaZXNgPJzjEVwDPn9-9VUxdDf2mLDw1-R0_KaN16q_51PIrQqPPAlU4IUGlMgWPJdsbprN8J_4chJcgvvbAKP8Tp7wJ8X0Dppk8jDqFMz1GyX6gjq23XjUqmEKxsU5BEtHQ58oJO5-iWEpylHuOi-EfSs7ScofnUMzbtpQMQsfvg3skVSNcEggbYTbfvtOGZsxBs_DVR4I6EmpzLSwbJeRuBbUWTGXRXRNGSoXMtMmIimzj6SvECZiCX58KIK4rX2cKTdKTO16_6ny7XOAc_c4Bvqx_HtWVjpwmYtsVHicprhXdzm1qo6dN0csdqD6K3gR0EJBzUgSVVrfdfkroau0AMJiisZrIGL1VkTthUxRSvzhslztVBw-MQNIvcgzNrwYrDhoQIWs1tNa4tyl58FzMnDrTvuIhh_j4R_UMkPbz1RC3LO4633pmHka8zw48bZvyBvxHgQB0VrRUr_dXrRn7aGxq60zVXQSnin-HXJLnDVMv50eFJlGsNUumtWnrLE4cXF4H_LF1cJyoDZi7QnZxmVQUrYGyineKne1pPMTWS7InVwM8ZWSXkKB0GbjZyeYKIOFJEafVmuNgvrIA62bOzZrgtaZTWgXjaMs3X1bmttaZDWxZ2XRWF4gx6frRXiHDQVNQgif7WYDZUfjCf25fKIBaAzMoQ3JmPi5lg33s8y07M1WM9KGwbnixEpeOjQv8y4hcFiHJnSn-G2Eu51W8Hj-KgXLD0yjP0jUv59zLCzd0ilLdDjFAQRso5AfyyhJs7Go-jiO7zHS-x7XnzZO-P_mX-eTyT_MxtloVOe_OVYlDgzt-uNipMyxlbwilylh_h8tgkKAnYVs97zB_1Y_zC9bx6zJ5VWtBQfSvoROKJQ1kidD4gPNSxXU2jo8UH9sQ4izvzF3iRlVDbm2JrJbasZMYWZWbwHbYibUDY3yK5Psbg8ENLWj-1FxC7U0836FSmybrD1rT16jd-8zwxoNECNM70KkA4AyX18IuMO2EqLS7yxLtz4AYx21XS1M6jTjk3fOXEOqFqtgylLi8TRuF8OGE4IT9b9MJtifzwTZQjtsfmNc5zNSelXlt_FAfUOQDw0Sg9fGFaX4jfzzeFQKoZLXKQ4qZ2V_LVKZWb5ADt2YBRtYUJQQr06B1bMhLy4Z0KYUwFPSAVi2n59ly7))


The project follows a strict **Model-View-Controller (MVC)** pattern adapted for desktop GUI.

### 1. The Model (Logic Layer)
* **`Person` (Abstract Base):** Defines common attributes (ID, Name, Email).
* **`Teacher` / `Student`:** Derived classes implementing specific roles.
* **`Subject`:** Contains assessments. It is **owned** by a Student but linked to a specific Teacher ID for data integrity.
* **`Assessment`:** Stores individual grade data.

### 2. The Controller (App Logic)
* **`App` Class:** A Singleton controller that orchestrates the application lifecycle. It owns the master data vectors and manages screen switching.
* **`FileManager`:** A static utility class that handles serialization/deserialization of data into the custom directory structure.

### 3. The View (GUI Layer)
* **`LoginWindow`:** Entry point validation.
* **`TeacherDashboard`:** Complex UI with Dropdowns (`Fl_Choice`), Popups (`Fl_Window`), and Browsers (`Fl_Hold_Browser`).
* **`StudentDashboard`:** Read-only view with `Fl_Tabs` and `Fl_Chart`.

---

## 📂 Data Storage Structure

The application acts as its own database engine. Data is stored in plain text for transparency:

```text
ProjectRoot/
└── data/
    ├── subjects.txt        # List of all available subjects
    ├── teachers.txt        # Credentials for all teachers
    └── students/           # Individual student records
        ├── 2001.txt        # Data for Student ID 2001
        ├── 2002.txt        # Data for Student ID 2002
        └── ...
```

*Note: The `data` folder is automatically created upon the first run.*

---

## 🚀 Getting Started

### Prerequisites
* **C++ Compiler:** GCC, Clang, or MSVC supporting **C++17**.
* **CMake:** Version 3.15 or higher.
* **Git:** To clone the repository.

### Installation & Build

1.  **Clone the Repository**
    ```bash
    git clone [https://github.com/yourusername/StudentProgressTracker.git](https://github.com/yourusername/StudentProgressTracker.git)
    cd StudentProgressTracker
    ```

2.  **Build with CMake**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
    *Note: The first build may take a few minutes as it downloads FLTK from GitHub.*

3.  **Run the Application**
    * **Windows:** `StudentProgressTracker.exe`
    * **Linux/Mac:** `./StudentProgressTracker`

---

## 🕹️ Usage Guide

### First Login (Default Admin)
When you run the app for the first time, a default teacher account is created:
* **Email:** `admin@school.com`
* **Password:** `password`

### Workflow
1.  **Log in** as the Admin Teacher.
2.  Click **"+ Add Student"** to register a new student (e.g., Alice).
3.  Click **"+ Create Subject"** to add a subject (e.g., "Physics").
4.  Select **Alice** from the list.
5.  Select **Physics** from the dropdown.
6.  Select **"Create New..."** in the assessment dropdown.
7.  Enter Title, Score, and Feedback, then click **Add Assessment**.
8.  **Logout** and log in as Alice (using the credentials you just created) to see the chart!
---

*Built with ❤️ using C++ and FLTK by Basil Saeed & Jaweria*
