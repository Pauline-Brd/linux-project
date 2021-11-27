#!/bin/bash
./initAll.sh
./danger.sh &
./interface &
while [ 1 ]
do
#On entre dans les 3 if si le bouton n'est pas appuyé
        if [ $(</sys/class/gpio/gpio5/value) = 0 ] #Feu voitures vert feu piétons rouge
        then
                ./LedOFF RED1 &
                sshpass -p raspberry ssh pi@192.168.137.14 ./LedOFF GREEN1 &
                ./LedON GREEN1 &
                sshpass -p raspberry ssh pi@192.168.137.14 ./LedON RED1 &
                ./clock 10
        fi
        if [ $(</sys/class/gpio/gpio5/value) = 0 ] #Feu voitures orange feu piétons rouge
        then
                ./LedOFF GREEN1 &
                sshpass -p raspberry ssh pi@192.168.137.14 ./LedON RED1 &
                ./LedON YELLOW1 &
                ./clock 10
        fi
        if [ $(</sys/class/gpio/gpio5/value) = 0 ] #feu voitures rouge feu piétons vert
        then
                ./LedOFF YELLOW1 &
                sshpass -p raspberry ssh pi@192.168.137.14 ./LedOFF RED1 &
                ./LedON RED1 &
                sshpass -p raspberry ssh pi@192.168.137.14 ./LedON GREEN1 &
                sshpass -p raspberry ssh pi@192.168.137.14 ./buzzer.sh &
                ./clock 10
        fi
done
