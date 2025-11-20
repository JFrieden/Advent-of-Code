#!/bin/bash

# -------------------- CREATE PUZZLE DIRECTORY STRUCTURE -------------------- # 
year_regex="^20[0-9]{2}"
echo -n "Puzzle Year: " 
read YEAR
if [[ ! "$YEAR" =~ $year_regex ]]; then
    echo "$YEAR does not match an existing directory, an is not a valid format for an advent of code year (20##)."
    exit 1
fi
echo -n "Puzzle Day (1-25): "
read DAY

day_regex="^(1[0-9]|2[0-5]|[1-9])$"
if [[ ! "$DAY" =~ $day_regex ]]; then
    echo "$DAY is not a valid day (1-25)."
    exit 1
fi
echo -n "Puzzle Name: "
read NAME

if [[ -d "$YEAR/Day $DAY - $NAME" ]]; then
    cd "$YEAR/Day $DAY - $NAME"
else
    mkdir "$YEAR"
    cd "$YEAR"
    mkdir "Day $DAY - $NAME"
    cd "Day $DAY - $NAME"
fi

if [[ ! -f "input.txt" ]]; then
    touch "input.txt"
fi

if [[ ! -f "test_input.txt" ]]; then
    touch "test_input.txt"
fi

# ----------------------------- Handle Languages ---------------------------- #

echo -n "Language (C, Python, Java, etc.): "
read LANG
case "$LANG" in
    "Python"|"python")
        if [[ ! -f "answer.py" ]]; then
            cp ../../templates/template.py answer.py
        fi ;;
    "C"|"c")
        if [[ ! -f "answer.c" ]]; then
            cp ../../templates/template.c answer.c
        fi ;;
    "Java"|"java")
        if [[ ! -f "answer.java" ]]; then
            cp ../../templates/template.java answer.java
        fi ;;
    *)
        if [[ ! -f "answer.txt" ]]; then
            touch "answer.txt"
        fi
        echo "Unsupported language: $LANG. No template copied."
        ;;
esac

# ----------------------------- Generate Readme ----------------------------- #
cp ../../templates/puzzle_readme.md readme.md
sed -i "s/{{YEAR}}/$YEAR/g" readme.md
sed -i "s/{{DAY}}/$DAY/g" readme.md
sed -i "s/{{NAME}}/$NAME/g" readme.md
sed -i "s/{{LANGUAGE}}/$LANG/g" readme.md