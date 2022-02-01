#include <iostream>
#include <algorithm>

struct Grafite {
    float calibre;
    std::string dureza;
    int tamanho;

    Grafite(float calibre = 0, std::string dureza = "", int tamanho = 0) :
       calibre{calibre}, dureza{dureza}, tamanho{tamanho} {
    }

    int desgastePorFolha() {
        if (this->dureza == "HB") {
            return 1;
        }
        if (this->dureza == "2B") {
            return 2;
        }
        if (this->dureza == "4B") {
            return 4;
        }
        if (this->dureza == "6B") {
            return 6;
        }
        return 0;
    }

    friend std::ostream& operator << (std::ostream& os, const Grafite& grafite) {
        os << "Calibre: " << grafite.calibre << " mm, ";
        os << "Dureza: " << grafite.dureza << ", ";
        os << "Tamanho: " << grafite.tamanho << " mm\n";

        return os;
    }
};

struct Lapiseira {
    float calibre;
    Grafite* grafite;

    Lapiseira(float calibre = 0, Grafite* grafite = nullptr) :
       calibre{calibre}, grafite{grafite} {
    }

    bool inserirGrafite(Grafite* grafite) {
        if (this->grafite != nullptr) {
            std::cout << "Ja possui grafite\n";
            return false;
        }
        if (grafite->calibre != this->calibre) {
            std::cout << "Calibre nao compativel\n";
            return false;
        }
        this->grafite = grafite;
        std::cout << "Grafite inserido com sucesso\n";
        return true;
    }

    Grafite* removerGrafite() {
        if (this->grafite == nullptr) {
            std::cout << "Nao foi possivel remover, pois ja esta sem grafite\n";
            return nullptr;
        }
        std::cout << "Grafite removido com sucesso\n";
        return std::exchange(this->grafite, nullptr);
    }

    bool escrever(int folhas) {
        if (this->grafite == nullptr) {
            std::cout << "Nao foi possivel escrever, pois a lapiseira nao possui grafite\n";
            return false;
        }
        while (this->grafite->tamanho > 0 && folhas > 0) {
            this->grafite->tamanho -= this->grafite->desgastePorFolha();
            folhas--;
        }
        if (this->grafite->tamanho <= 0) {
            std::cout << "Grafite esgotado\n";
            this->grafite = nullptr;
            return false;
        } else {
            std::cout << "Escrita concluida\n";
            return true;
        }
    }
};

int main() {
    Lapiseira lapiseira(0.5, nullptr);

    Grafite grafite(0.5, "HB", 10);
    lapiseira.inserirGrafite(&grafite);
    lapiseira.escrever(5);
    lapiseira.removerGrafite();

    std::cout << '\n';

    Grafite grafite2(0.2, "2B", 10);
    lapiseira.inserirGrafite(&grafite2);
    lapiseira.escrever(15);
    lapiseira.removerGrafite();

    std::cout << '\n';

    return 0;
}