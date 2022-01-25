#ifndef CENV_H
# define CENV_H

typedef struct s_cenv
{
	char	*key;
	char	*value;
}	t_cenv;

t_cenv	*cenv_create(const char *str);
void	cenv_delete(t_cenv *cenv);
void	cenv_print(t_cenv *cenv);
void	cenv_print_export(t_cenv *cenv);
int		cenv_compare(const t_cenv *c1, const t_cenv *c2);

#endif
