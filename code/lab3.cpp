#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

namespace lab3
{
template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() { return current->data; }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        Iterator& operator--() {
            current = current->prev;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        clear();
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else {
            head = tail = newNode;
        }
        size++;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        if (head) {
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        else {
            head = tail = newNode;
        }
        size++;
    }

    void pop_back() {
        if (tail) {
            Node* temp = tail;
            tail = tail->prev;
            if (tail) {
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }
            delete temp;
            size--;
        }
    }

    void pop_front() {
        if (head) {
            Node* temp = head;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }
            delete temp;
            size--;
        }
    }

    bool empty() const {
        return size == 0;
    }

    size_t get_size() const {
        return size;
    }

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    void clear() {
        while (head) {
            pop_front();
        }
    }

    void for_each(void (*func)(T&)) {
        for (Iterator it = begin(); it != end(); ++it) {
            func(*it);
        }
    }

    // Функция для сортировки пузырьком
    void bubble_sort() {
        if (size < 2) return;
        bool swapped;
        do {
            swapped = false;
            for (Iterator it = begin(); it != end(); ++it) {
                Iterator next_it = it;
                ++next_it;
                if (next_it != end() && *it > *next_it) {
                    std::swap(*it, *next_it);
                    swapped = true;
                }
            }
        } while (swapped);
    }
};

// Структура для теста (например, для теста людей)
struct Person {
    std::string first_name;
    std::string last_name;
    std::string patronymic;
    std::string birth_date;

    Person(std::string fn, std::string ln, std::string pt, std::string bd)
        : first_name(fn), last_name(ln), patronymic(pt), birth_date(bd) {
    }
};

// Функции для тестов
void test_1() {
    DoublyLinkedList<int> list;

    std::random_device rd; // Источник случайных чисел
    std::mt19937 gen(rd()); // Генератор случайных чисел
    std::uniform_int_distribution<> dis(-1000, 1000); // Равномерное распределение от -1000 до 1000

    for (int i = 0; i < 2001; ++i) { // Заполняем список 2001 случайным числом
        list.push_back(dis(gen));
    }

    // Подсчет суммы, среднего, минимального и максимального
    int sum = 0;
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    size_t count = list.get_size();

    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
        min_val = std::min(min_val, *it);
        max_val = std::max(max_val, *it);
    }

    double average = static_cast<double>(sum) / count;
    std::cout << "Sum: " << sum << ", Average: " << average << ", Min: " << min_val << ", Max: " << max_val << std::endl;
}

void test_2() {
    DoublyLinkedList<std::string> list;
    list.push_back("Hello");
    list.push_back("World");
    list.push_back("Test");
    list.push_back("C++");
    list.push_back("Iterator");
    list.push_back("List");
    list.push_back("Doubly");
    list.push_back("Linked");
    list.push_back("Structure");
    list.push_back("Example");

    list.pop_back();
    list.push_front("New First");

    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void test_3() {
    DoublyLinkedList<Person> list;
    // Генерация случайных данных для людей
    std::vector<std::string> first_names = { "Ivan", "Petr", "Alex", "John", "Max" };
    std::vector<std::string> last_names = { "Ivanov", "Petrikov", "Alexeev", "Johnson", "Maximov" };
    std::vector<std::string> patronymics = { "Ivanovich", "Petrovich", "Alexeevich", "Johsonovich", "Maximovich" };
    std::vector<std::string> birth_dates = { "01.01.1995", "15.05.1987", "23.11.2002", "12.03.1980", "20.06.2000" };

    for (int i = 0; i < 100; ++i) {
        std::string fn = first_names[rand() % first_names.size()];
        std::string ln = last_names[rand() % last_names.size()];
        std::string pt = patronymics[rand() % patronymics.size()];
        std::string bd = birth_dates[rand() % birth_dates.size()];
        list.push_back(Person(fn, ln, pt, bd));
    }

    // Фильтрация по возрасту
    DoublyLinkedList<Person> under_20;
    DoublyLinkedList<Person> over_30;

    for (auto it = list.begin(); it != list.end(); ++it) {
        int birth_year = std::stoi((*it).birth_date.substr(6, 4));
        int current_year = 2025;
        int age = current_year - birth_year;

        if (age < 20) {
            under_20.push_back(*it);
        }
        else if (age > 30) {
            over_30.push_back(*it);
        }
    }

    std::cout << "Under 20: " << under_20.get_size() << ", Over 30: " << over_30.get_size() << std::endl;
}

void test_4() {
    DoublyLinkedList<int> list;
    for (int i = 1; i <= 10; ++i) {
        list.push_back(i);
    }

    // Перемешиваем элементы
    std::vector<int> elements;
    for (auto it = list.begin(); it != list.end(); ++it) {
        elements.push_back(*it);
    }
    //std::random_shuffle(elements.begin(), elements.end());

    // Заполняем новый список перемешанными элементами
    list.clear();
    for (auto e : elements) {
        list.push_back(e);
    }

    // Печать перемешанных элементов
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void test_5(int n) {
    std::cout << "Testing with " << n << " elements:" << std::endl;
    // Инициализация случайного списка
    DoublyLinkedList<int> list;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-1, 1);

    // Заполняем список случайными числами
    for (int i = 0; i < n; ++i) {
        list.push_back(dis(gen));
    }

    // Замеряем время сортировки
    auto start = std::chrono::high_resolution_clock::now();
    list.bubble_sort();
    auto end = std::chrono::high_resolution_clock::now();

    // Замер времени сортировки
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken to sort " << n << " elements: " << elapsed.count() << " seconds" << std::endl;
}
}

//int main() {
//    lab3::test_1();
//    lab3::test_2();
//    lab3::test_3();
//    lab3::test_4();
//
//    for (int i = 1000; i < 128000; i *= 2)
//    {
//        lab3::test_5(i);
//    }
//
//    return 0;
//}
