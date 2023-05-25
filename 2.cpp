#include <iostream>
#include <string>
/*
Faça em C++ um programa para controle de um estoque de veiculos de uma 
locadora, utilizando as classes descritas a segiuir, com seus respectivos
atributos e métodos.
- Veiculo: classe abstrata com atributos ano de fabricação (int), valor (float);
além dos 'gets' e 'sets' para os atributos, definir dois métodos protegidos e 
virtuais: um (print_info) para exibir as informações do veículo na saída padrão
(cout) e outro (ipva_calculado) sem implementação, para retornar o valor do IPVA.
- Carro: classe que estende Veiculo e acrescenta os atributos motor (float) e 
  quantidade de portas (int); além dos 'gets' e 'sets' para os atributos, 
  sobreescrever o método print_info com as informações específicas do carro e
  implementar o método ipva_calculado usando a formula:
  ((idade do veículo) * (motor/10)) + (valor/1000)
- Moto: classe que estende Veiculo e acrescenta os atributos cilindradas (float)
  e aro (int); além dos 'gets' e 'sets' para os atributos, sobreescrever o método
  print_info com as informações específicas da moto e implementar o método 
  ipva_calculado usando a formula:
  ((idade do veículo) * (cilindradas/100)) + (valor/1100)
- Caminhao: classe que estende Veiculo e acrescenta os atributos eixos (float)
  e carga (float); além dos 'gets' e 'sets' para os atributos, sobreescrever 
  o método print_info com as informações específicas do caminhao e implementar
  o método ipva_calculado usando a formula:
  ((idade do veículo) * (eixos/2)) + (carga/1000) + (valor/900)

a) Cadastre uma instância de cada tipo de veículo.
b) Invoque o método print_info() de cada uma das instâncias. Explique o que foi 
   feito para a implementação adequada deste método - como foi a herançae e 
   posterior sobrescrita do método.
c) Insira todos os veiculos em um array de ponteiros para veículo e use esse
   array para calcular a média dos valores de IPVA dos veículos.
d) Descreva nos comentários o conceito de herança, e explique também o que é uma
   classe abstrata e qual sua relação com métodos virtuais em C++.
*/

#define ANO_CORRENTE 2023
#define QTD_VEICULOS 3

using std::cout;
using std::endl;

class veiculo {
    int ano_fabricacao;
    float valor;
protected:
    virtual void print_info() {
        cout << "Ano de fabricação: " << ano_fabricacao << endl;
        cout << "Valor: " << valor << endl;
    }
public:
    veiculo(int a, float v) : ano_fabricacao(a), valor(v) {}
    int get_ano_fabricacao() { return ano_fabricacao; }
    float get_valor() { return valor; }
    void set_ano_fabricacao(int a) { ano_fabricacao = a; }
    void set_valor(float v) { valor = v; }
    virtual float ipva_calculado() = 0;
};

class carro : public veiculo {
    int quantidade_portas;
    float motor;
public:
    carro(int a, float v, int q, float m) : veiculo(a, v), 
            quantidade_portas(q), motor(m) {}
    int get_quantidade_portas() { return quantidade_portas; }
    float get_motor() { return motor; }
    void set_quantidade_portas(int q) { quantidade_portas = q; }
    void set_motor(float m) { motor = m; }
    void print_info() {
        veiculo::print_info();
        cout << "Quantidade de portas: " << quantidade_portas << endl;
        cout << "Motor: " << motor << endl;
    }
    float ipva_calculado() {
        return ((ANO_CORRENTE - get_ano_fabricacao()) * (motor/10)) + (get_valor()/1000);
    }
};

class moto : public veiculo {
    float cilindradas;
    int aro;
public:
    moto(int a, float v, float c, int aro) : veiculo(a, v), 
            cilindradas(c), aro(aro) { }
    float get_cilindradas() { return cilindradas; }
    int get_aro() { return aro; }
    void set_cilindradas(float c) { cilindradas = c; }
    void set_aro(int a) { aro = a; }
    void print_info() {
        veiculo::print_info();
        cout << "Cilindradas: " << cilindradas << endl;
        cout << "Aro: " << aro << endl;
    }
    float ipva_calculado() {
        return ((ANO_CORRENTE - get_ano_fabricacao()) * (cilindradas/100)) + (get_valor()/1100);
    }    
};

class caminhao : public veiculo {
    int quantidade_eixos;
    float carga;
public:
    caminhao(int a, float v, int q, float c) : veiculo(a, v), 
                quantidade_eixos(q), carga(c) { }
    int get_quantidade_eixos() { return quantidade_eixos; }
    float get_carga() { return carga; }
    void set_quantidade_eixos(int q) { quantidade_eixos = q; }
    void set_carga(float c) { carga = c; }
    void print_info() {
        veiculo::print_info();
        cout << "Quantidade de eixos: " << quantidade_eixos << endl;
        cout << "Carga: " << carga << endl;
    }
    float ipva_calculado() {
        return ((ANO_CORRENTE - get_ano_fabricacao()) * (quantidade_eixos/2)) + (carga/1000) + (get_valor()/900);
    }
};

/*
Explique como poderia ser implementada a classe MotoCarro, sendo que esta
possui características das classes Moto e Carro. Explique o mecanismo utilizado
e quais são os possíveis problemas a serem enfrentados e como podem ser 
solucionados.
*/

class moto_carro : public moto, public carro {
    int quantidade_rodas;
public:
    moto_carro(int qr, int a, float v, float c, int aro,
               int qp, float m) :
            moto(a, v, c, aro), 
            carro(a, v, qp, m), quantidade_rodas(qr) { }
    int get_qtd_rodas() { return quantidade_rodas; }
    void set_quantidade_rodas(int q) { quantidade_rodas = q; }
};

int main() {
    veiculo* veiculos[QTD_VEICULOS];
    carro c1(2010, 10000, 4, 1.6);
    moto m1(2015, 5000, 150, 17);
    caminhao ca1(2018, 20000, 4, 10000);
    moto_carro mc1(4, 2019, 10000, 150, 17, 4, 1.6);

    mc1.carro::set_valor(15000);
    mc1.moto::set_ano_fabricacao(2020);

    veiculos[0] = &c1;
    veiculos[1] = &m1;
    veiculos[2] = &ca1;

    c1.print_info();
    m1.print_info();
    ca1.print_info();

    float media = 0;
    float soma_ipva = 0;

    for (int i = 0; i < QTD_VEICULOS; i++) {
        soma_ipva += veiculos[i]->ipva_calculado();
    }
    cout << "Media dos IPVA: " << soma_ipva/QTD_VEICULOS << endl;

    return 0;
}