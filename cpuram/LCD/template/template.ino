/**
	Author : Spyridakis Christos   
   	Created Date : 10/4/2019
   	Last Updated : 15/4/2019
   	Email : spyridakischristos@gmail.com
	
	Description: 	
		Σε  αυτό  το  πρόγραμμα  διαβάζονται από την σειριακή θύρα 
		πακέτα  τα  οποία  περιέχουν  πληροφορίες  σχετικά  με  το 
		ποσοστό χρήσης του cpu και της ram και εμφανίζονται σε μία 
		Liquid Crystal Display (LCD)

   	
	The circuit:
	* LCD VSS pin 	 -> ARDUINO ground
	* LCD VDD pin 	 -> ARDUINO 5V
	* LCD V0 pin 	 -> ARDUINO digital pin 6
	* LCD RS pin 	 -> ARDUINO digital pin 12
	* LCD R/W pin 	 -> ARDUINO ground
	* LCD Enable pin -> ARDUINO digital pin 11
	* 
	* 
	* 
	* 
	* LCD D4 pin 	 -> ARDUINO digital pin 5
	* LCD D5 pin 	 -> ARDUINO digital pin 4
	* LCD D6 pin 	 -> ARDUINO digital pin 3
	* LCD D7 pin 	 -> ARDUINO digital pin 2
	* LCD A pin 	 -> ARDUINO digital pin 9
	* LCD K pin 	 -> ARDUINO ground 
*/

#include <LiquidCrystal.h>

#define Contrast 100
int backPin = 9, contrPin=6; 

/**
 * \brief	Κάνει το απαραίτητο setup στην οθόνη
 * 
 * \param 12 	To reset 
 * \param 11   	Το Enable
 * \param 5    	Tο D4
 * \param 4    	Tο D5
 * \param 3    	Tο D6
 * \param 2    	Tο D7
 */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

/// Αυτές είναι οι τιμές των ποσοστών της ram και του CPU μαζί με αρχικοποίηση
String ramValue="0",cpuValue="0";

/**
 * \brief Εκτελείται μία φορά και κάνει τις απαραίτητες 
 *        αρχικοποιήσεις
 */
void setup(){
	// Xρησιμοποιούνται για τον έλεγχο του backlight και του Contrast
	pinMode(contrPin,OUTPUT);
	pinMode(backPin,OUTPUT);
	analogWrite(contrPin,Contrast);

	// Αρχικοποιεί την σειριακή θύρα σε bandwidth 9600 bits/sec

	// Αρχικοποιούμε την οθόνη, μετά από αυτό το σημείο
	// μπορούμε να την χρησιμοποιήσουμε κανονικά	

	// Εμφανίζουμε ένα μήνυμα καλωσορίσματος και περιμένουμε 500 milliseconds
}

/** 
 *  \brief Είναι το κύριο μέρος της εφαρμογής, επαναλαμβάνεται συνέχεια
 */
void loop(){
	// Περιμένουμε μέχρι να μας έρθουν δεδομένα
	
	// Διαβάζουμε τα δεδομένα
	
	// Από τα δεδομένα παίρνουμε την τιμή του cpu load
	
	// Από τα δεδομένα παίρνουμε την τιμή του ram load
	
	// Εμφανίζουμε τα δεδομένα στην σειρακή θύρα
	
	// Εμφανίζουμε τα δεδομένα στην LCD
	
	/// Περιμένουμε 100 milliseconds
}

//--------------------------------------------------------------------------
//			Οι συναρτήσεις που χρησιμοποιούνται


/**
 * \brief Επιστρέφει την τιμή του cpu
 * 
 * \param serialData Το μήνυμα που παραλάβαμε μέσω της σειριακής
 * 
 * \return String η τιμή του cpu
 */
String getCpuValue(String serialData){
	return getValue(getValue(serialData,'|',0),'[',1);
}

/**
 * \brief Επιστρέφει την τιμή της ram
 * 
 * \param serialData Το μήνυμα που παραλάβαμε μέσω της σειριακής
 * 
 * \return String η τιμή της ram
 */
String getRamValue(String serialData){
	return getValue(getValue(serialData,']',0),'|',1);
}

/**
 * \brief 	Βρίσκει μέσα σε ένα String αν υπάρχει ο separator
 *		που επιθυμούμε και επιστρεφει το string που υπάρχει
 *		πριν την Νοστή εμφάνιση του
 * 
 * \param 	data Το μήνυμα που θέλουμε να ελέγξουμε
 * \param 	separator ο separator που μας ενδιαφέρει
 * \param 	index η Nοστή εμφάνιση του
 * 
 * \return 	String η συμβολοσειρά που μας ενδιαφέρει
 * 
 * \see 	https://stackoverflow.com/questions/9072320/split-string-into-string-array
 *  		έχει χρησιμοποιηθεί από τον παραπάνω σύνδεσμο
 */
String getValue(String data, char separator, int index){
	int found = 0;
	int strIndex[] = {0, -1};
	int maxIndex = data.length()-1;

	for(int i=0; i<=maxIndex && found<=index; i++){
		if(data.charAt(i)==separator || i==maxIndex){
			found++;
			strIndex[0] = strIndex[1]+1;
			strIndex[1] = (i == maxIndex) ? i+1 : i;
		}
	}
 	return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

/**
 * \brief 	Ανάβει το backlight
 */
void backlightOn(){
	analogWrite(backPin,28836);
}
/**
 * \brief 	Σβήνει το backlight
 */
void backlightOff(){
	analogWrite(backPin,0);
}