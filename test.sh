TEST_DIR="/goinfre/mkardes"
counter=1
args="-a"

valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-la";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-l";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-lR";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-R";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args=". .. . ../..";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-l . .. . ../.";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-t";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-r";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-rt";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-rtl";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-rtlR";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter}; counter=$((counter + 1)) args="-rtlRa";
valgrind --leak-check=full ./ft_ls ${args} 1> ${TEST_DIR}/log/log${counter} 2> ${TEST_DIR}/log/log_val${counter}; ls ${args} > ${TEST_DIR}/log/ls_log${counter};