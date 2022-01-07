# Hexapode
 Ce projet consiste à mettre en marche un robot hexapode à l'aide d'une microcontrôleur LPC804. 
 Cet hexapode est constitué d'une base octogonale, et de six pattes situées à 45°, 90° et 135°, de façon symétrique par rapport à l'avant du robot. 
 Chacune des pattes est constituées de trois servomoteur [AX-12](https://emanual.robotis.com/docs/en/dxl/ax/ax-12a/) liés les uns aux autres, l'un d'eux étant accroché à la base octogonale, et un autre lié à un pied en plastique.
 
## Commande angulaire des servomoteurs
 Les servomoteurs se commandent à l'aide du [Dynamixel Protocol 1.0](https://emanual.robotis.com/docs/en/dxl/protocol1/). 
 Il consiste à envoyer une trame permettant d'identifier le moteur à commander, puis de lui demander d'exécuter diverses instructions, ce peut être de la lecture ou de l'écriture de données par exemple. 
 Du côté de la LPC804, l'émission des trames se fait à l'aide d'un périphérique UART par liaison série. 
 Pour imposer l'angle d'un servomoteur, il suffit alors d'envoyer une trame d'écriture à l'adresse 30 (goal position), suivi du LSB et du MSB de l'angle pour des valeurs entre 0 et 1023 (une règle de trois permet de retrouver l'angle réel). 
 Une fois la trame construite, elle est stockée dans un buffer circulaire puis chaque caractère est émis un à un à l'aide de l'interruption TXIDLE, qui déclenche une interruption lorsque la transmission n'est pas en cours. 
 Cette interruption est désactivée lorsque l'on a plus de donnée à émettre.
 
## Commande en position des pattes
 
 
 
 à rendre sur https://github.com/ajuton-ens/projets_divers_LPC804
