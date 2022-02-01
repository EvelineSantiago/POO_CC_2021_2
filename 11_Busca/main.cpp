#include <iostream>
#include <vector>
#include <sstream>
#include <string>
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

    friend std::ostream& operator<<(std::ostream& os, const Contato& c) {
        os << c.prefix << " " << c.nome;

        for (int i = 0; i < (int) c.fones.size(); i++) {
            os << " [" << i << ":" << c.fones[i] << "]";
        }

        os << '\n';
        return os;
    }
};

class Agenda {
    std::vector<Contato> contatos; 

    int findPosByName(std::string nome) {
        for (int i = 0; i < (int) this->contatos.size(); i++) {
            if (this->contatos[i].getNome() == nome) {
                return i;
            }
        }
        return -1;
    }

public:
    Agenda() {}

    void addContato(Contato contato) {
        this->contatos.push_back(contato);
        std::sort(this->contatos.begin(), this->contatos.end(), [](Contato c1, Contato c2) {
            if (c1.getNome() != c2.getNome()) {
                return c1.getNome() < c2.getNome();
            } 
        });
    }

    Contato* getContato(std::string nome) {
        int ind = findPosByName(nome);
        if (ind != -1) {
            return &this->contatos[ind];
        }
        return nullptr;
    }


    void rmContato(std::string nome) {
        int ind = findPosByName(nome);
        if (ind != -1) {
            this->contatos.erase(this->contatos.begin() + ind);
        } else {
            std::cout << "Nao foi possivel remover o contato" << '\n';
        }
    }

    std::vector<Contato> search(std::string pattern){
        std::vector<Contato> resultado;
        for (auto& c : this->contatos) {
            std::stringstream ss;
            ss << c;
            std::string texto = ss.str();
            if (texto.find(pattern) != std::string::npos) {
                resultado.push_back(c);
            }
        }
        return resultado;
    }

    std::vector<Contato> getContatos() {
        return this->contatos;
    }

    friend std::ostream& operator<<(std::ostream& os, const Agenda& agenda) {
        for (int i = 0; i < (int) agenda.contatos.size(); i++) {
            os << agenda.contatos[i] << '\n';
        }
        return os;
    }
};

int main() {
    Agenda agenda = Agenda();

    Contato c1 = Contato(std::vector<Fone>(), "Jason");
    c1.addFone(Fone("Cel", "(88) 98674-5226"));
    c1.addFone(Fone("Fixo", "(11) 92675-9321"));
    agenda.addContato(c1);
     
    std::vector<Contato> resultado = agenda.search("j");
    for (auto& c : resultado) {
        std::cout << c;
    }

    std::cout << '\n';

    Contato c2 = Contato(std::vector<Fone>(), "Rhita");
    c2.addFone(Fone("Cel", "(85) 99567-4432"));
    c2.addFone(Fone("Fixo", "(12) 98188-5542"));
    agenda.addContato(c2);
    agenda.rmContato("Rhita");
    std::cout << agenda;

    return 0;
}