#include "minishell.h"

void    ft_builtin_export(char **argv, t_env **env)
{
    int     i;
    char    **split;

    i = 1;
    if(!argv)
        return ;
    if(!argv[1])
        print_export(*env);
    else
    {
        while (argv[i])
        {
            split = ft_split(argv[i], '=');
            ft_printf("%s\n", split[0]);
            if(!is_var(*env, split[0]))
            {
                if(split[1])
                    ft_lstadd_back(env, ft_lstnew(split[0], split[1], 1));
                else
                    ft_lstadd_back(env, ft_lstnew(split[0], NULL, 1));
                ft_printf("%s\n", "test");
            }
            else
            {
                if(split[1])
                    ft_change_var(env, split[0], split[1]);
                else
                    ft_change_var(env, split[0], NULL);
            }
            i++;
            free_tab(split);
        }
    }
    return ;
}

void    ft_change_var(t_env **env, char *name, char *value)
{
    //t_env   *ptr;

    //ptr = *env;
    while((*env))
    {
        if(ft_strncmp((*env)->name, name, ft_strlen(name) + 1) == 0)
        {
            if ((*env)->print == 0)
            {
                (*env)->print = 1;
                return ;
            }
            free((*env)->value);
            //first->name = ft_strdup(name);
            (*env)->value = ft_strdup(value);
            return ;
        }
        *env = (*env)->next;
    }
}

void    print_export(t_env *env)
{
    t_env   *ptr;

    if (!env)
	    perror("env");
    ptr = env;
	while (ptr)
	{
        if(ptr->print == 1)
        {
            ft_printf("declare -x ");
		    ft_printf("%s=", ptr->name);
            ft_printf("%s\n", ptr->value);
        }
		ptr = ptr->next;
	}
}

int is_var(t_env *env, char *str)
{
    int i;
    char    *tmp;
    //t_env   *ptr;

    //ptr = env;
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