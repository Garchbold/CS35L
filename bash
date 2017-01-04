#!/bin/bash
# your code goes here

echo "enter your number"
read numin

num=$(( $numin%2 ))

if [ $num -ne 0 ] 
then
   echo "odd"
else
   echo "even"
fi