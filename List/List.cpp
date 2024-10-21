#include "List.h"

int main()
{
    List<int> intList;//默认构造函数 调用init()
    
    if(intList.empty()) std::cout << "Empty" << std::endl;
    intList.push_back(520);
    std::cout << "List size : " << intList.size() << std::endl;
    if(!intList.empty()) std::cout << "Nonempty" << std::endl;
    intList.push_back(1314);
    std::cout << "List size : " << intList.size() << std::endl;
    intList.display();
    intList.push_front(1234);
    intList.display();
    int rval = 10;//右值的push函数
    intList.push_back(std::move(rval));
    intList.push_front(std::move(rval));
    intList.display();
    intList.pop_back();//测试pop
    intList.pop_front();
    intList.display();

    //测试insert和begin还有end
    auto it = intList.begin();
    ++it;
    auto it_2 = intList.insert(it, 15);
    intList.display();
    std::cout << "The node whose position coincides what insert returns has value : " << 
    *it_2 << std::endl;
    std::cout << "The iterator it now points to " << *it << std::endl;
    it_2 = intList.end();
    --it_2;
    std::cout << "The iterator it_2 now points to " << *it_2 << std::endl;
    //看下const begin end 需要吗？
    List<int>::const_iterator it_3 = intList.begin();
    std::cout << "The iterator it_3 points to " << *it_3 << std::endl;
    it_3 = intList.end();
    it_3--;
    std::cout << "The iterator it_3 points to " << *it_3 << std::endl;
    //测试右值插入
    it_2 = intList.insert(it, std::move(rval));
    intList.display(); 
    std::cout << "The node whose position coincides what insert returns has value : " << 
    *it_2 << std::endl;
    std::cout << "The iterator it now points to " << *it << std::endl;

    //同理测试erase
    intList.erase(it);
    intList.display();
    it++;//后增运算符
    it_2--;
    --it_2;//测试--
    std::cout << "it_2 now points to : " << *it_2 << std::endl
    <<"it now points to : " << *it << std::endl;
    intList.erase(it_2, it);
    intList.display();
    intList.push_front(520);
    intList.clear();//clear
    intList.display();
    //测试其它constructor
    std::cout << "intializer list : "; List<int>intList_1{1,2,3,4,5,6};
    intList_1.display();
    List<int>intList_2(intList_1);
    std::cout << "copy : "; intList_2.display();
    List<int>intList_3(std::move(intList_1));
    std::cout << "move : "; intList_3.display();
    intList_1.display();//确认是move了
    //测试operator
    intList = (intList_2);
    intList.display();
    //测试front和back
    std::cout << "Front : " << intList.front() << std::endl;
    std::cout << "Back : " << intList.back() << std::endl;
    const List<int> intList_const = intList;
    intList_const.display();
    std::cout << "Const front : " << intList_const.front() << std::endl;
    std::cout << "Const back : " << intList_const.back() << std::endl;
}