#include <iostream>
#include "ATMController.hpp"
#include "supporting_classes/Account.hpp"

#include "main.hpp"

int main() {
    Bank bank;

    // Add a new account with $1000 in savings and $45 in checkings
    bank.AddAccount(Account("123456789012", "123456", 1000, 45));

    // Add another account with $0 in savings and $0 in checkings
    bank.AddAccount(Account("000000000001", "112233", 0, 0));

    // Making sure bank is owned by main
    ATMController atm1(&bank);

    std::cout << "\033c";  // Clear screen
    std::cout << "================================================\n";
    std::cout << "================================================\n";
    std::cout << "\t\tATM Controller\n";
    std::cout << "\nHelp:\n There are two accounts added to the bank:\n";

    std::cout << "\n  Card Number\t|\t   Pin  \t|\t Saving \t|\t Checking\n";
    std::cout << " 123456789012  \t|\t 123456 \t|\t 1000   \t|\t   45\n";
    std::cout << " 000000000001  \t|\t 112233 \t|\t   0    \t|\t   0\n";

    std::cout
      << "\n\nSTATE machine flow : NO_CARD_INSERTED +--> CARD_INSERTED +--> "
         "PIN_TESTED +--> ACCOUNT_READY\n";
    std::cout << "\nStart testing ATM controller using the menu below:-\n";

    menu_menu_item main_menu("Main Menu");

    /*=============== Insert Card ===============*/
    main_menu.add_item(
      std::unique_ptr<menu_item>(new text_menu_item("Insert Card", [&atm1] {
          std::cout << "Enter card number (12 digit numeric, no spaces): ";
          std::string cardNumber;
          std::cin >> cardNumber;
          try {
              atm1.InsertCard(cardNumber);
              std::cout << "\n\033[0;32m[SUCCESS] Card inserted!\033[0m\n";
          } catch (const std::exception& e) {
              std::cout << "\n\033[0;31m[ERROR] " << e.what() << "\033[0m\n";
          }
      })));

    /*=============== Enter Pin ===============*/
    main_menu.add_item(
      std::unique_ptr<menu_item>(new text_menu_item("Enter Pin", [&atm1] {
          std::cout << "Enter pin (6 digit numeric, no spaces): ";
          std::string pin;
          std::cin >> pin;
          try {
              atm1.EnterPin(pin);
              std::cout << "\n\033[0;32m[SUCCESS] Pin verified!\033[0m\n";
          } catch (const std::exception& e) {
              std::cout << "\n\033[0;31m[ERROR] " << e.what() << "\033[0m\n";
          }
      })));

    /*=============== Select Account ===============*/

    menu_menu_item select_account_menu("Select Account");

    select_account_menu.add_item(
      std::unique_ptr<menu_item>(new text_menu_item("Savings Account", [&atm1] {
          try {
              atm1.SelectAccount(Account::TYPE::TYPE_SAVING);
              std::cout
                << "\n\033[0;32m[SUCCESS] Savings account selected.\033[0m"
                << std::endl;
          } catch (const std::exception& e) {
              std::cout << "\n\033[0;31m[ERROR] " << e.what() << "\033[0m\n";
          }
      })));

    select_account_menu.add_item(std::unique_ptr<menu_item>(
      new text_menu_item("Checking Account", [&atm1] {
          try {
              atm1.SelectAccount(Account::TYPE::TYPE_SAVING);
              std::cout
                << "\n\033[0;32m[SUCCESS] Checking account selected.\033[0m"
                << std::endl;
          } catch (const std::exception& e) {
              std::cout << "\n\033[0;31m[ERROR] " << e.what() << "\033[0m\n";
          }
      })));

    main_menu.add_item(std::unique_ptr<menu_item>(
      new menu_menu_item(std::move(select_account_menu))));

    /*=============== Get Balance ===============*/
    main_menu.add_item(
      std::unique_ptr<menu_item>(new text_menu_item("Get Balance", [&atm1] {
          try {
              auto balance = atm1.GetBalance();
              std::cout << "\n\033[0;32m[SUCCESS] Account balance: " << balance
                        << "\033[0m" << std::endl;
          } catch (const std::exception& e) {
              std::cout << "\n\033[0;31m[ERROR] " << e.what() << "\033[0m\n";
          }
      })));

    /*=============== Deposit ===============*/
    main_menu.add_item(
      std::unique_ptr<menu_item>(new text_menu_item("Deposit", [&atm1] {
          std::cout << "Enter amount to deposit(numeric, whole numbers): ";
          long long amount;
          std::cin >> amount;
          try {
              atm1.Deposit(amount);
              std::cout << "\n\033[0;32m[SUCCESS] Amount deposited.\033[0m\n";
          } catch (const std::exception& e) {
              std::cout << "\n\033[0;31m[ERROR] " << e.what() << "\033[0m\n";
          }
      })));

    /*=============== Withdraw ===============*/
    main_menu.add_item(
      std::unique_ptr<menu_item>(new text_menu_item("Withdraw", [&atm1] {
          std::cout << "Enter amount to withdraw(numeric, whole numbers): ";
          long long amount;
          std::cin >> amount;
          try {
              atm1.Withdraw(amount);
              std::cout << "\n\033[0;32m[SUCCESS] Amount withdrawn.\033[0m\n";
          } catch (const std::exception& e) {
              std::cout << "\n\033[0;31m[ERROR] " << e.what() << "\033[0m\n";
          }
      })));

    /*=============== Eject Card ===============*/
    main_menu.add_item(
      std::unique_ptr<menu_item>(new text_menu_item("Eject Card", [&atm1] {
          try {
              atm1.EjectCard();
              std::cout << "\n\033[0;32m[SUCCESS] Card Ejected.\033[0m\n";
          } catch (const std::exception& e) {
              std::cout << "\n\033[0;31m[ERROR] " << e.what() << "\033[0m\n";
          }
      })));

    main_menu.run();

    return 0;
}