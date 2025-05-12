#include <iostream>
#include <string>
#include <iomanip> 

#include <mysql/jdbc.h>

using namespace std;

const string DB_HOST = "tcp://127.0.0.1:3306";
const string DB_USER = "root";
const string DB_PASS = "1621"; 
const string DB_NAME = "quickbuy";

sql::mysql::MySQL_Driver* driver;
sql::Connection* conn = nullptr;

string categories[5] = { "Electronics", "Fashion", "Books", "Beauty", "Groceries" };
string subcategories[5][3] = {
    {"Phones", "Laptops", "TVs"},
    {"Men", "Women", "Kids"},
    {"Fiction", "Non-fiction", "Textbooks"},
    {"Skincare", "Makeup", "Haircare"},
    {"Fruits", "Snacks", "Beverages"}
};

int getInt() {
    int x;
    while (!(cin >> x)) {
        cin.clear(); cin.ignore(10000, '\n');
        cout << "Invalid input. Try again: ";
    }
    cin.ignore();
    return x;
}
string getLine() { string s; getline(cin, s); return s; }
void pause() { cout << "Press Enter to continue..."; cin.get(); }

void connectDB() {
    driver = sql::mysql::get_mysql_driver_instance();
    conn = driver->connect(DB_HOST, DB_USER, DB_PASS);
    conn->setSchema(DB_NAME);
}

int signUp(string type) {
    sql::PreparedStatement* stmt = conn->prepareStatement(
        "INSERT INTO users (full_name, username, password, address, recovery_answer, user_type, cbe_account, telebirr_account) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");

    string name, uname, pass, addr, sec, cbe = "", tele = "";

    cout << "Full Name: "; name = getLine();
    cout << "Username: "; uname = getLine();
    cout << "Address: "; addr = getLine();
    cout << "Password: "; pass = getLine();
    cout << "Security Question - A word you used to mispronounce: "; sec = getLine();

    if (type == "seller") {
        cout << "CBE Account: "; cbe = getLine();
        cout << "Telebirr Account: "; tele = getLine();
    }

    stmt->setString(1, name);
    stmt->setString(2, uname);
    stmt->setString(3, pass);
    stmt->setString(4, addr);
    stmt->setString(5, sec);
    stmt->setString(6, type);
    stmt->setString(7, cbe);
    stmt->setString(8, tele);

    stmt->execute();

    sql::PreparedStatement* query = conn->prepareStatement("SELECT user_id FROM users WHERE username = ?");
    query->setString(1, uname);
    sql::ResultSet* rs = query->executeQuery();
    int id = -1;
    if (rs->next()) id = rs->getInt("user_id");

    cout << type << " registered! Your ID is: " << id << "\n";
    delete stmt;
    delete query;
    delete rs;
    return id;
}

int signIn(string type) {
    cout << "Username: "; string uname = getLine();
    cout << "Password: "; string pass = getLine();

    sql::PreparedStatement* stmt = conn->prepareStatement(
        "SELECT user_id, password, recovery_answer FROM users WHERE username = ? AND user_type = ?");

    stmt->setString(1, uname);
    stmt->setString(2, type);
    sql::ResultSet* rs = stmt->executeQuery();

    if (!rs->next()) {
        cout << "Username not found.\n";
        delete stmt; delete rs;
        return -1;
    }

    if (rs->getString("password") == pass) {
        cout << "Welcome back!\n";
        int id = rs->getInt("user_id");
        delete stmt; delete rs;
        return id;
    }

    cout << "Wrong password. Recovery answer? ";
    string ans = getLine();
    if (rs->getString("recovery_answer") == ans) {
        cout << "Access granted!\n";
        int id = rs->getInt("user_id");
        delete stmt; delete rs;
        return id;
    }

    cout << "Access denied.\n";
    delete stmt; delete rs;
    return -1;
}
void editProfile(int userId) {
    cout << "Update your profile:\n";
    string name, addr, pass, cbe, tele;

    cout << "Full Name: "; name = getLine();
    cout << "Address: "; addr = getLine();
    cout << "New Password: "; pass = getLine();

    sql::PreparedStatement* getType = conn->prepareStatement("SELECT user_type FROM users WHERE user_id = ?");
    getType->setInt(1, userId);
    sql::ResultSet* rs = getType->executeQuery();
    string type;
    if (rs->next()) 
        type = rs->getString("user_type");
    delete rs; delete getType;

    if (type == "seller") {
        cout << "New CBE Account: "; cbe = getLine();
        cout << "New Telebirr Account: "; tele = getLine();
    }

    sql::PreparedStatement* stmt = conn->prepareStatement(
        "UPDATE users SET full_name = ?, address = ?, password = ?, cbe_account = ?, telebirr_account = ? WHERE user_id = ?");

    stmt->setString(1, name);
    stmt->setString(2, addr);
    stmt->setString(3, pass);
    stmt->setString(4, type == "seller" ? cbe : "");
    stmt->setString(5, type == "seller" ? tele : "");
    stmt->setInt(6, userId);
    stmt->execute();
    delete stmt;

    cout << "Profile updated successfully.\n";
}
void deleteProduct(int sellerId) {
    cout << "Enter Product ID to delete: ";
    int pid = getInt();

    sql::PreparedStatement* stmt = conn->prepareStatement(
        "DELETE FROM products WHERE product_id = ? AND seller_id = ?");
    stmt->setInt(1, pid);
    stmt->setInt(2, sellerId);

    int affected = stmt->executeUpdate();
    delete stmt;

    if (affected > 0) cout << "Product deleted.\n";
    else cout << "Product not found or not owned by you.\n";
}
void updateProduct(int sellerId) {
    cout << "Enter Product ID to update: ";
    int pid = getInt();

    sql::PreparedStatement* check = conn->prepareStatement(
        "SELECT * FROM products WHERE product_id = ? AND seller_id = ?");
    check->setInt(1, pid);
    check->setInt(2, sellerId);
    sql::ResultSet* rs = check->executeQuery();

    if (!rs->next()) {
        cout << "Product not found or not owned by you.\n";
        delete rs; delete check;
        return;
    }

    delete rs; delete check;

    string name, desc;
    float price;
    int stock;

    cout << "New Product Name: "; name = getLine();
    cout << "New Description: "; desc = getLine();
    cout << "New Price: "; cin >> price; cin.ignore();
    cout << "New Stock: "; cin >> stock; cin.ignore();

    sql::PreparedStatement* stmt = conn->prepareStatement(
        "UPDATE products SET name = ?, description = ?, price = ?, stock = ? WHERE product_id = ?");

    stmt->setString(1, name);
    stmt->setString(2, desc);
    stmt->setDouble(3, price);
    stmt->setInt(4, stock);
    stmt->setInt(5, pid);
    stmt->execute();
    delete stmt;

    cout << "Product updated successfully.\n";
}



int selectCategory() {
    cout << "Choose Category:\n";
    for (int i = 0; i < 5; ++i)
        cout << i + 1 << ". " << categories[i] << "\n";
    int c = getInt();
    return c - 1;
}

int selectSubcategory(int catIndex) {
    cout << "Choose Subcategory:\n";
    for (int j = 0; j < 3; ++j)
        cout << j + 1 << ". " << subcategories[catIndex][j] << "\n";
    int s = getInt();
    return s - 1;
}


void addProduct(int sellerId) {
    string name, desc;
    float price;
    int stock;

    cout << "Product Name: "; name = getLine();
    int catIdx = selectCategory();
    int subIdx = selectSubcategory(catIdx);
    cout << "Description: "; desc = getLine();
    cout << "Price: "; cin >> price; cin.ignore();
    cout << "Stock: "; cin >> stock; cin.ignore();

    sql::PreparedStatement* stmt = conn->prepareStatement(
        "INSERT INTO products (name, description, price, stock, seller_id, category, subcategory) VALUES (?, ?, ?, ?, ?, ?, ?)");

    stmt->setString(1, name);
    stmt->setString(2, desc);
    stmt->setDouble(3, price);
    stmt->setInt(4, stock);
    stmt->setInt(5, sellerId);
    stmt->setString(6, categories[catIdx]);
    stmt->setString(7, subcategories[catIdx][subIdx]);
    stmt->execute();

    cout << "Product added successfully.\n";
    delete stmt;
}

void viewAllProducts() {
    sql::Statement* stmt = conn->createStatement();
    sql::ResultSet* rs = stmt->executeQuery(
        "SELECT p.product_id, p.name, p.category, p.subcategory, p.price, p.stock, u.full_name "
        "FROM products p JOIN users u ON p.seller_id = u.user_id");


    cout << "\n" << setw(5) << "ID"
        << setw(15) << "Name"
        << setw(15) << "Category"
        << setw(15) << "Subcategory"
        << setw(10) << "Price"
        << setw(10) << "Stock"
        << setw(20) << "Seller" << "\n";

    cout << string(90, '-') << "\n";

    while (rs->next()) {
        cout << setw(5) << rs->getInt("product_id")
            << setw(15) << rs->getString("name")
            << setw(15) << rs->getString("category")
            << setw(15) << rs->getString("subcategory")
            << setw(10) << fixed << setprecision(2) << rs->getDouble("price")
            << setw(10) << rs->getInt("stock")
            << setw(20) << rs->getString("full_name") << "\n";
    }

    delete rs;
    delete stmt;
}

void addToCart(int buyerId) {
    cout << "Enter Product ID: ";
    int pid = getInt();
    cout << "Enter Quantity: ";
    int qty = getInt();

    sql::PreparedStatement* stmt = conn->prepareStatement(
        "INSERT INTO cart_items (buyer_id, product_id, quantity) VALUES (?, ?, ?)");
    stmt->setInt(1, buyerId);
    stmt->setInt(2, pid);
    stmt->setInt(3, qty);
    stmt->execute();
    delete stmt;

    cout << "Product added to cart.\n";
}

void viewCart(int buyerId) {
    sql::PreparedStatement* stmt = conn->prepareStatement(
        "SELECT ci.product_id, p.name, p.price, ci.quantity, p.stock, p.seller_id, u.full_name, u.cbe_account, u.telebirr_account "
        "FROM cart_items ci "
        "JOIN products p ON ci.product_id = p.product_id "
        "JOIN users u ON p.seller_id = u.user_id "
        "WHERE ci.buyer_id = ?");

    stmt->setInt(1, buyerId);
    sql::ResultSet* rs = stmt->executeQuery();

    double total = 0;
    struct CartItem {
        int product_id, quantity, stock, seller_id;
        double price;
    };

    CartItem cart[50];  // fixed-size array
    int cartSize = 0;

    int i = 1;
    cout << "\n===== Your Cart =====\n";
    while (rs->next() && cartSize < 50) {
        string name = rs->getString("name");
        double price = rs->getDouble("price") * 1.15;  // Apply 15% markup
        int qty = rs->getInt("quantity");
        int stock = rs->getInt("stock");

        double itemTotal = price * qty;
        total += itemTotal;

        cart[cartSize++] = {
            rs->getInt("product_id"),
            qty,
            stock,
            rs->getInt("seller_id"),
            price
        };

        cout << i++ << ". " << name << " x" << qty << " = " << fixed << setprecision(2)
            << itemTotal << " birr (incl. 15%)\n";
        cout << "   Seller: " << rs->getString("full_name") << "\n";
        cout << "   CBE Account: " << rs->getString("cbe_account") << "\n";
        cout << "   Telebirr Account: " << rs->getString("telebirr_account") << "\n\n";
    }

    delete rs;
    delete stmt;

    if (cartSize == 0) {
        cout << "Your cart is empty.\n";
        return;
    }

    cout << "Total: " << fixed << setprecision(2) << total << " birr\n";
    cout << "Enter payment method (CBE, Telebirr, etc.): ";
    string paymentMethod = getLine();

    cout << "Proceed to checkout? (1 = Yes, 0 = No): ";
    int confirm = getInt();

    if (confirm == 1) {
        for (int i = 0; i < cartSize; ++i) {
            CartItem& item = cart[i];

            // 1. Deduct stock
            sql::PreparedStatement* updateStock = conn->prepareStatement(
                "UPDATE products SET stock = ? WHERE product_id = ?");
            updateStock->setInt(1, item.stock - item.quantity);
            updateStock->setInt(2, item.product_id);
            updateStock->execute();
            delete updateStock;

            // 2. Insert into orders table
            sql::PreparedStatement* insertOrder = conn->prepareStatement(
                "INSERT INTO orders (buyer_id, product_id, seller_id, quantity, payment_method, paid) "
                "VALUES (?, ?, ?, ?, ?, TRUE)");
            insertOrder->setInt(1, buyerId);
            insertOrder->setInt(2, item.product_id);
            insertOrder->setInt(3, item.seller_id);
            insertOrder->setInt(4, item.quantity);
            insertOrder->setString(5, paymentMethod);
            insertOrder->execute();
            delete insertOrder;
        }

        // 3. Clear cart
        sql::PreparedStatement* clearCart = conn->prepareStatement(
            "DELETE FROM cart_items WHERE buyer_id = ?");
        clearCart->setInt(1, buyerId);
        clearCart->execute();
        delete clearCart;

        cout << "Checkout complete. Your order has been placed.\n";
    }
}


void sellerMenu(int sellerId) {
    int ch;
    do {
        cout << "\n-- Seller Menu --\n"
            << "1. Add Product\n"
            << "2. View Products\n"
            << "3. Update Product\n"
            << "4. Delete Product\n"
            << "5. Edit Profile\n"
            << "0. Logout\n"
            << "Choice: ";
        ch = getInt();

        if (ch == 1) addProduct(sellerId);
        else if (ch == 2) viewAllProducts();
        else if (ch == 3) updateProduct(sellerId);
        else if (ch == 4) deleteProduct(sellerId);
        else if (ch == 5) editProfile(sellerId);
    } while (ch != 0);
}

void buyerMenu(int buyerId) {
    int ch;
    do {
        cout << "\n-- Buyer Menu --\n"
            << "1. View All Products\n"
            << "2. Add to Cart\n"
            << "3. View Cart\n"
            << "4. Edit Profile\n"
            << "0. Logout\n"
            << "Choice: ";
        ch = getInt();

        if (ch == 1) viewAllProducts();
        else if (ch == 2) addToCart(buyerId);
        else if (ch == 3) viewCart(buyerId);
        else if (ch == 4) editProfile(buyerId);
    } while (ch != 0);
}


int main() {
    connectDB();

    while (true) {
        cout << "\n=== QuickBuy Marketplace ===\n1. Seller\n2. Buyer\n0. Exit\nChoice: ";
        int role = getInt();
        if (role == 0) break;

        cout << "1. Sign Up\n2. Sign In\nChoice: ";
        int action = getInt();
        int id = -1;

        if (role == 1) id = (action == 1) ? signUp("seller") : signIn("seller");
        else if (role == 2) id = (action == 1) ? signUp("buyer") : signIn("buyer");

        if (id != -1) {
            if (role == 1) sellerMenu(id);
            else if (role == 2) buyerMenu(id);
        }

        pause();
    }

    cout << "Goodbye!\n";
    return 0;
}
