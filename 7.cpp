/*Para implementar a hierarquia de classes para representar diferentes tipos de plantas,
podemos seguir a descrição fornecida. Primeiro, criaremos a classe base chamada
Planta, com os atributos nome_cientifico, altura e tipo_de_folha. Em
seguida, criaremos uma classe derivada chamada Arvore que herda os atributos e
métodos da classe base Planta e adiciona atributos específicos, como
largura_do_tronco e tipo_de_copa. Por fim, criaremos outra classe derivada
chamada Flor que herda os atributos e métodos da classe base Planta e adiciona
atributos específicos, como cor_da_flor e numero_de_petalas*/

#include <iostream>
#include <string>

using namespace std;

class Planta {
protected:
    string nome_cientifico;
    double altura;
    string tipo_de_folha;

public:
    Planta(string nome, double altura, string folha)
        : nome_cientifico(nome), altura(altura), tipo_de_folha(folha) {}

    string getNomeCientifico() const {
        return nome_cientifico;
    }

    double getAltura() const {
        return altura;
    }

    string getTipoDeFolha() const {
        return tipo_de_folha;
    }
};

class Arvore : public Planta {
private:
    double largura_do_tronco;
    string tipo_de_copa;

public:
    Arvore(string nome, double altura, string folha, double tronco, string copa)
        : Planta(nome, altura, folha), largura_do_tronco(tronco), tipo_de_copa(copa) {}

    double getLarguraDoTronco() const {
        return largura_do_tronco;
    }

    string getTipoDeCopa() const {
        return tipo_de_copa;
    }
};

class Flor : public Planta {
private:
    string cor_da_flor;
    int numero_de_petalas;

public:
    Flor(string nome, double altura, string folha, string cor, int petalas)
        : Planta(nome, altura, folha), cor_da_flor(cor), numero_de_petalas(petalas) {}

    string getCorDaFlor() const {
        return cor_da_flor;
    }

    int getNumeroDePetalas() const {
        return numero_de_petalas;
    }
};

class ArvoreFlorifera : public Arvore, public Flor {
public:
    ArvoreFlorifera(string nome, double altura, string folha, double tronco, string copa,
                    string cor, int petalas)
        : Arvore(nome, altura, folha, tronco, copa), Flor(nome, altura, folha, cor, petalas) {}
};

/*Nessa implementação, a classe ArvoreFlorifera é criada como uma classe derivada
que herda tanto da classe Arvore quanto da classe Flor usando herança múltipla. A
herança múltipla permite que a classe ArvoreFlorifera tenha acesso aos atributos e
métodos tanto da classe Arvore quanto da classe Flor.*/



