#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <Windows.h>
using namespace std;

class HashTable
{
private:
    int tableSize;
    vector< list< string>> table; //реалізація через вектор

public:
    HashTable(int size) : tableSize(size), table(size) {}

    int secondaryHash(const string& key) //Вирішення колізії (ПодвХеш)
    {
        const int p1 = 17;
        int secondaryHashValue = 0;
        for (char ch : key)
        {
            secondaryHashValue = (p1 - (static_cast<int>(ch) % p1));
        }
        return secondaryHashValue;
    }
    
    int hash(const string& key, int attempt) // Хеш-функція
    {
        const int p = 31;
        int primaryHashValue = 0;
        for (char ch : key)
        {
            primaryHashValue = (primaryHashValue * p + static_cast<int>(ch)) % tableSize;
        }

        int secondaryHashValue = secondaryHash(key);

        return (primaryHashValue + attempt * secondaryHashValue) % tableSize;
    }

    void insert(const  string& key) // Додавання елемента
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        int attempt = 0;
        int index;

        do 
        {
            index = hash(key, attempt);
            attempt++;

        } while (!table[index].empty());

        table[index].push_back(key);
        cout << "Елемент '" << key << "' додано до хеш-таблиці." << endl;
    }

    void remove(const string& key) // Видалення елемента
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        int attempt = 0;
        int index;
        do 
        {
            index = hash(key, attempt);
            attempt++;

        } while (find(table[index].begin(), table[index].end(), key) == table[index].end());

        auto it = find(table[index].begin(), table[index].end(), key);
        table[index].erase(it);
        cout << "Елемент '" << key << "' вилучено з хеш-таблиці." << endl;
    }

    void search(const string& key) // Пошук елемента
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        int attempt = 0;
        int index;
        do 
        {
            index = hash(key, attempt);
            attempt++;

        } while (find(table[index].begin(), table[index].end(), key) == table[index].end());

        cout << "Елемент '" << key << "' знайдено в хеш-таблиці." << endl;
    }

    void display() // Вивід таблиці
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        for (int i = 0; i < tableSize; ++i)
        {
            cout << "Slot " << i << ": ";
            for (const auto& element : table[i])
            {
                cout << element << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int tableSize;
    cout << "Введіть розмір хеш-таблиці: ";
    cin >> tableSize;

    HashTable hashTable(tableSize);

    char number;
    string key;

    do 
    {
        cout << "\nМеню:\n";
        cout << "1. Знайти елемент\n";
        cout << "2. Додати елемент\n";
        cout << "3. Видалити елемент\n";
        cout << "4. Відобразити хеш-таблицю\n";
        cout << "5. Завершити\n";
        cout << "Введіть число: ";
        cin >> number;

        switch (number)
        {
        case '1':
            cout << "Введіть елемент, який потрібно знайти: ";
            cin >> key;
            hashTable.search(key);
            break;
        case '2':
            cout << "Введіть елемент, який потрібно додати: ";
            cin >> key;
            hashTable.insert(key);
            break;
        case '3':
            cout << "Введіть елемент, який потрібно видалити: ";
            cin >> key;
            hashTable.remove(key);
            break;
        case '4':
            hashTable.display();
            break;
        case '5':
            cout << "Вихід\n";
            break;
        default:
            cout << "Неправильний вибір\n";
        }

    } while (number != '5');

    return 0;
}
