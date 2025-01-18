#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <utility>
#include <vector>

struct Data {
  float distance;
  float cost;
  float time;
  Data() {}
  Data(float d, float c, float t) : distance(d), cost(c), time(t) {}
  Data(const Data& d) : distance(d.distance), cost(d.cost), time(d.time) {}
  ~Data() {}
};

class Edge {
public:
  std::vector<Data> vehicles;

  Edge() {}
  Edge(Data b, Data c, Data w) {
    vehicles.push_back(b);
    vehicles.push_back(c);
    vehicles.push_back(w);
  }

  ~Edge() {}

  void setData(Data b, Data c, Data w) {
    vehicles[1].distance = c.distance;
    vehicles[1].cost = c.cost;
    vehicles[1].time = c.time;
    vehicles[0].distance = b.distance;
    vehicles[0].cost = b.cost;
    vehicles[0].time = b.time;
    vehicles[2].distance = w.distance;
    vehicles[2].cost = w.cost;
    vehicles[2].time = w.time;
  }
};

class VehicleValue {
public:
  std::pair<int, float> dist;
  VehicleValue() : dist(0, 0.0) {}
  VehicleValue(int a, float b) {
    dist.first = a;
    dist.second = b;
  }
};

template <typename T> class Graph {
public:
  int nodes;
  std::vector<std::vector<T>> adjmat;

  Graph(int n) : nodes(n) { adjmat.resize(n, std::vector<T>(n)); }
  void generateGraph() {
    std::random_device rd;
    std::uniform_real_distribution<float> dis(10, 20);
    std::uniform_real_distribution<float> tim(1, 10);
    std::uniform_real_distribution<float> cst(1, 20);
    std::uniform_int_distribution<int> chance(1, 10);

    for (int i = 0; i < nodes; i++) {
      for (int j = i; j < nodes; j++) {
        int x = chance(rd);
        if (i == j) {
          Data c(0, 0, 0);
          Data b(0, 0, 0);
          Data w(0, 0, 0);
          adjmat[i][j] = Edge(b, c, w);
        } else if (x <= 7) {
          Data c(0, 0, 0);
          Data b(0, 0, 0);
          Data w(0, 0, 0);
          adjmat[i][j] = Edge(b, c, w);
          adjmat[j][i] = Edge(b, c, w);
        } else {
          Data c(1 + dis(rd), 1 + cst(rd), 1 + tim(rd));
          Data b(1 + dis(rd), 1 + cst(rd), 1 + tim(rd));
          Data w(1 + dis(rd), 1 + cst(rd), 1 + tim(rd));
          adjmat[i][j] = Edge(b, c, w);
          adjmat[j][i] = Edge(b, c, w);
        }
      }
    }
  }
};

void printGraph(Graph<Edge>& graph, int x) {
  if (x == 0) {
    std::cout << "Printing Bus Distance Data: \n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].vehicles[0].distance;
      }
      std::cout << std::endl;
    }
    std::cout << "Printing Bus Cost Data: \n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].vehicles[0].cost;
      }
      std::cout << std::endl;
    }
    std::cout << "Printing Bus Time Data: \n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].vehicles[0].time;
      }
      std::cout << std::endl;
    }
  } else if (x == 1) {
    std::cout << "Printing Car Distance Data: \n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].vehicles[1].distance;
      }
      std::cout << std::endl;
    }
    std::cout << "Printing Car Cost Data: \n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].vehicles[1].cost;
      }
      std::cout << std::endl;
    }
    std::cout << "Printing Car Time Data: \n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].vehicles[1].time;
      }
      std::cout << std::endl;
    }
  } else if (x == 2) {
    std::cout << "Printing Walking Distance Data: \n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].vehicles[2].distance;
      }
      std::cout << std::endl;
    }
    std::cout << "Printing Walking Cost Data: \n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].vehicles[2].cost;
      }
      std::cout << std::endl;
    }
    std::cout << "Printing Walking Time Data: \n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].vehicles[2].time;
      }
      std::cout << std::endl;
    }
  }
}

void printGraph(Graph<VehicleValue>& graph, char t) {
  if (t=='c') {
    if ((graph.adjmat[1][0].dist.first == 0)) {
      std::cout << "Printing Bus Data:\n";
      for (int i = 0; i < graph.nodes; i++) {
        for (int j = 0; j < graph.nodes; j++) {
          std::cout << std::setw(9) << graph.adjmat[i][j].dist.second;
        }
        std::cout << std::endl;
      }
    } else if ((graph.adjmat[0][1].dist.first == 1)) {
      std::cout << "Printing Car Data:\n";
      for (int i = 0; i < graph.nodes; i++) {
        for (int j = 0; j < graph.nodes; j++) {
          std::cout << std::setw(9) << graph.adjmat[i][j].dist.second << " ";
        }
        std::cout << std::endl;
      }
    }
  }
  else if (t=='m') {
    std::cout << "Printing Cost Data:\n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].dist.first << "-" << graph.adjmat[i][j].dist.second << " ";
      }
      std::cout << std::endl;
    }
  }
  else if (t=='t') {
    std::cout << "Printing Time Data:\n";
    for (int i = 0; i < graph.nodes; i++) {
      for (int j = 0; j < graph.nodes; j++) {
        std::cout << std::setw(9) << graph.adjmat[i][j].dist.first << "-" << graph.adjmat[i][j].dist.second << " ";
      }
      std::cout << std::endl;
    }
  }
}

Graph<VehicleValue> preprocess_comfort(Graph<Edge>& graph) {
  int choice;
  std::cout << "Enter 0 for bus and 1 for car.\n==>";
  std::cin >> choice;

  Graph<VehicleValue> newgraph(graph.nodes);

  if (choice == 0) {
    for (int x = 0; x < graph.nodes; x++) {
      for (int y = x; y < graph.nodes; y++) {
        if ((graph.adjmat[x][y].vehicles[0].distance) <= 0) {
          newgraph.adjmat[x][y] = VehicleValue(0, 0.0);
          newgraph.adjmat[y][x] = VehicleValue(0, 0.0);
        } else {
          float dist = graph.adjmat[x][y].vehicles[0].distance;
          float t = graph.adjmat[x][y].vehicles[0].time;
          float speed = dist / t;
          newgraph.adjmat[x][y] = VehicleValue(0, speed);
          newgraph.adjmat[y][x] = VehicleValue(0, speed);
        }
      }
    }
  } else if (choice == 1) {
    for (int x = 0; x < graph.nodes; x++) {
      for (int y = x; y < graph.nodes; y++) {
        if ((graph.adjmat[x][y].vehicles[0].distance) <= 0) {
          newgraph.adjmat[x][y] = VehicleValue(1, 0.0);
          newgraph.adjmat[y][x] = VehicleValue(1, 0.0);
        } else {
          float dist = graph.adjmat[x][y].vehicles[1].distance;
          float t = graph.adjmat[x][y].vehicles[1].time;
          float speed = dist / t;
          newgraph.adjmat[x][y] = VehicleValue(1, speed);
          newgraph.adjmat[y][x] = VehicleValue(1, speed);
        }
      }
    }
  }
  return newgraph;
}

Graph<VehicleValue> preprocess_time(Graph<Edge>& graph) {
  Graph<VehicleValue> newgraph(graph.nodes);
  for (int x = 0; x < graph.nodes; x++) {
    for (int y = x; y < graph.nodes; y++) {
      if ((graph.adjmat[x][y].vehicles[0].distance) <= 0) {
        newgraph.adjmat[x][y] = VehicleValue(0, 0.0);
        newgraph.adjmat[y][x] = VehicleValue(0, 0.0);
      } else {
        int temp_v = 0;
        float temp_t = graph.adjmat[x][y].vehicles[0].time;
        for (int k = 1; k < 3; k++) {
          float new_t = graph.adjmat[x][y].vehicles[k].time;
          if (new_t < temp_t) {
            temp_t = new_t;
            temp_v = k;
          }
        }
        newgraph.adjmat[x][y] = VehicleValue(temp_v, temp_t);
        newgraph.adjmat[y][x] = VehicleValue(temp_v, temp_t);
      }
    }
  }
  return newgraph;
}

Graph<VehicleValue> preprocess_cost(Graph<Edge>& graph) {
  Graph<VehicleValue> newgraph(graph.nodes);
  for (int x = 0; x < graph.nodes; x++) {
    for (int y = x; y < graph.nodes; y++) {
      if ((graph.adjmat[x][y].vehicles[0].distance) <= 0) {
        newgraph.adjmat[x][y] = VehicleValue(0, 0.0);
        newgraph.adjmat[y][x] = VehicleValue(0, 0.0);
      } else {
        int temp_v = 0;
        float temp_c = graph.adjmat[x][y].vehicles[0].cost;
        for (int k = 1; k < 3; k++) {
          float new_c = graph.adjmat[x][y].vehicles[k].cost;
          if (new_c < temp_c) {
            temp_c = new_c;
            temp_v = k;
          }
        }
        newgraph.adjmat[x][y] = VehicleValue(temp_v, temp_c);
        newgraph.adjmat[y][x] = VehicleValue(temp_v, temp_c);
      }
    }
  }
  return newgraph;
}

void shortestDistanceDijkstra(Graph<VehicleValue>& graph, int start, int end) {
  std::vector<float> distances(graph.nodes, std::numeric_limits<float>::max());
  std::vector<bool> visited(graph.nodes, false);
  distances[start] = 0;
  for (int i = 0; i < graph.nodes; i++) {
    int u = -1;
    for (int j = 0; j < graph.nodes; j++) {
      if (!visited[j] && (u == -1 || distances[j] < distances[u])) {
        u = j;
      }
    }
    if (distances[u] == std::numeric_limits<float>::max()) {
      break;
    }
    visited[u] = true;
    for (int j = 0; j < graph.nodes; j++) {
      if (graph.adjmat[u][j].dist.second > 0) {
        float newDist = distances[u] + graph.adjmat[u][j].dist.second;
        if (newDist < distances[j]) {
          distances[j] = newDist;
        }
      }
    }
  }
  if (distances[end] != std::numeric_limits<float>::max()) {
    std::cout << "Lowest weight sum from " << start << " to " << end << " is " << distances[end] << std::endl;
  }
  else {
    std::cout << "There is no path from " << start << " to " << end << std::endl;
  }
}

void shortestPathDijkstra(Graph<VehicleValue>& graph, int start, int end) {
  std::vector<float> distances(graph.nodes, std::numeric_limits<float>::max());
  std::vector<int> predecessors(graph.nodes, -1);
  std::vector<std::vector<int>> vehicleType(graph.nodes, std::vector<int>(graph.nodes, -1));
  std::vector<bool> visited(graph.nodes, false);

  distances[start] = 0;

  for (int i = 0; i < graph.nodes; ++i) {
    int u = -1;
    for (int j = 0; j < graph.nodes; ++j) {
      if (!visited[j] && (u == -1 || distances[j] < distances[u])) {
        u = j;
      }
    }

    if (distances[u] == std::numeric_limits<float>::max()) {
      break;
    }

    visited[u] = true;

    for (int v = 0; v < graph.nodes; ++v) {
      if (graph.adjmat[u][v].dist.second > 0) {
        float newDist = distances[u] + graph.adjmat[u][v].dist.second;
        if (newDist < distances[v]) {
          distances[v] = newDist;
          predecessors[v] = u;
          vehicleType[v][u] = graph.adjmat[u][v].dist.first;
        }
      }
    }
  }

  std::vector<int> path;
  for (int at = end; at != -1; at = predecessors[at]) {
    path.push_back(at);
  }
  std::reverse(path.begin(), path.end());

  if (distances[end] != std::numeric_limits<float>::max()) {
    std::cout << "Shortest path from " << start << " to " << end << " is: ";
    for (int i = 0; i < int(path.size()); ++i) {
      std::cout << path[i] << " ";
      if (i < int(path.size() - 1)) {
        std::cout << "-> ";
      }
    }
    std::cout << std::endl;

    for (int i = 0; i < int(path.size() - 1); ++i) {
      int u = path[i];
      int v = path[i + 1];
      std::cout << "From node " << u << " to node " << v << ", vehicle type: " << vehicleType[v][u] << std::endl;
    }
    std::cout << "Total weight: " << distances[end] << std::endl;
  }
  else {
    std::cout << "There is no path from " << start << " to " << end << std::endl;
  }
}

int main(void) {
  std::cout << std::setprecision(2) << std::fixed;
  bool run = true;
  Graph<Edge> main_graph(10000);
  main_graph.generateGraph();
  Graph<VehicleValue> filtered_graph(main_graph.nodes);
  do {
    int choice;
    std::cout << "Choose your preference: " << std::endl;
    std::cout << "1. Comfort\n2. Cost\n3. Time" << std::endl;
    std::cin >> choice;
    if (choice == 1) {
      filtered_graph = preprocess_comfort(main_graph);
      //printGraph(filtered_graph,'c');
      for (int i = 0; i < filtered_graph.nodes; i++) {
        shortestPathDijkstra(filtered_graph, 0, i);
        std::cout << std::endl;
      }
    }
    else if (choice == 2) {
      filtered_graph = preprocess_cost(main_graph);
      //printGraph(filtered_graph,'m');
      for (int i = 0; i < filtered_graph.nodes; i++) {
        shortestPathDijkstra(filtered_graph, 0, i);
        std::cout << std::endl;
      }
    }
    else if (choice == 3) {
      filtered_graph = preprocess_time(main_graph);
      //printGraph(filtered_graph,'t');
      for (int i = 0; i < filtered_graph.nodes; i++) {
        shortestPathDijkstra(filtered_graph, 0, i);
        std::cout << std::endl;
      }
      //shortestPathDijkstra(filtered_graph, 0, 9);
    }
    int x;
    std::cout << "Continue? 0-yes,1-no" << std::endl;
    std::cin >> x;
    if (x == 1) { run = false;}
  } while(run);
  return 0;
}
