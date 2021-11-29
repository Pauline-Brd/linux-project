#AUTEURS : Pauline Bernard, Cherine Seo, Edouard Mignien

#!/bin/bash
if [ ! -d /sys/class/gpio/gpio7 ]
then
    echo 7 > /sys/class/gpio/export
fi
echo out > /sys/class/gpio/gpio7/direction
i=0
while [ $i != 32 ]
do
    sh -c "echo 0 > /sys/class/gpio/gpio7/value"
    sh -c "echo 1 > /sys/class/gpio/gpio7/value"
    sh -c "echo 0 > /sys/class/gpio/gpio7/value"
    if [ $i -lt 10 ]
    then
        sleep 0.5
        elif [ $i -lt 20 ]
        then
            sleep 0.3
        else sleep 0.1
    fi

    let "i+=1" #i++
done
