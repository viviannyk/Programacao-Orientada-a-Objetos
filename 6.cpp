#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Ponto {
private:
    double x, y;

public:
    Ponto(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    void setX(double newX) {
        x = newX;
    }

    void setY(double newY) {
        y = newY;
    }
};

class Triangulo {
private:
    Ponto* pontos[3];

public:
    Triangulo(Ponto* p1, Ponto* p2, Ponto* p3) {
        pontos[0] = p1;
        pontos[1] = p2;
        pontos[2] = p3;
    }

    double calcular_area() const {
        double x1 = pontos[0]->getX();
        double y1 = pontos[0]->getY();
        double x2 = pontos[1]->getX();
        double y2 = pontos[1]->getY();
        double x3 = pontos[2]->getX();
        double y3 = pontos[2]->getY();

        return 0.5 * abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
    }
};

class Poligono {
private:
    vector<Ponto*> vertices;

public:
    Poligono() {}

    void adicionar_vertice(Ponto* ponto) {
        vertices.push_back(ponto);
    }

    void remover_vertice(int indice) {
        if (indice >= 0 && indice < vertices.size()) {
            vertices.erase(vertices.begin() + indice);
        }
    }

    void print_info() const {
        for (const auto& ponto : vertices) {
            cout << "Coordenadas: (" << ponto->getX() << ", " << ponto->getY() << ")" << endl;
        }
    }

    double calcular_area() const {
        int numVertices = vertices.size();
        if (numVertices < 3) {
            return 0.0;  // N�o � poss�vel calcular a �rea de um pol�gono com menos de 3 v�rtices
        }

        double area = 0.0;
        for (int i = 1; i < numVertices - 1; i++) {
            Triangulo triangulo(vertices[0], vertices[i], vertices[i + 1]);
            area += triangulo.calcular_area();
        }

        return area;
    }
};

int main() {
    // Exemplo de uso

    // Criando inst�ncias de pontos
    Ponto ponto1(0.0, 0.0);
    Ponto ponto2(1.0, 0.0);
    Ponto ponto3(0.0, 1.0);

    // Criando um tri�ngulo
    Triangulo triangulo(&ponto1, &ponto2, &ponto3);

    // Calculando e imprimindo a �rea do tri�ngulo
    cout << "�rea do tri�ngulo: " << triangulo.calcular_area() << endl;

    // Criando um pol�gono
    Poligono poligono;

    // Adicionando v�rtices ao pol�gono
    poligono.adicionar_vertice(&ponto1);
    poligono.adicionar_vertice(&ponto2);
    poligono.adicionar_vertice(&ponto3);

    // Imprimindo informa��es do pol�gono
    cout << "Informa��es do pol�gono:" << endl;
    poligono.print_info();

    // Calculando e imprimindo a �rea do pol�gono
    cout << "�rea do pol�gono: " << poligono.calcular_area() << endl;

    return 0;
}

