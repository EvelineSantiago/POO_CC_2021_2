#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <memory>
#include <map>

class IMedico;

class IPaciente {
public:
    virtual std::string get_id();
    virtual void add_medico(IMedico* medico);
    virtual void remover_medico(std::string id_medico);
    virtual std::vector<IMedico*> get_medicos();
    virtual std::string get_diagnostico();
};

class IMedico {
public:
    virtual std::string get_id();
    virtual void add_paciente(IPaciente* paciente);
    virtual void remover_paciente(std::string id_paciente);
    virtual std::vector<IPaciente*> get_pacientes();
    virtual std::string get_classe();
};

class Medico : public IMedico {
    std::string id;
    std::string classe;
    std::map<std::string, IPaciente*> pacientes;

public:
    Medico(std::string id, std::string classe) : id{id}, classe{classe} {}

    void add_paciente(IPaciente* paciente) override {
        pacientes[paciente->get_id()] = paciente;
    }

    std::string get_classe() override {
        return this->classe;
    }

    std::string get_id() override {
        return this->id;
    }

    std::vector<IPaciente*> get_pacientes() override {
        std::vector<IPaciente*> pacientes;
        for (auto p : this->pacientes) {
            pacientes.push_back(p.second);
        }
        return pacientes;
    }

    void remover_paciente(std::string id_paciente) override {
        pacientes.erase(id_paciente);
    }

    friend std::ostream& operator<<(std::ostream& os, Medico& med) {
        os << "Med: " << med.id << ":" << med.classe << " Pacs: [";
        for (auto p : med.pacientes) {
            os << p.first << " ";
        }
        os << "]";
        return os;
    }


};