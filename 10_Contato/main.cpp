#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Fone {
    std::string id;
    std::string numero;

public:
    Fone(std::string id, std::string numero) : id{id}, numero{numero} {}

    bool validate(std::string numero) {
        for (int i = 0; i < (int) numero.size(); i++) {
            if (numero[i] >= '0' || numero[i] <= '9' || numero[i] == '.' || numero[i] == '(' || numero[i] == ')') {
                return true;
            }
        }
        return false;
    }
    
    std::string getId() {
        return this->id;
    }

    std::string getNumero() {
        return this->numero;
    }

    void setId(std::string id) {
        this->id = id;
    }

    void setNumero(std::string numero) {
        this->numero = numero;
    }

    friend std::ostream &operator<<(std::ostream& os, const Fone& f) {
        os << f.id << ":" << f.numero;
        return os;
    } 
};

class Contato {
    std::string nome;
    std::vector<Fone> fones;
    std::string prefix = "-";

public:
    Contato(std::string nome, std::vector<Fone> fones) : nome{nome}, fones{fones} {}

    void addFone(Fone fone) {
        if (fone.validate(fone.getNumero())) {
            this->fones.push_back(fone);
        } else {
            std::cout << "Numero invalido" << '\n';
        }
    }

    void rmFone(int ind){
        if (ind >= 0 && ind < (int) this->fones.size()) {
            this->fones.erase(this->fones.begin() + ind);
        } else {
            std::cout << "Nao foi possivel remover o numero" << '\n';
        }
    }

    std::string getNome() {
        return nome;
    }

    std::vector<Fone> getFones() {
        return fones;
    }

    void setNome(std::string nome) {
        this->nome = nome;
    }

    friend std::ostream &operator<<(std::ostream& os, const Contato& c) {
        os << c.prefix << " " << c.nome;

        for (int i = 0; i < (int) c.fones.size(); i++) {
            os << " [" << i << ":" << c.fones[i] << "]";
        }

        os << '\n';
        return os;
    }
};

int main() {
    Contato contato("", {});

    while (true) {
        std::string line;
        std::string cmd;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        ss >> cmd;

        if (cmd == "init") {
            std::string nome {};
            ss >> nome;
            contato.setNome(nome);
        }
        else if (cmd == "show") {
            std::cout << contato;
        }
        else if (cmd == "add") {
            std::string id {};
            std::string numero {};
            ss >> id >> numero;
            contato.addFone(Fone(id, numero));
        }
        else if (cmd == "rm") {
            int ind {};
            ss >> ind;
            contato.rmFone(ind);
        }
        else if (cmd == "end") {
            break;
        }
        else {
            std::cout << "Comando invalido" << '\n';
        }
    }
}