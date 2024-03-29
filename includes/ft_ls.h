/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 08:55:26 by lbopp             #+#    #+#             */
/*   Updated: 2017/01/18 14:29:45 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define LS_RECUR	0b000000001
# define LS_ALL 	0b000000010
# define LS_LONG	0b000000100
# define LS_REV		0b000001000
# define LS_TIME	0b000010000
# define LS_NOPOINT	0b000100000
# define LS_COL		0b001000000
# define LS_NOGRID	0b010000000
# define LS_SIZE	0b100000000

# include <libft.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include <sys/ioctl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct		s_len
{
	int				total;
	size_t			max_name;
	size_t			max_nblink;
	size_t			max_user;
	size_t			max_gr;
	size_t			max_size;
	size_t			max_major;
	size_t			max_minor;
}					t_len;

typedef struct		s_node
{
	int				bug;
	struct dirent	*content;
	struct stat		st;
	struct passwd	*pass;
	struct group	*gr;
	struct s_node	*next_dir;
	struct s_node	*in_dir;
}					t_node;

extern int			g_optls;
extern int			g_multifile;
extern t_len		g_size;

void				add_node(t_node **tree, struct dirent *content,
					int (*f)(struct dirent *content, struct dirent *tcontent
					, const char *path), const char *path);
char				attr_acl(const char *path, char *name);
t_node				*before_read(t_node *tree, const char *dir_path);
void				btree_long(t_node **tree);
void				clean_tree(t_node *tree);
void				clean_lst(t_list *lst);
int					cmp(struct dirent *content,
					struct dirent *tcontent, const char *path);
int					cmp_arg(void *s1, void *s2);
int					cmp_arg_time(void *s1, void *s2);
int					cmp_size(struct dirent *content,
					struct dirent *tcontent, const char *path);
int					cmp_time(struct dirent *content,
					struct dirent *tcontent, const char *path);
t_node				*create_btree(struct dirent *content, t_node *next_dir,
					t_node *in_dir, const char *path);
t_list				*create_lst(const char *content, t_list *next);
void				create_recur_tree(t_node *tree, const char *dir_path);
void				error_open(const char *dir_path);
void				error_lstat(const char *name);
t_node				*ft_ls(const char *dir_path);
char				*get_time(t_node *tree);
void				init_size(void);
void				long_format(t_node *tree, const char *dir_path);
int					nb_col(void);
void				new_list(t_list **lst, const char *content,
					int (*f)(void *s1, void *s2));
void				normal_treat(t_node **tree,
					struct dirent *lecture, const char *path);
void				opt_to_bits(int opt);
void				print_date(t_node *tree);
void				print_gr_id(t_node *tree);
void				print_in_col(t_node *tree, int *nb_file);
void				print_long(int *i, t_node *tree, const char *dir_path);
void				print_nb_link(t_node *tree);
void				print_multi(t_list *lst_arg);
void				print_perm(t_node *tree, const char *dir_path);
void				print_size(t_node *tree);
void				print_space(int	nb_space, int len);
void				print_tree(t_node *tree, const char *dir_path, int *i,
					int *nb_file);
void				print_total(void);
void				print_uid(t_node *tree);
void				readding_dir(t_node **tree, struct dirent *lecture,
					const char *path);
int					revcmp(void *s1, void *s2);
void				sort_arg(int ac, const char *av[]);
char				sticky_bits(struct stat st, int mode);
void				to_recur(t_node *tree, const char *dir_path);

#endif
