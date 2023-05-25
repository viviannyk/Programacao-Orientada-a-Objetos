#include <iostream>
#include <string>

using namespace std;

class Pessoa {
protected:
    string nome;
    int idade;

public:
    // Classe base Pessoa com atributos nome e idade
    Pessoa(const string& _nome, int _idade) : nome(_nome), idade(_idade) {}

    // Método virtual para imprimir informações da Pessoa
    virtual void print_info() {
        cout << "Nome: " << nome << endl;
        cout << "Idade: " << idade << " anos" << endl;
    }

    virtual ~Pessoa() {}
};

class Funcionario : public Pessoa {
protected:
    float salario;
    string cargo;
    static int total_funcionarios;

public:
    // Classe Funcionario que herda de Pessoa
    Funcionario(const string& _nome, int _idade, float _salario, const string& _cargo)
        : Pessoa(_nome, _idade), salario(_salario), cargo(_cargo) {
        total_funcionarios++;
    }

    // Método para imprimir informações do Funcionario
    void print_info() {
        Pessoa::print_info();
        cout << "Salario: R$ " << salario << endl;
        cout << "Cargo: " << cargo << endl;
    }

    // Método estático para obter o número total de funcionarios
    static int get_total_funcionarios() {
        return total_funcionarios;
    }

    ~Funcionario() {
        total_funcionarios--;
    }
};

// Inicialização da variável estática total_funcionarios
int Funcionario::total_funcionarios = 0;

class Gerente : public Funcionario {
private:
    string setor;

public:
    // Classe Gerente que herda de Funcionario
    Gerente(const string& _nome, int _idade, float _salario, const string& _cargo, const string& _setor)
        : Funcionario(_nome, _idade, _salario, _cargo), setor(_setor) {}

    // Método para imprimir informações do Gerente
    void print_info() {
        Funcionario::print_info();
        cout << "Setor: " << setor << endl;
    }
};

int main() {
    const int tamanho = 2;
    Pessoa* empresa[tamanho];

    // Criação de objetos Funcionario e Gerente
    empresa[0] = new Funcionario("Joao", 25, 2500.0, "Analista");
    empresa[1] = new Gerente("Maria", 35, 5000.0, "Gerente de Projetos", "TI");

    // Exibir dados de todos os funcionarios e gerentes
    for (int i = 0; i < tamanho; i++) {
        empresa[i]->print_info();
        cout << "\n" << endl;
    }

    // Exibir o número total de funcionarios criados
    cout << "Total de funcionarios: " << Funcionario::get_total_funcionarios() << endl;

    // Liberar memória
    for (int i = 0; i < tamanho; i++) {
        delete empresa[i];
    }

    return 0;
}