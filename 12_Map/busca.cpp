#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

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
    
    friend std::ostream& operator<<(std::ostream& os, const Fone& f) {
        os << f.id << ":" << f.numero;
        return os;
    }
};

class Contato {
    std::string nome;
    std::vector<Fone> fones;
    std::string prefix = "-";

public:
    Contato(){}
    
    Contato(std::vector<Fone> fones, std::string nome) : fones{fones}, nome{nome} {}

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
            std::cout << "Nao foi possivel remover o numero, indice invalido" << '\n';
        }
    }

    std::string getNome() {
        return this->nome;
    }

    std::vector<Fone> getFones() {
        return this->fones;
    }

    void setNome(std::string nome) {
        this->nome = nome;
    }

    friend std::ostream& operator<<(std::ostream& os, const Contato& contato) {
        os << contato.prefix << " " << contato.nome;

        for (int i = 0; i < (int) contato.fones.size(); i++) {
            os << " [" << i << ":" << contato.fones[i] << "]";
        }

        os << '\n';
        return os;
    }
};

class Agenda {
    std::map<std::string, Contato> contatos;

public:
    Agenda() {}

    void addContato(Contato contato) {
        auto it = this->contatos.find(contato.getNome());
        if (it == this->contatos.end()) {
            this->contatos[contato.getNome()] = contato;
        } else {
            for (Fone fone : contato.getFones()) {
                it->second.addFone(fone);
            }
        }
    }

    Contato* getContato(std::string nome) {
        auto it = this->contatos.find(nome);
        if (it != this->contatos.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void rmContato(std::string nome) {
        auto it = this->contatos.find(nome);
        if (it != this->contatos.end()) {
            this->contatos.erase(it);
        } else {
            std::cout << "Contato nao foi encontrado" << '\n';
        }
    }

    std::vector<Contato> search(std::string pattern) {
        std::vector<Contato> resultado;
        for (auto contato : this->contatos) {
            if (contato.first.find(pattern) != std::string::npos) {
                resultado.push_back(contato.second);
            }
        }
        return resultado;
    }

    std::map<std::string, Contato> getContatos() {
        return this->contatos;
    }

    friend std::ostream& operator<<(std::ostream& os,const Agenda& a) {
        for (auto contato : a.contatos) {
            os << contato.second << '\n';
        }
        return os;
    }
};

int main() {
    Agenda agenda = Agenda();
    
    Contato contato1 = Contato(std::vector<Fone>(), "Tom");
    contato1.addFone(Fone("Cel", "(88) 98765-4321"));
    contato1.addFone(Fone("Fixo", "(11) 92746-1522"));
    agenda.addContato(contato1);

    Contato contato2 = Contato(std::vector<Fone>(), "Bob");
    contato2.addFone(Fone("Cel", "(85) 99254-5578"));
    agenda.addContato(contato2);
    agenda.rmContato("Bob");

    Contato contato3 = Contato(std::vector<Fone>(), "Diana");
    contato3.addFone(Fone("Fixo", "(25) 98185-1274"));
    contato3.addFone(Fone("Cel", "(15) 99233-9681"));
    agenda.addContato(contato3);

    std::cout << agenda << '\n';
}