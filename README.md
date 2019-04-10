# Arduino-workshop

Για να τρέξουν οι κώδικες χρειάζεται να έχουμε την 
τελευταία έκδοση του arduino 1.8.9 όπως επίσης και 
την python2.7 με την πιο πρόσφατη έκδοση του pip2 
(προτεινόμενη 8.1.1) 

## Εγκατάσταση

### Για windows:

#### Arduino
Κατεβάστε την τελευταία έκδοση του Arduino IDE από εδώ:
https://downloads.arduino.cc/arduino-1.8.9-windows.exe

#### Python
Ένας εύκολος τρόπος να έχετε όλα όσα χρειάζονται είναι να 
κατεβάσετε την τελευταία έκδοση του Anaconda από εδώ:
https://repo.anaconda.com/archive/Anaconda2-2019.03-Windows-x86_64.exe


### Για Linux

#### Arduino 
Κατεβάστε το Arduino IDE από το official site.

#### Python
Σιγουρευτείτε ότι το σύστημα σας τρέχει python2.7 και την πιο πρόσφατη
έκδοση του pip αλλιώς προσπαθήστε να τα εγκαταστήσετε μέσω κάποιου 
package manager

## Πώς ξέρω ότι είμαι έτοιμος;
Μόλις εγκαταστήσετε τα παραπάνω τρέξτε το εξής σε κάποιο terminal 
ή από το Anaconda Prompt

### Windows
Ανοίξτε το Anaconda Prompt και με την χρήση των εντολών dir και cd μεταφερθείτε
στο folder που υπάρχουν οι κώδικες και τρέξτε την παρακάτω εντολή.

```
C:\Users\CS\Desktop\Arduino > python runme.py -p 1 
```
Αν δεν υπάρχουν κάποια απαραίτητα πακέτα, σε περίπτωση που έχετε την τελευταία Python και pip θα εγκατασταθούν αυτόματα τα απαραίτητα dependencies και στην συνέχεια θα πρέπει να εμφανίζεται το παρακάτω μήνυμα 

```
My platform: Windows
Connecting to: COM1
USB is not connected
USB is not connected
USB is not connected
...
```

### Linux
Μέσω του terminal μεταφερθείτε στο folder του project και τρέξτε την παρακάτω εντολή

```
$ python runme.py -p 1
```

ΣΗΜΕΙΩΣΗ: Ισως χρειαστεί να τρέξει με sudo

Αν δεν υπάρχουν κάποια απαραίτητα πακέτα, σε περίπτωση που έχετε την τελευταία Python και pip θα εγκατασταθούν αυτόματα τα απαραίτητα dependencies και στην συνέχεια θα πρέπει να εμφανίζεται το παρακάτω μήνυμα 

```
My platform: Linux
Connecting to: /dev/ttyUSB1
USB is not connected
USB is not connected
USB is not connected
...
```
