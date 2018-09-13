#ifndef GOBREADER_INDENT_H
#define GOBREADER_INDENT_H

template<class T>
struct Node {
    T val;
    Node* next;
    Node* prev;
    Node(T val, Node* prev): val(val), next(NULL), prev(prev){
        if (prev)
            prev->next = this;
    }
};

template<class T>
class linked_iterator{
    public:
        linked_iterator<T>& operator=(const linked_iterator<T>& other){
            current = other.current;
        }
        linked_iterator<T>(Node<T>* ptr){
            current = ptr;
        }
        linked_iterator<T>& operator++(){
            current = current->next;
            return *this;
        }
        linked_iterator<T>& operator--(){
            current = current->prev;
        }
        linked_iterator<T> operator++(int){
            current = current->next;
        }
        linked_iterator<T> operator--(int){
            current = current->prev;
            return *this;
        }
        bool operator==(const linked_iterator<T>& other) const {
            return other.current == current;
        }
        bool operator!=(const linked_iterator<T>& other) const {
            return other.current != current;
        }
        T& operator*(){
            return current->val;
        }
        T operator*() const {
            return current->val;
        }
        T* operator->() const {
            return &(current->val);
        }

    private:
        Node<T>* current = NULL;
};

template<class T>
class linked_list {
    public:
        ~linked_list<T>(){
            Node<T>* next;
            while(first != NULL){
                next = first->next;
                delete first;
                first = next;
            }
        }
        linked_iterator<T> begin(){
            return linked_iterator<T>(first);
        }
        linked_iterator<T> end(){
            return linked_iterator<T>(NULL);
        }
        linked_iterator<T> rbegin(){
            return linked_iterator<T>(last);
        }
        linked_iterator<T> rend(){
            return linked_iterator<T>(NULL);
        }
        void push(T data){
            last = new Node<T>(data, last);
            if (!first){
                first = last;
            }
            count++;
        }
        void insert(T data){
            first = new Node<T>(data, first);
            if (!last){
                last = first;
            }
            count++;
        }
        T pop(){
            T data = last->val;
            last = last->prev;
            delete last->next;
            count--;
            last->next = NULL;
            return data;
        }
        T pop_front(){
            T data = first->val;
            first = first->next;
            delete first->prev;
            count--;
            first->prev = NULL;
            return data;
        }
        T front(){
            return first->val;
        }
        T back(){
            return last->val;
        }
        T debug(){
            return first->val;
        }

    private:
        Node<T>* first = NULL;
        Node<T>* last = NULL;
        int count;

};

#endif //GOBREADER_INDENT_H
