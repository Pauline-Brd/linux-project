#AUTEURS : Pauline Bernard, Cherine Seo, Edouard Mignien

#!/bin/bash

gpio4=4
gpio17=17
gpio22=22
gpio10=10
gpio9=9
gpio11=11
buzzer=7
key=8
construction=5
#Ce script exporte toutes les broches GPIO et les définit en sortie/entrée
for gpiono in $gpio4 $gpio17 $gpio22 $gpio10 $gpio9 $gpio11 $buzzer $key $construction
do
    if [ ! -d /sys/class/gpio/gpio$gpiono ]
    then
        echo $gpiono > /sys/class/gpio/export
        sleep 1
    fi
done

for gpiono in $gpio4 $gpio17 $gpio22 $gpio10 $gpio9 $gpio11 $buzzer $construction
do
    echo out > /sys/class/gpio/gpio$gpiono/direction
done

echo in > /sys/class/gpio/gpio$key/direction
