#include <stdio.h>
#include <unordered_map>
#include <vector>

struct ListNode
{
    ListNode *prev;
    ListNode *next;
    ListNode *rand;
    std::string data;
};

class List
{
public:
    void Serialize (FILE *file);
    void Deserialize (FILE *file);
private:
    ListNode *head = NULL;
    ListNode *tail = NULL;
    int count;
};

/* Допущения:
 * count == количеству элементов в списке
 * поля head, tail, next, prev и rand указаны корректно
 */
void List::Serialize(FILE *file)
{
    std::unordered_map<ListNode*, int> numbersMap; // хранит пары <адрес - номер в списке>

    // заполняем numbersMap
    ListNode *cur = head;
    for (int i = 0; i < count; i++, cur = cur->next)
        numbersMap.insert(std::pair<ListNode*, int>(cur, i));

    // пишем count в файл
    fwrite(&count, sizeof(int), 1, file);

    /* пишем в файл элементы списка, формат:
     * номер элемента в списке, на который указывает поле rand (-1 если там NULL)
     * размер строки
     * сама строка
     */
    cur = head;
    for (size_t i = 0; i < count; i++, cur = cur->next)
    {
        int rand;
        if (cur->rand == NULL)
            rand = -1;
        else
            rand = numbersMap[cur->rand];
        if (fwrite(&rand, sizeof(int), 1, file) < 1)
            throw std::runtime_error("Unable to write to file");

        size_t size = cur->data.size();
        if (fwrite(&size, sizeof(size_t), 1, file) < 1)
            throw std::runtime_error("Unable to write to file");

        const char* data = cur->data.c_str();
        if (fwrite(data, size, 1, file) < 1)
            throw std::runtime_error("Unable to write to file");
    }
}

void List::Deserialize(FILE *file)
{
    // очищаем старый список
    ListNode *cur = head;
    tail = NULL;
    while (cur != NULL)
    {
        head = head->next;
        free(cur);
        cur = head;
    }
    count = 0;

    // читаем количество элементов
    if (fread(&count, sizeof(int), 1, file) < 0)
        throw std::runtime_error("Corrupted file: no count provided");

    // файл пустой, head, tail и count уже установлены верно
    if (count == 0)
        return;

    std::vector<ListNode*> addrs(count); // хранит адреса
    std::vector<int> rands(count); // хранит номера поля rand, -1 если NULL

    // заполянем addrs и rand
    for (size_t i = 0; i < count; i++)
    {
        int rand;
        size_t size;

        if (fread(&rand, sizeof(int), 1, file) < 1)
            throw std::runtime_error("Corrupted file: no rand provided");
        if (rand >= count) // rand указывает на несуществующий элемент
            throw std::runtime_error("Corrupted file: pointer to invalid node");
        rands[i] = rand;

        if (fread(&size, sizeof(size_t), 1, file) < 1)
           throw std::runtime_error("Corrupted file: no size field");

        char data[size+1];
        data[size] = '\0';
        if (fread(data, size, 1, file) < 1)
            throw std::runtime_error("Corrupted file: no data field");

        ListNode *node = new ListNode;
        node->data = data;
        node->next = NULL;
        node->prev = NULL;
        node->rand = NULL;
        addrs[i] = node;
    }

    // устанавливаем head, tail и обрабатываем отдельно последний элемент
    head = addrs[0];
    tail = addrs[count-1];
    if (rands[count-1] != -1)
        tail->rand = addrs[rands[count-1]];

    if (count == 1)
        return;

    // заполняем все поля rand, prev и next
    for (size_t i = 0; i < count-1; i++)
    {
        addrs[i]->next = addrs[i+1];
        addrs[i+1]->prev = addrs[i];

        if (rands[i] != -1)
            addrs[i]->rand = addrs[rands[i]];
    }
}
