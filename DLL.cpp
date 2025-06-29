#include"DLL.h"

int Song::count = 0;

void CDLL::clear()
{
    while (!isEmpty())
        deleteFront();
}

void CDLL::insertFront(const Song& song)
{
    Node* n = new Node(song);
    if (isEmpty())
    {
        n->next = n->prev = n;
        head = n;
    }
    else
    {
        Node* tail = head->prev;
        n->next = head;
        n->prev = tail;
        tail->next = head->prev = n;
        head = n;
    }
}

void CDLL::insertBack(const Song& song)
{
    Node* n = new Node(song);
    if (isEmpty())
    {
        n->next = n->prev = n;
        head = n;
    }
    else
    {
        Node* tail = head->prev;
        n->next = head;
        n->prev = tail;
        tail->next = head->prev = n;
        /* tail stays the same; head unchanged */
    }
}

/* ---- deletions ---- */
bool CDLL::deleteFront()
{
    if (isEmpty()) return false;

    Node* doomed = head;
    if (head->next == head)          // single node
        head = nullptr;
    else
    {
        Node* tail = head->prev;
        head = head->next;
        head->prev = tail;
        tail->next = head;
    }
    delete doomed;
    return true;
}

bool CDLL::deleteBack()
{
    if (isEmpty()) return false;

    Node* tail = head->prev;
    if (tail == head)                // single node
    {
        delete tail;
        head = nullptr;
    }
    else
    {
        Node* newTail = tail->prev;
        newTail->next = head;
        head->prev = newTail;
        delete tail;
    }
    return true;
}

bool CDLL::deleteByName(const string& name)
{
    Node* n = search(name);
    if (!n) return false;

    if (n == head)      return deleteFront();
    if (n == head->prev) return deleteBack();

    n->prev->next = n->next;
    n->next->prev = n->prev;
    delete n;
    return true;
}
bool CDLL::deleteByID(const int id)
{
    Node* n = search(id);
    if (!n) return false;

    if (n == head)      return deleteFront();
    if (n == head->prev) return deleteBack();

    n->prev->next = n->next;
    n->next->prev = n->prev;
    delete n;
    return true;
}

/* ---- search ---- */
Node* CDLL::search(const int id) const
{
    if (isEmpty()) return nullptr;

    Node* cur = head;
    do {
        if (cur->s.id == id) return cur;
        cur = cur->next;
    } while (cur != head);

    return nullptr;
}
Node* CDLL::search(const string& n) const
{
    if (isEmpty()) return nullptr;

    Node* cur = head;
    do {
        if (cur->s.name == n) return cur;
        cur = cur->next;
    } while (cur != head);

    return nullptr;
}

/* ---- display ---- */
void CDLL::displayForward() const
{
    if (isEmpty()) { cout << "(empty)\n"; return; }

    Node* cur = head;
    do {
        cout << cur->s.name << " - " << cur->s.artist
            << " (" << cur->s.duration << "s)\n";
        cur = cur->next;
    } while (cur != head);
}

void CDLL::displayBackward() const
{
    if (isEmpty()) { cout << "(empty)\n"; return; }

    Node* cur = head->prev;      // start from tail
    do {
        cout << cur->s.name << " - " << cur->s.artist
            << " (" << cur->s.duration << "s)\n";
        cur = cur->prev;
    } while (cur != head->prev);
}


void CDLL::displayCurr(const Song s) const
{
    if (isEmpty())
        return;
    Node* cur = search(s.id);
    cout << cur->s.name << " - " << cur->s.artist
        << " (" << cur->s.duration << "s)\n";
}
Song CDLL::nextS(const Song s) const
{
    if (isEmpty()) return Song();
    Node* cur = search(s.id);
    if (!cur) return Song();
    return cur->next->s;
}
Song CDLL::prevS(const Song s) const
{
    if (isEmpty()) return Song();
    Node* cur = search(s.id);
    if (!cur) return Song();
    return cur->prev->s;
}
Song CDLL::crrRet()
{
    return head->s;
}
ifstream& operator>>(ifstream& is, Song& data)
{
    is >> data.id;
    getline(is, data.name, ',');
    getline(is, data.artist, ',');
    is >> data.duration;
    return is;
}
ofstream& operator<<(ofstream& is, Song& data)
{
    is << data.id << "," << data.name << "," << data.artist << "," << data.duration << endl;
    return is;
}
Song CDLL::lastSong() const
{
    while (!isEmpty())
    {
		Node* tail = head->prev; // Get the last node
		return tail->s; // Return the song in the last node
    }
}