#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

/*
Lê arquivo .ROM -> Linguagem de máquina hexa/binário
Caso hexa, converter para binário (mais fácil de usar)
Classificar instruções do arquivo por tipos (R, I, S, B, U, J), pegando os bits 6-0
Após identificar o tipo, separar as instruções por "partes" e converter os valores pra decimal
Exemplo na folha, olha lá!
*/

string hexToBin(string linha){
    string linhaBin, numBin;
    for(char c: linha){
        cout<<toupper(c)<<endl;
        switch(toupper(c)){
            case '0': numBin = "0000";
            case '1': numBin = "0001";
            case '2': numBin = "0010";
            case '3': numBin = "0011";
            case '4': numBin = "0100";
            case '5': numBin = "0101";
            case '6': numBin = "0110";
            case '7': numBin = "0111";
            case '8': numBin = "1000";
            case '9': numBin = "1001";
            case 'A': numBin = "1010";
            case 'B': numBin = "1011";
            case 'C': numBin = "1100";
            case 'D': numBin = "1101";
            case 'E': numBin = "1110";
            case 'F': numBin = "1111";
        }
        linhaBin.append(numBin);
    }
    return linhaBin;
}

bool isHex(string linha){
    for (char c: linha){
        if(c != '1' && c != '0'){
            return true;
        }
    }
    return false;
}

int main(){
    ifstream arquivo("fib_rec_hex.txt");
    if(!arquivo.is_open()){
        cout<<"Erro ao abrir o arquivo!"<<endl;
        return 1;
    }

    string linha;
    while(getline(arquivo, linha)){
        if(isHex(linha)){
            linha = hexToBin(linha);
        }
    }

    arquivo.close();
    return 0;
}