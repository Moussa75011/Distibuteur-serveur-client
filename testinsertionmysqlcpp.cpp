// Test connecteur C++ MySQL
// O. Dartois, Juin 2017

//#include <stdlib.h>
#include <iostream>

// Les includes strictement nécessaire pour cet exemple
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int main(void)
{
cout << endl;
cout << "Premier test du connecteur C++ Mysql" << endl;

// La gestion d'erreur se fait proprement avec les exceptions
// sinon retirer le try...catch

try {
  // Les variables nécessaires à notre programme
  sql::Driver* driver;
  sql::Connection* con;
  sql::Statement* stmt;
  

  // Etape 1 : créer une connexion à la BDD
  driver = get_driver_instance();
  // on note les paramètres classiques: adresse ip du serveur et port, login, mot de passe
  con = driver->connect("tcp://127.0.0.1:3306", "olivier", "olivier");

  // Etape 2 : connexion à la base choisie, ici olivier_db
  con->setSchema("olivier_db");

  // Etape 3 : création d'un objet qui permet d'effectuer des requêtes sur la base
  stmt = con->createStatement();

  // Etape 4 : exécution d'une requete : ici on insere un enregistrement
  // dans la table Animal
  string req = "INSERT INTO Animal VALUES(NULL,'chien','M', NOW(), 'medor', 'chien rare')";  
  int result = stmt->executeUpdate(req);
  cout << "Resultat INSERT: " << result << endl;

  // On nettoie tout avant de sortie : effacement des pointeurs
  // le pointeur sur le Driver sera effacé tout seul
  delete stmt;
  delete con;

} catch (sql::SQLException &e) {
  // Gestion des execeptions pour déboggage
  cout << "# ERR: " << e.what();
  cout << " (code erreur MySQL: " << e.getErrorCode();
  cout << ", EtatSQL: " << e.getSQLState() << " )" << endl;
}

cout << endl;

// on sort en indiquant que tout c'est bien passé
return EXIT_SUCCESS;
}