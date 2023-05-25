#include <iostream>

using std::cout;
using std::endl;

class pessoa {
	int cpf;
	int idade;
	float altura;
	static int contador;
	static float soma_altura;
public:
	pessoa(int c, int i, float a) {
		cpf = c;
		idade = i;
		altura = a;
		soma_altura += a;
		contador++;
	}
	/* gets e sets */
	static int get_contador() {
		return contador;
	}
	static float get_media_altura() {
		if (contador > 0) {
			return soma_altura / contador;
		}
		else {
			return 0;
		}
	}
};

class professor : public pessoa {
	int matricula;
	int ano_admissao;
	int titulacao;
	static int soma_idade;
	static int contador;
public:
	professor(int c, int i, float a,
		  int m, int aa, int t):
		   pessoa(c, i, a) {
		matricula = m;
		ano_admissao = aa;
		titulacao = t;
		soma_idade += i;
		contador++;
	}
	/* gets e sets */
	static float get_media_idade() {
		if (contador == 0) 
			return 0;

		return ((float)soma_idade)/contador;
	}
};

class aluno : public pessoa {
	int matricula;
	float cra;
	static int soma_idade;
	static int contador;
public:
	aluno(int c, int i, float a, 
	      int m, float cr):pessoa(c,i,a) {
		matricula = m;
		cra = cr;
		soma_idade += i;
		contador++;
	}
	void set_matricula(int m) {
		matricula = m;
	}
	int get_matricula() {
		return matricula;
	}
	void set_cra(float c) {
		cra = c;
	}
	float get_cra() {
		return cra;
	}
	static float get_media_idade() {
		if (contador == 0) 
			return 0;
		return ((float)soma_idade)/contador;
	}
};

class turma {
	int codigo;
	professor* responsavel;
	aluno** grupo;
	int tamanho;
	int qtd_alunos;
	static turma* instance;
	turma() {
		codigo = 0;
		responsavel = nullptr;
		qtd_alunos = 0;
		tamanho = 0;
	}
public:
	~turma() {
		delete[] grupo;
	}
	static turma* get_instance() {
		if (instance == nullptr) {
			instance = new turma;
		} 
		return instance;	
	}
	void set_responsavel(professor* p) {
		responsavel = p;
	}
	professor* get_responsavel() {
		return responsavel;
	}
	void create_grupo(int i) {
		//grupo = (aluno**)malloc(
		//		sizeof(aluno*)*i);
		grupo = new aluno*[i];
		tamanho = i;
	}
	void add_aluno(aluno* a) {
		if (grupo == NULL) {
			cout << "Turma nao alocada";
			cout << endl;
			return;
		}
		if (qtd_alunos < tamanho) {
			grupo[qtd_alunos] = a;
			qtd_alunos++;
		} else { 
			cout << "Turma lotada!";
			cout << endl;
		}
	}
	aluno* get_aluno(int i) {
		return grupo[i];
	}
	float get_media_cra() {
		if (qtd_alunos == 0) {
			return 0;
		}
		float soma = 0;
		for (int i = 0; i < qtd_alunos; i++) {
			soma += grupo[i]->get_cra();
		}
		return (soma / qtd_alunos);
	}
};

int pessoa::contador = 0;
int aluno::contador = 0;
int professor::contador = 0;
int professor::soma_idade = 0;
int aluno::soma_idade = 0;
float pessoa::soma_altura = 0;
turma* turma::instance = nullptr;

int main() {
	aluno a1(1011, 29, 1.80, 202109, 8.5);
	aluno a2(2345, 22, 1.67, 202010, 7.6);
	aluno a3(1234, 32, 1.81, 201906, 7.0);

	professor p1(9876, 45, 1.76, 1764, 1999, 3);

	turma* t = turma::get_instance();

	t->create_grupo(5);

	t->set_responsavel(&p1);

	t->add_aluno(&a1);
	t->add_aluno(&a2);
	t->add_aluno(&a3);

	cout << "a) quantidade de pessoas: ";
	cout << pessoa::get_contador() << endl;
	cout << "b) media dos cra: ";
	cout << t->get_media_cra() << endl; 
	cout << "c) media altura pessoas: ";
	cout << pessoa::get_media_altura() << endl;
	cout << "d.1) media idade profs: ";
	cout << professor::get_media_idade() << endl;
	cout << "d.2) media idade alunos: ";
	cout << aluno::get_media_idade() << endl;

	return 0;
}
