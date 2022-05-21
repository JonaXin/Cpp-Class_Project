#include<cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class MyException : public exception {
    const char* msg;
public:
    MyException(const char* msg) : msg(msg) {}

    const char* what() const noexcept {
        return msg;
    }
};

typedef int_least64_t OSMID;

struct Node {
    double x, y;
};

struct Road {
    string name;
    vector<OSMID> path;
};

struct Edge {
    Node start;
    OSMID start_id;
    Node dst;
    OSMID dst_id;
    double path_length;

    Edge(Node start, OSMID start_id, Node dst, OSMID dst_id, double path_length) : 
        start(start), start_id(start_id), dst(dst), dst_id(dst_id), path_length(path_length) {}

    bool operator<(const Edge& rhs) const {
        return path_length > rhs.path_length;
    }
};

map<OSMID, Node> load_nodes(const string& file_name) {
    ifstream nodes_file(file_name);
    map<OSMID, Node> nodes;
    double min_x, min_y, max_x, max_y;
    if (nodes_file.bad() || nodes_file.fail()) {
        throw MyException("Error opening nodes file.");
    }
    nodes_file >> min_x >> min_y >> max_x >> max_y;
    while (nodes_file.good()) {
        OSMID osmid;
        double x, y;
        nodes_file >> osmid >> x >> y;
        if (nodes_file.good()) {
            nodes[osmid] = { x, y };
        }
    }
    if (nodes_file.bad()) {
        throw MyException("Error reading nodes from file.");
    }
    nodes_file.close();
    return nodes;
}

map<OSMID, Road> load_roads(const string& file_name) {
    map<OSMID, Road> roads;
    ifstream roads_file(file_name);
    long num_roads = 0;
    if (roads_file.bad() || roads_file.fail()) {
        throw MyException("Error opening roads file.");
    }
    while (roads_file.good()) {
        OSMID osmid;
        int path_len;
        roads_file >> osmid >> path_len;
        if (roads_file.good()) {
            Road r;
            r.path.reserve(path_len);
            for (int j = 0; j < path_len; ++j) {
                OSMID node_id;
                roads_file >> node_id;
                ++num_roads;
                r.path.push_back(node_id);
            }
            roads_file.get(); // Read the extra space
            getline(roads_file, r.name);
            roads[osmid] = r;
        }
    }
    if (roads_file.bad()) {
        throw MyException("Error reading roads from file.");
    }
    roads_file.close();
    return roads;
}

double distance(const Node& a, const Node& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double get_road_length(const map<OSMID, Node>& nodes, const Road& road) {
    double len = 0.0;
    for (size_t i = 1; i < road.path.size(); ++i) {
        const Node& a = nodes.find(road.path[i - 1])->second;
        const Node& b = nodes.find(road.path[i])->second;
        len += distance(a, b);
    }
    return len;
}

map<string, double> get_road_lengths(
    const map<OSMID, Node>& nodes, const map<OSMID, Road>& roads) {
    map<string, double> road_lengths;
    for (const auto& osmid_road : roads) {
        const Road& road = osmid_road.second;
        road_lengths[road.name] += get_road_length(nodes, road);
    }
    return road_lengths;
}

struct DisjointSets
{
    map<OSMID, OSMID> parent;
    map<OSMID, int> rank;

    DisjointSets(const map<OSMID, Node>& nodes)
    {

        for (const auto n : nodes)
        {
            rank[n.first] = 0;
            parent[n.first] = n.first;
        }
    }

    OSMID find(OSMID node)
    {
        if (node != parent[node])
            parent[node] = find(parent[node]);
        return parent[node];
    }
    // Union by rank

    void merge(OSMID x, OSMID y)
    {
        x = find(x), y = find(y);
        if (rank[x] > rank[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rank[x] == rank[y])
            rank[y]++;
    }
};

typedef  pair<OSMID, OSMID> idPair;

void min_span_tree(const map<OSMID, Node>& nodes, const map<OSMID, Road>& roads)
{
    ofstream fout("output.txt");
    float rebuild_length = 0;
    int rebuild_count = 0;
    vector< pair<double, idPair> > edges;
    set<idPair> idsSet;

    for (const auto& osmid_road : roads) {
        const Road& road = osmid_road.second;

        for (size_t i = 1; i < road.path.size(); ++i) {
            const Node& start = nodes.find(road.path[i - 1])->second;
            const Node& dst = nodes.find(road.path[i])->second;
            double dist = distance(start, dst);
            edges.push_back({ dist, {road.path[i - 1], road.path[i]} });
        }
    }

    sort(edges.begin(), edges.end());

    // Create disjoint sets
    DisjointSets ds(nodes);

    vector< pair<double, idPair> >::iterator it;
    for (it = edges.begin(); it != edges.end(); it++)
    {
        OSMID st = it->second.first;
        OSMID dst = it->second.second;

        OSMID set_st = ds.find(st);
        OSMID set_dst = ds.find(dst);

        if (set_st != set_dst)
        {
            idsSet.insert({ st, dst });
            rebuild_length += static_cast<float>(it->first);
            rebuild_count++;
            ds.merge(set_st, set_dst);
        }
    }

    fout << rebuild_length << endl;
    fout << rebuild_count << endl;
    for (const auto& i : idsSet)
    {
        fout << i.first << " " << i.second << endl;
    }
}

int main(int argc, char* argv[]) {
    map<OSMID, Node> nodes = load_nodes(argc > 1 ? argv[1] : "nodes.txt");
    map<OSMID, Road> roads = load_roads(argc > 2 ? argv[2] : "roads.txt");

    min_span_tree(nodes, roads);
}