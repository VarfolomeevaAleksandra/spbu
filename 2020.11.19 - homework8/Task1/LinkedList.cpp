#include"LinkedList.h"


LinkedList::LinkedList(const LinkedList& list)
{
    tail = head = nullptr;
    count = 0;

    Node* temp = list.head;
    while (temp != nullptr)
    {
        addToTail(temp->data);
        temp = temp->next;
    }
}

LinkedList::~LinkedList()
{
    Node* temp = head;
    while (temp != nullptr)
    {
        Node* node = temp;
        temp = temp->next;
        delete node;
    }
}

bool LinkedList::indexValid(int index)
{
    return (index >= 0 && index < count);
}

int LinkedList::length()
{
    return count;
}

bool LinkedList::addToHead(int element)
{
    if (head == nullptr) 
    {
        head = tail = new Node(element);
    }
    else 
    {
        head = new Node(element, head);
    }
    ++count;
    return true;
}

bool LinkedList::addToTail(int element)
{
    if (tail == nullptr) 
    {
        head = tail = new Node(element);
    }
    else 
    {
        tail->next = new Node(element);
        tail = tail->next;
    }
    ++count;
    return true;
}

bool LinkedList::add(int index, int element)
{
    if (index == 0)
    {
        return addToHead(element);
    }
    if (index == count)
    {
        return addToTail(element);
    }
    if (!indexValid(index))
    {
        return false;
    }

    Node* temp = head;
    for (int i = 0; i < index - 1; ++i)
    {
        temp = temp->next;
    }
    temp->next = new Node(element, temp->next);
    ++count;

    return true;
}

int LinkedList::get(int index)
{
    if (!indexValid(index))
    {
        return -1;
    }
    if (index == 0)
    {
        return head->data;
    }
    if (index == count - 1)
    {
        return tail->data;
    }

    Node* temp = head;
    for (int i = 0; i < index; ++i)
    {
        temp = temp->next;
    }
    return temp->data;

}

bool LinkedList::set(int index, int element)
{
    if (!indexValid(index))
    {
        return false;
    }
    if (index == 0)
    {
        head->data = element;
    }
    else if (index == count - 1)
    {
        tail->data = element;
    }
    else
    {
        Node* temp = head;
        for (int i = 0; i < index; ++i)
        {
            temp = temp->next;
        }
        temp->data = element;
    }
    return true;
}

int& LinkedList::operator[](int index)
{
    if (head == nullptr)
    {
        addToHead(0);
        return head->data;
    }
    if (index <= 0)
    {
        return head->data;
    }
    if (index >= count)
    {
        addToTail(0);
        return tail->data;
    }
    if (index == count - 1)
    {
        return tail->data;
    }
    Node* temp = head;
    for (int i = 0; i < index; ++i)
    {
        temp = temp->next;
    }
    return temp->data;
}

std::ostream& operator<<(std::ostream& stream, const LinkedList list)
{
    stream << "[" << list.count << "]{";
    if (list.head == nullptr)
    {
        stream << "EMPTY";
    }
    else
    {
        Node* temp = list.head;
        while (temp != nullptr)
        {
            stream << temp->data;
            if (temp->next != nullptr)
            {
                stream << ", ";
            }
            temp = temp->next; 
        }
    }
    stream << "}";

    return stream;
}
void LinkedList::operator+= (int element)
{
    add(count, element);
}



int LinkedList::extractHead()
{
    if (head == nullptr)
    {
        return 0;
    }
    int c = head->data;
    Node* node = head;
    head = head->next;
    delete node;
    --count;
    return c;
}

int LinkedList::extractTail()
{
    if (head == nullptr)
    {
        return 0;
    }
    if (head->next == nullptr)
    {
        int c = head->data;
        delete head;
        head = nullptr;
        return c;
    }
    Node* node = head;
    while (node->next != nullptr && node->next->next != nullptr)
    {
        node = node->next;
    }
    int c = tail->data;
    delete node->next;
    node->next = nullptr;
    --count;
    return c;
    
}
void LinkedList::operator-=(int index)
{
    if (index == 0)
    {
        Node* temp = head;
        head = head->next;
        Node* node = temp;
        delete node;
    }
    else if (indexValid(index))
    {
        Node* temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        Node* node = temp->next;
        temp->next = node->next;
        delete node;
    }
    --count;
}

int LinkedList::extract(int index)
{
    if (head == nullptr)
    {
        return 0;
    }
    if (index == 0)
    {
        return extractHead();
    }
    if (index == length() - 1)
    {
        return extractTail();
    }
    if (indexValid(index))
    {
        Node* node = head;
        for (int i = 0; i < index - 1; ++i)
        {
            node = node->next;
        }
        int c = node->next->data;
        Node* temp = node->next;
        node->next = node->next->next;
        delete temp;
        return c;
    }
    --count;
}


LinkedList& LinkedList::operator= (const LinkedList& list)
{
    if (&list != this)
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            Node* node = temp;
            temp = temp->next;
            delete node;
        }
        count = 0;
        temp = list.head;
        while (temp != nullptr)
        {
            addToTail(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}

int LinkedList::indexOf(int element)
{
    Node* temp = head;
    int c = -1;
    for (int i = 0; i < count; ++i)  
    {
        if (temp->data == element)
        {
            c = i;
            break;
        }
        temp = temp->next;
    }
    if ((c < 0) && (count > 1))
    {
        c = (tail->data == element ? count - 1 : c);
    }
    return c;
}

bool LinkedList::contains(int element)
{
    return(indexOf(element) < 0 ? false : true);
}

bool LinkedList::swap(int index1, int index2)
{
        if ((!indexValid(index1)) or (!indexValid(index2)))
        {
            return false;
        }
        else if (index1 == index2)
        {
            return true;
        }
        if (index1 == 0)
        {
            if (index2 == count - 1)
            {
                Node* node1 = head->next;
                Node* node2 = tail;
                tail = head;
                tail->next = nullptr;
                head = node2;
                head->next = node1;
                delete node1;
                delete node2;
                return true;
            }
            else if (index2 == 1)
            {
                Node* node1 = head;
                Node* node2 = head->next->next;
                head = head->next;
                head->next = node1;
                head->next->next = node2;
                delete node1;
                delete node2;
                return true;
            }
            else
            {
                Node* temp = head;
                for (int i = 0; i < index2 - 1; ++i)
                {
                    temp = temp->next;
                }
                Node* node2 = head->next;
                Node* node3 = temp->next;
                Node* node1 = temp->next->next;
                temp->next = head;
                temp->next->next = node1;
                head = node3;
                head->next = node2;
                delete node1;
                delete node2;
                delete node3;
                return true;
            }
        }
        else
        {
            if (index2 == count - 1)
            {
                Node* temp1 = head;
                for (int i = 0; i < index1; ++i)
                {
                    temp1 = temp1->next;
                }
                Node* node1 = tail;
                Node* node2 = temp1->next->next;
                tail = temp1->next;
                tail->next = nullptr;
                temp1->next = node1;
                temp1->next->next = node2;
                delete node1;
                delete node2;
                return true;
            }
            else
            {
                Node* temp1 = head;
                for (int i = 0; i < index1 - 1; ++i)
                {
                    temp1 = temp1->next;
                }
                Node* temp2 = head;
                for (int i = 0; i < index2 - 1; ++i)
                {
                    temp2 = temp2->next;
                }
                Node* node1 = temp1->next;
                Node* node2 = temp1->next->next;
                temp1->next = temp2->next;
                temp1->next->next = temp2->next->next;
                temp2->next = node1;
                temp2->next->next = node2;
                delete node1;
                delete node2;
                return true;
            }
        }
}




