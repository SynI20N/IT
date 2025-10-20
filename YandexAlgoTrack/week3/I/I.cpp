#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cassert>

struct node {
	node* left;
    node* right;
    std::string value;

    node(std::string v, node* l = nullptr, node* r = nullptr)
	: value(v), left(l), right(r) {}
};

std::vector<std::string> tokenize(std::string& expr) {
    std::vector<std::string> tokens;
    for (size_t i = 0; i < expr.size(); i++) {
        if (strchr(" ", expr[i])) {
			continue;
		}
        if (strchr("+-*/^()", expr[i])) {
            tokens.push_back(std::string(1, expr[i]));
        } 
		else if (expr[i] >= 'a' && expr[i] <= 'z') {
            tokens.push_back(std::string(1, expr[i]));
        } 
		else {
            throw std::runtime_error("no such token");
        }
    }
    return tokens;
}

class Parser {
public:
    Parser(std::vector<std::string>& tokens) 
	: tokens_(tokens), pos_(0) {}

    node* parse() {
        node* n = parse_part();
        while (peek() == "+" || peek() == "-") {
            std::string op = consume();
            node* right = parse_part();
            n = new node(op, n, right);
        }
        return n;
    }

private:
    std::vector<std::string> tokens_;
    size_t pos_;

    std::string peek() const {
        return pos_ < tokens_.size() ? tokens_[pos_] : "";
    }

    std::string consume(const std::string& expected = "") {
        if (pos_ >= tokens_.size()) {
			throw std::runtime_error("end of input");
		}
        std::string current = tokens_[pos_++];
        if (!expected.empty() && current != expected) {
            throw std::runtime_error("expected '" + expected + "', got '" + current + "'");
		}
        return current;
    }

    node* parse_part() {
        node* n = parse_power_token();
        while (peek() == "*" || peek() == "/") {
            std::string op = consume();
            node* right = parse_power_token();
            n = new node(op, n, right);
        }
        return n;
    }

    node* parse_power_token() {
        node* n = parse_elem_token();
        if (peek() == "^") {
            std::string op = consume();
            node* right = parse_power_token();
            n = new node(op, n, right);
        }
        return n;
    }

    node* parse_elem_token() {
        if (peek() == "(") {
            consume("(");
            node* n = parse();
            consume(")");
            return n;
        } 
		else {
            return parse_variable();
        }
    }

    node* parse_variable() {
        std::string var = consume();
        return new node(var);
    }
};

struct result {
    std::vector<std::string> lines;
    int width;
    int height;
    int root_pos;
};

result draw_tree(node* n) {
    if(!n->left && !n->right) {
        return {{n->value}, (int)n->value.size(), 1, (int)n->value.size() / 2};
    }

    std::string s = "-[" + n->value + "]-";
    int s_len = s.size();

    if(!n->right) {
        result l = draw_tree(n->left);
        std::string first = std::string(l.root_pos + 1, '.') + std::string(l.width - l.root_pos - 1, '-') + s;
        std::string second = std::string(l.root_pos, ' ') + '|' + std::string(l.width - l.root_pos - 1 + s_len, ' ');
        std::vector<std::string> new_lines = {first, second};
        for (std::string& line : l.lines) {
            new_lines.push_back(line + std::string(s_len, ' '));
        }
        return {new_lines, l.width + s_len, l.height + 2, l.width + s_len / 2};
    }

    if(!n->left) {
        result r = draw_tree(n->right);
        std::string first = s + std::string(r.root_pos, '-') + std::string(r.width - r.root_pos, '.');
        std::string second = std::string(s_len + r.root_pos, ' ') + '|' + std::string(r.width - r.root_pos - 1, ' ');
        std::vector<std::string> new_lines = {first, second};
        for (std::string& line : r.lines) {
            new_lines.push_back(std::string(s_len, ' ') + line);
        }
        return {new_lines, r.width + s_len, r.height + 2, s_len / 2};
    }

    result l = draw_tree(n->left);
    result r = draw_tree(n->right);

    std::string first = std::string(l.root_pos + 1, '.') + std::string(l.width - l.root_pos - 1, '-') +
                   s +
                   std::string(r.root_pos, '-') + std::string(r.width - r.root_pos, '.');
    std::string second = std::string(l.root_pos, ' ') + '|' +
                    std::string(l.width - l.root_pos - 1 + s_len + r.root_pos, ' ') + '|';

    int total_width = l.width + r.width + s_len;
    int total_height = std::max(l.height, r.height) + 2;

    std::vector<std::string> new_lines = {first, second};
    for(int i = 0; i < std::max(l.height, r.height); i++) {
        std::string left = i < l.height ? l.lines[i] : std::string(l.width, ' ');
        std::string right = i < r.height ? r.lines[i] : std::string(r.width, ' ');
        new_lines.push_back(left + std::string(s_len, ' ') + right);
    }

    return {new_lines, total_width, total_height, l.width + s_len / 2};
}

void print_tree(node* root) {
    result d = draw_tree(root);
    for(const std::string& line : d.lines) {
        std::cout << line << '\n';
    }
}

std::vector<std::string> get_string_repr(std::string input) {
	std::vector<std::string> tokens = tokenize(input);
    Parser parser(tokens);
    node* root = parser.parse();
	result d = draw_tree(root);
	return d.lines;
}

void test1() {
	std::string input("(a+b+c)*(d-a)");
	std::vector<std::string> res_int = get_string_repr(input);
	std::vector<std::string> answ = {
		"         .----[*]----.   ",
		"         |           |   ",
		"   .----[+]-.     .-[-]-.",
		"   |        |     |     |",
		".-[+]-.     c     d     a",
		"|     |                  ",
		"a     b                  "
	};
	assert(res_int.size() == answ.size());
	for(int i = 0; i < res_int.size(); i++) {
		assert(res_int[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

void test2() {
	std::string input("z");
	std::vector<std::string> res_int = get_string_repr(input);
	std::vector<std::string> answ = {
		"z"
	};
	assert(res_int.size() == answ.size());
	for(int i = 0; i < res_int.size(); i++) {
		assert(res_int[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

void test3() {
	std::string input("a+b");
	std::vector<std::string> res_int = get_string_repr(input);
	std::vector<std::string> answ = {
		".-[+]-."
		"|     |"
		"a     b"
	};
	assert(res_int.size() == answ.size());
	for(int i = 0; i < res_int.size(); i++) {
		assert(res_int[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

void test4() {
	std::string input("a^b");
	std::vector<std::string> res_int = get_string_repr(input);
	std::vector<std::string> answ = {
		".-[^]-."
		"|     |"
		"a     b"
	};
	assert(res_int.size() == answ.size());
	for(int i = 0; i < res_int.size(); i++) {
		assert(res_int[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

void test5() {
	std::string input("a+b*c");
	std::vector<std::string> res_int = get_string_repr(input);
	std::vector<std::string> answ = {
		".-[+]----.   ",
		"|        |   ",
		"a     .-[*]-.",
		"      |     |",
		"      b     c",
	};
	assert(res_int.size() == answ.size());
	for(int i = 0; i < res_int.size(); i++) {
		assert(res_int[i] == answ[i]);
	}
	std::cout << "OK!\n";
}

int main() {
#ifdef TEST
	test1();
	test2(); //прошел
	test3();
	test4();
	test5();
	std::cout << "all tests passed!\n";	
	return 0;
#endif
	std::string in;
	std::cin >> in;
	std::vector<std::string> tokens = tokenize(in);
    Parser parser(tokens);
    node* root = parser.parse();
    print_tree(root);
	return 0;
}
