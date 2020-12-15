#include "dynamic_matrix.hpp"
#include <fstream>
#include <string>

struct edge {
  unsigned int a{0};
  unsigned int b{0};
  unsigned int weight{0};
};

brocolio::container::dynamic_matrix<>
create_graph_from_file(unsigned int& number_of_edges, unsigned int& start_node);

int main() {
  unsigned int start_node{};
  unsigned int number_of_edges{};
  auto graph_matrix{create_graph_from_file(number_of_edges, start_node)};
  graph_matrix.print();
}

brocolio::container::dynamic_matrix<>
create_graph_from_file(unsigned int& number_of_edges,
                       unsigned int& start_node) {
  std::ifstream input_file{"../entrada.txt"};
  unsigned int number_of_nodes{};

  {
    // read number of nodes, edges and the start node
    std::string line{};
    std::getline(input_file, line);
    number_of_nodes = std::stoi(line);

    std::getline(input_file, line);
    number_of_edges = std::stoi(line);

    std::getline(input_file, line);
    start_node = std::stoi(line);

    // skip (number_of_nodes) lines
  }

  // start reading edges and populate matrix
  brocolio::container::dynamic_matrix<> graph_matrix{number_of_nodes,
                                                     number_of_nodes};

  edge read_edge{};
  for (unsigned int i{0}; i < number_of_edges; ++i) {
    input_file >> read_edge.a;
    input_file >> read_edge.b;
    input_file >> read_edge.weight;
    graph_matrix(read_edge.a - 1, read_edge.b - 1) = read_edge.weight;
  }
  return std::move(graph_matrix);
}
