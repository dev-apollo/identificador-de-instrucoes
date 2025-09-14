#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

/*
Lê arquivo .ROM -> Linguagem de máquina hexa/binário
Caso hexa, converter para binário (mais fácil de usar)
Classificar instruções do arquivo por tipos (R, I, S, B, U, J), pegando os bits 6-0
Após identificar o tipo, separar as instruções por "partes" e converter os valores pra decimal
Exemplo na folha, olha lá!
*/

/*
    O que falta fazer: 
    - transformar fuct3 para decimal antes de salvar
    - pegar o rd, rs1, rs2, imm (das instruções que tem isso)
*/

string hexToBin(string linha){
    string linhaBin, numBin;
    //toupper converte o char para um código da tabela ascii. Ex: 0 -> 48 que o symbol é '0'
    for(char c: linha){
        switch(toupper(c)){
            case '0': numBin = "0000";break;
            case '1': numBin = "0001";break;
            case '2': numBin = "0010";break;
            case '3': numBin = "0011";break;
            case '4': numBin = "0100";break;
            case '5': numBin = "0101";break;
            case '6': numBin = "0110";break;
            case '7': numBin = "0111";break;
            case '8': numBin = "1000";break;
            case '9': numBin = "1001";break;
            case 'A': numBin = "1010";break;
            case 'B': numBin = "1011";break;
            case 'C': numBin = "1100";break;
            case 'D': numBin = "1101";break;
            case 'E': numBin = "1110";break;
            case 'F': numBin = "1111";break;
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

// Coloquei a lista de códigos em um arquivo txt e criei uma tabela, achei q dessa forma seria mais facil de ler depois
vector<vector<string>> lerTipos(){
    vector<vector<string>> tabela;
    ifstream arquivo("tipos.txt");
    if(!arquivo.is_open()){
        cout<<"Erro ao abrir o arquivo!"<<endl;
        return tabela;
    }
    string linha, tipo, temp;
    int i = 0;
    while(getline(arquivo,linha)){
        vector<string> linhaAtual;
        stringstream str(linha);
        while(getline(str,tipo,',')){
           linhaAtual.push_back(tipo);
        }
        tabela.push_back(linhaAtual);
    }
    arquivo.close();
    return tabela;
}

// verifica o opcode e fuct3
void checkInstrucoes(string codigo, vector<vector<string>>& tabelaTipos, vector<vector<string>>& tabelaInstrucoes){
    string tipo = codigo.substr(codigo.length()-7, codigo.length());
    for(int i = 0; i < tabelaTipos.size(); i++){
        if(!tabelaTipos.empty()){
            if(tipo == tabelaTipos[i][0]){
                vector<string> novaLinha;
                novaLinha.push_back(tabelaTipos[i][0]);
                if(tabelaTipos[i][1] == "R" || tabelaTipos[i][1] == "I" || tabelaTipos[i][1] == "S" || tabelaTipos[i][1] == "B" || tabelaTipos[i][1] == "J" || tabelaTipos[i][1] == "U"){
                    novaLinha.push_back(tabelaTipos[i][1]); // instrucao
                    novaLinha.push_back("-"); //RD - precisa implementar
                    if(tabelaTipos[i][1] != "J" || tabelaTipos[i][1] != "U" ){
                        //precisa converter pra decimal antes de salvar 
                        novaLinha.push_back(tabelaTipos[i][2]); // funct3
                    }
                }
                tabelaInstrucoes.push_back(novaLinha);
                break;
            }
        }

    }
}

//peguei do chat so pra imprimir rapidao, pode apagar e fazer outro se quiser
void imprimirMatriz(const vector<vector<string>>& matriz) {
    for (const auto& linha : matriz) {
        for (const auto& celula : linha) {
            // Troque '\t' por " "
            std::cout << celula << " "; 
        }
        std::cout << std::endl;
    }
}


int main(){
    ifstream arquivo("fib_rec_hex.txt");
    if(!arquivo.is_open()){
        cout<<"Erro ao abrir o arquivo!"<<endl;
        return 1;
    }

    ofstream binText ("bin.txt");

    string linha, bin;
    while(getline(arquivo, linha)){
        if(isHex(linha)){
            binText << hexToBin(linha) << endl;;
        }
    }
    arquivo.close();

    vector<vector<string>> tabelaTipos = lerTipos();
    vector<vector<string>> tabelaInstrucoes;

    ifstream codigoEmBin("bin.txt");
        if(!codigoEmBin.is_open()){
        cout<<"Erro ao abrir o arquivo!"<<endl;
        return 1;
    }

    while(getline(codigoEmBin, linha)){
        checkInstrucoes(linha,tabelaTipos,tabelaInstrucoes);
    }
    cout << tabelaInstrucoes.size() << endl;
    imprimirMatriz(tabelaInstrucoes);
    return 0;
}