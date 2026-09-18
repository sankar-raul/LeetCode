class MinStack {
public:
    stack<pair<int, int>> mini_stack;

    MinStack() {}

    void push(int value) {
        if (mini_stack.size()) {
            int current_mini = mini_stack.top().second;
            mini_stack.push({value, min(current_mini, value)});
        } else {
            mini_stack.push({value, value});
        }
    }
    
    void pop() {
        mini_stack.pop();
    }
    
    int top() {
        return mini_stack.top().first;
    }
    
    int getMin() {
        return mini_stack.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */