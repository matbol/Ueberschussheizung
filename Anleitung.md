# Das erste mal kompilieren

## Zugang zum RaspberryPi

Der Zugang zum RaspberryPi erfolgt über zwei Wegen, einmal einen "Spiegel" (VNC)[^1] der Oberfläche des RaspberryPi oder der Zugriff per Terminalsoftware auf die sogenannte Konsole. 
Konsolen oder Terminalzugriff erlangt man nur, wenn der RaspberryPI einen SSH [^2] Server aktiviert hat. Dieser kann natürlich nachträglich Installiert werden, will man den SSH direkt nach Installieren 
des Betriebssystems einsetzen, so muss in der Boot-Partition auf der SD-Karte einfach die Datei `ssh` abgelegt werden, ohne Inhalt und ohne Dateiendung. Danach startet der RaspberryPi mit der Möglichkeit 
per Standardpasswörter (User: pi Passwort: raspberry) und korrekter IP auf Ihn zuzugreifen.
Die IP wird in der Regel vom Router vergeben und lässt sich dementsprechend im heimischen Netzwerk über die Routerwebsite erfahren. Dort werden in der Regel alle angeschlossenen Geräte angezeigt und verwaltet. 

Nun kann mittels Terminalsoftware z.B. Putty [^3] oder einfach über das integrierte SSH Tool in der Windows Konsole auf das RaspberryPi-Terminal zugegriffen werden (IP entsprechend austauschen):

```shell
ssh pi@192.168.178.60
```
Dann wird beim erstmaligen Zugriff gefragt, ob man das öffentliche Zertifikat austauschen und für vertrauenswürdig anerkennt, dies muss man mit **Ja** bestätigen. 
Daraufhin erfolgt die Blindeingabe des Passwortes und schon ist man auf dem eher unscheinbaren Terminal angekommen. Nun hat man direkten Zugriff auf den RaspberryPi und dessen Befehlspalette.


## Git Repository "klonen"

Das Git Repository, also das Verzeichnis welches das Versionierungsprogramm GIT überwacht, speichert und versioniert ist unser Arbeitsverzeichnis.
Dieses muss nun an einem geeigneten Platz abgelegt werden. Um zum geeigneten Platz zu kommen, muss nun mit `cd ` und der Pfadangabe zum Verzeichnis gewechselt werden. Hier kann zB das Homeverzeichnis `/home/pi` genutzt werden. 

Nun wird das Verzeichniss mittels `git clone https://github.com/matbol/Ueberschussheizung.git`geladen.

## Programmieren und Kompilieren

Nun kann in der der Datei **heat_ctrl.c** mittels eines geeigneten Editors der Programmteil angesehen werden: `nano heat_ctrl.c`
und auch verändert werden. Änderungen mit ctrl+s und ctrl+c absichern.

Nun kann kompiliert werden. Der Compiler GCC [^4] wird zum kompilieren benötigt. Wenn man keine Optionen mitgibt, wird GCC den kompletten Workflow durchführen. Wie die offizielle Dokumentation [^5] sagt: "[...] it normally does preprocessing, compilation, assembly and linking."

Genau das wollen wir in unserem Fall. Das Linking setzt voraus das die Bibliotheken richtig installiert sind. Vorallem WiringPi in diesem Fall muss installiert werden:
http://wiringpi.com/download-and-install/

Danach kann losgelegt werden, der Kompiler kann seine Arbeit tun: `sudo gcc -o heat.exe heat_ctrl.c -lwiringPi -lcurl`. Das `.exe` ist nicht nötig, nur für mich als Hauptwindows-User ganz nett um zu sehen, welche die ausführbare Datei ist.

Nun kann das Programm gestartet werden:
`sudo ./heat.exe`



[^1]: https://www.realvnc.com/de/connect/download/vnc/raspberrypi/
[^2]: Secure Shell
[^3]: https://www.putty.org/
[^4]: https://gcc.gnu.org/
[^5]: https://man7.org/linux/man-pages/man1/gcc.1.html
