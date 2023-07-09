#include "minishell.h"

void    ft_builtin_export(char **argv)
{
    int     i;
    char    **split;

    i = 1;
    if(!argv)
        return ;
    if(!argv[1])
        print_export();
    else
    {
        while (argv[i])
        {
            split = ft_split(argv[i], '=');
            if(!is_var(split[0]))
            {
                if(split[1])
                    ft_lstadd_back(&env, ft_lstnew(split[0], split[1], 1));
                else
                    ft_lstadd_back(&env, ft_lstnew(split[0], NULL, 1));
            }
            else
            {
                if(split[1])
                    ft_change_var(split[0], split[1]);
                else
                    ft_change_var(split[0], NULL);
            }
            i++;
            free_tab(split);
        }
    }
    return ;
}

void    ft_change_var(char *name, char *value)
{
    t_env   *first;

    first = env;
    while(first->name)
    {
        if(!ft_strncmp(first->name, name, ft_strlen(name) + 1))
        {
            free(first->value);
            first->name = ft_strdup(name);
            first->value = ft_strdup(value);
            break;
        }
        env = env->next;
    }
}

void    print_export()
{
    t_env   *first;

    if (!env)
	    perror("env");
    first = env;
	while (first)
	{
        if(first->print == 1)
        {
            ft_printf("declare -x ");
		    ft_printf("%s=", first->name);
            ft_printf("%s\n", first->value);
        }
		first = first->next;
	}
}

int is_var(char *str)
{
    int i;
    char    *tmp;
    t_env   *first;

    first = env;
    i = 0;
    tmp = ft_strdup("");
    while(str[i] != '=' && str[i])
    {
        tmp = ft_str_add(tmp, str[i]);
        i++;
    }
    while(first)
    {
        if(!ft_strncmp(first->name, tmp, ft_strlen(tmp)))
        {
            ft_printf("var_connu\n");
            free(tmp);
            return (1);
        }
        first = first->next;
    }
    free(tmp);
    return (0);
}