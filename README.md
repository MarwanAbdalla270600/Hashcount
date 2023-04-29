# Hashcount -*Marwan Abdalla*

## Compilation
gcc -Wall -Wextra -pedantic main.c hashtable.c filereader.c -o prog 


## Execution
### Start Application
Das Programm besitzt mehrere Parameter. Man muss mindestens 2 Parameter angeben um das Programm auszuführen. 

 1. Die Textdatei welche anschließend in eine Hashtabelle gespeichert wird. Voraussetzung hierfür ist, das die Datei sich im Projektverzeichnis befindet. 
 2. Die Größe der Tabelle. Die Eingabe ist hier auf zwischen 0 und 1000 beschränkt. Grundsätzlich gibt es hier keine Beschränkung seitens der Funktionalität, allerdings macht es bei der vorgegebenen Datei wenig Sinn einen größeren Wert einzugeben. 

Aufrufbeispiel
./prog textfile.txt 8
 
 Als Ausgabe bekommt man eine Hashtabelle, in der alle Werte der Textdatei inklusive der Häufigkeit der einzelnen Wörter ausgegeben sind. 

Weiters gibt es noch optionale Parameter, welche Zusatzfunktionen aufrufen. 

**Flags**
 - -b : Erstellt mir zusätzlich eine Datei, in der die Tabelle namens "hashtable.bin" gespeichert wird. Diese Datei wird ausgelesen, in eine neue Tabelle gespeichert und anschließend wird diese Tabelle zur Kontrolle wieder ausgegeben. Sind beide Tabellen identisch, so war die Funktion erfolgreich.  b = "binary"
 
     Aufrufbeispiel
./prog testfile.txt 38 -b 
 - -c: Aktiviert eine Usereingabe, in der man sich einzelne Buckets der Tabelle ausgeben kann. Diese Usereingabe kann mittels der Eingabe "q" beendet werden.   c = "mir ist nichts eingefallen :)"
 
   Aufrufbeispiel
./prog testfile.txt 27 -c
 - -o: Dieses Flag erfordert nach der Eingabe der Tabellengröße einen weiteren Parameter, nämlich eine Auflistung von Buckets. Diese Buckets werden mit einem Beistrich von einander getrennt. Nach dem Aufruf wird eine neue Textdatei namens "output_only_buckets" erstellt. Diese Textdatei ist eine exakte Kopie der Textdatei, die der User mitgibt, jedoch kommen nur die Wörter darin vor, die in den Buckets in der Aufzählung enthalten sind. o = "only"
 
   Aufrufbeispiel
./prog testfile.txt 10 2,3,4,6,8,9 -o 
 
 - w: Fast identisch wie das Flag -o. Bei diesem Flag werden aber alle Wörter ausgegeben, die nicht in der Bucketliste vorkommen. Sprich, die Buckets in der Liste werden aus der Datei zensiert und in die Datei "output_without_buckets" geschrieben. w = without
 
   Aufrufbeispiel
./prog testfile.txt 10 2,3,4,6,8,9 -w

Die Bucketübergabe kann nur mit einem Bucketflag (-o oder -w) erfolgen. Ein Bucketflag kann nur mit einer zuvor übergebenen Bucketliste erfolgen. 
Die Flags -b und -c können immer erfolgen und die Flags lassen sich auch miteinander kombinieren.

**Mögliche Aufrufbeispiele**
./prog testfile.txt 15 1,2,3,10,11 -wo -bc
 ./prog testfile.txt 15 1,2,3,10,11 -w -o 
 ./prog testfile.txt 15 -b -c

**Keine möglichen Aufrufbeispiele**
  ./prog testfile.txt 15 1,2,3,10,11 -b
  ./prog testfile.txt 15 -w 
  ./prog testfile.txt 15 -o -c

**verwendete Libraries:**
 - stdlib.h
 - string.h
 - stdint.h
 - stdbool.h
 - ctype.h
 - math.h
 - unistd.h
 - getopt.h

