// VARIABLES
//OUTPUT DES LEDS D'AFFICHAGE (TABLE)
int DisplayLEDs[3] = { 2, 12, 8 };
int interval = 0;
// PINS ANALOGUES IN (LECTURE DE LA TENSION AUX BORNES DE R5)
const int analogPinA = A0;  // Pin de mesure pour le point A
const int analogPinB = A1;  // Pin de mesure pour le point B


float VoltageReading;  // VARIABLE DE STOCKAGE POUR LA LECTURE DE TENSION

bool CardInserted = false;  // VARIABLE POUR SAVOIR SI UNE CARTE EST CONNECTÉE OU NON
int lastCard;

String UserInput;  // VARIABLE POUR STOCKER L'INPUT DE L'UTILISATEUR

// DECLARATION DU DICTIONNAIRE DES 8 MODÈLES ET LEURS INTERVALLES DE TENSIONS
struct Vlt_DictionaryEntry {
  const char* key;
  float value1;
  float value2;
};
// LE DICTIONNAIRE AVEC LES VALEURS :
Vlt_DictionaryEntry Vlt_dictionary[] = {
  { "modèle 1", 1.38, 1.38 },
  { "modèle 2", 1.38, 1.67 },
  { "modèle 3", 1.72, 1.8 },
  { "modèle 4", 0.1, 0.21 },
  { "modèle 5", 2.7, 2.82 },
  { "modèle 6", 3.82, 4.6 },
  { "modèle 7", 1.98, 2.5 },
  { "modèle 8", 3.4, 3.76 }
};

// DECLARATION DU DICTIONNAIRE DES 8 MODÈLES ET LEURS NIVEAUX DE SÉCURITÉ
struct SecurityLVL_DictionaryEntry {
  const char* key;
  int value;
};
// LE DICTIONNAIRE AVEC LES VALEURS :
SecurityLVL_DictionaryEntry SecurityLVL_dictionary[] = {
  { "modèle 1", 2 },
  { "modèle 2", 5 },
  { "modèle 3", 6 },
  { "modèle 4", 6 },
  { "modèle 5", 2 },
  { "modèle 6", 3 },
  { "modèle 7", 4 },
  { "modèle 8", 1 }
};

// FONCTION DE SETUP
void setup() {
  Serial.begin(9600);            // DÉBIT D'ENVOI DES DONNÉES ENTRE L'ARDUINO ET LE PC (Serial.println()/Serial.readString())
  pinMode(LED_BUILTIN, OUTPUT);  // LED DE L'ARDUINO
  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
}

// FONCTION DE LOOP
void loop() {
  //VoltageReading = 1.4;  // VALEUR DE TEST

  // Lire les valeurs analogiques aux points A et B
  int valeurA = analogRead(analogPinA);  // VALEUR DE TENSION AU POINT A
  int valeurB = analogRead(analogPinB);  // VALEUR DE TENSION AU POINT B

  // Convertir les valeurs en tensions (0 à 5V correspond à 0 à 1023)
  float tensionA = (valeurA * 5.0) / 1023.0;
  float tensionB = (valeurB * 5.0) / 1023.0;

  // Calculer la différence de potentiel aux bornes de la résistance
  float VoltageReading = tensionA - tensionB;

  // Pause avant la prochaine lecture
  delay(1000);  // 1 seconde

  // FOR LOOP QUI PASSE SUR TOUS LES ÉLÉMENTS DU DICTIONNAIRE DES MODÈLES AVEC LEUR INTERVALLE DE TENSION
  
  for (int i = 0; i < 8; i++) {


    // SI LA TENSION LUE EST ENTRE L'INTERVALLE DU DICTIONNAIRE, NOTER LE MODÈLE DE CET INTERVAL COMME MODÈLE ACTUEL
    if (VoltageReading > Vlt_dictionary[i].value1 && VoltageReading < Vlt_dictionary[i].value2) {
      CardInserted = true;  // FAIRE SAVOIR AU SYSTÈME QU'UNE CARTE EST ACTUELLEMENT CONNECTÉE
      lastCard = i;
      Serial.println(VoltageReading);
      Serial.println(Vlt_dictionary[i].key);  // AFFICHER LE MODÈLE DÉTECTÉ
      LEDpattern(2);
      DetermineMAs(Vlt_dictionary[i].key);  // APPELER LA FONCTION DETERMINEMAS() EN LUI DONNANT LE MODÈLE DÉTECTÉ
    }
  }
}

// FONCTION DETERMINEMAS() QUI DÉTERMINE LE NIVEAU DE SÉCURITÉ À PARTIR DU MODÈLE DÉTECTÉ
// APPELLE LES FONCTIONS MA() CORRESPONDANTES SELON LE NIVEAU DE SÉCURITÉ
void DetermineMAs(String Model) {
  bool MA;  // VARIABLE POUR STOCKER LA VALEUR BOOLEENNE "STATUS" DE CHAQUE FONCTION MA() APPELÉE, QUI PERMET DE SAVOIR SI L'AUTHENTIFICATION A RÉUSSI OU PAS

  // DÉTERMINER LE NIVEAU DE SÉCURITÉ DU MODÈLE DÉTECTÉ :
  for (int i = 0; i < 8; i++) {
    // SI LE MODÈLE DU DICTIONNAIRE CORRESPOND AU MODÈLE DÉTECTÉ :
    if (Model == SecurityLVL_dictionary[i].key) {
      Serial.println(SecurityLVL_dictionary[i].value);  // AFFICHER LE NIVEAU DE SÉCURITÉ DU MODÈLE DÉTECTÉ
      // APPELER LES FONCTIONS MA() CORRESPONDANT AU NIVEAU DE SÉCURITÉ DU MODÈLE
      if (SecurityLVL_dictionary[i].value == 1) {
        MA = MA1();
        LEDpattern(2);
        if (MA == true) {
          MA = MA3();
          LEDpattern(2);
          if (MA == true) {
            Serial.println("Access Granted");  // ACCÈS ACCORDÉ
            LEDon();
          }
        }
      } else if (SecurityLVL_dictionary[i].value == 2) {
        MA = MA1();
        LEDpattern(2);
        if (MA == true) {
          MA = MA4();
          LEDpattern(2);
          if (MA == true) {
            Serial.println("Access Granted");
            LEDon();
          }
        }
      } else if (SecurityLVL_dictionary[i].value == 3) {
        MA = MA2();
        LEDpattern(2);
        if (MA == true) {
          MA = MA4();
          LEDpattern(2);
          if (MA == true) {
            Serial.println("Access Granted");
            LEDon();
          }
        }
      } else if (SecurityLVL_dictionary[i].value == 4) {
        MA = MA1();
        LEDpattern(2);
        if (MA == true) {
          MA = MA2();
          LEDpattern(2);
          if (MA == true) {
            MA = MA3();
            LEDpattern(2);
            if (MA == true) {
              MA = MA4();
              LEDpattern(2);
              if (MA == true) {
                Serial.println("Access Granted");
                LEDon();
              }
            }
          }
        }
      } else if (SecurityLVL_dictionary[i].value == 5) {
        MA = MA1();
        LEDpattern(2);
        if (MA == true) {
          MA = MA2();
          LEDpattern(2);
          if (MA == true) {
            MA = MA3();
            LEDpattern(2);
            if (MA == true) {
              MA = MA4();
              LEDpattern(2);
              if (MA == true) {
                MA = MA5b();
                LEDpattern(2);
                if (MA == true) {
                  Serial.println("Access Granted");
                  LEDon();
                }
              }
            }
          }
        }
      } else if (SecurityLVL_dictionary[i].value == 6) {
        MA = MA1();
        LEDpattern(2);
        if (MA == true) {
          MA = MA2();
          LEDpattern(2);
          if (MA == true) {
            MA = MA5b();
            LEDpattern(2);
            if (MA == true) {
              MA = MA5a();
              LEDpattern(2);
              if (MA == true) {
                Serial.println("Access Granted");
                LEDon();
              }
            }
          }
        }
      }
    }
  }
  if (MA == true){
    interval = 0;
    Serial.println("Appuyer sur n'importe quel touche pour fermer le coffre");
    while (Serial.available() == 0) {}  // ATTENDRE L'INPUT DE L'UTILISATEUR
    LEDoff();
  }
  else{
    interval = interval + 20;
    LEDblink(interval);
  }
}

// LES 6 FONCTIONS MA() [MA1(); MA2(); MA3(); MA4(); MA5b(); MA5a()]

// MA1 QUESTION-RÉPONSE
bool MA1() {
  bool Status = true;                      // VALEUR DE VALIDATION DU MA
  int chances = 2;                         // NOMBRE DE CHANCES ACCORDÉES
  Serial.println("MA1 question-réponse");  // AFFICHER LE NOM DU MA
  // DÉCLARATION DU DICTIONNAIRE POUR STOCKER LES QUESTIONS-RÉPONSES
  struct QCM_DictionaryEntry {
    const char* question;
    String Correct;
    const char* Answers[4];
  };

  int Nquestions = 3;  // NOMBRE DE QUESTIONS (POUR SAVOIR COMBIEN DE FOIS LE FOR LOOP DOIT TOURNER)
  // LES VALEURS DU DICTIONNAIRE DES QUESTIONS-RÉPONSES :
  QCM_DictionaryEntry QCM_dictionary[] = {
    { "Quel est le nom de ce projet ?", "2", { "WEAKBOX3000", "STRONGBOX3000", "BANANAMIXER8000", "CoffeeMachine" } },
    { "Quel groupe est le meilleur ?", "3", { "Groupe 1", "Groupe 7", "Groupe 6", "Groupe 3" } },
    { "Combien de jours dans une semaine ?", "1", { "Sept", "Deux", "Cinq", "Trois" } }
  };
  Serial.println("Choisissez la bonne réponse");  // AFFICHAGE À L'UTILISATEUR
  // PREMIER FOR LOOP POUR PASSER SUR TOUTES LES QUESTIONS DU DICTIONNAIRE
  for (int i = 0; i < Nquestions && Status == true; i++) {
    // DEUXIEME FOR LOOP POUR GÉRER LE NOMBRE DE CHANCES ACCORDÉ
    for (int k = 0; k < chances; k++) {
      Serial.println(QCM_dictionary[i].question);  // AFFICHER LA QUESTION
      // TROISIÈME FOR LOOP POUR AFFICHER LES 4 RÉPONSES POSSIBLES POUR LA QUESTION ACTUELLE
      for (int j = 0; j < 4 && Status == true; j++) {
        Serial.println(QCM_dictionary[i].Answers[j]);  // AFFICHER LA RÉPONSE
      }
      while (Serial.available() == 0) {}  // ATTENDRE L'INPUT DE L'UTILISATEUR
      delay(500);                         // ATTENDRE 500 ms

      UserInput = Serial.readStringUntil('\n');  // STOKER L'INPUT DE L'UTILISATEUR
      UserInput.trim();
      if (UserInput.equals(QCM_dictionary[i].Correct)) {  // SI L'UTILISATEUR A DONNÉ UNE RÉPONSE CORRECTE
        Serial.println("Bonne réponse");                  // AFFICHER BONNE RÉPONSE
        break;                                            // ARRÊTER LE DEUXIÈME LOOP POUR ÉVITER QUE LA MÊME QUESTION SOIT POSÉE UNE DEUXIÈME FOIS
      } else {                                            // SINON
        Serial.println("Mauvaise réponse");               // AFFICHER MAUVAISE RÉPONSE
        LEDblink(3);
        if (k == chances - 1) {                                // SI L'UTILISATEUR A ÉPUISÉ TOUTES SES CHANCES
          Serial.println("Erreur, authentification échouée");  // AFFICHER LE MESSAGE D'ERREUR
          Status = false;                                      // MA NON VALIDE
          return Status;                                       // DIRE À LA FONCTION DETERMINEMAS() QUE L'UTILISATEUR N'A PAS RÉUSSI À S'AUTHENTIFIER
        }
      }
    }
  }

  return Status;  // DIRE À LA FONCTION DETERMINEMAS() QUE L'UTILISATEUR A RÉUSSI À S'AUTHENTIFIER
}

// Fonction MA2
bool MA2() {
  Serial.println("MA2");
  bool Status = false;
  int chances = 1;  // Limiter à une seule chance

  byte c[16] = {
    0b0011, 0b0010, 0b0001, 0b0000,
    0b0111, 0b0110, 0b0101, 0b0100,
    0b1011, 0b1010, 0b1001, 0b1000,
    0b1111, 0b1110, 0b1100, 0b1101
  };
  int currentCodeIndex = 15;  // Par exemple, le code du jour est le dernier (1101 en binaire)
 
  int inputCode;

  Serial.println("Entrez le code d'aujourd'hui (en binaire)");

  while (Serial.available() == 0)
    ;
  String inputBinary = Serial.readStringUntil('\n');
  inputBinary.trim();

  inputCode = strtol(inputBinary.c_str(), NULL, 2);
  Serial.print("Code lu: ");
  Serial.println(inputCode, BIN);

  if (inputCode == c[currentCodeIndex]) {
    Status = true;
    Serial.println("Code correct !");
  } else {
    Serial.println("Erreur, code incorrect.");
    LEDblink(3);
  }

  return Status;
}

// Fonction MA3
bool MA3() {
  Serial.println("MA3 scan rétinien");
  bool Status;
  Serial.println("Scannez vos yeux :");
  while (Serial.available() == 0)
    ;

  String input = Serial.readStringUntil('\n');
  input.trim();

  if (input.equalsIgnoreCase("true")) {
    Serial.println("Scan réussi.");
    Status = true;
  } else {
    Serial.println("Échec du scan.");
    LEDblink(3);
  }
  return Status;
}

// Fonction MA4
bool MA4() {
  Serial.println("MA4 scan digital");
  bool Status;
  Serial.println("Scannez votre empreinte digitale :");
  while (Serial.available() == 0)
    ;

  String input = Serial.readStringUntil('\n');
  input.trim();

  if (input.equalsIgnoreCase("true")) {
    Serial.println("Empreinte scannée avec succès.");
    Status = true;
  } else {
    Serial.println("Impossible de scanner votre empreinte.");
    LEDblink(3);
  }
  return Status;
}

// Fonction MA5b
bool MA5b() {
  Serial.println("MA5b");
  bool Status = false;
  int chances = 2;
  String letterInput;
  int codeInput;
  String agents[16] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P" };
  int codes[16] = { 6321, 7534, 1457, 6575, 7573, 5732, 6724, 3457, 4378, 6423, 7654, 8659, 6867, 6034, 5008, 4658 };

  for (int i = 0; i < chances; i++) {
    Serial.println("Entrez votre lettre d'identification");
    while (Serial.available() == 0) {}
    letterInput = Serial.readStringUntil('\n');
    letterInput.trim();

    for (int z = 0; z < 16; z++) {
      if (letterInput.equals(agents[z])) {
        Serial.println("Entrez votre ID_Code");
        while (Serial.available() == 0) {}
        codeInput = Serial.parseInt();
        if (codeInput == codes[z]) {
          Status = true;
          Serial.println("Code ID correct");
          break;
        } else {
          Serial.println("Erreur, code incorrect");
          LEDblink(3);
        }
        break;
      }
    }
    if (Status) break;
  }
  return Status;
}

// Fonction MA5a
bool MA5a() {
  Serial.println("MA5a");
  bool Status = true;
   Serial.println("Appuyer sur n'importe quel touche");
    while (Serial.available() == 0) {}  // ATTENDRE L'INPUT DE L'UTILISATEUR
  return Status;
}


//FONCTIONS LEDS D'AFFICHAGE
void LEDon() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(DisplayLEDs[i], HIGH);
  }
}

void LEDoff() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(DisplayLEDs[i], LOW);
  }
}

void LEDblink(int num) {
  for (int j = 0; j < num; j++) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(DisplayLEDs[i], HIGH);
      
    }
delay(200);
    for (int i = 0; i < 3; i++) {
      digitalWrite(DisplayLEDs[i], LOW);
      
    }
  delay(200);
  }
}

void LEDpattern(int num) {
  for (int j = 0; j < num; j++) {
    for (int i = 0; i < 3; i++) {
      digitalWrite(DisplayLEDs[i], HIGH);
      delay(100);
    }
    
    for (int i = 0; i < 3; i++) {
      digitalWrite(DisplayLEDs[i], LOW);
      delay(100);
    }
  }
}
