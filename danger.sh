#AUTEURS : Pauline Bernard, Cherine Seo, Edouard Mignien

#!/bin/bash
./initAll.sh
KEY=8
BUTTONPUSHED=1

while [ true ]
do
    BUTTONPUSHED=$(</sys/class/gpio/gpio$KEY/value) #BUTTONPUSHED prend la valeur de l'état du bouton
    sleep 0.2

    if [ $BUTTONPUSHED = 0 ] #Si le bouton est appuyé
    then
        sh -c "echo 1 > /sys/class/gpio/gpio5/value" #GPIO5 prend 1
        #On éteint toutes les leds
        ./LedOFF RED1
        ./LedOFF YELLOW1
        ./LedOFF GREEN1
        sshpass -p raspberry ssh pi@192.168.137.14 ./LedOFF RED1
        sshpass -p raspberry ssh pi@192.168.137.14 ./LedOFF GREEN1
        sshpass -p raspberry ssh pi@192.168.137.14 ./LedOFF YELLOW1
        sshpass -p raspberry ssh pi@192.168.137.14 ./off
        i=0

        while [ true ]
        do
            BUTTONPUSHED=$(</sys/class/gpio/gpio$KEY/value)
                sleep 0.2

            if [ $BUTTONPUSHED = 0 ] #Si le bouton est appuyé à nouveau
            then
                ./LedOFF YELLOW2 #On éteint la led du mode danger

                sh -c "echo 0 > /sys/class/gpio/gpio5/value" #GPIO5 prend 0
                break
            else
                if [ $i = 0 ] #Sinon fait clignoter la led du mode danger
                then
                    ./LedON YELLOW2
                    i=1
                else
                    ./LedOFF YELLOW2
                    i=0
                fi
            fi
        done
        sleep 0.2
    fi
done
