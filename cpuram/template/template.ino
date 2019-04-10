#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/**
 * \brief 		Κάνει το απαραίτητο setup στην οθόνη
 * 
 * \param 0x27 	Η διεύθυνση στην οποία βρίσκεται η οθόνη 
 * \param 16   	Πόσοι χαρακτήρες υπάρχουν σε κάθε γραμμή 
 * \param 2    	Πόσες γραμμές υπάρχουν
 */
LiquidCrystal_I2C lcd(0x27,16,2);  

/// Αυτές είναι οι τιμές των ποσοστών της ram και του CPU μαζί με αρχικοποίηση
String ramValue="0",cpuValue="0";

void setup(){
	/// Αρχικοποιεί την σειριακή θύρα σε bandwidth 9600 bits/sec
	

	/// Αρχικοποιούμε την οθόνη
	

	/// Εμφανίζουμε ένα μήνυμα καλωσορίσματος και περιμένουμε 500 milliseconds
	
}

void loop(){
	/// Περιμένουμε μέχρι να μας έρθουν δεδομένα
	
	// Διαβάζουμε τα δεδομένα
	
	// Από τα δεδομένα παίρνουμε την τιμή του cpu load
	
	// Από τα δεδομένα παίρνουμε την τιμή του ram load
	
	//Εμφανίζουμε τα δεδομένα
	
	/// Περιμένουμε 1 δευτερόλεπτο
	delay(1000);
}






//--------------------------------------------------------------------------
//			Οι συναρτήσεις που χρησιμοποιούνται

/**
 *  \brief Επιστρέφει την τιμή του cpu
 * 
 *  \param serialData Το μήνυμα που παραλάβαμε
 * 
 *  \return String η τιμή του cpu
 */
String getCpuValue(String serialData){
	return getValue(serialData,'|',0);
}

/**
 *  \brief Επιστρέφει την τιμή της ram
 * 
 *  \param serialData Το μήνυμα που παραλάβαμε
 * 
 *  \return String η τιμή της ram
 */
String getRamValue(String serialData){
	return getValue(serialData,'|',1);
}

/**
 *  \brief 	Βρίσκει μέσα σε ένα String αν υπάρχει ο separator
 *		που επιθυμούμε και επιστρεφει το string που υπάρχει
 *		πριν την Νοστή εμφάνιση του
 * 
 *  \param 	data Το μήνυμα που θέλουμε να ελέγξουμε
 *  \param 	separator ο separator που μας ενδιαφέρει
 *  \param 	index η Nοστή εμφάνιση του
 * 
 *  \return String η συμβολοσειρά που μας ενδιαφέρει
 * 
 *  \see 	https://stackoverflow.com/questions/9072320/split-string-into-string-array
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