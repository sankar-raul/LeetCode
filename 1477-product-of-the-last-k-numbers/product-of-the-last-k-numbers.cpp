class ProductOfNumbers {
    vector<int> prod;
public:
    ProductOfNumbers() {
        
    }
    
    void add(int num) {
        if (!num) {
            prod.clear();
        } else {
            if (prod.size()) {
                num *= prod[prod.size()-1];
            }
            prod.push_back(num);
        }
    }
    
    int getProduct(int k) {
        if (prod.empty()) return 0;
        int left = k > prod.size() ? 0 : k == prod.size() ? 1 : prod[prod.size() - k - 1];
        return left ? prod[prod.size() - 1] / left : 0;
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */