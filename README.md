# Ueberschussheizung
Die Überschussheizung dient dazu, überschüssigen Photovoltaik-Strom zu nutzen und mittels Heizstab in einen Warmwassertank zu speichern. Der Heizstab soll kontinuierlich (stufenlos) angesteuert werden um auch bei geringer Einspeisung noch einen möglichst hohen Anteil Wärme in den Warmwassertank zu bringen.
Die Ansteuerung erfolgt über eine PWM und bedient eine Kemo Leistungsregelung [^1][^2]. 


Der Sollwert wird von einer externen Applikation - in diesem Fall "Volkszähler" [^3] - vorgegeben. Dafür bedarf es der libcurl welche auf Linux basierten System schon installiert ist. Eine weitere schon installierte Bibliothek ist die "Regex" Bibliothek, welche es ermöglicht Reguläre Ausdrücke zu nutzen. 

Dafür muss auf dem Volkszähler - genaueer **vzlogger** -  der *http* eingeschaltet und von dieser Applikation abgefragt werden.
```
"local": {
    "enabled": true,
    "port": 8081,
    "index": true,
    "timeout": 0,
    "buffer": 0
  },
```
Die bereitgestellten Daten sind in einem JSON Konstrukt untergebracht und können mittels JSON Parser abgefragt werden. IN diesem Projekt wurde der Abgriff der Daten mittels regulärer Ausdrücke durchgeführt, ein Parser wäre flexibler und umfangreicher, der reguläre Ausdruck ist somit relativ "dumm", änderungen am JSON werden eventuell Probleme auslösen. Dies sollte beachtet werden.

Die Pulsweitenmodulation greift auf Leistungsdaten eines ISKRA MT631 Zweirichtungszählers ab, welcher prinzipiell drei Dinge über seine optische Schnittstelle an den Verbraucher übermittelt: Zählerstand Bezug (Obis: 1-0:1.8.0), Einspeisung (Obis: 1-0:2.8.0) und aktuelle (Wirk-) Leistung (Obis: 1-0:1.67.0).


[^1]: https://www.kemo-electronic.de/de/Licht-Ton/Effekte/Module/M028-Leistungsregler-110-240-V-AC-2600-VA.php 
[^2]: https://www.kemo-electronic.de/de/Wandler-Regler/Konverter/M150-DC-Puls-Converter.php
[^3]: https://www.volkszaehler.org/








