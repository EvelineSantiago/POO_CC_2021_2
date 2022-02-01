#include <iostream>
#include <vector>
#include <algorithm>

//Busca
bool existe(std::vector<int> fila, int x){
    for(int i = 0; i < (int) fila.size(); i++)
        if(fila[i] == x)
           return true;
    return false;
}

int contar(std::vector<int> fila, int x){
    int cont = 0;

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] == x){
           cont++;
        }
    }

    return cont;
}

int procurar_valor(std::vector<int> fila, int x){
    for(int i = 0; i < (int) fila.size(); i++)
        if(fila[i] == x)
           return i;
    return -1;
}

int procurar_valor_apartir(std::vector<int> fila, int x, int inicio){
    for(int i = inicio; i < (int) fila.size(); i++)
        if(fila[i] == x)
           return i;
    return -1;
}

//Melhor Caso
int procurar_menor(std::vector<int> fila){
    int menor = 0;

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] < menor){
            menor = fila[i];
        }
    }

    return menor;
}

int procurar_menor_pos(std::vector<int> fila){
    int menor_pos = 0;

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] < menor_pos){
            menor_pos = i;
        }
    }

    return menor_pos;
}

int procurar_menor_pos_apartir(std::vector<int> fila, int inicio){
    int menor_pos = 0;

    for(int i = inicio; i < (int) fila.size(); i++){
        if(fila[i] < fila[menor_pos])
           menor_pos = i;
    }

    return menor_pos;
}

int procurar_melhor_pos_se(std::vector<int> fila){
    int menor_pos = 0;
    bool achou_homem = 0;

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] > 0 && fila[i] < fila[menor_pos]){
            menor_pos = i;
            achou_homem = true;
        }
    }

    if(achou_homem)
       return menor_pos;
    return -1;
}

//Contagem
float calcular_stress_medio(std::vector<int> fila){
    float str_media = 0;

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] < 0){
            str_media += -fila[i];
        }else{
            str_media += fila[i];
        }
    }

    str_media = str_media / (int) fila.size();
    return str_media;
}

std::string mais_homens_ou_mulheres(std::vector<int> fila){
    int cont_homens = 0;
    int cont_mulheres = 0;

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] > 0){
            cont_homens++;
        }else{
            cont_mulheres++;
        }
    }

    if(cont_homens == cont_mulheres){
        return "empate";
    }else if(cont_homens < cont_mulheres){
        return "mulheres";
    }else{
        return "homens";
    }
}

std::string qual_metade_eh_mais_estressada(std::vector<int> fila){
    int soma_primeira = 0;
    int soma_segunda = 0;

    for(int i = 0; i < ((int) fila.size() / 2); i++){
        if(fila[i] < 0){
            soma_primeira += -fila[i];
        }else{
            soma_primeira += fila[i];
        }
    }

    for(int i = ((int) fila.size() / 2); i < (int) fila.size(); i++){
        if(fila[i] < 0){
            soma_segunda += -fila[i];
        }else{
            soma_segunda += fila[i];
        }
    }

    if(soma_primeira == soma_segunda){
        return "empate";
    }else if(soma_primeira < soma_segunda){
        return "segunda";
    }else{
        return "primeira";
    }
}

float homens_sao_mais_estressados_que_mulheres(std::vector<int> fila){
    float media_mulheres = 0;
    float media_homens = 0;
    int cont_mulheres = 0;
    int cont_homens = 0;

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] < 0){
            cont_mulheres++;
            media_mulheres += -fila[i];
        }else{
            cont_homens++;
            media_homens += fila[i];
        }
    }

    media_mulheres /= cont_mulheres;
    media_homens /= cont_homens;

    if(media_mulheres < media_homens){
        return true;
    }else{
        return false;
    }
}

int main()
{
    //Busca
    std::cout << existe({1, 2, 3, 4, 5}, 5) << '\n'; //true
    std::cout << existe({1, 2, 3, 4, 5}, 0) << '\n'; //false

    std::cout << contar({-1, -50, -1, -99}, -1) << '\n'; //2
    std::cout << contar({-1, -50, -1, -99}, 10) << '\n'; //0

    std::cout << procurar_valor({-1, -50, -1, -99}, -50) << '\n'; //1
    std::cout << procurar_valor({-1, -50, -1, -99}, 10) << '\n';  //-1

    std::cout << procurar_valor_apartir({5, 3, -1, -50, -1 , -99}, -1 , 0) << '\n'; //2
    std::cout << procurar_valor_apartir({5, 3, -1, -50, -1 , -99}, -1 , 3) << '\n'; //4
    std::cout << procurar_valor_apartir({5, 3, -1, -50, -1 , -99}, -1 , 4) << '\n'; //4

    //Melhor Caso
    std::cout << procurar_menor({5, 3, -1, -50, -1, -99}) << '\n'; //-99

    std::cout << procurar_menor_pos({5, 3, -1, -50, -1, -99}) << '\n'; //5
    
    std::cout << procurar_menor_pos_apartir({5, 3, -1, -50, -1, 10}, 3) << '\n'; //3

    std::cout << procurar_melhor_pos_se({5, 3, -1, -50, -1, -99}) << '\n'; //1
    std::cout << procurar_melhor_pos_se({-1, -50, -1, -99}) << '\n'; //-1

    //Contagem
    std::cout << calcular_stress_medio({1, -2, -3, 4, 5}) << '\n'; //3

    std::cout << mais_homens_ou_mulheres({5, 3, -1, -50, -1, -99}) << '\n'; //mulheres
    std::cout << mais_homens_ou_mulheres({5, 3, 1, -50, -1, -99}) << '\n'; //empate
    std::cout << mais_homens_ou_mulheres({5, 3, 1, -50, -1, 99}) << '\n'; //homens

    std::cout << qual_metade_eh_mais_estressada({5, 3, -1, -50, -1, -99}) << '\n'; //segunda
    std::cout << qual_metade_eh_mais_estressada({50, 98, 2, -50, -1, -99}) << '\n'; //empate
    std::cout << qual_metade_eh_mais_estressada({-51, 99, 1, -50, -1, -99}) << '\n'; //primeira

    std::cout << homens_sao_mais_estressados_que_mulheres({-20, 30, -45, 15, -16}) << '\n'; //false
    std::cout << homens_sao_mais_estressados_que_mulheres({10, -5, 20, -35, 40}) << '\n'; //true
}