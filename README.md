# Console‑Commerce 🛒💻

A simple console‑based e‑commerce application written in C++ with MySQL integration, featuring user authentication and role‑based shopping (buyer/seller). 🔐🛍️
## 🧐 Overview

**Console‑Commerce** is a terminal‑based application that simulates a simple e‑commerce platform. Users can register, log in, choose to operate as a buyer or a seller, and then perform actions appropriate to their role—all through a text menu interface. 🎛️

This project is ideal for learning:  
- basic C++ class design & MySQL connectivity 🏷️  
- user authentication (login/logout) 🔑  
- role‑based menus and workflows 📊  

---

## ✨ Features

- **User Authentication** 🔐  
  - Sign up with username & password  
  - Secure login and logout  
- **Role Selection** 🎭  
  - Choose to act as **Buyer** or **Seller** each session  
- **Buyer Workflow** 🛍️  
  - Browse available products  
  - Place orders  
  - View order history  
- **Seller Workflow** 🏷️  
  - Add new products  
  - Update inventory  
  - View sales history  

---

## 🛠️ Prerequisites

- **C++17** compatible compiler (e.g. g++)  
- **MySQL** server & client libraries  
- **CMake** (optional, if using CMake build)  
- Basic familiarity with console applications  

---

## 🚀 Installation

1. **Clone the repository**  
   ```bash
   git clone https://github.com/your‑username/console‑commerce.git
   cd console‑commerce
````

2. **Configure MySQL**

   * Create database and user:

     ```sql
     CREATE DATABASE console_commerce;
     CREATE USER 'commerce_user'@'localhost' IDENTIFIED BY 'password';
     GRANT ALL PRIVILEGES ON console_commerce.* TO 'commerce_user'@'localhost';
     FLUSH PRIVILEGES;
     ```
   * Import schema:

     ```bash
     mysql -u commerce_user -p console_commerce < schema.sql
     ```

3. **Build the app**

   * With CMake:

     ```bash
     mkdir build && cd build
     cmake ..
     make
     ```
   * Or directly with g++:

     ```bash
     g++ ../src/*.cpp -o console_commerce -lmysqlclient -std=c++17
     ```

---

## 🎮 Usage

### Running the App

```bash
./console_commerce
```

---

### User Flow

#### 🔐 Sign Up / Login / Logout

1. **Start** the app—presented with a welcome menu.
2. **Register** a new account or **Login** with existing credentials.
3. Once authenticated, you can **Logout** at any time to return to the welcome menu. 🔄

#### 🎭 Choose Role: Buyer or Seller

After login, select your role:

```
1) Buyer 🛒
2) Seller 🏷️
3) Logout 🚪
```

---

#### 🛒 Buyer Actions

* **View Products**: Lists all items for sale. 📃
* **Purchase Product**: Enter product ID and quantity to buy. 💳
* **Order History**: View past purchases. 📜

#### 🏷️ Seller Actions

* **Add Product**: Provide name, description, price, and stock. ➕
* **Update Product**: Change price or stock for existing items. 🔄
* **View Sales**: See all orders placed for your products. 📈

---

## 📁 Project Structure

```
.
├── src/                # C++ source files
│   ├── main.cpp        # Entry point
│   ├── models/         # User, Product, Order classes
│   ├── db/             # MySQL connection & queries
│   └── utils/          # Helper functions (input validation, etc.)
├── include/            # Header files
├── sql/                # schema.sql, seed data
├── build/              # CMake build directory
├── tests/              # Unit tests
└── README.md           # This file
```

---

## 🤝 Extending & Contributing

1. **Fork** this repository 🍴
2. **Create** a feature branch:

   ```bash
   git checkout -b feature/awesome‑feature
   ```
3. **Commit** your changes:

   ```bash
   git commit -m "Add awesome feature"
   ```
4. **Push**:

   ```bash
   git push origin feature/awesome‑feature
   ```
5. **Open** a Pull Request 🔃

---

## 📜 License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details. 📖

---

## 📬 Contact

Developed by 
Questions? Feedback? Open an issue or discussion on GitHub! 🗨️

```
```
