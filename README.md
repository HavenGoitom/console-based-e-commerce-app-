````markdown
# 🛍️ QuickBuy Marketplace (C++ + MySQL)

Welcome to **QuickBuy**, a terminal-based e-commerce marketplace built with **C++** and **MySQL**! This project simulates a simple multi-user system where buyers and sellers can interact — from managing products to purchasing with checkout and cart support.

---

## 🚀 Features

- 👥 **User System**
  - Separate login/sign-up for `buyers` and `sellers`
  - Profile editing with password and account updates

- 🛒 **Buyers**
  - Browse all products with formatted output
  - Add products to cart, view cart contents
  - Proceed to checkout with stock update
  - View seller’s **CBE** and **Telebirr** account for payment

- 🧑‍💼 **Sellers**
  - Add, view, update, and delete their own products
  - Manage inventory
  - Edit profile, including payment accounts

- 💾 **MySQL Database Integration**
  - All data is persistent using `MySQL Connector/C++`
  - Uses parameterized queries to prevent SQL injection

---

## ⚙️ Tech Stack

- 🧠 Language: **C++**
- 🗄️ Database: **MySQL**
- 🔌 Connector: `mysql/jdbc.h` (MySQL Connector/C++)

---

## 📦 Setup Instructions

### 1. 📥 Clone the Repository
```bash
git clone https://github.com/your-username/quickbuy.git
cd quickbuy
````

### 2. 🛠️ Compile

```bash
g++ -std=c++17 quickbuy.cpp -o quickbuy -lmysqlcppconn
```

> Make sure `libmysqlcppconn` is installed. On Ubuntu:
>
> ```bash
> sudo apt install libmysqlcppconn-dev
> ```

### 3. 🧱 Set Up the Database

* Open **MySQL CLI** or any SQL client (e.g. phpMyAdmin)
* Paste and execute the schema from `schema.sql` or:

```sql
-- Provided in the /docs or see README.md below
```

### 4. 🚀 Run

```bash
./quickbuy
```

---

## 📌 TODO / Future Ideas

* 🧾 Add order history tracking
* 🔎 Add product search & filter
* 📦 Save cart across sessions
* 📤 Upload product images (via future web version)

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
