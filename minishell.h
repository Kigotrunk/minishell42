/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:58:04 by kortolan          #+#    #+#             */
/*   Updated: 2023/09/07 11:42:54 by kallegre         ###   ########.fr       */
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
	int		err_code;
	int		fd_0;
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

//quote
char	*replace_quote(char *arg, t_env **env, int err_code);
int		var_size(char *str);
char	*get_var(char *str, t_env **env, int err_code);
int		is_in_quote(char *str, int index);

int		cmd_count(char ***tab);
int		quote_check(char *str);
int		is_ope(char *str);
char	*end_ope(char *str);
int		arg_c(char *str);
char	*eoa_quote(char *str, char c);
char	*eoa_str(char *str);
int		arg_len(char *str);
char	*cpy_arg(char *str);
char	*get_arg(char **ptr, char *str);
char	**split_args(char *str);

char	**get_argv(char **tab, t_env **env, int err_code);
int		pipe_count(char **argv);
char	***cmd_tab_init(int n);
int		pipe_len(char **tab);
char	**get_pipe(char **tab);
char	***get_pipe_tab(char **tab);

int		minishell(t_env **env, char *input, int err_code);
int		syntax_error(char **argv);
void	ft_sig(int code);

//pipex
int		only_builtin(t_vars va, t_env **env);
char	*find_cmd_name(char **argv);
int		pipex(t_env **env, char ***argv, int err_code);
char	*pathfinder(char *str, char **envp);
int		check_path(char *cmd, char **envp);
void	path_error(char *str);
char	*ft_strjoin_path(char const *s1, char const *s2);
void	cmd(t_env **env, t_vars va, int k);
void	close_all(int n, int **fd);
int		check_errors(int *pid, int n);
char	**get_tab_env(t_env *lst);
int		exec_cmd(t_env **env, t_vars va);
int		get_heredoc(int *heredoc, char *delimiter, int fd_0);
void	free_fd(t_vars va);
int		redir_err(char *ope, char *filename);
int		redir_out(char *ope, char *filename);
int		redir_in(char *ope, char *filename, int **heredoc, int fd_0);
char	**remove_wrg_arg(char **argv);
void	make_redir(t_env **env, t_vars va, int k);
int		get_io(char **argv, int **heredoc, t_env **env, t_vars va);
int		replace_io(char *ope, char *filename, int **heredoc, int fd_0);

//new var
int		is_new_var_cmd(char	**argv);
int		get_new_var(char **argv, t_env *env);
void	modif_var_value(t_env *env, char *arg);
int		is_new_var(char *arg);
char	*get_value(char *str);
char	*get_name(char *str);
int		tab_size(char **tab);

//lst
t_env	*cpy_env(char **envp);
int		ft_lstsize(t_env *lst);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstdelone(t_env *lst, void (*del)(void*));
int		ft_lstclear(t_env **lst, void (*del)(void*));
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(char *name, char *value, int print);

//builtin
int		is_builtin(char *cmd);
int		do_builtin(char **cmd, t_env **env);
int		builtin_cd(char	**cmd, t_env **env);
void	builtin_pwd(void);
void	ft_change_pwd(t_env **env);
char	*get_home_dir(t_env *env);
void	builtin_env(t_env *env);
void	builtin_unset(char **argv, t_env **env);
void	remove_env_var(t_env **env, char *var);
void	builtin_echo(char **argv);
int		is_n_option(char *arg);

//builtin_export
int		ft_builtin_export(char **argv, t_env **env);
int		ft_change_var(t_env **env, char *name, char *value);
int		print_export(t_env *env);
int		is_var(t_env *env, char *str);
int		var_name(char *str);
int		ft_builtin_export_1(char *name, char *value, t_env **env, int code);
int		print_export_error(int code, int id, char *value);
void	ft_builtin_export_2(char *name, char *value, t_env **env);

//builtin_exit
int		builtin_exit(char **argv);
int		is_number(char *arg);
int		check_longl(char *str);

char	*ft_str_add(char *str, char c);
char	*ft_strjoin_free1(char *s1, char *s2);
void	print_tab(char **argv);
void	fd_back(int fd[]);
void	fd_save(int fd[]);
void	print_err(char *str, char *var);
void	free_tab(char **tab);
void	free_tab_tab(char ***tab);

#endif