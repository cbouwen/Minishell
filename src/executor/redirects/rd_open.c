/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rd_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlegendr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:55:01 by mlegendr          #+#    #+#             */
/*   Updated: 2024/03/29 20:05:35 by mlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

extern t_signal	g_signal;

int	open_output(t_rd_col *rd)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (i < rd->output_size)
	{
		if (rd->output[i][0] == '#')
		{
			temp = ft_strdup(rd->output[i] + 1);
			if (!temp)
				return (rd_error_handler(12, NULL, rd));
			free(rd->output[i]);
			rd->output[i] = temp;
			rd->o_fd = open(rd->output[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		}
		else
			rd->o_fd = open(rd->output[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (rd->o_fd < 0)
			return (rd_error_handler(2, rd->output[i], rd));
		if (i < rd->output_size - 1)
			close(rd->o_fd);
		i++;
	}
	return (rd_error_handler(0, NULL, rd));
}

int	open_input(t_rd_col *rd)
{
	int		i;

	i = 0;
	while (i < rd->input_size)
	{
		if (rd->input[i][0] == '#')
			rd->i_fd = open_heredoc(rd->input[i] + 1, rd);
		else
			rd->i_fd = open(rd->input[i], O_RDONLY);
		if (rd->i_fd < 0)
			return (rd_error_handler(2, rd->input[i], rd));
		if (i < rd->input_size - 1)
			close(rd->i_fd);

		i++;
	}
	return (rd_error_handler(0, NULL, rd));
}

static void	the_real_readline(int hd_fd, char *input)
{
	char	*line;

	g_signal.in_heredoc = true;
	line = NULL;
	line = readline("heredoc> ");
	while (line != NULL && ft_strcmp(line, input) != 0)
	{
		write(hd_fd, line, ft_strlen(line));
		write(hd_fd, "\n", 1);
		free(line);
		line = NULL;
		line = readline("heredoc> ");
	}
	g_signal.in_heredoc = false;
	if (line)
		free(line);
}

static int	dupe_readline(int hd_fd, char *input)
{
    int		tty_fd;
    int		stdout_fd;

    tty_fd = open("/dev/tty", O_RDWR);
    if (tty_fd == -1)
        return (rd_error_handler(3, NULL, NULL));
    stdout_fd = dup(STDOUT_FILENO);
    if (stdout_fd == -1)
    {
        close(tty_fd);
        return (rd_error_handler(3, NULL, NULL));
    }
    if (dup2(tty_fd, STDOUT_FILENO) == -1)
    {
        close(tty_fd);
        close(stdout_fd);
        return (rd_error_handler(3, NULL, NULL));
    }
	the_real_readline(hd_fd, input);
    if (dup2(stdout_fd, STDOUT_FILENO) == -1)
		return (rd_error_handler(3, NULL, NULL));
    close(stdout_fd);
    close(tty_fd);
	return (rd_error_handler(0, NULL, NULL));
}

int	open_heredoc(char *input, t_rd_col *rd)
{
	/*int		heredoc_fd;
	pid_t	pid;
	int		status;

	status = 0;
	heredoc_fd = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		heredoc_fd = open("/tmp/heredoc_dump", WR_C_A, 0644);
		if (heredoc_fd == -1)
			return (rd_error_handler(2, "/tmp/heredoc_dump", NULL));
		status = dupe_readline(heredoc_fd, input);
		close(heredoc_fd);
		free_rd_full(rd);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status != 0)
			g_signal.in_heredoc = true;
	}
	signal(SIGINT, sig_handler);
	return (heredoc_fd);*/
	int		heredoc_fd;
	int		status;

	status = 0;
	heredoc_fd = 0;
	signal(SIGINT, SIG_DFL);
	heredoc_fd = open("/tmp/heredoc_dump", WR_C_A, 0644);
	if (heredoc_fd == -1)
		return (rd_error_handler(2, "/tmp/heredoc_dump", NULL));
	status = dupe_readline(heredoc_fd, input);
	close(heredoc_fd);
	free_rd_full(rd);
	(void)status;
	signal(SIGINT, sig_handler);
	return (heredoc_fd);
}

//rd->i_fd = open(rd->input[i], O_RDWR | O_CREAT | O_APPEND, 0644);
