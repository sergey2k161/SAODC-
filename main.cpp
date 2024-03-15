#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

using namespace std;


struct StackData
{
    int data;
    StackData *last;
};

StackData *mainTop, *trashTop;

bool IsNum(string const& check)
{
    if (check.empty()) return false;
    size_t startPos = (check[0] == '-') ? 1 : 0;
    return check.find_first_not_of("0123456789", startPos) == string::npos;
}


bool IsEmpty()
{
    return mainTop == nullptr;
}

bool IsEmptyTrash()
{
    return trashTop == nullptr;
}

void Push(int num)
{
    StackData *element;
    element = new StackData();
    element -> data = num;
    if (IsEmpty())
    {
        mainTop = element;
    }
    else
    {
        element -> last = mainTop;
        mainTop = element;
    }
}

void PushFromTrash()
{
    if(!IsEmptyTrash())
    {
        if(IsEmpty())
        {
            mainTop = trashTop;
            trashTop = trashTop -> last;
            mainTop -> last = nullptr;
        }
        else
        {
            StackData *q = trashTop;
            trashTop = trashTop -> last;
            q -> last = mainTop;
            mainTop = q;
        }
        cout << "Элемент добавлен\n";
    }
    else {cout << "Вспомогательный стек пуст\n"; }
}

void PushRandomElements(int count)
{
    srand(time(0));
    while(count != 0)
    {
        Push(rand() % 1000 + 0);
        count--;
    }
}

void Pop()
{
    if(!IsEmpty())
    {
        StackData *q = mainTop;
        mainTop = mainTop -> last;
        q -> data = NULL;
        q -> last = nullptr;
        delete q;
        cout << "Элемент удалён\n";
    }
    else
    {
        cout << "Стек пуст\n";
    }
}

void PopToTrash()
{
    if (!IsEmpty())
    {
        if (IsEmptyTrash())
        {
            trashTop = mainTop;
            mainTop = mainTop -> last;
            trashTop -> last = nullptr;
        }
        else
        {
            StackData *q = mainTop;
            mainTop = mainTop -> last;
            q -> last = trashTop;
            trashTop = q;
        }
        cout << "Элемент перемещён в вспомогательный стек\n";
    }
    else
    {
        cout << "Стек пуст\n";
    }
}

void PrintStackTrash()
{
    if (!IsEmptyTrash())
    {
        cout << "Вспомогательный стек: ";
        StackData *q = trashTop;
        while(q)
        {
            cout << q->data << " ";
            q = q -> last;
        }
        cout << '\n';
        delete q;
    }
    else { cout << "Вспомогательный стек пуст\n";}

}

void PrintStack()
{
    if (!IsEmpty())
    {
        cout << "Стек: ";
        StackData *q = mainTop;
        while(q)
        {
            cout << q->data << " ";
            q = q -> last;
        }
        cout << '\n';
        delete q;
    }
    else { cout << "Стек пуст\n";}

}

void InitializeStack()
{
    mainTop = nullptr;
    trashTop = nullptr;
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    string dialog;
    bool flag = true;
    std::string menu = "1 - Стек пуст?\n"
                       "2 - Добавить новый элемент\n"
                       "3 - Добавить несколько случайных элементов\n"
                       "4 - Удалить элемент\n"
                       "5 - Вывести текущее состояние стека\n"
                       "6 - Вывести текущее состояние вспомогательного стека\n"
                       "0 - Завершение программы\n";
    std::cout << menu;
    cin >> dialog;
    InitializeStack();
    while(flag)
    {
        if (IsNum(dialog))
        {
            switch (stoi(dialog))
            {
                case 1:
                    if (IsEmpty())
                    {
                        cout << "Стек пуст\n";
                    }
                    else
                    {
                        cout << "Стек не пустой\n";
                    }
                    std::cout << menu;
                    cin >> dialog;
                    break;
                case 2:
                    cout << "1 - Создать новый элемент\n"
                            "2 - Взять элемент из вспомогательного списка\n";
                    cin >> dialog;
                    switch(stoi(dialog))
                    {
                        case 1:
                            cout << "Введите число: ";
                            cin >> dialog;
                            while(!IsNum(dialog))
                            {
                                cout << "Неверный ввод чилсла. Повторите ввод\n";
                                cin >> dialog;
                            }
                            Push(stoi(dialog));
                            cout << "Элемент добавлен\n";
                            std::cout << menu;
                            break;
                        case 2:
                            PushFromTrash();
                            std::cout << menu;
                            break;
                    }
                    cout << "Введите команду\n";
                    cin >> dialog;
                    break;
                case 3:
                    cout << "Сколько элементов добавить?\n";
                    cin >> dialog;
                    while(!IsNum(dialog))
                    {
                        cout << "Неверный ввод чилсла. Повторите ввод\n";
                        cin >> dialog;
                    }
                    PushRandomElements(stoi(dialog));
                    cout << "Элементы добавлены\n";
                    std::cout << menu;
                    cin >> dialog;
                    break;
                case 4:
                    cout << "1 - Удалить с освобождением памяти\n"
                            "2 - Переместить в спомогательный стек\n";
                    cin >> dialog;
                    switch(stoi(dialog))
                    {
                        case 1:
                            Pop();
                            break;
                        case 2:
                            PopToTrash();
                            break;
                    }
                    std::cout << menu;
                    cin >> dialog;
                    break;
                case 5:
                    PrintStack();
                    std::cout << menu;
                    cin >> dialog;
                    break;
                case 6:
                    PrintStackTrash();
                    std::cout << menu;
                    cin >> dialog;
                    break;
                case 0:
                    flag = false;
                    break;
                default:
                    cout << "Несуществующая команда. Повторите ввод.\n";
                    std::cout << menu;
                    cin >> dialog;
            }
        }
        else
        {
            cout << "Неверная команда. Повторите ввод.\n";
            std::cout << menu;
            cin >> dialog;
        }
    }
    return 0;
}
