if [ $# -lt 1 ]; then
    echo "Error: not enough input arguments"
    echo "Usage: ./run.sh [arguments] [script_name]"
    read -p "Press any key to continue..."
    exit 1
fi

if [ $# -gt 1 ]; then
    echo "Error: Too many input arguments."
    echo "Usage: ./run.sh [arguments] [script_name]"
    read -p "Press any key to continue..."
    exit 1
fi


gcc -o ${1}_TEMP_EXE_.exe $1 src/ipv4_collection.c -Wall
./${1}_TEMP_EXE_.exe && rm -rf ${1}_TEMP_EXE_.exe
read -p "Press any key to continue..."
