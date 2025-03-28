#!/bin/bash

#조건이 참인경우 계속 돎
number=0
while [ $number -lt 10 ]
do
echo "$number"
number=`expr $number + 1`
done

#조건이 거짓인경우 계속 돎
number=0
until [ $number -gt 10 ]
do
echo "$number"
number=`expr $number + 1`
done
echo "script complete."
