/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 08:55:26 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/15 14:07:06 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define LS_RECUR 0b000001
# define LS_ALL 0b000010
# define LS_LONG 0b000100
# define LS_REV 0b001000
# define LS_TIME 0b010000
# define LS_NOPOINT 0b100000

#include <libft.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

typedef struct	s_len
{
	size_t		max_nblink;
	size_t		max_user;
	size_t		max_gr;
	size_t		max_size;
	size_t		max_major;
	size_t		max_minor;
}				t_len;

typedef struct	s_node
{
	struct dirent	*content;
	struct stat		st;
	struct passwd	*pass;
	struct group	*gr;
	struct s_node	*next_dir;
	struct s_node	*in_dir;
}				t_node;

extern int		g_optls;
extern int		g_multifile;
extern t_len	g_size;

void	add_node(t_node **tree, struct dirent *content,
		int (*f)(void *s1, void *s2, const char *path), const char *path);
char	attr_acl(const char *path, char *name);
t_node	*before_read(t_node *tree, const char *dir_path);
void	btree_long(struct dirent *content, const char *path, t_node **tree);
void	clean_tree(t_node *tree);
void	clean_lst(t_list *lst);
int		cmp(void *s1, void *s2, const char *path);
int		cmp_arg(void *s1, void *s2);
int		cmp_arg_time(void *s1, void *s2);
int		cmp_time(void *s1, void *s2, const char *path);
t_node	*create_btree(struct dirent *content, t_node *next_dir, t_node *in_dir, const char *path);
t_list	*create_lst(const char *content, t_list *next);
void	create_recur_tree(t_node *tree, const char *dir_path);
void	error_lstat(char *name);
t_node	*ft_ls(const char *dir_path);
void	init_size(void);
void	long_format(t_node *tree, const char *dir_path);
void	new_list(t_list **lst, const char *content,
		int (*f)(void *s1, void *s2));
void	opt_to_bits(int opt);
void	print_date(t_node *tree);
void	print_gr_id(t_node *tree);
void	print_nb_link(t_node *tree);
void	print_multi(t_list *lst_arg);
void	print_perm(t_node *tree, const char *dir_path);
void	print_size(t_node *tree);
void	print_space(int	nb_space, int len);
void	print_tree(t_node *tree, const char *dir_path, int *i);
void	print_total(t_node *tree);
void	print_uid(t_node *tree);
void	readding_dir(t_node **tree, struct dirent *lecture, const char *path);
int		revcmp(void *s1, void *s2);
void	sort_arg(int ac, const char *av[]);
char	sticky_bits(struct stat st, int mode);

#endif
