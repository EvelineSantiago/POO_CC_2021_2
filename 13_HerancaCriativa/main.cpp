#include <iostream>

class Automovel {
protected:
    int velocidade;
    int combustivel;

public:
    Automovel(int velocidade, int combustivel) : velocidade{velocidade}, combustivel{combustivel} {
    }

    virtual void combustivel_Gasto() {
        std::cout << "Combustivel gasto" << '\n';
    }

    virtual void ligar_Automovel() {
        std::cout << "Ligando o automovel" << '\n';
    }

    virtual void dirigir_Automovel() {
        std::cout << "Dirigindo o automovel" << '\n';
    }

    friend std::ostream &operator<<(std::ostream &os, const Automovel& automovel) {
        os << "Velocidade: " << automovel.velocidade << '\n';
        return os;
    }
};

class Carro : public Automovel {
private:
    int qtdPortas;
    std::string cor;

public:
    Carro(int velocidade, int combustivel, int qtdPortas, std::string cor) : Automovel{velocidade, combustivel}, qtdPortas{qtdPortas}, cor{cor} {
    }

    virtual void ligar_Carro() {
        if (velocidade == 0) {
            std::cout << "Precisa rodar a chave para poder ligar carro" << '\n';
        } else {
            std::cout << "O carro ja esta ligado" << '\n';
        }
    }

    virtual void dirigir_Carro() {
        if (velocidade >= 20) {
            if (velocidade > 80){
                std::cout << "O carro esta quase estourando o limite de velocidade" << '\n';
            } else  if (velocidade >= 20) {
                std::cout << "O carro esta em movimento no limite certo" << '\n';
            } else if (velocidade < 20) {
                std::cout << "O carro esta parando" << '\n';
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Carro& carro) {
        Automovel* automovel = (Automovel*) &carro;
        os << *automovel << "Qtd de portas: " << carro.qtdPortas << '\n'
           << "Cor: " << carro.cor << '\n'
           << "Combustivel: " << carro.combustivel << '\n';
        return os;
    }
};

class Moto : public Automovel {
private:
    std::string modelo;
    std::string cor;

public:
    Moto(int velocidade, int combustivel, std::string modelo, std::string cor) : Automovel{velocidade, combustivel}, modelo{modelo}, cor{cor} {
    }

    virtual void ligar_Moto() {
        if (velocidade == 0) {
            std::cout << "Precisa rodar a chave para poder ligar moto" << '\n';
        } else {
            std::cout << "O moto ja esta ligado" << '\n';
        }
    }

    virtual void dirigir_Moto() {
        if (velocidade >= 20) {
            if (velocidade > 50){
                std::cout << "A moto esta quase estourando o limite de velocidade" << '\n';
            } else if (velocidade >= 20) {
                std::cout << "A moto esta em movimento no limite certo" << '\n';
            } else if (velocidade < 20) {
                std::cout << "Moto esta parando" << '\n';
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Moto& moto) {
        Automovel* automovel = (Automovel*) &moto;
        os << *automovel << "Modelo: " << moto.modelo << '\n'
           << "Cor: " << moto.cor << '\n'
           << "Combustivel: " << moto.combustivel << '\n';
        return os;
    }
};

int main() {
    Carro carro1(60, 200, 4, "Azul");
    carro1.ligar_Carro();
    carro1.dirigir_Carro();
    carro1.combustivel_Gasto();
    std::cout << carro1 << '\n';

    Moto moto1(0, 100, "Yamaha", "Vermelha");
    moto1.ligar_Moto();
    moto1.dirigir_Moto();
    moto1.combustivel_Gasto();
    std::cout << moto1 << '\n';

    return 0;
}