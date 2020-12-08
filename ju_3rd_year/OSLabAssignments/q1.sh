#!/bin/bash

echo "Addition please enter two different numbers"

read -p "Enter the value of userv1: " userv1
read -p "Enter the value of userv2: " userv2

# check if entered numbers are integers
re='^[+-]?[0-9]+([.][0-9]+)?$'

if  [[ $userv1 =~ $re ]] &&  [[ $userv2 =~ $re ]]; then
    echo "Addition of $userv1 + $userv2 = $((userv1 + userv2))"
    echo "Multiplication of $userv1 * $userv2 = $((userv1 * userv2))"
    echo "Division of $userv1 / $userv2 = $((userv1 / userv2))"
    
else
    echo "Wrong format please enter integers"; exit 1
fi

## concatenation and common substring 

read -p "Enter first string: " str1   
read -p "Enter second string: " str2





