/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouwen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:41:07 by cbouwen           #+#    #+#             */
/*   Updated: 2024/02/13 17:27:15 by cbouwen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/Libft/libft.h"
# include "../lib/Printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_environment
{
	char					*name;
	char					*value;
	struct s_environment	*next;
}							t_environment;

/*typedef struct s_token
{
    char*       str;
	//to run a ft_strcmp for 'Echo' and of course just regular arguments
    int         prio;
    char*       type; //Like COMMAND, ARGUMENT, PIPE etc.
}							t_token;


typedef struct s_node 
{
    t_token     *token;
    int         redirects;
	//Think we have to declare this to properly handle this. Could be wrong
   
	//note: Redirect can change the priority of the files. cat < input.txt needs to start with reading the file before cat can be applied
   
	//Maybe we can apply the correct prio in the parser. How would the executor handle this information though?
    struct s_node      *next;
    struct s_node      *previous; //double linked necessary?
}							t_node;

typedef struct s_command_line
{
    t_node					*node;
    int     pipes; 
	//Declaring the amount of pipes gives us an idea how many command lines.
    int     command_lines;
	//Do we need a number for this so we can properly loop? Or loop until node->next = NULL?

}							t_command_line;


typedef struct s_command_line
{
    t_node      node*
    t_pipes     pipe*

};
*/

int							ft_error(char *str);
t_environment				*env_parser(char *envp[]);
void						free_env_node(t_environment *env);
void						free_env(t_environment *env);
t_environment				*get_env_node(t_environment *head, char *name);

#endif
