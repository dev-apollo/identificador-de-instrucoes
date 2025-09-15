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
    mostrar saída que o professor pede.
    Só da uma analisada se peguei os bits corretos para as intruções
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

int binToDec(const string& bin){
    return stoi(bin, nullptr, 2);
}

// verifica o opcode e fuct3
void checkInstrucoes(string codigo, vector<vector<string>>& tabelaTipos, vector<vector<string>>& tabelaInstrucoes){
    string tipo = codigo.substr(25, 7);
    for(int i = 0; i < tabelaTipos.size(); i++){
        if(!tabelaTipos.empty()){
            if(tipo == tabelaTipos[i][0]){
                
                vector<string> novaLinha;
                novaLinha.push_back(tabelaTipos[i][1]); // instrucao
                novaLinha.push_back(tabelaTipos[i][0]); // opcode

                // rd
                if(tabelaTipos[i][1] != "S" && tabelaTipos[i][1] != "B" ){
                    novaLinha.push_back(to_string(binToDec(codigo.substr(20, 5)))); 
                }else{
                    novaLinha.push_back("---");
                }

                // funct3
                if(tabelaTipos[i][1] != "J" && tabelaTipos[i][1] != "U" ){
                    novaLinha.push_back(to_string(binToDec(codigo.substr(17, 3)))); // funct3 bits [14-12]
                    novaLinha.push_back(to_string(binToDec(codigo.substr(12, 5)))); // rs1 bits [19-15]
                }else{
                    novaLinha.push_back("---");
                    novaLinha.push_back("---");
                }
                
                // rs2
                if(tabelaTipos[i][1] == "R" || tabelaTipos[i][1] == "S" || tabelaTipos[i][1] == "B"){
                    novaLinha.push_back(to_string(binToDec(codigo.substr(7, 5)))); // rs2 bits [24-20]
                }else{
                    novaLinha.push_back("---");
                }

                // imm I
                if(tabelaTipos[i][1] == "I"){
                    string imm = codigo.substr(0, 12); 
                    novaLinha.push_back(to_string(binToDec(imm))); 
                }

                // imm S
                if(tabelaTipos[i][1] == "S"){
                    string imm_11_5 = codigo.substr(0, 7);
                    string imm_4_0 = codigo.substr(20, 5); 
                    string imm = imm_11_5 + imm_4_0;
                    novaLinha.push_back(to_string(binToDec(imm))); 
                }

                // imm B
                if(tabelaTipos[i][1] == "B"){
                    string imm_12 = codigo.substr(0, 1);
                    string imm_10_5 = codigo.substr(1, 6);
                    string imm_4_1 = codigo.substr(20, 4);
                    string imm_11 = codigo.substr(24, 1); 
                    string imm = imm_12 + imm_11 + imm_10_5 + imm_4_1 + "0";
                    novaLinha.push_back(to_string(binToDec(imm))); 
                }

                // imm U
                if(tabelaTipos[i][1] == "U"){
                    string imm = codigo.substr(0, 20); 
                    novaLinha.push_back(to_string(binToDec(imm))); 
                }

                // imm J
                if(tabelaTipos[i][1] == "J"){
                    string imm_20 = codigo.substr(0, 1);
                    string imm_10_1 = codigo.substr(1, 10);
                    string imm_11 = codigo.substr(11, 1);
                    string imm_19_12 = codigo.substr(12, 8);
                    string imm = imm_20 + imm_19_12 + imm_11 + imm_10_1 + "0";
                    novaLinha.push_back(to_string(binToDec(imm))); 
                }
                
                tabelaInstrucoes.push_back(novaLinha);
                
                break;
            }
        }

    }
}



void imprimirMatriz(const vector<vector<string>>& matriz) {
    for (const auto& linha : matriz) {
        for (const auto& celula : linha) {
            // Troque '\t' por " "
            cout << celula << " "; 
        }
        cout << endl;
    }
}

void imprimirInstrucoes(const vector<vector<string>>& instrucoes, const vector<string>& originais) {
    for (size_t i = 0; i < instrucoes.size(); i++) {
        cout << "A instrucao " << originais[i] 
             << " formato = " << instrucoes[i][0];

        // rd
        if(instrucoes[i][2] != "---")
            cout << ", rd = " << instrucoes[i][2];

        // funct3
        if(instrucoes[i][3] != "---")
            cout << ", f3 = " << instrucoes[i][3];

        // rs1
        if(instrucoes[i][4] != "---")
            cout << ", rs1 = " << instrucoes[i][4];

        // rs2
        if(instrucoes[i][5] != "---")
            cout << ", rs2 = " << instrucoes[i][5];

        // imm
        if(instrucoes[i].size() > 6)
            cout << ", imed = " << instrucoes[i][6];
        cout << endl;
    }
}


int main(){
    vector<string> originais;

    ifstream arquivo("fib_rec_bin.txt");
    if(!arquivo.is_open()){
        cout<<"Erro ao abrir o arquivo!"<<endl;
        return 1;
    }

    ofstream binText ("bin.txt");

    string linha, bin;
    while(getline(arquivo, linha)){
        if(isHex(linha)){
            originais.push_back("0x" + linha);
            binText << hexToBin(linha) << endl;;
        } else {
            originais.push_back(linha);
            binText << linha << endl;
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
        checkInstrucoes(linha, tabelaTipos, tabelaInstrucoes);
    }

    imprimirInstrucoes(tabelaInstrucoes, originais);
    return 0;
}