#include <iostream>
#include <string>
#include <cctype>
#include <stack>
#include <sstream>

using namespace std;

bool estCaractereValide(char c) {
    return (isdigit(c) || c == '+' || c == '*' || c == '/' || c == '-' || c == ' ');
}

bool verifierExpression(const string& expression) {
    int nombreChiffres = 0;
    int nombreOperateurs = 0;

    for (size_t i = 0; i < expression.size(); ++i) {
        if (isdigit(expression[i])) {
            nombreChiffres++;
            while (i + 1 < expression.size() && isdigit(expression[i + 1])) {
                ++i;
            }
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            nombreOperateurs++;
        } else if (!estCaractereValide(expression[i]) && !isspace(expression[i])) {
            cout << "Caractere invalide rencontre : '" << expression[i] << "'" << endl;
            return false;
        }
    }
    if (nombreChiffres - 1 != nombreOperateurs) {
        cout << "Le nombre de chiffres doit etre exactement 4 et superieur d'1 au nombre d'operateurs." << endl;
        return false;
    }

    if (nombreOperateurs <= 0) {
        cout << "Il doit y avoir au moins un operateur." << endl;
        return false;
    }

    return true;
}


int calculer(int nombre1, int nombre2, char operateur) {
    switch (operateur) {
        case '+':
            return nombre1 + nombre2;
        case '-':
            return nombre1 - nombre2;
        case '*':
            return nombre1 * nombre2;
        case '/':
          if(nombre2==0){
            cout<<"Calcul impossible car le dénominateur vaut 0"<<endl;
            return 0;
          }else{
            return nombre1 / nombre2;
          }
        default:
            return 0; // Opérateur non reconnu
    }
}

void empiler(stack<int>& pileChiffres, int chiffre) {
    pileChiffres.push(chiffre);
}

int depiler(stack<int>& pileChiffres, char operateur) {
    int nombre2 = pileChiffres.top();
    pileChiffres.pop();
    int nombre1 = pileChiffres.top();
    pileChiffres.pop();
    int resultat = calculer(nombre1, nombre2, operateur);
    return resultat;
}

int evaluerExpression(const string& expression) {
    stack<int> pileChiffres;
    stringstream lecteurExpression(expression);
    int resultat;
    char caractere;
    while (lecteurExpression >> caractere) {
        if (isdigit(caractere)) {
            lecteurExpression.putback(caractere);
            int chiffre;
            lecteurExpression >> chiffre;
            empiler(pileChiffres, chiffre);
        } else if (caractere == '+' || caractere == '-' || caractere == '*' || caractere == '/') {
            resultat = depiler(pileChiffres, caractere);
            empiler(pileChiffres, resultat);
        }
    }

    return pileChiffres.top();
}

void demanderExpression(string& expression) {
    cout << "Entrez une expression mathematique : ";
    try {
        getline(cin, expression);
    } catch (const ios_base::failure& e) {
        cerr << "Erreur lors de la lecture de l'expression : " << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

void affichage(const string& expression, bool verif, int resultat) {
    if (verif) {
        cout << "Le résultat est : " << resultat << endl;
    } else {
        cout << "L'expression contient des caracteres invalides." << endl;
    }
}

int main() {
    string expression;
    bool verification;
    int resultat;

    try {
        demanderExpression(expression);
        verification = verifierExpression(expression);
        resultat = evaluerExpression(expression);
        affichage(expression, verification, resultat);
    } catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
