#include <bits/stdc++.h>
using namespace std;

class Page;
class HeapFile;
class Record
{
private:
  int pk; // primary key
  int size;
  friend class Page;
  friend class HeapFile;

public:
  Record(int size, int pk);
  ~Record();
};

class Page
{
private:
  vector<Record> records;
  vector<int> book_keeping = vector<int>(2); // at 0, num_rec, at 1, ptr to free space starting
  int page_id;
  Page *prev;
  Page *next;
  friend class HeapFile;

public:
  Page(Page *prv, Page *nxt);
  ~Page();
};

class HeapFile
{
private:
  int page_capacity;
  Page *head;
  int num_pages;
  Page *insert_page_at_end();
  int space_in_page(Page *);

public:
  HeapFile(int page_capacity);
  void insert(int rec_size, int rec_pk);
  void search(int rec_pk);
  void display_status();
  ~HeapFile();
};

Record::Record(int s, int primary_key)
{
  size = s;
  pk = primary_key;
}

Record::~Record()
{
}

Page::Page(Page *p, Page *n)
{
  prev = p;
  next = n;
  book_keeping[0] = 0;
  book_keeping[1] = 0;
}

Page::~Page()
{
}

HeapFile::HeapFile(int c)
{
  page_capacity = c;
  head = nullptr;
  num_pages = 0;
}

Page *HeapFile::insert_page_at_end()
{
  Page *curr = head;
  if (curr == nullptr)
  {
    Page *p = new Page(nullptr, nullptr);
    head = p;
    head->page_id = num_pages;
    num_pages++;
    return head;
  }
  while (curr->next != nullptr)
  {
    curr = curr->next;
  }
  Page *p = new Page(curr, nullptr);
  curr->next = p;
  p->page_id = num_pages;
  num_pages++;
  return p;
}

int HeapFile::space_in_page(Page *p)
{
  return page_capacity - (p->book_keeping.size() + 2) * 4 - p->book_keeping[1];
}

void HeapFile::insert(int rec_size, int rec_pk)
{
  Record *r = new Record(rec_size, rec_pk);
  Page *curr = head;
  Page *curr_parent = nullptr;
  while (curr != nullptr)
  {
    if (space_in_page(curr) >= (rec_size + 4))
    {
      curr->records.push_back(*r);
      curr->book_keeping[0]++;
      curr->book_keeping.push_back(curr->book_keeping[1]);
      curr->book_keeping[1] += rec_size;
      return;
    }
    else
    {
      curr_parent = curr;
      curr = curr->next;
    }
  }
  Page *p = insert_page_at_end();
  delete r;
  insert(rec_size, rec_pk); // if record size greater than page size, dont do this
}

void HeapFile::search(int rec_pk)
{
  Page *curr = head;
  while (curr != nullptr)
  {
    for (int i = 0; i < curr->book_keeping[0]; i++)
    {
      if (curr->records[i].pk == rec_pk)
      {
        cout << curr->page_id << " " << i << endl;
        return;
      }
    }
    curr = curr->next;
  }
  cout << -1 << " " << -1 << endl;
  return;
}

void HeapFile::display_status()
{
  cout << num_pages << " ";
  Page *curr = head;
  while (curr != nullptr)
  {
    cout << curr->records.size() << " ";
    curr = curr->next;
  }
  cout << endl;
}

HeapFile::~HeapFile()
{
}

int main()
{
  int page_capacity;
  cin >> page_capacity;
  HeapFile *h = new HeapFile(page_capacity);
  int a, size_record, primary_key;
  while (true)
  {
    cin >> a;
    switch (a)
    {
    case 1:
      cin >> size_record >> primary_key;
      h->insert(size_record, primary_key);
      break;
    case 2:
      h->display_status();
      break;
    case 3:
      cin >> primary_key;
      h->search(primary_key);
      break;
    case 4:
      return 0;
    default:
      return 0;
    }
  }
}