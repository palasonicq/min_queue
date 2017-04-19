#include <algorithm>
#include <iostream>
#include <utility>

int min(int a, int b) { return (a < b ? a : b); }

class MinStack {
 private:
    int size = 0;
    struct stack_el {
        int val;
        int min;
    };
    struct Node {
        Node(const stack_el& new_val = {0, 0}, Node* new_last = NULL)
            : p(new_val), last(new_last) {}
        stack_el p;
        Node* last;
    };
    Node* pstack = NULL;

 public:
    ~MinStack() {
        Node* tmp_link;
        while (pstack != NULL) {
            tmp_link = pstack->last;
            delete pstack;
            pstack = tmp_link;
        }
    }
    bool empty() const { return (size == 0); }
    stack_el top() const {
        if (pstack != NULL) {
            return pstack->p;
        }
        return {0, 0};
    }
    void push(const stack_el& a) {
        Node* new_el = new Node(a, pstack);
        pstack = new_el;
        ++size;
    }
    void pop() {
        if (pstack == NULL) {
            return;
        }
        Node* tmp_link = pstack->last;
        delete pstack;
        pstack = tmp_link;
        --size;
    }
};

class MinQueue {
 private:
    int _size;
    MinStack stack_first, stack_second;

 public:
    MinQueue() : _size(0) {}
    void push(int val) {
        int min_element;
        if (stack_first.empty()) {
            min_element = val;
        } else {
            min_element = min(val, stack_first.top().min);
        }
        stack_first.push({val, min_element});
        ++_size;
    }
    int size() const { return _size; }
    int GetMin() const {
        if (stack_first.empty() || stack_second.empty()) {
            if (stack_first.empty()) {
                return stack_second.top().min;
            } else {
                return stack_first.top().min;
            }
        } else {
            return min(stack_second.top().min, stack_first.top().min);
        }
    }
    void pop() {
        if (stack_second.empty()) {
            while (!stack_first.empty()) {
                int a = stack_first.top().val;
                stack_first.pop();
                int min_element;
                if (stack_second.empty()) {
                    min_element = a;
                } else {
                    min_element = min(stack_second.top().min, a);
                }
                stack_second.push({a, min_element});
            }
        }
        --_size;
        stack_second.pop();
    }
};

int main() {
    MinQueue min_queue;
    int number_of_elements;
    int length_of_window;
    int new_element;
    std::cin >> number_of_elements >> length_of_window;
    for (int i = 1; i <= number_of_elements; ++i) {
        std::cin >> new_element;
        min_queue.push(new_element);
        if (min_queue.size() > length_of_window) {
            min_queue.pop();
        }
        if (min_queue.size() == length_of_window) {
            std::cout << min_queue.GetMin() << std::endl;
        }
    }
    return 0;
}
