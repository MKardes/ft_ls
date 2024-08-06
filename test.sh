valgrind --leak-check=full ./ft_ls -a              1> /tmp/log/log1 2> /tmp/log/log_val1;  ls -a              > /tmp/log/ls_log1; 
valgrind --leak-check=full ./ft_ls -la             1> /tmp/log/log2 2> /tmp/log/log_val2;  ls -la             > /tmp/log/ls_log2; 
valgrind --leak-check=full ./ft_ls -l              1> /tmp/log/log3 2> /tmp/log/log_val3;  ls -l              > /tmp/log/ls_log3; 
valgrind --leak-check=full ./ft_ls -lR             1> /tmp/log/log4 2> /tmp/log/log_val4;  ls -lR             > /tmp/log/ls_log4; 
valgrind --leak-check=full ./ft_ls -R              1> /tmp/log/log5 2> /tmp/log/log_val5;  ls -R              > /tmp/log/ls_log5; 
valgrind --leak-check=full ./ft_ls . .. . ../..    1> /tmp/log/log6 2> /tmp/log/log_val6;  ls . .. . ../..    > /tmp/log/ls_log6; 
valgrind --leak-check=full ./ft_ls -l . .. . ../.. 1> /tmp/log/log7 2> /tmp/log/log_val7;  ls -l . .. . ../.. > /tmp/log/ls_log7; 
valgrind --leak-check=full ./ft_ls                 1> /tmp/log/log8 2> /tmp/log/log_val8;  ls                 > /tmp/log/ls_log8;