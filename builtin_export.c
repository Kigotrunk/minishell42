#include "minishell.h"

void    ft_builtin_export(char **argv, t_env **env)
{
	int     i;
	char    **split;

	i = 1;
	if(!argv || argv == NULL)
		return ;
	if(!argv[1])
		print_export(*env);
	else
	{
		while (argv[i])
		{
			split = ft_split(argv[i], '=');
			if (split[0] == NULL)
				return ;
			if(!is_var(*env, split[0]))
			{
				if(split[1] && var_name(split[0]))
					ft_lstadd_back(env, ft_lstnew(split[0], split[1], 1));
				else if(var_name(split[0]))
					ft_lstadd_back(env, ft_lstnew(split[0], NULL, 1));
				else
				ft_printf("invalid var Name\n");
			}
			else
			{
				if(split[1] && var_name(split[0]))
					ft_change_var(env, split[0], split[1]);
				else if (var_name(split[0]))
					ft_change_var(env, split[0], NULL);
				else 
				ft_printf("invalid var Name\n");
			}
			i++;
			free_tab(split);
		}
	}
	return ;
}

void    ft_change_var(t_env **env, char *name, char *value)
{
	t_env   *ptr;

	ptr = *env;
	while((ptr))
	{
		if(ft_strncmp(ptr->name, name, ft_strlen(name) + 1) == 0)
		{
			if (ptr->print == 0)
				ptr->print = 1;
			if(value == NULL)
				return ;
			free(ptr->value);
			ptr->value = ft_strdup(value);
			return ;
		}
		ptr = ptr->next;
	}
}

void    print_export(t_env *env)
{
	//t_env   *ptr;

	if (!env)
		perror("env");
	//ptr = env;
	while (env)
	{
		if(env->print == 1)
		{
			ft_printf("declare -x ");
			ft_printf("%s", env->name);
			if (env->value != NULL)
				ft_printf("=\"%s\"\n", env->value);
			else
				ft_printf("\n");
		}
		env = env->next;
	}
}

int is_var(t_env *env, char *str)
{
	int i;
	char    *tmp;
	//t_env   *ptr;

	//ptr = env;
	if (str == NULL)
		return (0);
	i = 0;
	tmp = ft_strdup("");
	while(str[i] != '=' && str[i])
	{
		tmp = ft_str_add(tmp, str[i]);
		i++;
	}
	while(env)
	{
		if(!ft_strncmp(env->name, tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (1);
		}
		env = env->next;
	}
	free(tmp);
	return (0);
}

int var_name(char *str)
{
	int i;

	i = 0;
	if(!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if(!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}