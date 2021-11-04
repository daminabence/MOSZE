#!/bin/bash

IFS=$'\n'
./$1 < ./input.txt > $2
