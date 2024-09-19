#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"

		//DATA_STRUCTURE
typedef struct s_node {
	int				val;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct s_stk {
	int		len;
	t_node	*head;
}			t_stk;

t_node	*node_create(int val);
void	stk_push_node(t_stk *stk, t_node *node);
t_node	*stk_pop_node(t_stk *stk);
void	stk_free_nodes(t_stk *stk);

typedef enum e_op {
	OP_SA,
	OP_RA,
	OP_RRA,
	OP_PB,
	OP_PA,
	OP_SS,
	OP_RRR,
	OP_RR,
	OP_SB,
	OP_RB,
	OP_RRB,
	NB_OP
}	t_op;

typedef struct	s_sol {
	t_op		*val;
	int			len;
	int			size;
}				t_sol;

typedef void	(*t_ps_op_handler)(t_stk *stk_a, t_stk *stk_b);
t_ps_op_handler	ps_op_to_func(t_op move);
//void	(*ps_op_to_func(t_op move))(t_stk *stk_a, t_stk *stk_b);
char	*ps_op_to_str(t_op move);
t_op	ps_str_to_op(char *move);

bool	ps_parse(int *res, char **nums, int size);
bool	compress(int *res, int size);
int		*parse_and_compress(char **nums, int size);

void	stks_init(t_node *input, int input_len, t_stk *stk_a, t_stk *stk_b);
void	stks_execute(t_op *moves, int moves_len, t_stk *stk_a, t_stk *stk_b);
bool	stks_is_solved(t_stk *stk_a, t_stk *stk_b);
void	stks_destroy(t_stk *stk_a, t_stk *stk_b);
void	stks_print(t_stk *a, t_stk *b);


void	ps_op_pa(t_stk *a, t_stk *b);
void	ps_op_pb(t_stk *a, t_stk *b);
void	ps_op_sa(t_stk *a, t_stk *b);
void	ps_op_sb(t_stk *a, t_stk *b);
void	ps_op_ss(t_stk *a, t_stk *b);
void	ps_op_ra(t_stk *a, t_stk *b);
void	ps_op_rb(t_stk *a, t_stk *b);
void	ps_op_rr(t_stk *a, t_stk *b);
void	ps_op_rra(t_stk *a, t_stk *b);
void	ps_op_rrb(t_stk *a, t_stk *b);
void	ps_op_rrr(t_stk *a, t_stk *b);
bool	is_solution(t_node *nodes, int input_len, t_op *moves, int moves_len);
void    solve_brute_force(t_node *nodes, int size); 
void	solve_backtrack(t_node *nodes, int size);
#endif
t_node	*parsed_to_nodes(int *parsed, int size);
void	nodes_reset(t_node *nodes, int size);
bool	is_sorted(t_node *nodes, int size);
void	sol_init(t_sol *sol);
void	sol_realloc(t_sol *sol);
void	sol_append_one(t_sol *sol, t_op op);
void	sol_print(t_sol	sol);
void	sol_destroy(t_sol sol);
t_sol	solve_big(t_node *parsed, int size);
