#include <bits/stdc++.h>
using namespace std;

int hash_function(int d)
{
  return d;
}

class Bucket
{
private:
public:
  int creation_time;
  int capacity;
  int local_depth;
  int occupancy;
  vector<int> contents;
  Bucket(int l, int c, int t);
  bool operator<(const Bucket b) const;
  ~Bucket();
};
class Directory
{
private:
  int global_depth;
  int bucket_size;

public:
  vector<Bucket *> buckets;
  int num_buckets = 0; // actual number of buckets
  int t = -1;          // last bucket's creation time

  set<Bucket *> setb;

  Directory(int g, int c);
  void double_dir();
  void halve_dir();
  void insert(int d);
  void del(int d);
  bool search(int d);
  void display();

  ~Directory();
};

Bucket::Bucket(int l, int c, int t)
{
  local_depth = l;
  capacity = c;
  occupancy = 0;
  creation_time = t + 1;
  contents.resize(capacity, -1);
}

bool Bucket::operator<(const Bucket b) const
{
  return creation_time < b.creation_time;
}

Bucket::~Bucket()
{
}
Directory::Directory(int g, int c)
{
  global_depth = g;
  bucket_size = c;
  int a = (int)pow(2, g);
  for (int i = 0; i < a; i++)
  {
    num_buckets++;
    Bucket *b = new Bucket(g, c, t);
    t++;
    buckets.push_back(b);
    setb.insert(b);
  }
}

void Directory::double_dir()
{
  for (int i = 0; i < (1 << global_depth); i++)
  {
    buckets.push_back(buckets[i]);
  }
  global_depth++;
}
void Directory::halve_dir()
{
  int b = buckets.size();
  buckets.resize(b / 2);
}

void Directory::insert(int d)
{
  int f = hash_function(d);
  int lsb = pow(2, global_depth);
  int id = f % lsb;

  if ((buckets[id])->occupancy < bucket_size)
  {
    for (int i = 0; i < bucket_size; i++)
    {
      if (buckets[id]->contents[i] == -1)
      {
        (buckets[id])->contents[i] = d;
        (buckets[id])->occupancy++;
        break;
      }
    }
  }
  else
  {
    int l = (buckets[id])->local_depth;
    int g = global_depth;
    int lf = id % (1 << l);
    if (l < g)
    {
      Bucket *b = new Bucket(l + 1, bucket_size, t);
      Bucket *b1 = buckets[id];
      t++;
      num_buckets++;
      setb.insert(b);
      vector<int> cont = buckets[id]->contents;
      for (int i = 0; i < (1 << (g - l)); i++)
      {
        if (i == 0)
        {
          buckets[lf] = b1;
        }
        else if (i % 2 == 0)
        {
          buckets[(i << (l)) + lf] = b1;
        }
        else
        {
          buckets[(i << (l)) + lf] = b;
        }
      }
      b->occupancy = 0;
      b1->contents = vector<int>(bucket_size, -1);
      b1->occupancy = 0;
      b1->local_depth++;
      cont.push_back(d);
      for (auto i : cont)
      {
        if (i != -1)
        {
          int p = (((hash_function(i)) >> (l)) & 1);
          if (p == 1)
          {
            insert(i);
          }
          else
          {
            insert(i);
          }
        }
      }
    }
    else
    {
      double_dir();
      g++;
      id = f % (1 << global_depth);
      lf = id % (1 << l);
      Bucket *b = new Bucket(l + 1, bucket_size, t);
      Bucket *b1 = buckets[id];
      setb.insert(b);
      t++;
      num_buckets++;
      vector<int> cont = buckets[id]->contents;
      for (int i = 0; i < (1 << (g - l)); i++)
      {
        if (i == 0)
        {
          buckets[lf] = b1;
        }
        else if (i % 2 == 0)
        {
          buckets[(i << (l)) + lf] = b1;
        }
        else
        {
          buckets[(i << (l)) + lf] = b;
        }
      }
      b->occupancy = 0;
      b1->occupancy = 0;
      b1->contents = vector<int>(bucket_size, -1);
      b1->local_depth++;
      cont.push_back(d);
      for (auto i : cont)
      {
        if (i != -1)
        {
          int p = (((hash_function(i)) >> (l)) & 1);
          if (p == 1)
          {
            insert(i);
          }
          else
          {
            insert(i);
          }
        }
      }
    }
  }
}
bool Directory::search(int d)
{
  int f = hash_function(d);
  int lsb = pow(2, global_depth);
  f %= lsb;
  for (int i = 0; i < buckets[f]->contents.size(); i++)
  {
    if (buckets[f]->contents[i] == d)
    {
      return true;
    }
  }
  return false;
}

void Directory::del(int d)
{
  int f = hash_function(d);
  int b = pow(2, global_depth);
  f %= b;
  for (int i = 0; i < buckets[f]->contents.size(); i++)
  {
    if (buckets[f]->contents[i] == d)
    {
      buckets[f]->contents[i] = -1;
      buckets[f]->occupancy--;
      return;
    }
  }
}
void Directory::display()
{
  cout << global_depth << endl;
  cout << num_buckets << endl;
  vector<Bucket> vec;
  for (auto b : setb)
  {
    vec.push_back(*b);
  }
  sort(vec.begin(), vec.end());
  for (auto b : vec)
  {
    cout << b.occupancy << " " << b.local_depth << " " << endl;
  }
}
Directory::~Directory()
{
}

int main()
{
  int g, c;
  cin >> g >> c;
  int a, b;
  Directory dir(g, c);
  while (true)
  {
    cin >> a;
    switch (a)
    {
    case 2:
      cin >> b;
      dir.insert(b);
      break;
    case 3:
      cin >> b;
      dir.search(b);
      break;
    case 4:
      cin >> b;
      dir.del(b);
      break;
    case 5:
      dir.display();
      break;
    case 6:
      return 0;
      break;
    default:
      break;
    }

    // duplicates (handle in insert, del, search), unlazy deletion, search found/not found, delete element not found, insert element already there
    // think about unlazy deletion and linear hashing before lab
  }
}