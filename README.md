# 💰 Smart Expense Manager (C Project)

---

## 📌 Project Overview

Smart Expense Manager is a console-based application written in **C language** that allows users to:

- Register & Login
- Add expenses
- View expense history
- Set monthly budget
- View basic analytics

The project uses **binary file handling** for persistent data storage.

---

## 🛠 Technologies Used

- C Programming
- File Handling (Binary Files)
- Structures
- Time Library
- Standard I/O

---

## 📂 Project Structure

```
smart-expense-manager/
│
├── src/
│   └── main.c
│
├── data/
│   ├── expenses.dat
│   └── user.dat
│
├── .gitignore
└── README.md
```

---

## 🚀 Features

✔ User Registration & Login  
✔ Add Expenses with Date & Time  
✔ View Expense History  
✔ Monthly Budget Setting  
✔ Basic Expense Analytics  
✔ Binary File Storage  

---

## 🧠 Concepts Used

- Structures
- File Handling (fopen, fread, fwrite)
- Date & Time handling
- Modular Programming
- Menu-driven Console UI

---

## ▶ How to Run

### 🔹 Using GCC

```
gcc src/main.c -o expense
./expense
```

### 🔹 Using CodeBlocks / Dev-C++

1. Open main.c
2. Compile
3. Run

---

## 📊 Sample Output

```
========================================
 SMART EXPENSE MANAGER
========================================
1. Add Expense
2. View Expenses
3. Set Budget
4. Analytics
0. Exit
========================================
Choice:
```

---

## 🔐 Data Storage

- `user.dat` → Stores login credentials
- `expenses.dat` → Stores all expense records

Both are stored in **binary format**.

---

## 🎯 Future Improvements

- Category-wise analytics
- Monthly report generation
- Delete/Edit expense feature
- Password encryption
- GUI version
- Cloud sync version

---

## 👨‍💻 Author

**Your Name**
Computer Engineering Student

---

## ⭐ If you like this project

Give it a star ⭐ on GitHub!
