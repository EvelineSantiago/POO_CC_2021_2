#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <string>
#include <map>
#include <stdexcept>

class Account {
protected:
    int id;
    float balance;
    std::string clientId;
    std::string type;

public:
    Account(int id, std::string clientId) : id(id), clientId(clientId) {}

    virtual void monthlyUpdate() = 0;

    void withdraw(float value) {
        this->balance -= value;
    }

    void deposit(float value) {
        this->balance += value;
    }

    void transfer(Account& other, float value) {
        this->withdraw(value);
        other.deposit(value);
    }

    int getId() {
        return this->id;
    }

    float getBalance() {
        return this->balance;
    }

    std::string getClientId() {
        return this->clientId;
    }

    std::string getType() {
        return this->type;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Account& account) {
        os << account.id << ":" << account.clientId << ":" << account.balance << ":" << account.type;
        return os;
    }   
};

class CheckingAccount : public Account {
public:
    CheckingAccount(int id, std::string clientId) : Account(id, clientId) {
        this->type = "CC";
    }

    void monthlyUpdate() override {
        this->balance -= 20;
    }
};

class SavingsAccount : public Account {
public:
   SavingsAccount(int id, std::string clientId) : Account(id, clientId) {
        this->type = "CP";
    }

    void monthlyUpdate() override {
        this->balance += this->balance * 0.01;
    }
};

class Client {
private:
    std::vector<std::shared_ptr<Account>> accounts;
    std::string clientId;

public:
    Client(std::string clientId) : clientId(clientId) {}

    void addAccount(std::shared_ptr<Account> account) {
        this->accounts.push_back(account);
    }

    std::vector<std::shared_ptr<Account>> getAccounts() {
        return this->accounts;
    }

    std::string getClientId() {
        return this->clientId;
    }

    void setAccounts(std::vector<std::shared_ptr<Account>> accounts) {
        this->accounts = accounts;
    }

    void setClientId(std::string clientId) {
        this->clientId = clientId;
    }

    friend std::ostream& operator<<(std::ostream& os, const Client& client) {
        os << client.clientId << " [";
        bool flag = true;
        for (auto account : client.accounts) {
            if (flag) {
                os << account->getId();
                flag = false;
                continue;
            }
            os << ", " << account->getId();
        }

        os << "]";
        return os;
    }
};

class BankAgency {
private:
    std::map<int, std::shared_ptr<Account>> accounts;
    std::map<std::string, std::shared_ptr<Client>> clients;
    int nextAccountId = 0;
    
    std::shared_ptr<Account> getAccount(int id) {
        return this->accounts[id];
    }

public:
    BankAgency() {}

    void addClient(std::string clientId) {
        auto it = this->clients.find(clientId);
        if (it == this->clients.end()) {
            this->clients[clientId] = std::make_shared<Client>(clientId);
            this->accounts[this->nextAccountId] = std::make_shared<CheckingAccount>(this->nextAccountId, clientId);
            this->accounts[this->nextAccountId + 1] = std::make_shared<SavingsAccount>(this->nextAccountId + 1, clientId);
            this->clients[clientId]->addAccount(this->accounts[this->nextAccountId]);
            this->clients[clientId]->addAccount(this->accounts[this->nextAccountId + 1]);
            this->nextAccountId += 2;
        } else {
            throw std::invalid_argument("fail: Cliente ja existe");
        }
    }

    void withdraw(int idConta, float value) {
        if (this->accounts.find(idConta) == this->accounts.end()) {
            throw std::invalid_argument("fail: Conta nao existe");
        } else {
            this->accounts[idConta].get()->withdraw(value);
        }
    }

    void monthlyUpdate() {
        for (auto account : this->accounts) {
            account.second->monthlyUpdate();
        }
    }

    void deposit(int idConta, float value) {
        if (idConta >= this->nextAccountId) {
            throw std::invalid_argument("fail: Conta nao existe");
        } else {
            this->accounts[idConta].get()->deposit(value);
        }
    }

    void transfer(int contaDe, int contaPara, float value) {
        if (contaDe >= this->nextAccountId || contaPara >= this->nextAccountId) {
            throw std::invalid_argument("fail: Conta nao existe");
        } else {
            this->accounts[contaDe].get()->transfer(*this->accounts[contaPara], value);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const BankAgency& bankAgency) {
        os << "Clients: " << '\n';
        for (auto client : bankAgency.clients) {
           os << "- " << *client.second << '\n';; 
        }
        os << "Accounts: " << '\n';
        for (auto account : bankAgency.accounts) {
            os << *account.second << '\n';
        }
        return os;
    }
};

int main() {
    BankAgency bankAgency;

    while (true) {
        std::string line, cmd;
        std::cin >> cmd;
        std::getline(std::cin, line);
        std::stringstream ss(line);

        try {
            if (cmd == "end") {
                break;
            } 
            else if (cmd == "show") {
                std::cout << bankAgency;
            }
            else if (cmd == "addClient") {
                std::string clientId;
                ss >> clientId;
                bankAgency.addClient(clientId);
            }
            else if (cmd == "update") {
                bankAgency.monthlyUpdate();
            }
            else if (cmd == "deposito") {
                int idConta;
                float value;
                ss >> idConta >> value;
                bankAgency.deposit(idConta, value);
            } 
            else if (cmd == "saque") {
                int idConta;
                float value;
                ss >> idConta >> value;
                bankAgency.withdraw(idConta, value);
            } 
            else if (cmd == "transf") {
                int contaDe, contaPara;
                float value;
                ss >> contaDe >> contaPara >> value;
                bankAgency.transfer(contaDe, contaPara, value);
            }
            else {
                std::cout << "fail: Comando invalido" << '\n';
            }
        } 
        catch (std::exception& e) {
            std::cout << e.what() << '\n';
        }
    }
}