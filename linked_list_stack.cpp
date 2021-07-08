#include <iostream>
#include <memory>


/*
build a stack using nodes as the underlying container.
push() and pop() should be O(1)
decided to make it generic and use unique_ptr for the heck of it.
the ctor and dtor are to ensure we aren't leaking memory, I don't have valgrind installed on my current system.
*/
template<typename T>
class QuickStack
{
    private:
    struct Node
    {
        static std::size_t s_count;
        T val;
        std::unique_ptr<Node> next;

        explicit Node(T value,std::unique_ptr<Node>&& ptr):val(value),next(std::move(ptr))
        {
            ++s_count;
            std::cout << __FUNCTION__ << " #" <<s_count<<'\n';
        }
        
        ~Node()
        {
            std::cout << __FUNCTION__ << " #" <<s_count<<'\n';
            --s_count;
        }

    };
    std::unique_ptr<Node> head{};
    public:
    void push(T val)
    {
        //this line works only becuase we have a ctor, it doesn't play well with braced initilaztion
        head = std::make_unique<Node>(val,std::move(head));
    }
    T pop()
    {
        //we will crush if list is empty
        auto val = head->val;
        head=std::move(head->next);
        return val;
    }
    [[nodiscard]] std::size_t size() const
    {
        std::size_t size{0};
        auto ptr = head.get();
        while(ptr != nullptr)
        {
            ++size;
            ptr=ptr->next.get();
        }
        return size;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return (!head.operator bool());
    }
};
template<typename T>
std::size_t QuickStack<T>::Node::s_count=0;
int main()
{
    QuickStack<float> mystackF;
    QuickStack<int> mystack;
    std::cout<<std::boolalpha<<"is stack empty?: " << mystack.isEmpty() << " stack size " << mystack.size()<<'\n';
    mystack.push(11);
    mystack.push(12);
    std::cout<<std::boolalpha<<"is stack empty?: " << mystack.isEmpty() << " stack size " << mystack.size()<<'\n';
    int val =mystack.pop();
    std::cout<<std::boolalpha<<"is stack empty?: " << mystack.isEmpty() << " stack size " << mystack.size()<< " value from stack " <<val<<'\n';
    val =mystack.pop();
    std::cout<<std::boolalpha<<"is stack empty?: " << mystack.isEmpty() << " stack size " << mystack.size()<< " value from stack " <<val<<'\n';
    mystack.push(13);
    mystack.push(14);

    
    mystackF.push(15.0);
    mystackF.push(16.0);
    mystackF.push(17.0);

}