#define _CRT_SECURE_NO_WARNINGS

#include <glm/vec3.hpp> 
#include <glm/common.hpp> 
#include <glm/geometric.hpp> 

#include<iostream>
#include<vector>
#include<map>
#include<string>

//// ������� 1
//// �������� �������, ������� ��������� �� ���� �������� ����� ����� � �������� ��� 
//// �������� �������������, �� ��������� ������������ ������� ��� �������.
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

//// ������� 2
/// ���������� ������� ������������ � �������������� ����������� ������ 
/// � �������� ������� � ����.
struct ListNode {
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // ��������� �� ������������ ������� ������� ������ ���� NULL
    std::string data;
};
class List
{
public:
    void Serialize(FILE* file); // ���������� � ���� (���� ������ � ������� fopen(path, "wb"))
    void Deserialize(FILE* file); // �������� �� ����� (���� ������ � ������� fopen(path, "rb"))
    ~List()
    {
        ListNode* currNode = head;
        // ������� ������
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
        // ��� �������� ������ ���� � ������ ��������� �� ������� ������ � ��������� = ��� ����������� ������
        while (currNode != tail->next)
        {
            myMap.insert({ currNode, i });
            currNode = currNode->next;
            i++;
        }

        currNode = head;

        // ���������� � ���� �������� �������� � ����� ���������� �������� �� ������� �� ���������
        // ���������� � ����������� ������� ���������� �� �����, ��� ��� � ����� ��� �������� � ��� ����� � �������� �������
        while (currNode != tail->next)
        {
            int strnum = 0;
            if (currNode->rand != nullptr)
                strnum = myMap.find(currNode->rand)->second;
            const char* data = currNode->data.c_str();
           
            std::fputs(data, file); // �������� ������ � ����
            std::fputs(std::to_string(strnum).c_str(), file); // �������� ������ � ����
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
        // ������� ������
        if (currNode)
        {
            ListNode* tmp = currNode->next;
            delete currNode;
            currNode = tmp;
        }

        // ������ ����� (�������� ��� � ���� data ��������� �� ����� 100 ��������)
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

        // ������� ������ ��� ��������� ������

        std::vector<ListNode*> nodes;
        for (int i = 0; i < count; i++)
        {
            if (i == 0)
            {
                // ������������� ������� ��������
                head = new ListNode();
                currNode = head;
                nodes.push_back(currNode);
                currNode->prev = nullptr;
                currNode->data = datas[i];
                currNode->next = nullptr;
            }
            else {
                // ������������� ��������� ���������
                currNode->next = new ListNode();
                currNode->next->prev = currNode;
                currNode->next->data = datas[i];
                currNode = currNode->next;
                nodes.push_back(currNode);
                currNode->next = nullptr;
            }
            if (i == count - 1)
            {
                // ���� ��� ��� ��������� �������, �������� ��� ������� 
                tail = currNode;
            }
        }

        // ��������� ��������� �����
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

/// ������� 3
//
// Calculate smooth (average) per-vertex normals
//
// [out] normals - output per-vertex normals
// [in] verts - input per-vertex positions
// [in] faces - triangles (triplets of vertex indices)
// [in] nverts - total number of vertices (# of elements in verts and normals arrays)
// [in] nfaces - total number of faces (# of elements in faces array)
//
///���������� ������� ������� ����������� �������� ��� ������ ����, ��������� ���������������� ��������������.


void calc_mesh_normals(glm::vec3* normals, const glm::vec3* verts, const int* faces, int nverts, int nfaces)
{
    // ������ ���� ��� ������� �� ������ ������� � ��������, ������� ��������� � ��� � ����� � ��� �� �������������
    std::multimap<int, std::pair<int, int>> mapOfVertices;
    for (int i = 0; i < nfaces; i += 3)
    {
        mapOfVertices.insert(std::make_pair(faces[i],   std::make_pair(faces[i + 1], faces[i + 2])));
        mapOfVertices.insert(std::make_pair(faces[i+1], std::make_pair(faces[i],     faces[i + 2])));
        mapOfVertices.insert(std::make_pair(faces[i+2], std::make_pair(faces[i],     faces[i + 1])));
    }
    
    // ������ ������� ����� ����, ����� � ��� ���������� ����������� ��������
    // ��� �������� ������� ������� �� ���� �����
    glm::vec3 avr_vertex(0, 0, 0);
    for (int i = 0; i < nverts; i++)
        avr_vertex += verts[i];
    avr_vertex /= nverts;

    // ��� ������ ������� ������ �������
    for (int i = 0; i < nverts; i++) 
    {
        normals[i] = glm::vec3(0, 0, 0);

        auto range = mapOfVertices.equal_range(i);
        int count = 0;
        // ������ ������� ������������� � ������� ��� ������ � ���� �� ��� �������
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
    /*��������� ���������� tmp:
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