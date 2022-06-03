#include "ListGraph.h"
#include "MatrixGraph.h"

ListGraph::ListGraph (IGraph* _oth) {
    //fast copy
    if (typeid(this) == typeid(_oth)) {
        container = (dynamic_cast<const ListGraph*>(_oth)->container);
        return;
    }

    //full copy
    std::vector<int> vertices;
    _oth->GetVertices(vertices);
    std::vector<int> buffer;
    for (const auto& fromVertex : vertices) {
        _oth->GetNextVertices(fromVertex, buffer);
        for (auto toVertex : buffer) {
            this->ListGraph::AddEdge(fromVertex, toVertex);
        }
    }
}

void ListGraph::AddEdge (int from, int to) {
    //from-vertex add and edge add
    auto it = container.find(from);
    if (it == container.end()) {
        std::set<int> list {to};
        container[from] = list;
    }
    else {
        it->second.insert(to);
    }

    //to-vertex add
    it = container.find(to);
    if (it == container.end()) {
        std::set<int> list{};
        container[to] = list;
    }
}

int ListGraph::VerticesCount () const {
    return (int)container.size();
}

void ListGraph::GetNextVertices (int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    auto it = container.find(vertex);
    if (it != container.end()) {
        for (auto adjacentVertex : it->second){
            vertices.push_back(adjacentVertex);
        }
    }
}


void ListGraph::GetPrevVertices (int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    for (const auto& mapIt : container) {
        for (auto adjacentVertex : mapIt.second) {
            if (adjacentVertex == vertex) {
                vertices.push_back(mapIt.first);
            }
        }
    }
}

void ListGraph::GetVertices(std::vector<int> &vertices) const {
    vertices.clear();
    for (const auto& item : container) {
        vertices.push_back(item.first);
    }
}
