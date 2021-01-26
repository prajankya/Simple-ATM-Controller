#ifndef __ATMCONTROLLER_MAIN_H__
#define __ATMCONTROLLER_MAIN_H__

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct menu_item {
    virtual ~menu_item() {}
    virtual std::string get_text() const = 0;
    virtual void run() = 0;
};

struct text_menu_item : menu_item {
    text_menu_item(std::string const& text_, std::function<void()> func_)
        : text(text_), func(func_) {}

    std::string get_text() const { return text; }
    void run() { return func(); }

private:
    std::string text;
    std::function<void()> func;
};

struct menu_menu_item : menu_item {
    menu_menu_item(std::string const& text) : text_(text), items() {}
    void add_item(std::unique_ptr<menu_item> item) {
        items.push_back(std::move(item));
    }
    void run() {
        std::cout << "================================================\n";
        int idx = 0;

        std::for_each(
          items.begin(),
          items.end(),
          [&idx](std::unique_ptr<menu_item> const& item) mutable {
              std::cout << ++idx << ":\t" << item->get_text() << "\n";
          });

        std::cout << ++idx << ":\t"
                  << "Back / Exit\n";

        std::cout << "\nEnter your choice (numeric): ";

        int choice;
        std::cin >> choice;

        if (0 < choice && choice <= items.size()) {
            std::cout << "\033c";  // Clear screen
            try {
                items[choice - 1]->run();
            } catch (const std::exception& e) {
                std::cout << "\n\033[0;31m[ERROR] " << e.what() << "\033[0m\n";
            }

        } else if (choice == idx) {
            std::cout << "\033c";  // Clear screen
            return;                // exit
        } else {
            std::cout << "\n\033[0;31m[ERROR] Invalid Choice:" << (choice - 1)
                      << "\033[0m\n";

            std::cin.clear();  // clear bad input flag
            std::cin.ignore(
              std::numeric_limits<std::streamsize>::max(),
              '\n');  // discard input
        }
        return run();
    }
    std::string get_text() const { return text_; }

private:
    std::string text_;
    std::vector<std::unique_ptr<menu_item>> items;
};

#endif