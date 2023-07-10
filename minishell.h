/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:58:04 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/10 11:35:30 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line_bonus.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_vars
{
	int		n;
	int		**fd;
	int		*pid;
	char	**envp;
	char	***argv;
	char	**io_lst;
}		t_vars;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				print;
	struct s_env	*next;
}		t_env;

typedef struct s_global
{
	t_env	*env;
	int		fork;
}		t_global;
 
t_env   *env;
 
void    free_tab(char **tab);
void	free_tab_tab(char ***tab);
int     tab_size(char ***tab);
int     quote_check(char *str);
int     is_ope(char *str);
char    *end_ope(char *str);
int	    arg_c(char *str);
char	*eoa_quote(char *str, char c);
char    *eoa_str(char *str);
int     arg_len(char *str);
char	*get_arg(char *str);
char	**split_args(char *str);
char    ***get_cmd_tab(char **tab);
char    **get_io(char **argv);
int     pipe_count(char **argv);
int     redir_count(char **argv);
char    ***cmd_tab_init(int n);
char    **io_init();
char    *ft_stradd(char *s1, char *s2);
int     syntax_error(char **argv);
int		minishell(t_env **env, char **argv);
void	rl_replace_line(const char *text, int clear_undo);
void    ft_sig(int code);

//pipex
int	    pipex(t_env **env, char ***argv, char **io_list);
char	*pathfinder(char *str, char **envp);
void	path_error(char *str);
char	*ft_strjoin2(char const *s1, char const *s2);
void	cmd(t_env **env, t_vars va, int k);
void	close_all(int n, int **fd);
int		check_errors(int *pid, int n);
char    **get_tab_env(t_env *lst);
int		exec_cmd(t_env **env, t_vars va);
void	get_doc(char *argv[], t_vars va);
int		here_doc(int argc, char *argv[], char *envp[]);
int		exec_cmd_b(char *argv[], char *envp[], t_vars va);
void	free_fd(int **fd, int n);
void    redir_err(t_vars va);
void    redir_input(t_vars va, int k);
void    redir_output(t_vars va, int k);

//new_var
char    **get_new_var(char **argv, t_env *env);
char     *get_value(char *str);
char    *get_name(char *str);
int 	is_new_var(char *arg);

//lst
int     ft_lstsize(t_env *lst);
t_env  *ft_lstlast(t_env *lst);
void    ft_lstdelone(t_env *lst, void (*del)(void*));
void    ft_lstclear(t_env **lst, void (*del)(void*));
void    ft_lstadd_back(t_env **lst, t_env *new);
t_env  *ft_lstnew(char *name, char *value, int print);

//is_builtin && called ft_builtins
int     is_builtin(char *cmd);
void    do_builtin(char **cmd, t_env **env, char **envp);

//ft_builtin
void    builtin_cd(char	**cmd);
void    builtin_pwd(char **cmd);
void    builtin_env(t_env *env);
char    *ft_str_lower(char *cmd);


//ft_builtin_unset
void	builtin_unset(char **argv, t_env **env);
void	remove_env_var(t_env **env, char *var);

//ft_builtin_echo
void	builtin_echo(char **argv);
int		parsing_echo(char **argv, int index);
void	echo_d_quote(int *in);
void	echo_s_quote(int *in);
void 	number_quote (char **argv, int index, int *count_s_quote, int *count_d_quote);

int	var_with_value(char *str);

//ft_utils
t_env   *cpy_env(char **envp);
void	ft_unset_utils(t_env **env, char *var, int index);
int		ft_strlen_env(char *env);
void    ft_print_echo(char **argv, int index);
void	ft_putstr_echo(char *str, int i);

//builtin_export
void	ft_builtin_export(char **argv, t_env **env);
void    ft_change_var(t_env **env, char *name, char *value);
void    print_export(t_env *env);
int 	is_var(t_env *env, char *str);



//parsing without quote and $
char	***ft_fix_args(char ***args);
char	*ft_str_replace(char *arg, int *in_quote);
char	*ft_size(char *arg, int	*in_quote);
char	*ft_is_dollars(char *arg, int in_quote, int i);
char	*ft_dollars(int *n, char *arg, int i);
int		ft_is_space(char c);
char	*ft_str_add(char *str, char c);
int 	ft_is_quote(char c);
void    print_tab(char **argv);
char	*ft_size_var(int *n);
int		var_with_value(char *str);


#endif