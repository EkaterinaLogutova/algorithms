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

ListNode *duplicates(ListNode *head)
{
    ListNode dummy(0);  //создаем фиктивный узел для упрощения обработки головы списка
    ListNode *prev = &dummy;  //указатель на предыдущий узел, начинаем с фиктивного узла
    dummy.next = head;  //связываем с головой списка

    while (head)
    {
        //проверяем, есть ли следующий узел и совпадают ли значения текущего и следующего узлов
        if (head->next && head->val == head->next->val)
        {
            //пропускаем все дубликаты
            while (head->next && head->val == head->next->val)
            {
                head = head->next;  //переходим к следующему узлу
            }
            prev->next = head->next;  //убираем дубликаты из списка
        }
        else
        {
            prev = prev->next;  //переходим к следующему узлу, если дубликатов нет
        }
        head = head->next;  //переходим к следующему узлу
    }
    return dummy.next;  //возвращаем голову списка без дубликатов
}

int main()
{
    ListNode *a4 = new ListNode(3); // [1,1,1,2,3]
    ListNode *a3 = new ListNode(2, a4);
    ListNode *a2 = new ListNode(1, a3);
    ListNode *a1 = new ListNode(1, a2);
    ListNode *a0 = new ListNode(1, a1);
    a0 = duplicates(a0);
    print_list(a0);

    return 0;
}