#ifndef INC_31_5_LISTGRAPH_H
#define INC_31_5_LISTGRAPH_H

#include <map>
#include <set>
#include "IGraph.h"


class ListGraph : public IGraph {
public:
    ListGraph () = default;

    ListGraph (IGraph* _oth);

    // Метод принимает вершины начала и конца ребра и добавляет ребро
    void AddEdge (int from, int to) override;

    // Метод должен считать текущее количество вершин
    int VerticesCount () const override;

    // Для конкретной вершины метод выводит в вектор “вершины” все вершины, в которые можно дойти по ребру из данной
    void GetNextVertices (int vertex, std::vector<int> &vertices) const override;

    // Для конкретной вершины метод выводит в вектор “вершины” все вершины, из которых можно дойти по ребру в данную
    void GetPrevVertices (int vertex, std::vector<int> &vertices) const override;

    // Выводит в вектор все вершины
    void GetVertices (std::vector<int> &vertices) const override;

private:
    std::map<int, std::set<int>> container;
};


#endif //INC_31_5_LISTGRAPH_H
