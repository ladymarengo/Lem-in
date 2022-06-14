void	del_stack(t_stack *stack)
{
	t_stack	*next;

	while (stack != NULL)
	{
		next = stack->next;
		stack->value = 0;
		free(stack);
		stack = next;
	}
}

t_stack	*new_node(int value)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->value = value;
	return (new);
}

void	add_to_start(t_stack **a, int value)
{
	t_stack	*tmp;

	if (!a || !*a)
		(*a) = new_node(value);
	else
	{
		tmp = new_node(value);
		tmp->next = *a;
		*a = tmp;
	}
}
