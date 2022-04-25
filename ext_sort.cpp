#include<bits/stdc++.h>

using namespace std;



class Page
{
private:
  int capacity;
  vector<int> contents;
public:
  int occupancy;
  Page(int );
  bool insert(int );
  vector<int> getcontents();
  void setcontents(int index, int value);
  ~Page();
};

Page::Page(int c)
{
  capacity = c;
  occupancy = 0;
  contents.resize(0);
}
bool Page::insert(int r){
  if(occupancy == capacity){
    cout << "Can't insert";
    return false;
  }else{
    occupancy++;
    contents.push_back(r);
    return true;
  }
}
vector<int> Page::getcontents(){
  return contents;
}
void Page::setcontents(int i, int v){
  contents[i] = v;
}
Page::~Page()
{
}

int main() {
  int B; cin >> B;
  int page_capacity; cin >> page_capacity;
  int num_rec; cin >> num_rec;
  int num_pages =  ceil((double)num_rec/(double)page_capacity);
  vector<Page*> data_file;
  int left = num_rec;
  for(int i = 0; i < num_pages; i++) {                                // insert all records into pages initially
    Page* p = new Page(page_capacity);
    data_file.push_back(p);
    for(int j = 0; j < min(left+1, page_capacity); j++) {
      int rec;
      cin >> rec;
      p->insert(rec);
      left--;
    }
  }
  int run_size = 1;
  int num_iterations = (int) ceil((double)num_pages/(double)B);
  for(int i = 0; i < num_iterations; i+=B) {                                     // Phase 0
    vector<int> recs_to_be_sorted;
    for(int j = i; j < i+B; j++){
      for(int k = 0; k < data_file[j]->getcontents().size(); k++){
        recs_to_be_sorted.push_back(data_file[j]->getcontents()[k]);
      }
    }
    sort(recs_to_be_sorted.begin(), recs_to_be_sorted.end());
    left = recs_to_be_sorted.size();
    // if(i==0){
    //   for(int u = 0; u < recs_to_be_sorted.size();u++){
    //     cout << recs_to_be_sorted[u] << "d";
    //   }
    // }
    int f = 0;
    for(int j = i; j < i+B; j++) {                            
      for(int k = 0; k < min(left, page_capacity); k++) {
        data_file[j]->setcontents(k, recs_to_be_sorted[f]);
        f++;
        left--;
      }
    }
  }
  run_size = B;
  int num_runs = num_iterations;

  // while(run_size < num_pages){
  //   num_iterations = (int)ceil(((double)num_runs)/(double)(B-1));
  //   for(int i = 0; i < num_iterations; i+=B-1) {
  //     vector<int> recs_to_be_sorted;
  //     for(int j = i; j < i + B - 1; j++){
  //       for(int l = j; l < j + run_size; l++){
  //         for(int k = 0; k < data_file[l]->getcontents().size(); k++){
  //           recs_to_be_sorted.push_back(data_file[l]->getcontents()[k]);
  //         }
  //       }
  //     }
  //     sort(recs_to_be_sorted.begin(), recs_to_be_sorted.end());
  //     left = recs_to_be_sorted.size();
  //     int f = 0;
  //     for(int j = i; j < i+B; j++) { 
  //       for(int l = j; l < j + run_size; l++){
  //         for(int k = 0; k < min(left, page_capacity); k++) {
  //           data_file[l]->setcontents(k, recs_to_be_sorted[f]);
  //           f++;
  //           left--;
  //         } 
  //       }                            
  //     }
  //   }
  //   num_runs = num_iterations;
  //   run_size *= B-1;
  // }

  for(int i = 0; i < num_pages; i++) {
    for(int j = 0; j < data_file[i]->occupancy; j++) {
      cout << data_file[i]->getcontents()[j] << " ";
    }cout << endl;
  }

}