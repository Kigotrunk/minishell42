/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:58:04 by kortolan          #+#    #+#             */
/*   Updated: 2023/08/28 23:30:04 by kallegre         ###   ########.fr       */
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
	int		*heredoc;
	int		**fd;
	int		*pid;
	char	**envp;
	char	***argv;
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
	//t_env	*env;
	int		fork;
}		t_global;

char	**replace_quote_argv(char **argv, t_env env, int err_code);
char	*replace_quote(char *arg, t_env env, int err_code);
int 	var_size(char *str);
char	*get_var(char *str, t_env env, int err_code);
int		is_in_quote(char *str, int index);

void	print_err(char *name, char *str);
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
char    ***get_cmd_tab(char **tab, t_env env, int err_code);
char	**get_argv(char **tab, t_env env, int err_code);
int		get_io(char **argv, int **heredoc, t_env **env);
int		replace_io(char *ope, char *filename, int **heredoc);
int     pipe_count(char **argv);
int     redir_count(char **argv);
char    ***cmd_tab_init(int n);
char    **io_init();
char	*ft_strjoin_free1(char *s1, char *s2);
int     syntax_error(char **argv);
int		minishell(t_env **env, char **argv);
void	rl_replace_line(const char *text, int clear_undo);
void    ft_sig(int code);

//pipex
int		only_builtin(t_vars *va, t_env **env);
int	    pipex(t_env **env, char ***argv, int *heredoc);
char	*pathfinder(char *str, char **envp);
int		path_error(char *str);
char	*ft_strjoin2(char const *s1, char const *s2);
void	cmd(t_env **env, t_vars va, int k);
void	close_all(int n, int **fd);
int		check_errors(int *pid, int n);
char    **get_tab_env(t_env *lst);
int		exec_cmd(t_env **env, t_vars va);
void	get_doc(char *argv[], t_vars va);
int		get_heredoc(int *heredoc, char *delimiter);
int		exec_cmd_b(char *argv[], char *envp[], t_vars va);
void	free_fd(int **fd, int n);
int		redir_err(char* ope, char *filename);
int		redir_out(char* ope, char *filename);
int		redir_in(char* ope, char *filename, int **heredoc);
char	**remove_wrg_arg(char **argv);

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
int		do_builtin(char **cmd, t_env **env, char **envp);

//ft_builtin
void    builtin_cd(char	**cmd, t_env *env);
void	builtin_pwd(void);
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
int		option_n(char *argv);
int		ft_print_echo(char **argv, int index);

int	var_with_value(char *str);

//ft_utils
t_env   *cpy_env(char **envp);
void	ft_unset_utils(t_env **env, char *var, int index);
int		ft_strlen_env(char *env);
void	ft_putstr_echo(char *str, int i);
void	ft_change_pwd(t_env *env);

//builtin_export
void	ft_builtin_export(char **argv, t_env **env);
void    ft_change_var(t_env **env, char *name, char *value);
void    print_export(t_env *env);
int 	is_var(t_env *env, char *str);
int		var_name(char *str);

int builtin_exit(char **argv);
int is_number(char *arg);
int	check_longl(char *str);

//parsing without quote and $
char	**ft_fix_args(char **args, t_env **env);
char	*ft_str_replace(char *arg, t_env **env);
char	*ft_is_dollars(char *arg, int in_quote, int i, t_env **env);
char	*ft_dollars(int *n, char *arg, int i, t_env *env);
int		ft_is_space(char c);
char	*ft_str_add(char *str, char c);
int 	ft_is_quote(char c);
void    print_tab(char **argv);
char	*ft_size_var(int *n, t_env *env);
int		var_with_value(char *str);


#endif