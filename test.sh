TEST_DIR="/goinfre/mkardes"
counter=1
args_array=(
    '' 
    '-la' 
    '-lR' 
    '-l . .. . ../.' 
    '-tl' 
    '-rl' 
    '-rtl' 
    '-rtlR' 
    '-rtlRa' 
    '-lR ./'
    '-lRa -a -a -a .'
    '-lRa . Makefile -t'
    '-lR'
    '-lR .'
    '-l  . .'
    '-lR  . .'
    '-l'
    '- l'
    '-l main.c'
    '-l Makefile Makefile Makefile'
    '-jsd'
)

mkdir -p /goinfre/mkardes/log/diff
print_arguments() {
    local args=("$@")
    for arg in "${args[@]}"; do
        echo "./ft_ls \"${arg}\" testing..."
        valgrind --leak-check=full ./ft_ls ${arg} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter};
        ls ${arg} > ${TEST_DIR}/log/ls_log${counter};
        diff ${TEST_DIR}/log/log${counter} ${TEST_DIR}/log/ls_log${counter} > ${TEST_DIR}/log/diff/diff_${counter};
        counter=$((counter + 1));
    done
}

# Call the function with the array
print_arguments "${args_array[@]}"