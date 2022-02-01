#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

//Filter
std::vector<int> clone(const std::vector<int>& v){
    std::vector<int> vetor;

    for (int i = 0; i < (int) v.size(); i++){
        vetor.push_back(v[i]);
    }

    return vetor;
}

std::vector<int> pegar_homens(const std::vector<int>& v){
    std::vector<int> p_homens;

    for (int i = 0; i < (int) v.size(); i++){
        if (v[i] > 0){
            p_homens.push_back(v[i]);
        }
    }

    return p_homens;
}

std::vector<int> pegar_calmos(const std::vector<int>& v){
    std::vector<int> p_calmos;

    for (int i = 0; i < (int) v.size(); i++){
        if (abs(v[i]) < 10){
            p_calmos.push_back(v[i]);
        }
    }

    return p_calmos;
}

std::vector<int> pegar_mulheres_calmas(const std::vector<int>& v){
    std::vector<int> mulheres_calmas;

    for (int i = 0; i < (int) v.size(); i++){
        if (abs(v[i]) < 10){
            mulheres_calmas.push_back(v[i]);
        }
    }

    return mulheres_calmas;
}

//Acesso
std::vector<int> inverter_com_copia(const std::vector<int>& v){
    std::vector<int> inverter;

    for (int i = (int) v.size() -1; i >= 0; i--){
        inverter.push_back(v[i]);
    }

    return inverter;
}

void inverter_inplace(std::vector<int>& v){
    int aux = 0;
    int j = v.size() - 1;

    for (int i = 0; i < (int) v.size() / 2; i++){
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
        j--;
    }
}

int sortear(const std::vector<int>& v){
    int numero_sort = 0;
        
    numero_sort = rand() % (v.size());

    return v[numero_sort];
}

void embaralhar(std::vector<int>& v){
    int aux = 0;

    for (int i = 0; i < (int) v.size() / 2; i++){
        int r = rand() % (int) v.size();
        aux = v[i];
        v[i] = v[r];
        v[r] = aux;
    }
}

void ordenar_vetor(std::vector<int>& v){
    int aux = 0;

    for (int i = 0; i < (int) v.size(); i++){
        for (int j = i+1; j < (int) v.size(); j++){
            if (v[i] > v[j]){
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}

//Conjuntos
bool ver_existe(std::vector<int> fila, int x){
    for (int i = 0; i < (int) fila.size(); i++)
        if (fila[i] == x)
           return true;
    return false;
}


std::vector<int> exclusivos(const std::vector<int>& v){
    std::vector<int> aux;
    
    for (int i = 0; i < (int) v.size(); i++){
        if (!ver_existe(aux, v[i])){
            aux.push_back(v[i]);
        }
    }

    return aux;
}

std::vector<int> diferentes(const std::vector<int>& v){
    std::vector<int> aux;
    
    for (int i = 0; i < (int) v.size(); i++){
        if (!ver_existe(aux, abs(v[i]))){
            aux.push_back(abs(v[i]));
        }
    }

    return aux;
}

bool ver_repetidos(std::vector<int> fila, int x){
    int cont = 0;

    for (int i = 0; i < (int) fila.size(); i++){
        if (fila[i] == x){
            cont += 1;
        }
    }

    if (cont > 1)
        return true;
    return false;
}

std::vector<int> abandonados(const std::vector<int>& v){
    std::vector<int> aux;

    for (int i = 0; i < (int) v.size(); i++){
        if (ver_repetidos(v, v[i]) && !ver_existe(aux, v[i])){
            aux.push_back(v[i]);
        }
    }

    return aux;
}

int main()
{
    //Filter
    for (int i : clone({1, 2, 3, 4, 5, 6})){
        std::cout << i << " ";
    }

    std::cout << '\n';

    for (int i : pegar_homens({1, -2, 4, -5, 6, -8, 9})){
        std::cout << i << " ";
    }

    std::cout << '\n';
   
    for (int i : pegar_calmos({2, -3, -4, 5, -6, 8, 9})){
        std::cout << i << " ";
    }

    std::cout << '\n';

    for (int i : pegar_mulheres_calmas({-2, 3, -4, 5, -6, 8, -9})){
        std::cout << i << " ";
    }

    std::cout << '\n';

    //Acesso
    for (int i : inverter_com_copia({2, -4, 6, -8, 10})){
        std::cout << i << " ";
    }

    std::cout << '\n';

    std::vector<int> array1{1, 2, 3, 4, 5, 6};
    inverter_inplace(array1);
    for (int i : array1){
        std::cout << i << " ";
    }
   
    std::cout << '\n';
    
    srand(time(NULL));
    std::cout << sortear({1, 2, 3, 4, 5, 6}) << '\n';

    srand(time(NULL));
    std::vector<int> array2{1, 2, 3, 4, 5, 6};
    embaralhar(array2);
    for (int i : array2){
        std::cout << i << " ";
    }

    std::cout << '\n'; 

    std::vector<int> array3{3, -2, -1, 0, 4, 1, 2};
    ordenar_vetor(array3);
    for (int i : array3){
        std::cout << i << " ";
    }

    std::cout << '\n';

    //Conjuntos
    for (int i : exclusivos({1, 3, 4, 3, -1, -2, -2})){
        std::cout << i << " ";
    }

    std::cout << '\n';

    for (int i : diferentes({1, 3, 4, 3, -1, -2, -2})){
        std::cout << i << " ";
    }

    std::cout << '\n';

    for (int i : abandonados({1, 3, 4, 3, -1, -2, -2})){
        std::cout << i << " ";
    }

    std::cout << '\n';

    return 0;
}