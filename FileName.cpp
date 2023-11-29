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
    vector< list< string>> table; //��������� ����� ������

public:
    HashTable(int size) : tableSize(size), table(size) {}

    int secondaryHash(const string& key) //�������� ���糿 (�������)
    {
        const int p1 = 17;
        int secondaryHashValue = 0;
        for (char ch : key)
        {
            secondaryHashValue = (p1 - (static_cast<int>(ch) % p1));
        }
        return secondaryHashValue;
    }
    
    int hash(const string& key, int attempt) // ���-�������
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

    void insert(const  string& key) // ��������� ��������
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
        cout << "������� '" << key << "' ������ �� ���-�������." << endl;
    }

    void remove(const string& key) // ��������� ��������
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
        cout << "������� '" << key << "' �������� � ���-�������." << endl;
    }

    void search(const string& key) // ����� ��������
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

        cout << "������� '" << key << "' �������� � ���-�������." << endl;
    }

    void display() // ���� �������
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
    cout << "������ ����� ���-�������: ";
    cin >> tableSize;

    HashTable hashTable(tableSize);

    char number;
    string key;

    do 
    {
        cout << "\n����:\n";
        cout << "1. ������ �������\n";
        cout << "2. ������ �������\n";
        cout << "3. �������� �������\n";
        cout << "4. ³��������� ���-�������\n";
        cout << "5. ���������\n";
        cout << "������ �����: ";
        cin >> number;

        switch (number)
        {
        case '1':
            cout << "������ �������, ���� ������� ������: ";
            cin >> key;
            hashTable.search(key);
            break;
        case '2':
            cout << "������ �������, ���� ������� ������: ";
            cin >> key;
            hashTable.insert(key);
            break;
        case '3':
            cout << "������ �������, ���� ������� ��������: ";
            cin >> key;
            hashTable.remove(key);
            break;
        case '4':
            hashTable.display();
            break;
        case '5':
            cout << "�����\n";
            break;
        default:
            cout << "������������ ����\n";
        }

    } while (number != '5');

    return 0;
}
