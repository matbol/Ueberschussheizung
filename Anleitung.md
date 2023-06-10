# Zugang zum RaspberryPi

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






[^1]: https://www.realvnc.com/de/connect/download/vnc/raspberrypi/
[^2]: Secure Shell
[^3]: https://www.putty.org/
