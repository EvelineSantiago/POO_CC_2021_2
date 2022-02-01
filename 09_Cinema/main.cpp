#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Cliente {
    std::string nome;
    std::string fone;

public:
    Cliente(std::string nome = "", std::string fone = "") : nome{nome}, fone{fone} {}
     
    friend std::ostream& operator<<(std::ostream& os, const Cliente& c) {
        os << c.nome << ":" << c.fone;
        return os;
    }

    std::string getNome() {
        return nome;
    }

    std::string getFone() {
        return fone;
    }

    void setNome(std::string nome) {
        this->nome = nome;
    }

    void setFone(std::string fone) {
        this->fone = fone;
    }  
};

class Cinema {
private:
    std::vector<std::shared_ptr<Cliente>> assentos;

public:

    Cinema(int capacidade ) : assentos(capacidade, nullptr) {}


    friend std::ostream& operator<<(std::ostream& os, const Cinema& c) {
        os << "[ ";

        for (auto assento : c.assentos) {
            if (assento == nullptr) {
                os << "- ";
            } else {
                os << *assento << " ";
            }
        }

        os << "]\n";

        return os;
    }

    int procurarCliente(std::string nome) {
        for (int i = 0; i < (int) assentos.size(); i++)
            if (assentos[i] != nullptr && assentos[i]->getNome() == nome) 
                return i;
        return -1;
    }

    bool reservar(std::string nome, std::string fone, int ind) {
        if (ind < 0 || ind >= this->assentos.size()) {
            std::cout << "Assento invalido" << '\n';
            return false;
        }
        if (assentos[ind] != nullptr) {
            std::cout << "Assento ocupado" << '\n';
            return false;
        }
        if (procurarCliente(nome) != -1) {
            std::cout << "Cliente ja esta no cinema" << '\n';
            return false;
        }   
        if (this->assentos[ind] == nullptr) {
            this->assentos[ind] = std::make_shared<Cliente>(nome, fone);
            return true;
        }
    }

    void cancelar(std::string nome){
        int ind = procurarCliente(nome);
        if (ind == -1) {
            std::cout << "Cliente nao encontrado no cinema" << '\n';
        }
        else {
            this->assentos[ind] = nullptr;
        }
    }
};

int main() {
    Cinema cinema(0);

    while (true) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "init") {
            int capacidade;
            std::cin >> capacidade;
            cinema = Cinema(capacidade);
        }
        else if (cmd == "show") {
            std::cout << cinema << '\n';
        }
        else if (cmd == "reservar") {
            std::string nome {};
            std::string fone {};
            int ind;
            std::cin >> nome >> fone >> ind;
            cinema.reservar(nome, fone, ind);
        }
        else if (cmd == "cancelar") {
            std::string nome {};
            std::cin >> nome;
            cinema.cancelar(nome);
        }
        else if (cmd == "end") {
            break;
        } 
        else {
            std::cout << "Comando invalido\n";
        }
    }
    return 0;
}