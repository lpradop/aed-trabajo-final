#include "dynamic_matrix.hpp"
#include <cmath>
#include <fstream>
#include <string>
struct edge {
  unsigned int u{0};
  unsigned int v{0};
  unsigned int weight{0};
};

bool zero_row(brocolio::container::dynamic_matrix<> const& graph_matrix,
              unsigned int row) {

  for (unsigned int j{0}; j < graph_matrix.columns(); ++j) {
    if (graph_matrix(row, j) != 0) {
      return false;
    }
  }
  return true;
}

void reduce(brocolio::container::dynamic_matrix<>& graph_matrix,
            unsigned int number_of_edges, double reduce_factor) {

  double mean{};
  double std_deviation{};
  double tolerance{};

  {
    double sum{0};
    for (int i{1}; i < graph_matrix.rows(); ++i) {
      for (int j{0}; j < i; ++j) {
        sum += graph_matrix(i, j);
      }
    }
    mean = sum / number_of_edges;

    for (int i{1}; i < graph_matrix.rows(); ++i) {
      for (int j{0}; j < i; ++j) {
        std_deviation += std::pow(graph_matrix(i, j) - mean, 2);
      }
    }
    std_deviation = std::sqrt(std_deviation / number_of_edges);
    tolerance = mean + reduce_factor * std_deviation;
  }

  for (int i{1}; i < graph_matrix.rows(); ++i) {
    for (int j{0}; j < i; ++j) {

      int tmp{graph_matrix(i, j)};
      if (tmp > tolerance) {
        graph_matrix(i, j) = 0;
        graph_matrix(j, i) = 0;
        if (zero_row(graph_matrix, i) || zero_row(graph_matrix, j)) {
          graph_matrix(i, j) = tmp;
          graph_matrix(j, i) = tmp;
        }
      }
    }
  }
  std::cout << "removed edges with weight above: " << tolerance << std::endl;
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
    input_file >> read_edge.u;
    input_file >> read_edge.v;
    input_file >> read_edge.weight;
    graph_matrix(read_edge.u - 1, read_edge.v - 1) = read_edge.weight;
    graph_matrix(read_edge.v - 1, read_edge.u - 1) = read_edge.weight;
  }
  return std::move(graph_matrix);
}

bool is_cyclic(unsigned int* arr, unsigned int node, unsigned int parent);

int main() {
  unsigned int start_node{};
  unsigned int number_of_edges{};
  auto graph_matrix{create_graph_from_file(number_of_edges, start_node)};
  graph_matrix.print();
  reduce(graph_matrix, number_of_edges, 0.5);
  std::cout << "---------------------------" << std::endl;
  graph_matrix.print();
}
