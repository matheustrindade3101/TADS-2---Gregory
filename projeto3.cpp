/* Aluno: Matheus Machado da Trindade
   Sistema de Clínica Veterinária
*/

#include <iostream>
#include <string>

#define MAX_TUTORES 50
#define MAX_ANIMAIS 200

using namespace std;

// contadores de posições
int posTutores = 0;
int posAnimais = 0;

// structs
struct Tutor {
    int id;
    string nome;
    string endereco;
};

struct Animal {
    int codigo;
    string nome;
    string especie;
    int idade;
    int idTutor; // associação: id do tutor dono deste animal
};

// protótipos
void mostrarMenu();
void cadastrarTutor(Tutor vet[], int &pos);
bool existeTutorPorId(Tutor vet[], int pos, int id);
void cadastrarAnimal(Animal vetA[], int &posA, Tutor vetT[], int posT);
void listarTutores(Tutor vet[], int pos);
void listarAnimais(Animal vetA[], int posA, Tutor vetT[], int posT);
void buscarAnimaisPorTutor(Animal vetA[], int posA, Tutor vetT[], int posT);
void relatorioGeral(Animal vetA[], int posA, Tutor vetT[], int posT);
string nomeTutorPorId(Tutor vet[], int pos, int id);

int main(){
    Tutor vetTutores[MAX_TUTORES];
    Animal vetAnimais[MAX_ANIMAIS];
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
                listarTutores(vetTutores, posTutores);
                break;
            case 4:
                listarAnimais(vetAnimais, posAnimais, vetTutores, posTutores);
                break;
            case 5:
                buscarAnimaisPorTutor(vetAnimais, posAnimais, vetTutores, posTutores);
                break;
            case 6:
                relatorioGeral(vetAnimais, posAnimais, vetTutores, posTutores);
                break;
            case 7:
                cout << "Saindo... Obrigado!\n";
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n";
        }
    } while(opcao != 7);

    return 0;
}

// implementações
void mostrarMenu(){
    cout << "\n-------- MENU CLINICA VETERINARIA --------\n";
    cout << "1 - Cadastrar tutor\n";
    cout << "2 - Cadastrar animal\n";
    cout << "3 - Listar tutores\n";
    cout << "4 - Listar animais\n";
    cout << "5 - Buscar animais por tutor\n";
    cout << "6 - Relatorio geral (quantidade de animais por tutor)\n";
    cout << "7 - Sair\n";
    cout << "Digite a sua opcao: ";
}

void cadastrarTutor(Tutor vet[], int &pos){
    if (pos >= MAX_TUTORES){
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
    getline(cin, t.nome);
    cout << "Digite o endereco do tutor: ";
    getline(cin, t.endereco);

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
    if (posA >= MAX_ANIMAIS){
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
    getline(cin, a.nome);
    cout << "Digite a especie: ";
    getline(cin, a.especie);
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
