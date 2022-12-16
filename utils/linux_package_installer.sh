#!/bin/bash

argc=$#
flag="all"

configfile=$(find $(dirname "$0") -name "utils.conf")
configcount=$(echo "$configfile" | wc -l)

if [ -n "$configfile" ] && [ $configcount -eq 1 ]; then
    source $configfile
else
    echo "ERROR: unable to locate utils.config file"
    exit 0
fi

if [ $argc -gt 1 ]; then
    echo "ERROR: too many arguments"
    flag="h"
elif [ $argc -eq 1 ]; then
    if [[ "$1" == "--help" ]] || [[ "$1" == "-h" ]]; then
        flag="h"
    elif [[ "$1" == "--essential" ]] || [[ "$1" == "-e" ]]; then
        flag="e"
    elif [[ "$1" == "--optional" ]] || [[ "$1" == "-o" ]]; then
        flag="o"
    else
        echo "ERROR: unknown option"
        flag="h"
    fi
fi

if [[ "$flag" == "h" ]]; then
    echo "usage: ./linux_package_installer.sh [ options ]"
    echo "options:"
    echo "  -h --help       - displays help"
    echo "  -e --essential  - installs essential packages"
    echo "  -o --optonal    - installs optional packages"
    echo "  (no option)     - (default) launches the script with [-e] and [-o] flags"
    exit 0
fi

sudo apt-get update

echo "" && echo "installing kit: $projectname: ESSENTIAL"
if [[ "$flag" == "e" ]] || [[ "$flag" == "all" ]]; then
    for ((i=0; i<${#packages_ess[@]}; i++)); do
        package="${packages_ess[i]}"
        echo "   installing $package..."
        check=$(dpkg -s $package 2>/dev/null | grep -c "ok installed")
        if [ $check -eq 0 ]; then
            sudo apt-get install $package
            check=$(dpkg -s $package 2>/dev/null | grep -c "ok installed")
            if [ $check -ne 1 ]; then
                echo "      ERROR: $package package not found after attempting installation; exit"
                exit 0;
            else echo "      $package installation complete"
            fi
        else echo "      $package is already installed"
        fi
    done
else echo "      skip"
fi

echo "" && echo "installing kit: $projectname: OPTIONAL"
if [[ "$flag" == "o" ]] || [[ "$flag" == "all" ]]; then
    for ((i=0; i<${#packages_opt[@]}; i++)); do
        package="${packages_opt[i]}"
        echo "   installing $package..."
        check=$(dpkg -s $package 2>/dev/null | grep -c "ok installed")
        if [ $check -eq 0 ]; then
            sudo apt-get install $package
            check=$(dpkg -s $package 2>/dev/null | grep -c "ok installed")
            if [ $check -ne 1 ]; then
                echo "      ERROR: $package package not found after attempting installation; exit"
                exit 0;
            else echo "      $package installation complete"
            fi
        else echo "      $package is already installed"
        fi
    done
else echo "      skip"
fi
