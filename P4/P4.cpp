#include <iostream>

using namespace std;

// Определение класса BankAccount для представления банковского счета
class BankAccount {
private:
    int accountNumber;  // Номер счета
    double balance;     // Баланс счета
    double interestRate; // Процентная ставка

public:
    // Конструктор класса BankAccount для инициализации полей
    BankAccount(int accNumber, double initialBalance, double initialInterestRate)
        : accountNumber(accNumber), balance(initialBalance), interestRate(initialInterestRate) {}

    // Метод для внесения средств на счет
    void deposit(double amount) {
        balance += amount;
    }

    // Метод для снятия средств со счета
    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }

    // Метод для получения текущего баланса счета
    double getBalance() const {
        return balance;
    }

    // Метод для расчета процентов на остаток на счету
    double getInterest() const {
        return balance * interestRate * (1.0 / 12);
    }

    // Метод для установки новой процентной ставки
    void setInterestRate(double newRate) {
        interestRate = newRate;
    }

    // Метод для получения номера счета
    int getAccountNumber() const {
        return accountNumber;
    }

    // Объявление функции transfer() в качестве друга класса BankAccount
    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

// Функция для перевода средств между двумя счетами
bool transfer(BankAccount& from, BankAccount& to, double amount) {
    // Проверка, что счет отправителя и счет получателя различны
    if (&from == &to) {
        cerr << "Error: Нельзя перевести на тот же аккаунт.\n";
        return false;
    }

    // Проверка наличия достаточного баланса на счете отправителя для перевода
    if (from.balance >= amount) {
        // Снятие средств со счета отправителя и внесение их на счет получателя
        from.balance -= amount;
        to.balance += amount;
        return true;
    }
    else {
        cerr << "Error: Недостаточно средств для перевода.\n";
        return false;
    }
}

// Основная функция программы
int main() {
    setlocale(LC_ALL, "Russian");

    // Создание двух банковских счетов с инициализацией номера счета, баланса и процентной ставки
    BankAccount account1(123456, 0.0, 0.05);
    BankAccount account2(654321, 0.0, 0.03);

    int choice;  // Переменная для выбора действия пользователем
    double amount;  // Переменная для суммы операции

    // Цикл для отображения меню и выполнения выбранных действий, пока пользователь не выберет выход (0)
    do {
        cout << "Выберите действие:\n";
        cout << "1. Депозит\n";
        cout << "2. Вывод\n";
        cout << "3. Перевести\n";
        cout << "4. Посмотреть баланс\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите сумму для депозита: ";
            cin >> amount;
            account1.deposit(amount);
            cout << "Депозит успешен.\n";
            break;
        case 2:
            cout << "Введите сумму для вывода: ";
            cin >> amount;
            if (account1.withdraw(amount))
                cout << "Вывод средств успешен.\n";
            else
                cout << "Error: Недостаточно средств на счету.\n";
            break;
        case 3:
            cout << "Введите сумму для перевода: ";
            cin >> amount;
            if (transfer(account1, account2, amount))
                cout << "Перевод успешен.\n";
            else
                cout << "Ошибка во время передачи.\n";
            break;
        case 4:
            cout << "Баланс 1-го Аккаунта: $" << account1.getBalance() << endl;
            cout << "Баланс 2-го Аккаунта: $" << account2.getBalance() << endl;
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Error: Неверный выбор.\n";
        }

    } while (choice != 0);

    return 0;
}
