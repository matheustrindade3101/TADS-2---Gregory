/* Aluno: Matheus Machado da Trindade
   Sistema de Clínica Veterinária
*/

#include <iostream>
#include <string>
#include <fstream>


#define MAX 200

using namespace std;

// contadores de posições
int posTutores = 0;
int posAnimais = 0;
int posDetalheAnimal = 0;

// structs
struct Tutor {
    int id;
    char nome[100];
    char endereco[100];
};

struct Animal {
    int codigo;
    char nome[100];
    char especie[100];
    int idade;
    int idTutor; // associação: id do tutor dono deste animal
};

struct DetalheAnimal{
    //int codigoAnimal;
    char raca[100];
    char cor[100];
};

// protótipos
void mostrarMenu();
void cadastrarTutor(Tutor vet[], int &pos);
bool existeTutorPorId(Tutor vet[], int pos, int id);
void cadastrarAnimal(Animal vetA[], int &posA, Tutor vetT[], int posT);
void cadastrarDetalheAnimal(DetalheAnimal vetD[],Animal vetA[], int &posA, Tutor vetT[], int posT);
void listarDetalheAnimal(DetalheAnimal vetD[],Animal vetA[], int &posA, Tutor vetT[], int posT);
void listarTutores(Tutor vet[], int pos);
void listarAnimais(Animal vetA[], int posA, Tutor vetT[], int posT);
void buscarAnimaisPorTutor(Animal vetA[], int posA, Tutor vetT[], int posT);
void relatorioGeral(Animal vetA[], int posA, Tutor vetT[], int posT);
string nomeTutorPorId(Tutor vet[], int pos, int id);


void salvar(Tutor vet[],DetalheAnimal vetD[], Animal vetA[], int n) {
    fstream meuArquivo;

    meuArquivo.open("clinica.bin", ios::out | ios::binary);

    if(meuArquivo.is_open()) {
        meuArquivo.write((char *) vet, sizeof(Tutor) * n);
        meuArquivo.write((char *) vetA, sizeof(Animal) * n);
        meuArquivo.write((char *) vetD, sizeof(DetalheAnimal) * n);
        meuArquivo.write((char *) &posTutores, sizeof(posTutores));
        meuArquivo.write((char *) &posAnimais, sizeof(posAnimais));
        meuArquivo.write((char *) &posDetalheAnimal, sizeof(posDetalheAnimal));
        meuArquivo.close();
        cout << "Informacoes salvas com sucesso!!\n";
    }
    else {
        cout << "Falha ao gravar informacoes.\n";
    }
}

void carregar(Tutor vet[],DetalheAnimal vetD[], Animal vetA[], int n) {
    fstream meuArquivo;
    meuArquivo.open("clinica.bin", ios::in | ios::binary);

    if(meuArquivo.is_open()) {
        meuArquivo.read((char *) vet, sizeof(Tutor) * n);
        meuArquivo.read((char *) vetA, sizeof(Animal) * n);
        meuArquivo.read((char *) vetD, sizeof(DetalheAnimal) * n);
        meuArquivo.read((char *) &posTutores, sizeof(posTutores));
        meuArquivo.read((char *) &posAnimais, sizeof(posAnimais));
        meuArquivo.read((char *) &posDetalheAnimal, sizeof(posDetalheAnimal));
        meuArquivo.close();
        cout << "Informacoes carregadas com sucesso!!\n";
    } else {
        cout << "Falha ao carregar informacoes.\n";
    }
}


int main(){
    Tutor vetTutores[MAX];
    Animal vetAnimais[MAX];
    DetalheAnimal vetDetalheAnimal[MAX];
    int opcao;

    do {
        mostrarMenu();
        cin >> opcao;
        switch(opcao){
            case 1:
                cadastrarTutor(vetTutores, posTutores);
                break;
            case 2:
                cadastrarAnimal(vetAnimais, posAnimais, vetTutores, posTutores);
                break;
            case 3:
                cadastrarDetalheAnimal(vetDetalheAnimal,vetAnimais, posAnimais, vetTutores, posTutores);
                break;
            case 4:
                listarDetalheAnimal(vetDetalheAnimal,vetAnimais, posAnimais, vetTutores, posTutores);
                break;
            case 5:
                listarTutores(vetTutores, posTutores);
                break;
            case 6:
                listarAnimais(vetAnimais, posAnimais, vetTutores, posTutores);
                break;
            case 7:
                buscarAnimaisPorTutor(vetAnimais, posAnimais, vetTutores, posTutores);
                break;
            case 8:
                relatorioGeral(vetAnimais, posAnimais, vetTutores, posTutores);
                break;
            case 9:
                salvar(vetTutores,vetDetalheAnimal,vetAnimais,MAX);
                break;
            case 10:
                carregar(vetTutores,vetDetalheAnimal,vetAnimais,MAX);
                break;
            case 11:
                cout << "Saindo... Obrigado!\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    } while(opcao != 11);

    return 0;
}

// implementações
void mostrarMenu(){
    cout << "\n-------- MENU CLINICA VETERINARIA --------\n";
    cout << "1 - Cadastrar tutor\n";
    cout << "2 - Cadastrar animal\n";
    cout << "3 - Cadastrar detalhes do animal\n";
    cout << "4 - Detalhes do animal\n";
    cout << "5 - Listar tutores\n";
    cout << "6 - Listar animais\n";
    cout << "7 - Buscar animais por tutor\n";
    cout << "8 - Relatorio geral (quantidade de animais por tutor)\n";
    cout << "9 - Salvar(quantidade de animais por tutor)\n";
    cout << "10 - Carregar\n";
    cout << "11 - Sair\n";
    cout << "Digite a sua opcao: ";
}

void cadastrarTutor(Tutor vet[], int &pos){
    if (pos >= MAX){
        cout << "Limite de tutores atingido.\n";
        return;
    }

    Tutor t;
    cout << "Digite o ID do tutor (inteiro): ";
    cin >> t.id;

    if (existeTutorPorId(vet, pos, t.id)){
        cout << "Erro: ja existe um tutor cadastrado com esse ID.\n";
        return;
    }

    cin.ignore(); // limpar buffer antes do getline
    cout << "Digite o nome do tutor: ";
    cin.getline(t.nome,100);
    cout << "Digite o endereco do tutor: ";
    cin.getline(t.endereco,100);

    vet[pos++] = t;
    cout << "Tutor cadastrado com sucesso!\n";
}

bool existeTutorPorId(Tutor vet[], int pos, int id){
    for (int i = 0; i < pos; i++){
        if (vet[i].id == id) return true;
    }
    return false;
}

void cadastrarAnimal(Animal vetA[], int &posA, Tutor vetT[], int posT){
    if (posA >= MAX){
        cout << "Limite de animais atingido.\n";
        return;
    }

    if (posT == 0){
        cout << "Nenhum tutor cadastrado. Cadastre um tutor antes de cadastrar animais.\n";
        return;
    }

    Animal a;
    cout << "Digite o codigo do animal (inteiro): ";
    cin >> a.codigo;

    // opcional: verificar codigo duplicado entre animais
    for (int i=0;i<posA;i++){
        if (vetA[i].codigo == a.codigo){
            cout << "Erro: ja existe um animal com esse codigo.\n";
            return;
        }
    }

    cin.ignore();
    cout << "Digite o nome do animal: ";
    cin.getline(a.nome,100);
    cout << "Digite a especie: ";
    cin.getline(a.especie,100);
    cout << "Digite a idade (anos): ";
    cin >> a.idade;

    cout << "Digite o ID do tutor dono (o tutor ja precisa estar cadastrado): ";
    cin >> a.idTutor;

    if (!existeTutorPorId(vetT, posT, a.idTutor)){
        cout << "Erro: tutor com ID " << a.idTutor << " nao encontrado. Animal nao cadastrado.\n";
        return;
    }

    vetA[posA++] = a;
    cout << "Animal cadastrado com sucesso!\n";
}

void cadastrarDetalheAnimal(DetalheAnimal vetD[],Animal vetA[], int &posA, Tutor vetT[], int posT){
   if (posT == 0){
        cout << "Nenhum tutor cadastrado. Cadastre um tutor antes de cadastrar animais.\n";
        return;
    }

    Animal a;
    DetalheAnimal d;
    cout << "Digite o codigo do animal (inteiro): ";
    cin >> a.codigo;

    cin.ignore();
    cout << "Digite a raca do animal: ";
    cin.getline(d.raca,100);
    cout << "Digite a cor do animal: ";
    cin.getline(d.cor,100);

    if (!existeTutorPorId(vetT, posT, a.idTutor)){
        cout << "Erro: tutor com ID " << a.idTutor << " nao encontrado. Animal nao cadastrado.\n";
        return;
    }

    vetD[posDetalheAnimal++] = d;
    cout << "Detalhes cadastrados com sucesso!\n";
}

void listarDetalheAnimal(DetalheAnimal vetD[],Animal vetA[], int &posA, Tutor vetT[], int posT){
    if (posA == 0){
        cout << "Nenhum animal cadastrado.\n";
        return;
    }
    cout << "\n--- Lista de Animais ---\n";
    for (int i=0;i<posA;i++){
        cout << "Codigo: " << vetA[i].codigo
             << " | Nome: " << vetA[i].nome
             << " | Especie: " << vetA[i].especie
             << " | Idade: " << vetA[i].idade
             << " | Tutor: " << nomeTutorPorId(vetT, posT, vetA[i].idTutor)
             << " (ID " << vetA[i].idTutor << ")"
             << " | Raca: " << vetD[i].raca
             << " | Cor: " << vetD[i].cor
             << endl;
    }
}

void listarTutores(Tutor vet[], int pos){
    if (pos == 0){
        cout << "Nenhum tutor cadastrado.\n";
        return;
    }
    cout << "\n--- Lista de Tutores ---\n";
    for (int i=0;i<pos;i++){
        cout << "ID: " << vet[i].id << " | Nome: " << vet[i].nome
             << " | Endereco: " << vet[i].endereco << endl;
    }
}

string nomeTutorPorId(Tutor vet[], int pos, int id){
    for (int i=0;i<pos;i++){
        if (vet[i].id == id) return vet[i].nome;
    }
    return string("[Tutor nao encontrado]");
}

void listarAnimais(Animal vetA[], int posA, Tutor vetT[], int posT){
    if (posA == 0){
        cout << "Nenhum animal cadastrado.\n";
        return;
    }
    cout << "\n--- Lista de Animais ---\n";
    for (int i=0;i<posA;i++){
        cout << "Codigo: " << vetA[i].codigo
             << " | Nome: " << vetA[i].nome
             << " | Especie: " << vetA[i].especie
             << " | Idade: " << vetA[i].idade
             << " | Tutor: " << nomeTutorPorId(vetT, posT, vetA[i].idTutor)
             << " (ID " << vetA[i].idTutor << ")"
             << endl;
    }
}

void buscarAnimaisPorTutor(Animal vetA[], int posA, Tutor vetT[], int posT){
    if (posT == 0){
        cout << "Nenhum tutor cadastrado.\n";
        return;
    }
    int id;
    cout << "Digite o ID do tutor para listar seus animais: ";
    cin >> id;

    if (!existeTutorPorId(vetT, posT, id)){
        cout << "Tutor com ID " << id << " nao encontrado.\n";
        return;
    }

    cout << "\nAnimais do tutor " << nomeTutorPorId(vetT, posT, id) << " (ID " << id << "):\n";
    int cont = 0;
    for (int i=0;i<posA;i++){
        if (vetA[i].idTutor == id){
            cout << " - Codigo: " << vetA[i].codigo
                 << " | Nome: " << vetA[i].nome
                 << " | Especie: " << vetA[i].especie
                 << " | Idade: " << vetA[i].idade << endl;
            cont++;
        }
    }
    if (cont == 0) cout << "Nenhum animal cadastrado para esse tutor.\n";
}

void relatorioGeral(Animal vetA[], int posA, Tutor vetT[], int posT){
    if (posT == 0){
        cout << "Nenhum tutor cadastrado.\n";
        return;
    }

    cout << "\n--- Relatorio Geral: Numero de animais por tutor ---\n";

    // para simplicidade crio um vetor auxiliar de contadores indexado pelo tutor (mesma ordem do vetT)
    for (int i=0;i<posT;i++){
        int idTutor = vetT[i].id;
        int contador = 0;
        for (int j=0;j<posA;j++){
            if (vetA[j].idTutor == idTutor) contador++;
        }
        cout << "Tutor: " << vetT[i].nome << " (ID " << idTutor << ") -> " << contador << " animal(is)\n";
    }
}
