#include <iostream>
#include <vector>

using namespace std;

//определение структуры для узла связного списка
struct ListNode
{
    int val;         //значение узла
    ListNode *next;

    //конструкторы для удобного создания узлов
    ListNode() : val(0), next(nullptr) {}  
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//функция для печати связного списка
void print_list(ListNode *head)
{
    ListNode *current = head; 
    while (current != nullptr)
    {
        std::cout << current->val;
        if (current->next != nullptr)
        {
            std::cout << " ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}


ListNode *merge(ListNode *list1, ListNode *list2)
{
    //создаем фиктивный узел для упрощения обработки головы нового списка
    ListNode dummy(0);
    //указатель на текущий узел нового списка, начинаем с фиктивного узла
    ListNode *current = &dummy;
    while (list1 && list2)
    {
        //сравниваем значения текущих узлов list1 и list2
        if (list1->val < list2->val)
        {
            //если значение в list1 меньше, добавляем его в новый список
            current->next = list1;
            //переходим к следующему узлу в list1
            list1 = list1->next;
        }
        else
        {
            //добавляем его в новый список значение
            current->next = list2;
            //переходим к следующему узлу в list2
            list2 = list2->next;
        }
        //переходим к следующему узлу в новом списке
        current = current->next;
    }
    //если один из списков закончился, добавляем оставшиеся узлы из другого списка
    current->next = list1 ? list1 : list2;
    //возвращаем голову нового объединенного списка (следующий узел после фиктивного)
    return dummy.next;
}
int main()
{
    ListNode *a_12 = new ListNode(5); // [1,3,5], [1,3,6]
    ListNode *a_11 = new ListNode(3, a_12);
    ListNode *a_10 = new ListNode(1, a_11);
    ListNode *a_22 = new ListNode(6);
    ListNode *a_21 = new ListNode(3, a_22);
    ListNode *a_20 = new ListNode(1, a_21);
    print_list(merge(a_10, a_20));

    return 0;
}