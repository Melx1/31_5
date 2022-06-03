#ifndef INC_31_5_MATRIXGRAPH_H
#define INC_31_5_MATRIXGRAPH_H

#include <vector>
#include "IGraph.h"

class MatrixGraph : public IGraph {
public:
    MatrixGraph () = default;

    MatrixGraph (IGraph* _oth);

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
    // Добавляет новый узел
    void addVertex (int vertex);

    //Доступ ячейке матрицы чтение/запись
    std::vector<bool>::reference at (int fromVertex, int toVertex);

    //Доступ ячейке матрицы только на чтение
    bool at (int fromVertex, int toVertex) const;

    //Поиск индекса узла для доступа к матрице
    int findIndex (int vertex) const;

private:
    std::vector<int> indexList;
    std::vector<std::vector<bool>> container;
};


#endif //INC_31_5_MATRIXGRAPH_H
