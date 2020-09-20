#define _CRT_SECURE_NO_WARNINGS

#include <glm/vec3.hpp> 
#include <glm/common.hpp> 
#include <glm/geometric.hpp> 

#include<iostream>
#include<vector>
#include<map>
#include<string>

//// Задание 1
//// Напишите функцию, которая принимает на вход знаковое целое число и печатает его 
//// двоичное представление, не используя библиотечных классов или функций.
template<int N>
void to_bin(int a)
{
    int check_value = 1 << (N - 1);
    for (int i = 0; i < N; i++)
    {
        std::cout << (((a & check_value) >> (N - 1)) & 1);
        a = a << 1;
    }
    std::cout << std::endl;
    return;
}

//// Задание 2
/// Реализуйте функции сериализации и десериализации двусвязного списка 
/// в бинарном формате в файл.
struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // указатель на произвольный элемент данного списка либо NULL
    std::string data;
};
class List
{
public:
    void Serialize(FILE* file); // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize(FILE* file); // загрузка из файла (файл открыт с помощью fopen(path, "rb"))
    ~List()
    {
        ListNode* currNode = head;
        // очистка списка
        if (currNode)
        {
            ListNode* tmp = currNode->next;
            delete currNode;
            currNode = tmp;
        }
    }
private:
    ListNode* head;
    ListNode* tail;
    int count;
};
void List::Serialize(FILE* file)
{
    if (file != NULL)
    {
        std::map<ListNode*, int> myMap;

        ListNode* currNode = head;
        int i = 1;
        // для удобства делаем мапу с ключем указателя на элемент списка и значением = его порядковому номеру
        while (currNode != tail->next)
        {
            myMap.insert({ currNode, i });
            currNode = currNode->next;
            i++;
        }

        currNode = head;

        // записываем в файл значение элемента и номер случайного элемента на который он ссылается
        // предыдущий и последующий элемент записывать не нужно, так как в файле все элементы и так будут в заданном порядке
        while (currNode != tail->next)
        {
            int strnum = 0;
            if (currNode->rand != nullptr)
                strnum = myMap.find(currNode->rand)->second;
            const char* data = currNode->data.c_str();
           
            std::fputs(data, file); // записать строку в файл
            std::fputs(std::to_string(strnum).c_str(), file); // записать строку в файл
            if (currNode != tail)
                std::fputs("\n", file);

            currNode = currNode->next;
        }

        //fclose (file);
    }
}
void List::Deserialize(FILE* file)
{
    if (file != NULL)
    {
        ListNode* currNode = head;
        // очистка списка
        if (currNode)
        {
            ListNode* tmp = currNode->next;
            delete currNode;
            currNode = tmp;
        }

        // чтение файла (допустим что в поле data храниться не более 100 символов)
        std::vector<std::string> datas;
        std::vector<int> rand_vals;
        currNode = nullptr;

        char buf[100];
        while (std::fgets(buf, sizeof buf, file) != NULL)
        {
            datas.push_back(std::string(buf));

            if (std::fgets(buf, sizeof buf, file) == NULL) break;
            rand_vals.push_back(atoi(buf));
        }

        count = rand_vals.size();

        // создаем список без рандомных связей

        std::vector<ListNode*> nodes;
        for (int i = 0; i < count; i++)
        {
            if (i == 0)
            {
                // инициализация первого элемента
                head = new ListNode();
                currNode = head;
                nodes.push_back(currNode);
                currNode->prev = nullptr;
                currNode->data = datas[i];
                currNode->next = nullptr;
            }
            else {
                // инициализация остальных элементов
                currNode->next = new ListNode();
                currNode->next->prev = currNode;
                currNode->next->data = datas[i];
                currNode = currNode->next;
                nodes.push_back(currNode);
                currNode->next = nullptr;
            }
            if (i == count - 1)
            {
                // если это был последний элемент, называем его хвостом 
                tail = currNode;
            }
        }

        // добавляем рандомные связи
        for (int i = 0; i < count; i++)
        {
            if (rand_vals[i] == 0)
            {
                nodes[i]->rand = nullptr;
            }
            else
            {
                nodes[i]->rand = nodes[rand_vals[i] - 1];
            }
        }

        //fclose (file);
    }
}

/// Задание 3
//
// Calculate smooth (average) per-vertex normals
//
// [out] normals - output per-vertex normals
// [in] verts - input per-vertex positions
// [in] faces - triangles (triplets of vertex indices)
// [in] nverts - total number of vertices (# of elements in verts and normals arrays)
// [in] nfaces - total number of faces (# of elements in faces array)
//
///Реализуйте функцию расчета усредненных нормалей для вершин меша, заданного индексированными треугольниками.


void calc_mesh_normals(glm::vec3* normals, const glm::vec3* verts, const int* faces, int nverts, int nfaces)
{
    // создаю мапу для доступа от каждой вершины к вершинам, которые находятся с ней в одних и тех же треугольниках
    std::multimap<int, std::pair<int, int>> mapOfVertices;
    for (int i = 0; i < nfaces; i += 3)
    {
        mapOfVertices.insert(std::make_pair(faces[i],   std::make_pair(faces[i + 1], faces[i + 2])));
        mapOfVertices.insert(std::make_pair(faces[i+1], std::make_pair(faces[i],     faces[i + 2])));
        mapOfVertices.insert(std::make_pair(faces[i+2], std::make_pair(faces[i],     faces[i + 1])));
    }
    
    // нахожу среднюю точку меша, чтобы с ней сравнивать направление нормалей
    // для простоты берется среднее от всех точек
    glm::vec3 avr_vertex(0, 0, 0);
    for (int i = 0; i < nverts; i++)
        avr_vertex += verts[i];
    avr_vertex /= nverts;

    // для каждой вершины считаю нормаль
    for (int i = 0; i < nverts; i++) 
    {
        normals[i] = glm::vec3(0, 0, 0);

        auto range = mapOfVertices.equal_range(i);
        int count = 0;
        // считаю нормали треугольников в которые она входит и беру от них среднее
        for (auto j = range.first; j != range.second; ++j, count++)
        {
            glm::vec3 normalCross = glm::cross(verts[j->second.first] - verts[i], verts[j->second.second] - verts[i]);
            
            if (glm::dot<3, float, glm::qualifier::highp>(avr_vertex - verts[i], normalCross) > 0)
                normalCross *= -1;

            normals[i] += normalCross;
 
        }
        normals[i] *=  1.0 / count;
    }
}

int main(int argc, char* argv[])
{


    std::cout << "Task 1: Examle" << std::endl << std::endl;

    int num = 100;
    to_bin<sizeof(int) * 8>(num);

    std::cout << "Task 2: Examle" << std::endl << std::endl;
    
    
    FILE* fromFile = fopen("tmp", "rb");
    /*примерное содержимое tmp:
asd
5
rtu
1
tds
1
igfy
2
iudh
3
    */
    List l;
    l.Deserialize(fromFile);

    FILE* toFile = fopen("tmp2", "wb");
    l.Serialize(toFile);


    fclose(fromFile);
    fclose(toFile);

    std::cout << "Task 3: Examle" << std::endl << std::endl;
    glm::vec3 points[] = { glm::vec3(3,    1,  0),
                           glm::vec3(-1,   1,  0),
                           glm::vec3(2,    0,  0),
                           glm::vec3(2,    1,  1)
    };
    int faces[] = { 0,1,2,
                    1,0,3,
                    3,0,2,
                    2,1,3
    };
    glm::vec3 results[4];


    calc_mesh_normals(results, points, faces, 4, 12);

    for (int i = 0; i < 4; i++)
    {
        std::cout << results[i].x << " " << results[i].y << results[i].z << std::endl;
    }
    
    return 0;
}