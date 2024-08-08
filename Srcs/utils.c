#include "ft_ls.h"

char* getPath(const char* dir_path, const char*  dir_name)
{
	char*		path = NULL;
	if(dir_path[ft_strlen(dir_path) - 1] != '/'){
		char* tmp = ft_strjoin(dir_path, "/");
		path = ft_strjoin(tmp, dir_name);
		free(tmp);
	}
	else
		path = ft_strjoin(dir_path, dir_name);
	return path;
}
