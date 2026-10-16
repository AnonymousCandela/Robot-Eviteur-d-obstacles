#include <Servo.h> // Inclut la bibliothèque pour contrôler les servomoteurs.
Servo Myservo ; // Crée une instance de la classe Servo pour contrôler un servo-moteur.
// Définition des broches pour le capteur de distance HC-SR04.
#define trigPin 11 // Broche Trig pour envoyer les impulsions ultrasoniques.
#define echoPin 12 // Broche Echo pour recevoir les impulsions ultrasoniques réfléchies.
// Définition des broches pour le contrôle des moteurs.
#define ENA 9 // Broche d'activation pour le moteur A.
#define IN1 8 // Broche de commande 1 pour le moteur A.
 

#define IN2 7 // Broche de commande 2 pour le moteur A.
#define ENB 3 // Broche d'activation pour le moteur B.
#define IN3 5 // Broche de commande 1 pour le moteur B.
#define IN4 6 // Broche de commande 2 pour le moteur B.
long duration, distance; // Variables pour stocker la durée des impulsions et la distance calculée.
void setup() {
 // Configuration des broches comme sorties ou entrées.
 pinMode(ENA, OUTPUT) ;
 pinMode(IN1, OUTPUT) ;
 pinMode(IN2, OUTPUT) ;
 pinMode(ENB, OUTPUT) ;
 pinMode(IN3, OUTPUT) ;
 pinMode(IN4, OUTPUT) ;
 pinMode(trigPin, OUTPUT) ; // Configure la broche Trig comme sortie.
 pinMode(echoPin, INPUT) ; // Configure la broche Echo comme entrée.
 Myservo.attach(13) ; // Attache le servo-moteur à la broche 13.
}
void loop() {
 Serial.begin(9600) ; // Initialise la communication série à 9600 
 // Envoie une impulsion ultrasonique.
 digitalWrite(trigPin, LOW) ;
 delayMicroseconds(2) ;
 digitalWrite(trigPin, HIGH) ;
 delayMicroseconds(10) ;
 digitalWrite(trigPin, LOW) ;
 // Calcule la distance en mesurant le temps de retour de l'impulsion.
 duration = pulseIn(echoPin, HIGH) ;
 distance = duration / 58.2; // Convertit la durée en distance.
 Serial.println(distance) ; // Affiche la distance sur le moniteur série.
 // Contrôle des moteurs en fonction de la distance détectée.
 if (distance > 15) {
 // Si aucun obstacle n'est détecté, fait avancer le robot.
 Myservo.write(90) ; // Positionne le servo-moteur à 90 degrés.
 // Fait avancer les moteurs.
 digitalWrite(IN1, HIGH) ;
 digitalWrite(IN2, LOW) ;
 

 analogWrite(ENA, 200) ; // Régle la vitesse du moteur A.
 digitalWrite(IN3, HIGH) ;
 digitalWrite(IN4, LOW) ;
 analogWrite(ENB, 200) ; // Régle la vitesse du moteur B.
 } else if ((distance < 15) && (distance > 0)) {
 // Si un obstacle est détecté à moins de 15 cm, fait reculer le robot.
 // Arrête les moteurs.
 digitalWrite(IN1, LOW) ;
 digitalWrite(IN2, LOW) ;
 digitalWrite(IN3, LOW) ;
 digitalWrite(IN4, LOW) ;
 delay(100) ;
 // Fait pivoter le robot pour éviter l'obstacle.
 Myservo.write(0) ;
 delay(500) ;
 Myservo.write(180) ;
 delay(500) ;
 Myservo.write(90) ;
 delay(500) ;
 // Fait reculer les moteurs.
 digitalWrite(IN1, LOW) ;
 digitalWrite(IN2, HIGH) ;
 analogWrite(ENA, 200) ; // Régle la vitesse du moteur A.
 digitalWrite(IN3, LOW) ;
 digitalWrite(IN4, HIGH) ;
 analogWrite(ENB, 200) ; // Régle la vitesse du moteur B.
 delay(500) ;
 // Arrête les moteurs.
 digitalWrite(IN1, LOW) ;
 digitalWrite(IN2, LOW) ;
 digitalWrite(IN3, LOW) ;
 digitalWrite(IN4, LOW) ;
 delay(100) ;
 }
}