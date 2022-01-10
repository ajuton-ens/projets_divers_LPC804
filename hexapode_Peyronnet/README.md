# Hexapode
 Ce projet consiste à mettre en marche un robot hexapode à l'aide d'une microcontrôleur LPC804. 
 Cet hexapode est constitué d'une base octogonale, et de six pattes situées à 45°, 90° et 135°, de façon symétrique par rapport à l'avant du robot. 
 Chacune des pattes est constituées de trois servomoteur [AX-12](https://emanual.robotis.com/docs/en/dxl/ax/ax-12a/) liés les uns aux autres, l'un d'eux étant accroché à la base octogonale, et un autre lié à un pied en plastique.
 ![Robot](https://github.com/VoltXd/TP_HEXAPODE/blob/main/image/robot.png "Vue de dessus")
 
## Commande angulaire des servomoteurs
 Les servomoteurs se commandent à l'aide du [Dynamixel Protocol 1.0](https://emanual.robotis.com/docs/en/dxl/protocol1/). 
 Il consiste à envoyer une trame permettant d'identifier le moteur à commander, puis de lui demander d'exécuter diverses instructions, ce peut être de la lecture ou de l'écriture de données par exemple. 
 Du côté de la LPC804, l'émission des trames se fait à l'aide d'un périphérique UART par liaison série. 
 Pour imposer l'angle d'un servomoteur, il suffit alors d'envoyer une trame d'écriture à l'adresse 30 (goal position), suivi du LSB et du MSB de l'angle pour des valeurs entre 0 et 1023 (une règle de trois permet de retrouver l'angle réel). 
 Une fois la trame construite, elle est stockée dans un buffer circulaire puis chaque caractère est émis un à un à l'aide de l'interruption TXIDLE, qui déclenche une interruption lorsque la transmission n'est pas en cours. 
 Cette interruption est désactivée lorsque l'on a plus de donnée à émettre.
 ![protoc](https://github.com/VoltXd/TP_HEXAPODE/blob/main/image/protoc.PNG)
 ![CB](https://github.com/VoltXd/TP_HEXAPODE/blob/main/image/CB.png)
 
## Commande en position des pattes
 Les pattes sont pilotés en commandant la position cartésienne de l'extrémité des pieds.
 Pour cela, on dispose de plusieurs équations permettant de passer de la position désirée, aux trois angles à envoyer aux moteur de la patte.
 ![eq](https://github.com/VoltXd/TP_HEXAPODE/blob/main/image/eq.PNG)
 ![r](https://github.com/VoltXd/TP_HEXAPODE/blob/main/image/robot%20-%20Copie.png "Vue de dessus")
 ![t1](https://github.com/VoltXd/TP_HEXAPODE/blob/main/image/pattes_theta1.png "Vue de dessus")
 ![t23](https://github.com/VoltXd/TP_HEXAPODE/blob/main/image/pattes_theta23.png "Vue de côté")
 
## Trajectoire du robot
 Le robot suit une simple trajectoire rectiligne.
 La bibliothèque fournit était censé permettre une rotation, celle-ci n'a malheureusement jamais fonctionné.
 Afin d'effectuer cette trajectoire rectiligne, les pieds suivent une trajectoire circulaire.
 Par exemple pour aller tout droit, le pied central droit et les pieds extérieurs gauche vont suivre un cercle, les autres pieds vont suivre le même cercle avec un déphasage de 180°, ce qui permet au robot d'avancer.  
 [![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/M41KNuEWdtw/0.jpg)](https://www.youtube.com/watch?v=M41KNuEWdtw)
 
## Commande de la trajectoire par bluetooth
 Afin de piloter l'hexapode à distance, on utilise un périphérique permettant de convertir des données bluetooth en données lisible par liaison série, celles-ci sont émise via un smartphone et l'application [SENA BTerm Bluetooth Terminal](https://play.google.com/store/apps/details?id=com.sena.bterm&hl=fr&gl=US).
 Les données reçues permettent de faire les actions suivantes : 
  * 'Z' : Aller tout droit; 
  * 'Q' : Aller à gauche;
  * 'S' : Aller en arrière;
  * 'D' : Aller à droite;
  * 32 (espace) : S'arrêter; 

## Diagramme synoptique
 ![diag](https://github.com/VoltXd/TP_HEXAPODE/blob/main/image/synoptique.png)
 
###### Rendu
 à rendre sur https://github.com/ajuton-ens/projets_divers_LPC804
