#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

int GetHashId(const std::string& s_id);
void DFS(int node_id, int group_id, std::unordered_map<int, int>& new_id, std::unordered_map<int, std::vector<int>>& edge);

int main(int argc, char** argv) {
  const std::string INPUTFILE = argv[1];

  std::ifstream input(INPUTFILE);
  std::string customer_id, card_id;
  std::vector<std::string> customers;
  std::unordered_map<int, std::vector<int>> edge;
  while(input >> customer_id >> card_id) {
    customers.push_back(customer_id);
    edge[GetHashId(customer_id)].push_back(GetHashId(card_id));
    edge[GetHashId(card_id)].push_back(GetHashId(customer_id));
  }
  input.close();
  
  std::unordered_map<int, int> new_id;
  for(int idx = 0; const auto& customer : customers) {
    if(new_id.find(GetHashId(customer)) == new_id.end()) {
      DFS(GetHashId(customer), idx++, new_id, edge);
    }
  }

  std::ofstream output("output.txt");
  for(const auto& customer : customers) {
    output << customer << ' ' << new_id[GetHashId(customer)] << '\n';
  }
  output.close();
  return 0;
}

int GetHashId(const std::string& s_id) {
  static std::unordered_map<std::string, int> hash_id;
  static int hid = 0;
  if(hash_id.find(s_id) == hash_id.end()) {
    hash_id[s_id] = hid++;
  }
  return hash_id[s_id];
}

void DFS(int node_id, int group_id, std::unordered_map<int, int>& new_id, std::unordered_map<int, std::vector<int>>& edge) {
  new_id[node_id] = group_id;
  
  for(int neighbor : edge[node_id]) {
    if(new_id.find(neighbor) == new_id.end()) {
      DFS(neighbor, group_id, new_id, edge);
    }
  }
}
