#include <string> // подключаем строки
#include <fstream> // подключаем файлы
#include <iostream>
using namespace std;
int n=0,nn;

typedef struct _Node
{
    int  ID;
    char name[128];
    int value;
    struct  _Node* parent;
    struct  _Node* prev;
    struct  _Node* next;
    //_Node* next= new next[5];
} Node;

_Node* tree = NULL;
_Node* head = NULL;
struct _Node *add(int id, _Node *tr) {
    if ((tr) == NULL)
    {
        tr = new _Node;//задаем узлу данные
        (tr)->ID = id;
        if (id == 1) {
            head = tr;
        }
        (tr)->prev = NULL;
        (tr)->next = NULL;
    }
    int si = 0, zz = 0, zmax = 0, ll = 0, p = 0;
    string s; // сюда будем класть считанные строки
    ifstream file("spisok.txt"); // файл из которого читаем
    while (getline(file, s)) { // пока не достигнут конец файла класть очередную строку в переменную (s)
        si = si + 1;//количество строк
        while (p < 3)
        {
            if (s[ll] == ',') {//счетчик мак количесва наследников
                zz++;
            }
            ll++;
            if (s[ll] == ';') {
                p++;
            }
        }
        if (zz > n) {
            n = zz;
            zz = 0;
        }
    }
    n++;
    file.clear();
    file.seekg(0);//Возврат в начало
     /*******************************************************************************************/
    
    while (getline(file, s)) {
        char names[128];
        int index = 0, k = 1, buff = 0, chi = 0;
        int ID, VAL, POT, iPOT = 0;//ipot индекс наследника
        int start = s.size() - 1;
        int finish;
        memset(names, 0, sizeof(char) * 128);
        //Найдем в строке заданные поля
        for (; start >= 0; --start) {
            if (s[start] == ';') {
                if (index == 2)
                {
                    int z = strlen(names) - 1, zb = 0;
                    for (int i = 0; i < z / 2; i++)//разворот названий
                    {
                        zb = names[i];
                        names[i] = names[z - i];
                        names[z - i] = zb;
                    }
                    if (z == 2) {
                        zb = names[1];
                        names[1] = names[0];
                        names[0] = zb;
                    }
                }
                if (index == 3) {
                    if (ID == id )//условие нахождения нужной строки
                    {
                        (tr)->ID = id;
                        (tr)->next =add(POT, (tr)->next);
                        return(tr);
                    }
                    else
                    {
                        break;
                    }
                }
                k = 1;//обнуление буфферов
                buff = 0;
                iPOT = 0;
                ++index;

            }
            if (index == 1)
                finish = start;
            if (index == 4)
                break;
            if (s[start] != ' ' && index == 0) {//для состояния
                buff = buff + ((s[start] - 48) * k);
                k = k * 10;
                VAL = buff;
            }
            if (s[start] != ' ' && index == 1 && s[start] != ';') {//для букв
                names[chi] = s[start];
                chi++;
            }
            if (s[start] != ' ' && index == 2 && s[start] != ';') {//для айди

                buff = buff + ((s[start] - 48) * k);
                k = k * 10;
                ID = buff;

            }
            if (s[start] != ' ' && index == 3 && s[start] != ';') {//для айди
                if (s[start] != ',') {
                    buff = buff + ((s[start] - 48) * k);
                    k = k * 10;
                    POT = buff;
                }
                if (s[start - 1] == ',' )
                {
                    if (ID == id )//условие нахождения нужной строки
                    {
                        (tr)->ID = id;
                        (tr)->prev =  add(POT, (tr)->prev);
                        k = 1;
                        buff = 0;
                        POT = 0;
                    }
                }

            }
        }


        
    }
    file.close();
   
    return(tr);
}
int dlinna(char name[128]) {
    int count = 0;
    while (name[count] != 'М') {
        count++;
    }
    return count;
}


int main()
{
    struct _Node* tree;
    tree = NULL;
    tree = add(1, NULL);
    return 0;
    return 0;
}

