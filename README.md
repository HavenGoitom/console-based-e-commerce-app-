
# 🛍️ QuickBuy Marketplace (C++ + MySQL)

**QuickBuy** is a terminal-based marketplace system built in **C++** using **MySQL**. It allows buyers and sellers to interact, manage products, and handle checkout operations — all in the command line.
```
Are you:
1. seller
2.buyer
3.exit
````
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



# Team Members

| Name                | ID         |
| ------------------- | ---------- |
| Gelila Melaku       | ETS0618/16 |
| Haleluya Gashawtena | ETS0646/16 |
| Halwa Mohammed      | ETS0647/16 |
| Hana Gadissa        | ETS0653/16 |
| Haven Goitom        | ETS0667/16 |
| Hiwot Anmut         | ETS0721/16 |


## 📜 License

MIT License — see `LICENSE` file.

