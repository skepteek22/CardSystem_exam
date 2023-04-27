#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <ctime>
#include <algorithm>

using namespace std;


class Wallet {
private:
    string name;
    double balance;

public:
    Wallet(string name, double balance) {
        this->name = name;
        this->balance = balance;
    }

    void add_balance(double amount) {
        balance += amount;
    }

    void subtract_balance(double amount) {
        if (balance - amount >= 0) {
            balance -= amount;
        }
        else {
            cout << "Not enough money on your balance " << name << endl;
        }
    }

    double get_balance() {
        return balance;
    }

    string get_name() {
        return name;
    }
};


class Card {
private:
    string name;
    double balance;
    string type;

public:
    Card(string name, double balance, string type) {
        this->name = name;
        this->balance = balance;
        this->type = type;
    }

    void add_balance(double amount) {
        balance += amount;
    }

    void subtract_balance(double amount) {
        if (balance - amount >= 0) {
            balance -= amount;
        }
        else {
            cout << "Not enough money on your balance " << name << endl;
        }
    }

    double get_balance() {
        return balance;
    }

    string get_name() {
        return name;
    }

    string get_type() {
        return type;
    }
};


class Expense {
private:
    double amount;
    string category;
    time_t timestamp;

public:
    Expense(double amount, string category) {
        this->amount = amount;
        this->category = category;
        this->timestamp = time(nullptr);
    }

    double get_amount() {
        return amount;
    }

    string get_category() {
        return category;
    }

    time_t get_timestamp() {
        return timestamp;
    }
};


class PersonalFinanceManager {
private:
    vector<Wallet> wallets;
    vector<Card> cards;
    vector<Expense> expenses;

public:
    void add_wallet(Wallet wallet) {
        wallets.push_back(wallet);
    }

    void add_card(Card card) {
        cards.push_back(card);
    }

    void add_expense(Expense expense) {
        expenses.push_back(expense);
    }

    void show_wallets() {
        cout << "Wallets:" << endl;
        for (auto wallet : wallets) {
            cout << wallet.get_name() << " - " << wallet.get_balance() << endl;
        }
    }

    void show_cards() {
        cout << "Cards:" << endl;
        for (auto card : cards) {
            cout << card.get_name() << " (" << card.get_type() << ") - " << card.get_balance() << endl;
        }
    }

    void show_expenses(time_t start_timestamp, time_t end_timestamp) {
        cout << "Expenses:" << endl;
        double total_amount = 0;
        map<string, double> category_amounts;
        for (auto expense : expenses) {
            if (expense.get_timestamp() >= start_timestamp && expense.get_timestamp() <= end_timestamp) {
                cout << expense.get_category() << " - " << expense.get_amount() << endl;
                total_amount += expense.get_amount();
                category_amounts[expense.get_category()] += expense.get_amount();
            }
        }
        cout << "Total: " << total_amount << endl;
        cout << "By categories:" << endl;
        for (auto pair : category_amounts) {
            cout << pair.first << " - " << pair.second << endl;
        }
    }

    void show_top_expenses(time_t start_timestamp, time_t end_timestamp, string period) {
        map<string, double> category_amounts;
        for (auto expense : expenses) {
            if (expense.get_timestamp() >= start_timestamp && expense.get_timestamp() <= end_timestamp) {
                category_amounts[expense.get_category()] += expense.get_amount();
            }
        }
        vector<pair<string, double>> sorted_category_amounts(category_amounts.begin(), category_amounts.end());
        sort(sorted_category_amounts.begin(), sorted_category_amounts.end(), [](auto& left, auto& right) {
            return left.second > right.second;
            });
        if (period == "week") {
            cout << "TOP-3 expenses for a week:" << endl;
        }
        else if (period == "month") {
            cout << "TOP-3 expenses for a month:" << endl;
        }
        int count = 0;
        for (auto pair : sorted_category_amounts) {
            cout << pair.first << " - " << pair.second << endl;
            count++;
            if (count == 3) {
                break;
            }
        }
    }

    void show_top_categories(time_t start_timestamp, time_t end_timestamp, string period) {
        map<string, double> category_amounts;
        for (auto expense : expenses) {
            if (expense.get_timestamp() >= start_timestamp && expense.get_timestamp() <= end_timestamp) {
                category_amounts[expense.get_category()] += expense.get_amount();
            }
        }
        vector<pair<string, double>> sorted_category_amounts(category_amounts.begin(), category_amounts.end());
        sort(sorted_category_amounts.begin(), sorted_category_amounts.end(), [](auto& left, auto& right) {
            return left.second > right.second;
            });
        if (period == "week") {
            cout << "TOP-3 categories for a week:" << endl;
        }
        else if (period == "month") {
            cout << "TOP-3 categories for a month:" << endl;
        }
        int count = 0;
        for (auto pair : sorted_category_amounts) {
            cout << pair.first << " - " << pair.second << endl;
            count++;
            if (count == 3) {
                break;
            }
        }
    }

    void save_report(string filename, time_t start_timestamp, time_t end_timestamp) {
        ofstream file(filename);
        file << "Cost report:" << endl;
        file << "Period: " << ctime(&start_timestamp) << " - " << ctime(&end_timestamp) << endl;
        file << endl;
        double total_amount = 0;
        map<string, double> category_amounts;
        for (auto expense : expenses) {
            if (expense.get_timestamp() >= start_timestamp && expense.get_timestamp() <= end_timestamp) {
                file << expense.get_category() << " - " << expense.get_amount() << endl;
                total_amount += expense.get_amount();
                category_amounts[expense.get_category()] += expense.get_amount();
            }
        }
        file << endl;
        file << "Total: " << total_amount << endl;
        file << "By categories:" << endl;
        for (auto pair : category_amounts) {
            file << pair.first << " - " << pair.second << endl;
        }
        file.close();
    }
};

int main()
{
    Wallet wallet1("Wallet 1", 1000);
    Wallet wallet2("Wallet 2", 500);

    Card card1("Wallet 1", 2000, "Debet");
    Card card2("Wallet 2", 5000, "Credit");

    
    PersonalFinanceManager manager;

    
    manager.add_wallet(wallet1);
    manager.add_wallet(wallet2);
    manager.add_card(card1);
    manager.add_card(card2);

   
    wallet1.add_balance(500);
    card2.add_balance(1000);

 
    Expense expense1(100, "Food");
    Expense expense2(200, "Clothes");
    Expense expense3(300, "Funs");
    manager.add_expense(expense1);
    manager.add_expense(expense2);
    manager.add_expense(expense3);

   
    manager.show_wallets();
    manager.show_cards();
    manager.show_expenses(0, time(nullptr));

    
    manager.show_top_expenses(time(nullptr) - 604800, time(nullptr),"week");
    manager.show_top_expenses(time(nullptr) - 2592000, time(nullptr), "month");
    manager.save_report("report.txt", time(nullptr) - 2592000, time(nullptr));
}