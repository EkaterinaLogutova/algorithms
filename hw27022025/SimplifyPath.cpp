//нужно удалить лишние /
//. - текущий каталог => его можно пропускать
//.. - на один каталог вверх => нужно запоминать путь => нужен стек
//путь всегда с /, даже если передали пустую строку
#include <iostream>
#include <stack>
#include <string>
using namespace std;

string path(string path){
    stack<string> stack;
    string symbols="", result="";
    int start = 0, n=path.length();

    while(start<n)
    {
        symbols="";
        // пропускаем /, если их много
        while (start < n && path[start] == '/') start++;

        //cчитываем имена между /
        while (start < n && path[start] != '/') {
            symbols += path[start];
            start++;
        }
        if (symbols == "..") {
            if (!stack.empty())  //перемещаемся вверх на один каталог, вынимаем из стека элемент
                stack.pop();
        } 
        else if (!symbols.empty() && symbols != ".") {  // кладем в стек всё, кроме точек и пустык строк
            stack.push(symbols);
        }
    }
    while (!stack.empty()) { // формируем ответ
        result = "/" + stack.top() + result;
        stack.pop();
    }
    return result.empty() ? "/" : result; // на случай, если будет пустая строка, нужно вывести просто /
}

int main(){
    
    string path1= "/.../a/../b/c/../d/./";
    string path2= "/../";
    string path3= "/home/user/Documents/../Pictures";
    cout<<path(path1)<<" next"<<path(path2)<<" next"<<path(path3);
    return 0;

}