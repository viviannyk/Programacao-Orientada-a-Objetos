#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class conta {
    private:
        int numero;
        float saldo;
        string titular;
    public:
        conta(int n, float s, const string& t) {
            numero = n;
            saldo = s;
            titular = t;
        }
        int get_numero() {
            return numero;
        }
        float get_saldo() {
            return saldo;
        }
        string get_titular() {
            return titular;
        }
        void set_numero(int n) {
            numero = n;
        }
        void set_saldo(float s) {
            saldo = s;
        }
        void set_titular(const string& t) {
            titular = t;
        }
        void depositar(float valor) {
            this->saldo += valor;
        }
        void sacar(float valor) {
            this->saldo -= valor;
        }
        void print() {
            cout << "Numero: " << this->numero << endl;
            cout << "Saldo: " << this->saldo << endl;
            cout << "Titular: " << this->titular << endl;
        }
};

class conta_corrente : public conta {
    private:
        float limite;
    public:
        conta_corrente(int numero, float saldo, 
                const string& titular, float limite) : 
                conta(numero, saldo, titular) {
            this->limite = limite;
        }
        void sacar(float valor) {
            if (valor > this->get_saldo() + this->limite) {
                cout << "Saldo insuficiente" << endl;
            } else {
                this->set_saldo(get_saldo() + valor);
            }
        }
};

class conta_poupanca : public conta {
    private:
        float rendimento;
    public:
        conta_poupanca(int numero, float saldo, 
        const string& titular, float rendimento) :
        conta(numero, saldo, titular) {
            this->rendimento = rendimento;
        }
        void render() {
            this->set_saldo(get_saldo()+
                    (get_saldo() * this->rendimento));
        }
};

class banco {
    private:
        conta** contas;
        int n_contas;
    public:
        banco(int n) {
            contas = new conta*[n];
            n_contas = 0;
        }
        void adicionar_conta(conta* c) {
            contas[n_contas] = c;
            n_contas++;
        }
        void listar_contas() {
            for (int i = 0; i < n_contas; i++) {
                contas[i]->print();
            }
        }
};

int main(void) {
    banco b(2);

    conta_corrente cc(1, 1000, "Joao", 100);
    conta_poupanca cp(2, 2000, "Maria", 0.1);

    b.adicionar_conta(&cc);
    b.adicionar_conta(&cp);

    b.listar_contas();

    cc.sacar(100);
    cp.sacar(100);
    cp.render();
    cc.depositar(150);
    cc.sacar(10);
    cc.sacar(10000);

    b.listar_contas();

    return 0;
}
