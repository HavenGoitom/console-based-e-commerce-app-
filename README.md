````markdown
# 🛍️ QuickBuy Marketplace (C++ + MySQL)

**QuickBuy** is a terminal-based marketplace system built in **C++17** using **MySQL**. It allows buyers and sellers to interact, manage products, and handle checkout operations — all in the command line.

---

## 🚀 Features

- 👤 Sign up / log in as **buyer** or **seller**
- 🛍️ Buyers can:
  - Browse and search products
  - Add to cart and checkout
  - View seller’s CBE / Telebirr accounts
- 🧑‍💼 Sellers can:
  - Add, update, delete products
  - Edit their profile & payment info
- 💽 All data is stored in **MySQL**, using safe prepared statements

---

## ⚙️ Tech Stack

- 💻 C++17
- 🗄️ MySQL
- 🔌 MySQL Connector/C++

---

## 🧰 Setup Instructions

### 1. 📦 Clone the repo

```bash
git clone https://github.com/your-username/quickbuy.git
cd quickbuy
````

### 2. 🛠️ Compile

```bash
g++ -std=c++17 quickbuy.cpp -o quickbuy -lmysqlcppconn
```

### 3. 🧱 Setup MySQL

Run the SQL script located in:

```
/database/quickbuy.sql
```

### 4. 🚀 Run the app

```bash
./quickbuy
```

---

## 📂 Project Structure

| File / Folder  | Description          |
| -------------- | -------------------- |
| `quickbuy.cpp` | Main C++ source file |
| `database/`    | SQL schema setup     |
| `README.md`    | This file            |

---

## 📌 Roadmap

* 🧾 Order history
* 🔍 Product search
* 🛒 Persistent carts
* 🖼️ Image upload (future UI)

---

## 📜 License

MIT License — see `LICENSE` file.

```


```
