#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <memory>
#include <sstream>

class Kid {
    std::string nome;
    int age;

public:
    Kid(std::string nome = "", int age = 0) : nome{nome}, age{age} {}

    friend std::ostream& operator<<(std::ostream& os, const Kid& k) {
        os << k.nome << ":" << k.age;
        return os;
    }

    std::string getNome() {
        return nome;
    }

    int getAge() {
        return age;
    }

    void setNome(std::string nome) {
        this->nome = nome;
    }

    void setAge(int age) {
        this->age = age;
    }
};

class Trampoline {
    std::list<std::shared_ptr<Kid>> playing;
    std::list<std::shared_ptr<Kid>> waiting;

public:
    Trampoline(int lugarFila) : playing(lugarFila, nullptr), waiting() {}  

    friend std::ostream& operator<<(std::ostream& os, const Trampoline& t) {
        os << "=> ";

        for (auto kid : t.waiting) {
            if (kid != nullptr) {
                os << *kid << " ";
            }
        }

        os << "=> [ ";

        for (auto kid : t.playing) {
            if (kid != nullptr) {
                os << *kid << " ";
            }
        }

        os << "]\n";
        return os;
    }

    void arrive(std::shared_ptr<Kid> kid) {
        this->waiting.push_back(kid);
    }

   void in() {
       if (this->waiting.empty()) {
           std::cout << "Nao ha ninguem na fila\n";
       }
       else {
           this->playing.push_back(this->waiting.front());
           this->waiting.pop_front();
       }
   }

   void out() {
       if (this->playing.empty()) {
           std::cout << "Nao ha ninguem no trampolim\n";
       }
       else {
           this->waiting.push_back(this->playing.front());
           this->playing.pop_front();
       }
    }

    std::shared_ptr<Kid> removerKid(std::string nome) {
        for (auto it = playing.begin(); it != playing.end(); it++) {
            if (it->get()->getNome() == nome) {
                return *playing.erase(it);
            }
        }

        for (auto it = waiting.begin(); it != waiting.end(); it++) {
            if (it->get()->getNome() == nome) {
                return *waiting.erase(it);
            }
        }
        return nullptr;
    }
};

int main() {
    Trampoline trampolim(0);

    while (true) {
        std::string cmd;
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        ss >> cmd;
        
        if (cmd == "arrive") {
            std::string nome {};
            int age {};
            ss >> nome >> age;
            trampolim.arrive(std::make_shared<Kid>(nome, age));
        }
        else if(cmd == "show") {
            std::cout << trampolim << '\n';
        }
        else if (cmd == "in") {
            trampolim.in();
        }
        else if (cmd == "out") {
            trampolim.out();
        }
        else if (cmd == "remove") {
            std::string nome {};
            ss >> nome;
            trampolim.removerKid(nome);
            std::cout << nome << '\n';
        }
        else if (cmd == "end") {
            break;
        }
        else {
            std::cout << "Comando invalido\n";
        }
    }
}