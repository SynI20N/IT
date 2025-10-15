#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <cassert>
#include <string>
#ifdef TEST
    #include <sstream>
    #include <random>
    #include <chrono>
#endif

std::vector<std::string> splitString(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = 0;
    
    while ((end = str.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }
    
    tokens.push_back(str.substr(start));
    return tokens;
}

#ifdef TEST
std::string generateRandomString(int length) {
    const std::string charset = "abcdefghijklmnopqrstuvwxyz";
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, charset.size() - 1);
    std::string randomString(length, ' ');
    
    for (int i = 0; i < length; ++i) {
        randomString[i] = charset[distribution(generator)];
    }
    
    return randomString;
}
#endif

class FigonSubList;

class IList {
public:
    virtual size_t size() const = 0;
    virtual void add(int x) = 0;
    virtual int get(size_t i) const = 0;
    virtual void set(size_t i, int x) = 0;
    virtual FigonSubList* subList(int start, int end) = 0;
    virtual ~IList() = default;
};

class FigonList : public IList {
private:
    std::vector<int> data_;
public:
    FigonList(std::vector<int> data) {
        data_ = data;
    }

    size_t size() const {
        return data_.size();
    }

    void add(int x) {
        data_.push_back(x);
    }

    int get(size_t i) const {
        i--;
        if(i >= data_.size() || i < 0) {
            throw std::domain_error("Index out of range\n");
        }
        return data_[i];
    }

    void set(size_t i, int x) {
        i--;
        if(i >= data_.size() || i < 0) {
            throw std::domain_error("Index out of range\n");
        }
        data_[i] = x;
    }

    FigonSubList* subList(int start, int end);
};

class FigonSubList : public IList {
private:
    IList& ref_;
    int start_;
    int end_;
public:
    FigonSubList(IList& list, int start, int end) 
        : ref_(list) {
        int n = list.size();
        start_ = start - 1;
        end_ = end - 1;
        if(end_ >= n || start_ < 0) {
            throw std::domain_error("Could not create sublist\n");
        }
    }

    size_t size() const { return end_ - start_ + 1; }
    void add(int x) {}

    FigonSubList* subList(int start, int end) { 
        return new FigonSubList(ref_, start + start_, end + start_); 
    }

    int get(size_t i) const {
        size_t j = i + start_;
        return ref_.get(j);
    }

    void set(size_t i, int x) {
        size_t j = i + start_;
        ref_.set(j, x);
    }
};

FigonSubList* FigonList::subList(int start, int end) {
    return new FigonSubList(*this, start, end);
}

std::unordered_map<std::string, IList*> lists;

std::string process(std::string command) {
    if(command.substr(0, 4) == "List") {
        command = command.substr(5);
        std::vector<std::string> sp1 = splitString(command, " = ");
        std::string name = sp1[0];
        std::vector<std::string> sp2 = splitString(sp1[1], "(");
        std::string cmd = sp2[0];
        std::string arg_str = sp2[1].substr(0, sp2[1].length() - 1);
        std::vector<std::string> args = splitString(arg_str, ",");
        if(cmd.find('.') != std::string::npos) {
            std::vector<std::string> sp3 = splitString(cmd, ".");
            std::string name2 = sp3[0];
            int start = stoi(args[0]);
            int end = stoi(args[1]);
            lists[name] = lists[name2]->subList(start, end);
        }
        else {
            std::vector<int> data;
            for(std::string a : args) {
                if(a == "") {
                    break;
                }
                data.push_back(stoi(a));
            }
            lists[name] = new FigonList(data);
        }
    }
    else {
        std::vector<std::string> sp1 = splitString(command, ".");
        std::string name = sp1[0];
        std::vector<std::string> sp2 = splitString(sp1[1], "(");
        std::string cmd = sp2[0];
        std::string arg_str = sp2[1].substr(0, sp2[1].length() - 1);
        std::vector<std::string> args = splitString(arg_str, ",");
        if(cmd == "get") {
            int i = stoi(arg_str);
            int el = lists[name]->get(i);
            return std::to_string(el) + "\n";
        }
        else if(cmd == "set") {
            int i = stoi(args[0]);
            int x = stoi(args[1]);
            lists[name]->set(i, x);
        }
        else if(cmd == "add") {
            int x = stoi(arg_str);
            lists[name]->add(x);
        }
    }
    return "";
}

void run(std::istream& input, std::ostream& output) {
    int n;
    input >> n;
    std::string cmd;
    std::getline(input, cmd);
    for(int i = 0; i < n; i++) {
        std::getline(input, cmd);
        output << process(cmd);
    }
}

#ifdef TEST
void test1(std::istream& input) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == "3\n");
    std::cout << "OK!\n";
}

void test2(std::istream& input) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == "16\n5\n");
    std::cout << "OK!\n";
}

void test3(std::istream& input) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == "7\n2\n100\n100\n43\n14\n");
    std::cout << "OK!\n";
}

void test4(std::istream& input) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == "2\n");
    std::cout << "OK!\n";
}

void test5(std::istream& input) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == "1000005460\n");
    std::cout << "OK!\n";
}

void test6(std::istream& input) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == "1\n6\n503\n909\n");
    std::cout << "OK!\n";
}

void test7(std::istream& input) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == "1\n4501\n1\n503\n6666\n101\n6\n6\n");
    std::cout << "OK!\n";
}

void test8(std::istream& input) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == "");
    std::cout << "OK!\n";
}

void test9(std::istream& input) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == "99\n");
    std::cout << "OK!\n";
}

void test10(std::istream& input) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == "100\n");
    std::cout << "OK!\n";
}

void test11(std::istream& input, std::string cmp) {
    std::stringstream ss;
    run(input, ss);
    assert(ss.str() == cmp);
    std::cout << "OK!\n";
}
#endif

int main() {
#ifdef TEST
    std::ifstream test("test.txt");
    if(!test) {
        throw std::runtime_error("Could not open file \"test.txt\"\n");
    }
    
    test1(test);
    test2(test);
    test3(test);

    //test 4
    std::stringstream ss;
    ss << 1003 << '\n';
    ss << "List a = new List(1,2,3,5)\n";
    ss << "List abcdeabcde = a.subList(1,4)\n";
    for(int i = 0; i < 1000; i++) {
        ss << "List " << generateRandomString(9) << " = a.subList(2,3)\n";
    }
    ss << "abcdeabcde.get(2)\n";

    test4(ss);

    ss.clear();

    //test 5
    ss << 90003 << '\n';
    ss << "List a = new List(";
    for(int i = 1; i < 100001; i++) {
        if(i < 100001 - 1) {
            ss << i + 1000000000 << ',';
        }
        else {
            ss << i + 1000000000 << ")\n";
        }
    }
    ss << "List abcdeabcde = a.subList(5460,5465)\n";
    for(int i = 0; i < 90000; i++) {
        ss << "List " << generateRandomString(9) << " = a.subList(1,100000)\n";
    }
    ss << "abcdeabcde.get(1)\n";

    auto start = std::chrono::high_resolution_clock::now();
    test5(ss);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "test5 time: " << elapsed.count() << '\n';

    ss.clear();
    //

    test6(test);
    test7(test);

    //test 8
    ss << 1000 << '\n';
    for(int j = 0; j < 1000; j++) {
        ss << "List " << generateRandomString(10) << " = new List(";
        for(int i = 1; i < 101; i++) {
            if(i < 101 - 1) {
                ss << i + 1000000000 << ',';
            }
            else {
                ss << i + 1000000000 << ")\n";
            }
        }
    }

    auto start2 = std::chrono::high_resolution_clock::now();
    test8(ss);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;
    std::cout << "test8 time: " << elapsed2.count() << '\n';

    ss.clear();
    //
    test9(test);
    test10(test);

    //test 11
    ss << 100001 << '\n';
    ss << "List a = new List(1,2,3,5,9)\n";
    std::string prev = "a";
    for(int j = 0; j < 50000; j++) {
        std::string new_list = generateRandomString(10);
        ss << "List " << new_list << " = " << prev << ".subList(1,5)\n";
        prev = new_list;
    }
    std::string cmp = "";
    for(int j = 0; j < 50000; j++) {
        ss << prev << ".get(5)\n";
        cmp += "9\n";
    }

    auto start3 = std::chrono::high_resolution_clock::now();
    test11(ss, cmp);
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed3 = end3 - start3;
    std::cout << "test11 time: " << elapsed3.count() << '\n';

    ss.clear();
    //

    test.close();
    for(std::pair<std::string, IList*> l : lists) {
        delete l.second;
    }
    std::cout << "all tests passed!\n";
    return 0;
#endif
    std::ifstream input("input.txt");
    if(!input) {
        throw std::runtime_error("Could not open file \"test.txt\"\n");
    }
    std::ofstream output("output.txt", std::ios::out);
    run(input, output);
    for(std::pair<std::string, IList*> l : lists) {
        delete l.second;
    }
    input.close();
    output.close();
    return 0;
}