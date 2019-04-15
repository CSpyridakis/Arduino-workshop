/**
	Author : Spyridakis Christos   
   	Created Date : 10/4/2019
   	Last Updated : 15/4/2019
   	Email : spyridakischristos@gmail.com
	
	Description: 	
		Σε  αυτό  το  πρόγραμμα  διαβάζονται από την σειριακή θύρα 
		πακέτα  τα  οποία  περιέχουν  πληροφορίες  σχετικά  με  το 
		ποσοστό χρήσης του cpu και της ram και εμφανίζονται σε μία 
		Liquid Crystal Display (LCD) με την χρήση του I2C protocol

   	Dependencies: LiquidCrystal_I2C.h
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/**
 * \brief	Κάνει το απαραίτητο setup στην οθόνη
 * 
 * \param 0x27 	Η διεύθυνση στην οποία βρίσκεται η οθόνη 
 * \param 16   	Πόσοι χαρακτήρες υπάρχουν σε κάθε γραμμή 
 * \param 2    	Πόσες γραμμές υπάρχουν
 */
LiquidCrystal_I2C lcd(0x27,16,2);  

/// Αυτές είναι οι τιμές των ποσοστών της ram και του CPU μαζί με αρχικοποίηση
String ramValue="0",cpuValue="0";

/**
 * \brief Εκτελείται μία φορά και κάνει τις απαραίτητες 
 *        αρχικοποιήσεις
 */
void setup(){
	// Αρχικοποίηση της σειριακή θύρα σε bandwidth 9600 bits/sec

	// Αρχικοποιούμε την οθόνη

	// Εμφανίζουμε ένα μήνυμα καλωσορίσματος και περιμένουμε 500 milliseconds

}

/** 
 *  \brief Είναι το κύριο μέρος της εφαρμογής, επαναλαμβάνεται συνέχεια
 */
void loop(){
	// Περιμένουμε μέχρι να μας έρθουν δεδομένα
	
	// Διαβάζουμε τα δεδομένα
	
	// Από τα δεδομένα παίρνουμε την τιμή του cpu load
	// Hind: χρησιμοποιήστε την έτοιμη συνάρτηση getCpuValue

	// Από τα δεδομένα παίρνουμε την τιμή του ram load
	// Hind: χρησιμοποιήστε την έτοιμη συνάρτηση getRamValue
	
	// Εμφανίζουμε τα δεδομένα στην σειρακή θύρα
	
	// Εμφανίζουμε τα δεδομένα στην LCD
		
	/// Περιμένουμε 100 milliseconds

}








//--------------------------------------------------------------------------
//			Οι συναρτήσεις που χρησιμοποιούνται
//			Μπορείτε να προσθέσετε τις δικές σας 
//			αλλά δεν είναι απαραίτητο

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