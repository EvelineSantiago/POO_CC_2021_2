#include <iostream>
#include <vector>
#include <algorithm>

//Map
std::vector<int> sozinhos(const std::vector<int>& fila){
    std::vector<int> sozinhos;

    for(int i = 0; i < (int) fila.size(); i++){
        bool not_exists{true};

        for (int j = 0; j < (int) fila.size(); j++){
            if (i != j && abs(fila[i]) == abs(fila[j])){
                not_exists = false;
                break;
            }
        }

        if (not_exists){
            sozinhos.push_back(fila[i]);
        }
    }

    return sozinhos;
}

int ocorrencias(const std::vector<int>& fila){
    int maior = 1;
    
    for (int i = 0; i < (int) fila.size(); i++){
        int cont = 0;
        for (int j = 0; j < (int) fila.size(); j++){
            if (abs(fila[i]) == abs(fila[j])){
                cont++;
            }
        }
        if (cont > maior){
            maior = cont;
        }
    }

    return maior;
}

std::vector<int> recorrentes(const std::vector<int>& fila){
    std::vector<int> repetidos;
    int maior = 0;
    
    for (int i = 0; i < (int) fila.size(); i++){
        int cont = 0;
        for (int j = i+1; j < (int) fila.size(); j++){
            if (abs(fila[i]) == abs(fila[j])){
                cont++;
            }
        }
        if (cont > maior){
            maior = cont;
        }
    }

    for (int i = 0; i < (int) fila.size(); i++){
        int cont = 0;
        for (int j = i+1; j < (int) fila.size(); j++){
            if (abs(fila[i]) == abs(fila[j])){
                cont++;
            }
        }
        if (cont == maior){
            repetidos.push_back(fila[i]);
        }
    }

    return repetidos;
}

//Proximidade
int briga(const std::vector<int>& fila){
    int cont = 0;

    for (int i = 0; i < (int) fila.size(); i++){
        if (abs(fila[i]) > 50 && abs(fila[i-1]) > 30 && abs(fila[i+1]) > 30){
            cont++;
        }
    }

    return cont;
}

std::vector<int> apaziguado(const std::vector<int>& fila){
    std::vector<int> posicao;

    for (int i = 0; i < (int) fila.size(); i++){
        if (i == ((int) fila.size() - 1)){
            if (abs(fila[i]) > 80 && (abs(fila[i-1]) < 10)) posicao.push_back(i);
        }else if(i == 0){
            if(abs(fila[i]) > 80 && (abs(fila[i+1]) < 10)) posicao.push_back(i);
        }else{
            if(abs(fila[i]) > 80 && (abs(fila[i+1]) < 10 || abs(fila[i-1]) < 10)) posicao.push_back(i);
        }
    }

    return posicao;
}

//Sequencias
int quantos_times(const std::vector<int>& fila){
    int contP = 0, contN = 0, times = 0;

    for (int i = 0; i < (int) fila.size(); i++){
        if (fila[i] > 0){
            contP++;

            if (fila[i+1] < 0 && (i+1) < (int) fila.size()){
                if (contP >= 2){
                    times++;
                }
            }
            contN = 0;
        }
        else{
            contN++;

            if (fila[i+1] > 0 && (i+1) < (int) fila.size()){
                if (contN >= 2){
                    times++;
                }
            }
            contP = 0;
        }
    }

    return times;
}

int maior_time(const std::vector<int>& fila){
    int contP = 0, contN = 0, maior_time = 0;

    for (int i = 0; i < (int) fila.size(); i++){
        if (fila[i] > 0){
            contP++;

            if (fila[i+1] < 0 && (i+1) < (int) fila.size()){
                if (contP >= 2){
                    if (maior_time < contP){
                        maior_time = contP;
                    }
                }
            }
            contN = 0;
        }
        else{
            contN++;

            if (fila[i+1] > 0 && (i+1) < (int) fila.size()){
                if (contN >= 2){
                    if (maior_time < contN){
                        maior_time = contN;
                    }
                }
            }
            contP = 0;
        }
    }

    return maior_time;
}

int sozinhosT(const std::vector<int>& fila){
    int cont = 0;

    for (int i = 0; i < (int) fila.size(); i++){
        if (fila[i] > 0 && (fila[i+1] < 0 && fila[i-1] < 0)){
            cont++;
        }
        if (fila[i] < 0 && (fila[i+1] > 0 && fila[i-1] > 0)){
            cont++;
        }
    }

    return cont;
}

//Grupos

//Alteracao
std::vector<int> remove(std::vector<int> fila, int X){
    for (int i = 0; i < (int) fila.size(); i++){
        if (fila[i] == X){
            fila.erase(fila.begin() + i);
        }
    }

    return fila;
}

std::vector<int> insert(std::vector<int> fila, int X, int Y){
    for (int i = 0; i < (int) fila.size(); i++){
        if (i == Y){
            fila.insert(fila.begin() + i, X);
        }
    }

    return fila;
}

int main(){
    //Map
    for (int i : sozinhos({1, 3, 4, 3, -1, -3, -3})){ 
        std::cout << i << " ";
    }

    std::cout << '\n';

    std::cout << ocorrencias({1, 3, 4, 5, -1, -5, -5}) << '\n'; 

    for(int i : recorrentes({1, 3, 4, 5, -1, -5, -5, 3, -3})){ 
        std::cout << i << " ";
    }

    std::cout << '\n';

    //Proximidade
    std::cout << briga({50, 98, 31, -51, 31, -99, 32}) << '\n';
    
    for (int i : apaziguado({83, -4, 65, 8, -99, 12})){ 
        std::cout << i << " ";
    }

    std::cout << '\n';

    //Sequencias
    std::cout << quantos_times({5, 3, 1, -20, 4, 45, -15, -22, -9, 10}) << '\n';

    std::cout << maior_time({8, -5, 4, -25, -9, 30, -12, -45}) << '\n';

    std::cout << sozinhosT({-10, 2, 6, -22, -19, 55, -25, -12, -9}) << '\n';

    //Grupos

    //Alteracao
    for (int i : remove({-2, 3, 4, -6, -7, 1, 9, -8}, -7)){
        std::cout << i << " ";
    }

    std::cout << '\n';

    for (int i : insert({-10, -9, 6, 3, -7, -1, -2,}, -20, 3)){
        std::cout << i << " ";
    }

    std::cout << '\n';

}