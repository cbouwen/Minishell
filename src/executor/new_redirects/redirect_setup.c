/*header pls*/

#include "../../../inc/minishell.h"

int	redirect_syntax_check(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	while (temp && temp->type != PIPE)
	{
		if (temp->type == REDIRECT)
		{
			if (temp->next->type == ARG)
			{
				if (ft_isdigit(temp->next->str[0]) == 1)
					return (ft_error("syntax error\n", 3));
			}
		}
		temp = temp->next;
	}
	return (0);
}

int	init_rd(t_token *tokens, t_rd_collection *rd)
{
	t_token			*temp;
	t_rd_collection	*temp_rd;

	temp = tokens;
	temp_rd = rd;
	temp_rd->input = ft_calloc(sizeof(char *), count_rd(temp) + 1);
	if (!temp_rd->input)
		return (12);
	temp_rd->output = ft_calloc(sizeof(char *), count_rd(temp) + 1);
	if (!temp_rd->output)
		return (12);
	temp_rd->append = ft_calloc(sizeof(char *), count_rd(temp) + 1);
	if (!temp_rd->append)
		return (12);
	return (0);
}

int	free_rd(t_rd_collection *rd)
{
	t_rd_collection	*temp_rd;

	temp_rd = rd;
	free_array(temp_rd->input);
	free_array(temp_rd->output);
	free_array(temp_rd->append);
	return (0);
}

char *get_directory(const char *path);
int is_path_viable(const char *path);

int redirect_test(t_token *tokens)
{
	t_rd_collection	rd;

	int status = redirect_syntax_check(tokens);
	init_rd(tokens, &rd);
	fill_rd(tokens, &rd);
	for (int i = 0; i < 10; i++)
	{
		if (rd.input[i] != NULL)
			printf("input[%d]: %s\n", i, rd.input[i]);
		else
			break;
	}
	for (int i = 0; i < 10; i++)
	{
		if (rd.output[i] != NULL)
			printf("output[%d]: %s\n", i, rd.output[i]);
		else
			break;
	}
	for (int i = 0; i < 10; i++)
	{
		if (rd.append[i] != NULL)
			printf("append[%d]: %s\n", i, rd.append[i]);
		else
			break;
	}
	printf("%d\n", is_path_viable(rd.input[0]));
	int fd = open(rd.input[0], O_RDONLY);
	printf("%d\n", fd);
	free_rd(&rd);
	return (status);
}

char *get_directory(const char *path) 
{
    char *last_slash = ft_strrchr(path, '/');
    if (last_slash == NULL) {
        // No slashes in the path, so it's a relative path in the current directory
        return strdup(".");
    }

    // Calculate the length of the directory part of the path
    size_t dir_len = last_slash - path;

    // Allocate memory for the directory string
    char *dir = malloc(dir_len + 1);
    if (dir == NULL) {
        return NULL;  // Failed to allocate memory
    }

    // Copy the directory part of the path into the new string
    strncpy(dir, path, dir_len);
    dir[dir_len] = '\0';  // Null-terminate the string

    return dir;
}

int is_path_viable(const char *path)
{
    // Duplicate the path because dirname can modify its argument
    char *path_copy = ft_strdup(path);
    if (path_copy == NULL) {
        return 0;  // Failed to allocate memory
    }

    char *dir = get_directory(path_copy);

    // Check if the directory exists
    struct stat statbuf;
    if (stat(dir, &statbuf) != 0) {
        free(path_copy);
        return 0;  // Directory does not exist
    }

    // Check if the directory is actually a directory
    if (!S_ISDIR(statbuf.st_mode)) {
        free(path_copy);
        return 0;  // Not a directory
    }

    // Check if we have write access to the directory
    int result = access(dir, W_OK);

    free(path_copy);

    return result == 0;
}