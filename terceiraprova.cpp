/** Sistema de cadastro de produtos

Crie uma classe produto que represente um produto genérico.
- campos: valor, codigo_barras, nome_fabricante
Crie uma classe produto_alimenticio que herde da classe produto.
- campos: data_validade, data_fabricacao
Crie uma classe produto_eletronico que herde da classe produto.
- campos: voltagem, potencia
Crie uma classe template estoque que represente uma estoque com multiplos
produtos (alimenticios ou eletronicos).
- A classe deve ter um campo int limite_armazenamento que representa o limite
de produtos no estoque.
- A classe deve ter um campo vector de produtos.
- A classe deve ter um método adicionar_produto() que recebe como parâmetro
um produto e o adiciona ao vector de produtos.
- A classe deve ter um método calcular_valor_total() que calcula o valor total
do estoque com base nos produtos adicionados.

Sobrecarregue o operador << para imprimir as informações de um objeto da classe estoque.
Sobrecarregue o operador + para adicionar um produto ao estoque.
Sobrecarregue o operador - para remover um produto do estoque.

Crie uma função friend template chamada transferir_produtos() que receba como parâmetros
dois objetos da classe estoque (com o mesmo tipo template) e transfira todos os produtos
do primeiro estoque para o segundo estoque.

Adicione tratamento de exceções ao código para lidar com situações em que o usuário tente
adicionar produtos acima do limite do estoque (campo limite_armazenamento).

Crie uma funcao main que crie três objetos da classe estoque, com pelo menos três produtos
cada. Imprima as informações de cada estoque e transfira os produtos do primeiro estoque
para o segundo estoque. Imprima novamente as informações de cada estoque.
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Classe base Produto
class Produto {
protected:
    float valor;
    string codigoBarras;
    string nomeFabricante;

public:
    Produto(float valor, string codigoBarras, string nomeFabricante)
        : valor(valor), codigoBarras(codigoBarras), nomeFabricante(nomeFabricante) {}

    float getValor()  {
        return valor;
    }

    string getCodigoBarras() {
        return codigoBarras;
    }

    string getNomeFabricante() {
        return nomeFabricante;
    }

    // Método virtual para obter informações do produto
    virtual string info(){
        return "Valor: " + std::to_string(valor) + " \nCodigo de barras: " + codigoBarras +
               " \nNome do fabricante: " + nomeFabricante;
    }
};

// Classe derivada ProdutoAlimenticio, herda de Produto
class ProdutoAlimenticio : public Produto {
private:
    string dataValidade;
    string dataFabricacao;

public:
    // Construtor de ProdutoAlimenticio
    ProdutoAlimenticio(float valor, string codigoBarras, string nomeFabricante,
                       string dataValidade, string dataFabricacao)
        : Produto(valor, codigoBarras, nomeFabricante),
          dataValidade(dataValidade),
          dataFabricacao(dataFabricacao) {}

    // Sobrescrita do método info para incluir informações adicionais
    string info() override {
        return Produto::info() + " \nData de validade: " + dataValidade + " \nData de fabricacao: " + dataFabricacao;
    }
};

// Classe derivada ProdutoEletronico, herda de Produto
class ProdutoEletronico : public Produto {
private:
    string voltagem;
    float potencia;

public:
    // Construtor de ProdutoEletronico
    ProdutoEletronico(float valor, string codigoBarras, string nomeFabricante,
                      string voltagem, float potencia)
        : Produto(valor, codigoBarras, nomeFabricante),
          voltagem(voltagem),
          potencia(potencia) {}

    // Sobrescrita do método info para incluir informações adicionais
    string info() override {
        return Produto::info() + " \nVoltagem: " + voltagem + " \nPotencia: " + std::to_string(potencia);
    }
};

// Classe template estoque
template <typename T>
class estoque {
private:
    vector<T*> produtos;
    int quantidadeMax;

public:
    // Construtor do estoque
    estoque(int quantidadeMax) : quantidadeMax(quantidadeMax) {}

    // Método para inserir um produto no estoque
    void inserir(T* produto) {
        if (produtos.size() < quantidadeMax) {
            produtos.push_back(produto);
        } else {
            cout << "Estoque cheio" << endl;
        }
    }

    // Método para remover um produto do estoque
    void remover(T* produto) {
        for (int i = 0; i < produtos.size(); i++) {
            if (produtos[i] == produto) {
                produtos.erase(produtos.begin() + i);
                return;
            }
        }
    }

    // Sobrecarga do operador de inserção em stream para exibir o estoque
    friend ostream& operator<<(ostream& os, const estoque& e) {
        for (int i = 0; i < e.produtos.size(); i++) {
            os << e.produtos[i]->info() << endl;
        }
        return os;
    }

    // Sobrecarga do operador de adição para combinar dois estoques
    estoque operator+(const estoque& e) {
        estoque novo(quantidadeMax + e.quantidadeMax);
        for (int i = 0; i < produtos.size(); i++) {
            novo.inserir(produtos[i]);
        }
        for (int i = 0; i < e.produtos.size(); i++) {
            novo.inserir(e.produtos[i]);
        }
        return novo;
    }

    // Sobrecarga do operador de subtração para remover produtos de um estoque
    estoque operator-(const estoque& e) {
        estoque novo(quantidadeMax);
        for (int i = 0; i < produtos.size(); i++) {
            novo.inserir(produtos[i]);
        }
        for (int i = 0; i < e.produtos.size(); i++) {
            novo.remover(e.produtos[i]);
        }
        return novo;
    }

    // Método para calcular o valor total do estoque
    void calcularValorTotal() {
        float valorTotal = 0;
        for (int i = 0; i < produtos.size(); i++) {
            valorTotal += produtos[i]->getValor();
        }
        cout << "Valor total: " << valorTotal << endl;
    }

    // Função friend para transferir um produto entre dois estoques
    friend void transferir(estoque& e1, estoque& e2, T* produto) {
        e1.remover(produto);
        e2.inserir(produto);
    }
};

int main (){
    // Criação de dois estoques de produtos
    estoque<Produto> e1(3);
    estoque<Produto> e2(3);

    // Criação de produtos eletrônicos e alimentícios
    ProdutoEletronico* p1 = new ProdutoEletronico(100, "123", "Samsung", "220V", 1000);
    ProdutoEletronico* p2 = new ProdutoEletronico(200, "456", "LG", "110V", 2000);
    ProdutoEletronico* p3 = new ProdutoEletronico(300, "789", "Apple", "220V", 3000);

    ProdutoAlimenticio* p4 = new ProdutoAlimenticio(400, "101", "Nestle", "10/10/2020", "10/10/2019");
    ProdutoAlimenticio* p5 = new ProdutoAlimenticio(500, "202", "Coca-Cola", "10/10/2021", "10/10/2020");
    ProdutoAlimenticio* p6 = new ProdutoAlimenticio(600, "303", "Pepsi", "10/10/2022", "10/10/2021");

    try{
        // Inserção de produtos nos estoques
        e1.inserir(p1);
        e1.inserir(p2);
        e1.inserir(p3);
        e1.inserir(p4);
        e1.inserir(p5);
        e1.inserir(p6);
    } catch (const std::exception& e) {
        cout << e.what() << endl;
    }

    // Exibição dos estoques
    cout <<"Estoque 1: \n" << e1 << endl;
    cout <<"====================================\n"<< endl;
    cout <<"Estoque 2: \n" << e2 << endl;

    // Transferência de produtos do estoque 1 para o estoque 2
    cout <<"Transferindo produtos...\n"<< endl;
    transferir(e1, e2, p1);
    transferir(e1, e2, p2);
    transferir(e1, e2, p3);
    cout <<"trasnferencia concluida\n"<< endl;

    // Exibição dos estoques após a transferência
    cout <<"Estoque 1: \n" << e1 << endl;
    cout <<"====================================\n"<< endl;
    cout <<"Estoque 2: \n" << e2 << endl;

    return 0;
}
