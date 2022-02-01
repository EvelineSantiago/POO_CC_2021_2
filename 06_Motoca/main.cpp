#include <iostream>
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

struct Motoca {
    Pessoa *pessoa {nullptr};
    int tempo;
    int potencia;

    Motoca(int potencia = 1) : potencia{potencia}, tempo{0} {
    }

    bool addPessoa(Pessoa* pessoa) {
        if (this->pessoa != nullptr) {
            std::cout << "Moto cheia" << '\n';
            return false;
        } else if (pessoa->idade < 18) {
            std::cout << "Pessoa menor de idade nao pode andar" << '\n';
            return false;
        }
        this->pessoa = pessoa;
        return true;
    }
    
    Pessoa* removerPessoa() {
        Pessoa* pessoa = this->pessoa;
        this->pessoa = nullptr;
        return pessoa;
    }

    std::string buzinar() {
        if (this->pessoa == nullptr) {
            return "Moto esta vazia, logo nao ha como buzina\n";
        }
        return "Bi" + std::string(this->potencia, 'i') + "r"; 
    }

    void ticketTempo(int tempo) {
        this->tempo += tempo;
    }

    bool dirigir(int tempo) {
        if (this->pessoa == nullptr) {
            std::cout << "Nao tem ninguem pra pilotar a moto" << '\n';
            return false;
        }
        if (tempo > this->tempo) {
            std::cout << "So conseguiu dirigir por " << this->tempo << " minutos" << '\n';
            this->tempo = 0;
            return false;
        }

        this->tempo -= tempo;
        std::cout << "Conseguiu dirigir " << this->tempo << " minutos" << '\n';
        return true;
    }

    friend std::ostream& operator << (std::ostream& os, const Motoca& moto) {
        os << "Potencia: " << moto.potencia << " Tempo: " << moto.tempo;
        os << "[" << (moto.pessoa == nullptr ? "null" : moto.pessoa->nome) << "]";
        return os;
    }
};

int main() {
    Motoca BMW(1);
    
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string command;
        ss >> command;
        if (command == "end") {
            break;
        } else if (command == "init") {
            int potencia;
            ss >> potencia;
            BMW.potencia = potencia;
        } else if (command == "show") {
            std::cout << BMW << '\n';
        } else if (command == "inserir") {
            std::string nome;
            int idade;
            ss >> nome >> idade;
            Pessoa* pessoa = new Pessoa(nome, idade);
            if (!BMW.addPessoa(pessoa)) {
                delete pessoa;
            }
        } else if (command == "retirar") {
            Pessoa* pessoa = BMW.removerPessoa();
            if (pessoa != nullptr) {
                delete pessoa;
            }
        } else if (command == "dirigir") {
            int tempo;
            ss >> tempo;
            BMW.dirigir(tempo);
        } else if (command == "ticket") {
            int tempo;
            ss >> tempo;
            BMW.ticketTempo(tempo);
        } else if (command == "buzinar") {
            std::cout << BMW.buzinar() << '\n';
        } else {
            std::cout << "Comando invalido" << '\n';
        }
    }
}