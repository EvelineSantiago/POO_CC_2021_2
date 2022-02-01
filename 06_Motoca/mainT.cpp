#include <iostream>
#include <vector>
#include <sstream>

struct Pessoa {
    std::string nome;
    int idade;
    
    Pessoa(std::string nome = "", int idade = 0) : 
        nome{nome}, idade{idade} {
    }

    friend std::ostream& operator << (std::ostream& os, const Pessoa& pessoa) {
        os << "Nome: " << pessoa.nome << " Idade: " << pessoa.idade;
        return os;
    }
};

struct Trenzinho {
    static const int qtd_pessoas {10};
    Pessoa *pessoa [qtd_pessoas];
    int qtd_pessoas_atual {0};
    int tempo;
    int potencia;
   
    Trenzinho(int tempo = 0, int potencia = 1) : tempo{tempo}, potencia{potencia} {
        for (int i = 0; i < qtd_pessoas; i++) {
            pessoa[i] = nullptr;
        }
    }
    
    bool subirTrem(Pessoa *pessoa) {
        if (this->qtd_pessoas_atual == this->qtd_pessoas) {
            std::cout << "Trenzinho com capacidade maxima" << '\n';
            return false;
        } else if (pessoa->idade > 12) {
            std::cout << "Nao pode subir idade muita avancada" << '\n';
            return false;
        }
        this->pessoa[this->qtd_pessoas_atual] = pessoa;
        this->qtd_pessoas_atual++;
        return true;
    }

    Pessoa* removerPessoa() {
        if (this->qtd_pessoas_atual == 0) {
            std::cout << "Trenzinho vazio" << '\n';
            return nullptr;
        }
        Pessoa *pessoa = this->pessoa[this->qtd_pessoas_atual - 1];
        this->qtd_pessoas_atual--;
        return pessoa;
    }

    std::string buzinar() {
        return "P" + std::string(this->potencia, 'e') + "m";
    }

    void ticketTempo(int tempo) {
        this->tempo += tempo;
    }

    bool dirigir(int tempo) {
        if (this->qtd_pessoas_atual == 0) {
            std::cout << "Nao tem ninguem pra dirigir" << '\n';
            return false;
        } else if (tempo > this->tempo) {
            std::cout << "So conseguimos passear por " << this->tempo << " minutos" << '\n';
            this->tempo = 0;
            return false;
        }
        
        this->tempo -= tempo;
        std::cout << "Conseguimos passear por " << this->tempo << " minutos" << '\n';
        return true;
    }
};

int main() {
    Trenzinho trenzinho(1);

    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string comando;
        ss >> comando;
        if (comando == "subir") {
            std::string nome;
            int idade;
            ss >> nome >> idade;
        } else if (comando == "init") {
            int potencia;
            ss >> potencia;
            trenzinho.potencia = potencia;
        } else if (comando == "buzinar") {
            std::cout << trenzinho.buzinar() << '\n';
        } else if (comando == "dirigir") {
            int tempo;
            ss >> tempo;
            trenzinho.dirigir(tempo);
        } else if (comando == "inserir") {
            std::string nome;
            int idade;
            ss >> nome >> idade;
            Pessoa *pessoa = new Pessoa(nome, idade);
            if (!trenzinho.subirTrem(pessoa)) {
                delete pessoa;
            }
        } else if (comando == "retirar") {
            Pessoa *pessoa = trenzinho.removerPessoa();
            if (pessoa != nullptr) {
                delete pessoa;
            }
        } else if (comando == "sair") {
            break;
        } else {
            std::cout << "Comando invalido" << '\n';
        }
    }
    
}