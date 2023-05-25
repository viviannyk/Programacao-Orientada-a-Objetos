#include <iostream>
#include <string>

using namespace std;

// Classe base Veiculo
class Veiculo {
protected:
    string marca;
    string modelo;
    int ano;

public:
    // Construtor da classe Veiculo
    Veiculo(const string& _marca, const string& _modelo, int _ano)
        : marca(_marca), modelo(_modelo), ano(_ano) {}

    // Método virtual puro para imprimir informações do veículo
    virtual void print_info() = 0;

    // Destrutor virtual da classe Veiculo
    virtual ~Veiculo() {}
};

// Classe Carro que herda virtualmente de Veiculo
class Carro : virtual public Veiculo {
protected:
    int numero_portas;

public:
    // Construtor da classe Carro
    Carro(const string& _marca, const string& _modelo, int _ano, int _numero_portas)
        : Veiculo(_marca, _modelo, _ano), numero_portas(_numero_portas) {}

    // Implementação do método print_info para Carro
    void print_info() {
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Ano: " << ano << endl;
        cout << "Número de Portas: " << numero_portas << endl;
    }
};

// Classe Barco que herda virtualmente de Veiculo
class Barco : virtual public Veiculo {
protected:
    float comprimento;

public:
    // Construtor da classe Barco
    Barco(const string& _marca, const string& _modelo, int _ano, float _comprimento)
        : Veiculo(_marca, _modelo, _ano), comprimento(_comprimento) {}

    // Implementação do método print_info para Barco
    void print_info() {
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Ano: " << ano << endl;
        cout << "Comprimento: " << comprimento << " metros" << endl;
    }
};

// Classe Anfibio que herda de Carro e Barco
class Anfibio : public Carro, public Barco {
public:
    // Construtor da classe Anfibio
    Anfibio(const string& _marca, const string& _modelo, int _ano, int _numero_portas, float _comprimento)
        : Veiculo(_marca, _modelo, _ano), Carro(_marca, _modelo, _ano, _numero_portas), Barco(_marca, _modelo, _ano, _comprimento) {}

    // Implementação do método print_info para Anfibio
    void print_info() {
        cout << "Marca: " << marca << endl;
        cout << "Modelo: " << modelo << endl;
        cout << "Ano: " << ano << endl;
        cout << "Número de Portas: " << numero_portas << endl;
        cout << "Comprimento: " << comprimento << " metros" << endl;
    }
};

int main() {
    Veiculo* veiculos[6];

    // Cadastro de instâncias de Carro, Barco e Anfibio
    veiculos[0] = new Carro("Ford", "Mustang", 2022, 2);
    veiculos[1] = new Carro("Chevrolet", "Camaro", 2022, 2);
    veiculos[2] = new Barco("Sea Ray", "Sundancer 320", 2021, 9.75);
    veiculos[3] = new Barco("Bayliner", "Element E18", 2022, 5.49);
    veiculos[4] = new Anfibio("Amphicar", "Model 770", 1967, 2, 5.2);
    veiculos[5] = new Anfibio("Gibbs", "Quadski", 2021, 0, 3.2);

    // Impressão das informações de cada veículo
    for (int i = 0; i < 6; i++) {
        veiculos[i]->print_info();
        cout << endl;
    }

    // Liberação da memória alocada
    for (int i = 0; i < 6; i++) {
        delete veiculos[i];
    }

    return 0;
}

/*Esse código cria uma hierarquia de classes para representar vários tipos de veículos. A classe principal é chamada "Veiculo" e existem classes derivadas chamadas "Carro", "Barco" e "Anfibio". A classe base possui atributos comuns a todos os veículos, como marca, modelo e ano, além de um método virtual puro chamado "print_info" que é responsável por exibir informações específicas de cada veículo.

As classes derivadas implementam o método "print_info" de acordo com as características particulares de cada tipo de veículo. A classe "Carro" possui um atributo adicional chamado "numero_portas" e exibe informações sobre o número de portas do carro. A classe "Barco" possui um atributo adicional chamado "comprimento" e exibe informações sobre o comprimento do barco. A classe "Anfibio" herda tanto da classe "Carro" quanto da classe "Barco" e exibe informações sobre o número de portas e o comprimento do veículo anfíbio.

No programa principal, são criadas instâncias de carros, barcos e veículos anfíbios, que são armazenadas em um array de ponteiros para a classe "Veiculo". Em seguida, o método "print_info" é chamado para cada veículo, exibindo suas informações específicas. Por fim, é feita a liberação da memória alocada dinamicamente utilizando o operador "delete" para evitar possíveis vazamentos de memória.*/