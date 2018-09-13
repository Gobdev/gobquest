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
        }
        T pop(){
            T data = last->val;
            last = last->prev;
            delete last->next;
            last->next = NULL;
            return data;
        }
        T debug(){
            return first->val;
        }

    private:
        Node<T>* first = NULL;
        Node<T>* last = NULL;

};

#endif //GOBREADER_INDENT_H
