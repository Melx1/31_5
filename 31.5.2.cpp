#include <iostream>

#include "ListGraph.h"
#include "MatrixGraph.h"

template<typename T>
void printTest (T& graph) {
    int vertex = 3; // узел для проверки

    std::cout << "Vertices count: " << graph.VerticesCount() << std:: endl;

    std::vector<int> vct;
    graph.GetNextVertices(3, vct);
    std::cout << "Head vertex " << vertex << " list: ";
    for (auto& it : vct) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;

    graph.GetPrevVertices(3, vct);
    std::cout << "Tail vertex " << vertex << " list: ";
    for (auto& it : vct) {
        std::cout << it << ' ';
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

int main () {
    ListGraph listGraph;
    std::cout << "Template function test for ListGraph" << std::endl;
    listGraph.AddEdge(1,3);
    listGraph.AddEdge(3,2);
    listGraph.AddEdge(3,4);
    listGraph.AddEdge(4,5);
    printTest(listGraph);

    MatrixGraph matrixGraph;
    std::cout << "Template function test for MatrixGraph" << std::endl;
    matrixGraph.AddEdge(1,3);
    matrixGraph.AddEdge(3,2);
    matrixGraph.AddEdge(3,4);
    matrixGraph.AddEdge(4,5);
    matrixGraph.AddEdge(4,3);
    printTest(matrixGraph);


    std::cout << "Copy constructor test for MatrixGraph" << std::endl;
    IGraph* ptr1 = &listGraph;
    MatrixGraph matrixGraph2(ptr1);
    printTest(matrixGraph2);

    matrixGraph2.AddEdge(3, 6);
    IGraph* ptr2 = &matrixGraph2;
    MatrixGraph matrixGraph3(ptr2);
    printTest(matrixGraph3);

    std::cout << "Copy constructor test for ListGraph" << std::endl;
    IGraph* ptr3 = &matrixGraph3;
    ListGraph listGraph2(ptr3);
    printTest(listGraph2);

    listGraph2.AddEdge(7, 3);
    IGraph* ptr4 = &listGraph2;
    ListGraph listGraph3(ptr4);
    printTest(listGraph3);
}