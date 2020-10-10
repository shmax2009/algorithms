#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
int FieldLengthByY, FieldLengthByX;
int PosOnVectorOfPosition = 0;

//структура одной ячейки поля
struct cell {
    cell(int x_, int y_) {
        x = x_;
        y = y_;
    }

    int x = 0;
    int y = 0;
};

struct cellMatrix {
    cell OldPosition;

    cellMatrix(cell oldPosition) : OldPosition(oldPosition) {}

    int value = -1;

};

// метод проверки правильная координата и свободна ли она
bool IsCorrectMove(vector<vector<cellMatrix>> matrix, cell a) {
    return (a.x >= 0 && a.y >= 0 && a.x < FieldLengthByX && a.y < FieldLengthByY && matrix[a.x][a.y].value == -1);
}

//метод заполнения таблицы
void FindNewPosition(vector<vector<cellMatrix>> &matrix, vector<cell> &arr) {
    // 2 1
    // 2 -1
    // -2 -1
    // -2 1
    // 1 2
    // -1 -2
    // 1 -2
    // -1 2

    //все варианты позиций ходов^

    //записываем координать нынешней клетки про которую мы буддем говорить
    int x = arr[PosOnVectorOfPosition].x, y = arr[PosOnVectorOfPosition].y;
    PosOnVectorOfPosition++;
    //массив ходов
    vector<cell> A;
    // проверяем какие координаты будут у клеток
    cell a1(x + 2, y + 1), a2(x + 2, y - 1), a3(x - 2, y - 1), a4(x - 2, y + 1), a5(x + 1, y + 2), a6(x - 1, y - 2), a7(
            x + 1, y - 2), a8(x - 1, y + 2);
    //записываем из в массив ходов
    A.push_back(a1);
    A.push_back(a2);
    A.push_back(a3);
    A.push_back(a4);
    A.push_back(a5);
    A.push_back(a6);
    A.push_back(a7);
    A.push_back(a8);
    for (int i = 0; i < A.size(); ++i) {
        if (IsCorrectMove(matrix, A[i])) {
            arr.push_back(A[i]);
            matrix[A[i].x][A[i].y].value = matrix[x][y].value + 1;
            matrix[A[i].x][A[i].y].OldPosition = cell(x, y);
        }
    }
}

int main() {
    int StartcoordinateX, StartcoordinateY, EndcoordinateX, EndcoordinateY;
    cin >> FieldLengthByX >> FieldLengthByY >> StartcoordinateX >> StartcoordinateY >> EndcoordinateX >> EndcoordinateY;
    StartcoordinateX--;
    StartcoordinateY--;
    EndcoordinateX--;
    EndcoordinateY--;
    vector<vector<cellMatrix>> matrix;
    for (int i = 0; i < FieldLengthByX; ++i) {
        vector<cellMatrix> t;
        for (int j = 0; j < FieldLengthByY; ++j) {
            cellMatrix tmp(cell(-1, -1));
            t.push_back(tmp);
        }
        matrix.push_back(t);
    }
    matrix[StartcoordinateX][StartcoordinateY].value = 0;
    vector<cell> arr;
    arr.push_back(cell(StartcoordinateX, StartcoordinateY));
    while (matrix[EndcoordinateX][EndcoordinateY].value == -1) {
        FindNewPosition(matrix, arr);
    }

    vector<cell> fordraw;

    int a = EndcoordinateX, b = EndcoordinateY;
    while (true) {
        if (a + 1 == 0 && b + 1 == 0) {
            break;
        }
        fordraw.push_back(cell(a, b));
        //cout << a + 1 << " " << b + 1 << " ";
        int at = a, bt = b;
        a = matrix[at][bt].OldPosition.x;
        b = matrix[at][bt].OldPosition.y;


    }
    RenderWindow window(VideoMode(900, 900), "Test");
    Texture pole1_texture;
    pole1_texture.loadFromFile("/home/maxim/CLionProjects/algorithms/resources/pole.png");
    Sprite Pole;
    Pole.setTexture(pole1_texture);
    Texture pole2_texture;
    pole2_texture.loadFromFile("/home/maxim/CLionProjects/algorithms/resources/pole1.png");
    Sprite Pole1;
    Pole1.setTexture(pole2_texture);
    Pole.setScale(0.05, 0.05);
    Pole1.setScale(0.05, 0.05);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        bool b = false;
        for (int i = 0; i < FieldLengthByY; ++i) {
            for (int j = 0; j < FieldLengthByX; ++j) {
                for (int k = 0; k < fordraw.size(); ++k) {
                    if ((fordraw[k].y == i && fordraw[k].x == j)) {
                        Pole1.setPosition((i) * 656 / 15, (j) * 656 / 15);
                        window.draw(Pole1);
                        b = true;
                        break;

                    }


                }
                if (!b) {
                    Pole.setPosition(i * 656 / 15, j * 656 / 15);
                    window.draw(Pole);
                }
                b = false;

            }
        }

        window.display();
    }
}