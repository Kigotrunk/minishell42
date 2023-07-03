/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:58:04 by kortolan          #+#    #+#             */
/*   Updated: 2023/07/03 11:51:26 by kallegre         ###   ########.fr       */
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
	char	**argv;
	char	**io_lst;
}		t_vars;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}		t_env;
 
void    free_tab(char **tab);
int     tab_size(char **tab);
int     quote_check(char *str);
int     is_ope(char *str);
char    *end_ope(char *str);
int	    arg_c(char *str);
char	*eoa_quote(char *str, char c);
char    *eoa_str(char *str);
int     arg_len(char *str);
char	*get_arg(char *str);
char	**split_args(char *str);
char    **get_cmd_tab(char **argv);
int     pipe_count(char **argv);
char    **cmd_tab_init(int n);
char    *ft_stradd(char *s1, char *s2);
int     syntax_error(char **argv);
int    minishell(char **argv, t_env **envp);

t_env	*lstnew(char *content, t_env *next);
t_env	*ft_lstlast1(t_env *lst);
int	ft_lst_size(t_env *lst);
int	    pipex(char **argv, t_env **env);
char	*pathfinder(char *str, char **envp);
char	*ft_strjoin2(char const *s1, char const *s2);
void	cmd(char **argv, char **envp, t_vars va, int k);
void	close_all(int n, int **fd);
int		check_errors(int *pid, int n);
char    **get_tab_env(t_env *lst);
int		exec_cmd(char *argv[], t_env *env, t_vars va);
void	get_doc(char *argv[], t_vars va);
int		here_doc(int argc, char *argv[], char *envp[]);
int		exec_cmd_b(char *argv[], char *envp[], t_vars va);
void	free_fd(int **fd, int n);

void    leak_test(t_env *lst);

//lst
int     ft_lstsize(t_env *lst);
t_env  *ft_lstlast(t_env *lst);
void    ft_lstdelone(t_env *lst, void (*del)(void*));
void    ft_lstclear(t_env **lst, void (*del)(void*));
void    ft_lstadd_back(t_env **lst, t_env *new);
t_env  *ft_lstnew(void *str);

//is_builtin && called ft_builtins
int     is_builtin(char *cmd);
void    do_builtin(char **cmd, t_env **env);

//ft_builtin
void    builtin_cd(const char *path);
void    builtin_pwd(char **cmd);
void    builtin_env(t_env **envp);
t_env	*builtin_unset(t_env **env, char **argv);
char    *ft_str_lower(char *cmd);


//ft_builtin_echo
void	builtin_echo(char **argv);
int		parsing_echo(char **argv, int index);
void	echo_d_quote(int *in);
void	echo_s_quote(int *in);
void 	number_quote (char **argv, int index, int *count_s_quote, int *count_d_quote);


//ft_utils
t_env   *cpy_env(char **envp);
void	ft_unset_utils(t_env **env, char *var, int index);
int		ft_strlen_env(char *env);
void    ft_print_echo(char **argv, int index);
void	ft_putstr_echo(char *str, int i); 

//parsing without quote and $
char	**ft_fix_args(char **args, t_env **env);
char	*ft_str_replace(char *arg, int *in_quote, t_env **env);
char	*ft_size(char *arg, int	*in_quote, t_env **env);
char	*ft_is_dollars(char *arg, int in_quote, int i, t_env **env);
char	*ft_dollars(int *n, char *arg, int i, t_env **env);
int		ft_is_space(char c);
char	*ft_str_add(char *str, char c);
int 	ft_is_quote(char c);
void    print_tab(char **argv);
char	*ft_size_var(int *n, t_env *env);

#endif
