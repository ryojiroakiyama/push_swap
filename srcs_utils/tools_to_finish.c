# include "../header.h"

void	put_cl(t_circl *nil[], char *comment)
{
	int	i;
	t_circl	*tmp;

	ft_printf("----------%s----------\n", comment);
	i = 0;
	while (i < STACK_NUM)
	{
		if (i == A)
			ft_printf("==>a_stack<==\n");
		if (i == B)
			ft_printf("==>b_stack<==\n");
//		ft_printf("clsize:%d\n", nil[i]->size);
		tmp = nil[i]->next;
		while (tmp != nil[i])
		{
			ft_printf("value:%d\n", tmp->value);
//			ft_printf("num:%d\n", tmp->num);
//			ft_printf("class:%d\n", tmp->class);
			tmp = tmp->next;
		}
/*		tmp = nil[i]->prev;
		ft_printf("------reverse\n");
		while (tmp != nil[i])
		{
			ft_printf("value:%d\n", tmp->value);
			ft_printf("num:%d\n", tmp->num);
			ft_printf("class:%d\n", tmp->class);
			tmp = tmp->prev;
		}
*/		i++;
	}
}

void	put_op(t_oplist *nop)
{
	void		*op_str[OP_NUM];
	t_oplist	*move;

	op_str[SA] = "sa\n";
	op_str[SB] = "sb\n";
	op_str[SS] = "ss\n";
	op_str[PA] = "pa\n";
	op_str[PB] = "pb\n";
	op_str[RA] = "ra\n";
	op_str[RB] = "rb\n";
	op_str[RR] = "rr\n";
	op_str[RRA] = "rra\n";
	op_str[RRB] = "rrb\n";
	op_str[RRR] = "rrr\n";
	move = nop->next;
	while (move != nop)
	{
		if (SA <= move->op && move->op <= RR)
			write(1, op_str[move->op], 3);
		if (RR < move->op)
			write(1, op_str[move->op], 4);
		move = move->next;
	}
}

int	is_sorted(t_circl *nil[], int i)
{
	t_circl	*tmp;
	int		prevalue;

	tmp = nil[i]->next;
	prevalue = tmp->value;
	while (tmp != nil[i])
	{
		if (prevalue > tmp->value)
			break ;
		prevalue = tmp->value;
		tmp = tmp->next;
	}
	if (tmp == nil[i])
		return (1);
	return (0);
}

void	ft_clclear(t_circl *nil[])
{
	t_circl	*move;
	t_circl	*tmp;
	int		i;

	if (!nil)
		return ;
	i = 0;
	while (i < STACK_NUM)
	{
		move = nil[i]->next;
		while (move != nil[i])
		{
			tmp = move->next;
			free(move);
			move = tmp;
		}
		free(move);
		nil[i] = NULL;
		i++;
	}
}

void	ft_opclear(t_oplist *nop)
{
	t_oplist	*move;
	t_oplist	*tmp;

	if (!nop)
		return ;
	move = nop->next;
	while (move != nop)
	{
		tmp = move->next;
		free(move);
		move = tmp;
	}
	free(move);
}

void	ft_exit(t_circl *nil[], t_oplist *nop, int result)
{
//	put_cl(nil, "last");//
	if (result == 1)
		write(2, "Error\n", 6);
	else
	{
		if (nil[A]->class != -1)
			put_op(nop);
		else
			write(1, "OK\n", 3);
	}
//	if (is_sorted(nil, A))//
//		ft_printf("----------------------ok!\n");//
	ft_clclear(nil);
	ft_opclear(nop);
//	system("leaks a.out");//
	exit(result);
}
