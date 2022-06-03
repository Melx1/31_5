#include <stdexcept>
#include "MatrixGraph.h"

MatrixGraph::MatrixGraph (IGraph* _oth) {
    //fast copy
    if (typeid(this) == typeid(_oth)) {
        container = (dynamic_cast<const MatrixGraph*>(_oth)->container);
        indexList = (dynamic_cast<const MatrixGraph*>(_oth)->indexList);
        return;
    }

    //full copy
    std::vector<int> vertices;
    _oth->GetVertices(vertices);
    std::vector<int> buffer;
    for (const auto& fromVertex : vertices) {
        _oth->GetNextVertices(fromVertex, buffer);
        for (auto toVertex : buffer) {
            this->MatrixGraph::AddEdge(fromVertex, toVertex);
        }
    }
}

void MatrixGraph::AddEdge (int from, int to) {
    addVertex(from);
    addVertex(to);
    at(from, to) = true;
}

int MatrixGraph::VerticesCount () const {
    return (int)indexList.size();
}

void MatrixGraph::GetNextVertices (int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    int i = this->findIndex(vertex);
    if ( i == -1) return;
    for (int j = 0; j < indexList.size(); ++j) {
        if (container[i][j]) {
            vertices.push_back(indexList[j]);
        }
    }
}

void MatrixGraph::GetPrevVertices (int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    int j = this->findIndex(vertex);
    if ( j == -1) return;
    for (int i = 0; i < indexList.size(); ++i) {
        if (container[i][j]) {
            vertices.push_back(indexList[i]);
        }
    }
}

void MatrixGraph::GetVertices (std::vector<int> &vertices) const {
    vertices.clear();
    const std::vector<int>& ref = indexList;
    vertices = ref;
}


void MatrixGraph::addVertex (int vertex) {
    if (this->findIndex(vertex) != -1) return;

    indexList.push_back(vertex);
    for (auto& it: container) {
        it.push_back(false);
    }
    std::vector<bool> row (indexList.size(), false);
    container.push_back(row);
}

std::vector<bool>::reference MatrixGraph::at (int fromVertex, int toVertex) {
    int i = this->findIndex(fromVertex);
    int j = this->findIndex(toVertex);
    if ( i == -1 or j == -1) {
        throw std::out_of_range{"MatrixGraphContainer::at(int, int)"};
    }
    return container[i][j];
}

bool MatrixGraph::at (int fromVertex, int toVertex) const {
    int i = this->findIndex(fromVertex);
    int j = this->findIndex(toVertex);
    if ( i == -1 or j == -1) {
        throw std::out_of_range{"MatrixGraphContainer::at(int, int)"};
    }
    return container[i][j];
}

int MatrixGraph::findIndex (int vertex) const {
    for (int i = 0; i < indexList.size(); ++i) {
        if (indexList[i] == vertex) return i;
    }
    return -1;
}
