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

/**
 * \brief Εκτελείται μία φορά και κάνει τις απαραίτητες 
 *        αρχικοποιήσεις
 */
void setup(){
	/// Αρχικοποιεί την σειριακή θύρα σε bandwidth 9600 bits/sec
	Serial.begin(9600);

	/// Αρχικοποιούμε την οθόνη, μετά από αυτό το σημείο
	/// μπορούμε να την χρησιμοποιήσουμε κανονικά
	lcd.init();                     
	lcd.backlight();

	/// Εμφανίζουμε ένα μήνυμα καλωσορίσματος και περιμένουμε 500 milliseconds
	lcd.setCursor(1,0);
	lcd.print("Welcome to the");
	lcd.setCursor(0,1);
	lcd.print("Arduino Workshop");
	delay(500);
}

/** 
 *  \brief Είναι το κύριο μέρος της εφαρμογής
 */
void loop(){
	/// Περιμένουμε μέχρι να μας έρθουν δεδομένα
	if(Serial.available()>0 ){
		//Διαβάζουμε τα δεδομένα
		String serialData = Serial.readString();
		// Από τα δεδομένα παίρνουμε την τιμή του cpu load
		cpuValue = getCpuValue(serialData);
		// Από τα δεδομένα παίρνουμε την τιμή του ram load
		ramValue = getRamValue(serialData);
		//Εμφανίζουμε τα δεδομένα
		printInScreen(cpuValue, ramValue);
	}
	/// Περιμένουμε 1 δευτερόλεπτο
	delay(1000);
}

//--------------------------------------------------------------------------
//					Οι συναρτήσεις που χρησιμοποιούνται

/**
 *  \brief Εμφανίζει στην οθόνη τις απαραίτητες πληροφορίες
 * 
 *  \param cpuValue Η ποσοστιαία τιμή χρήσης του cpu
 *	\param ramValue Η ποσοστιαία τιμή χρήσης της virtual mem 
 * 
 */
void printInScreen(String cpuValue, String ramValue){
	//Καθαρίζει την οθόνη και είναι σίγουρος ότι έχει backlight
	lcd.clear();
	lcd.backlight();
	//Εμφανίζει ένα κείμενο που εξηγεί τι δεδομένα έχουμε
	lcd.setCursor(0,0);lcd.print("CPU usage: ");
	lcd.setCursor(0,1);lcd.print("Ram usage: ");
	//Εμφανίζει τα δεδομένα
	lcd.setCursor(12,0);lcd.print(cpuValue);lcd.setCursor(15,0);lcd.print("%");
	lcd.setCursor(12,1);lcd.print(ramValue); lcd.setCursor(14,1);lcd.print(" %");
}

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
 *			που επιθυμούμε και επιστρεφει το string που υπάρχει
 *			πριν την Νοστή εμφάνιση του
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