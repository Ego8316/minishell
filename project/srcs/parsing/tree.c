/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:44:32 by ego               #+#    #+#             */
/*   Updated: 2025/05/19 18:26:07 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Recursively frees the syntax tree.
 * 
 * @param root Pointer to the tree's root.
 * 
 * @warning Should be called with the tree's root.
 * 
 * @return NULL for convenience.
 */
t_ast	*free_ast(t_ast *root)
{
	if (!root)
		return (NULL);
	free_ast(root->left);
	free_ast(root->right);
	token_free_list(&root->cmd);
	free(root);
	return (NULL);
}

t_ast	*create_leaf(t_token *t)
{
	t_ast	*leaf;

	leaf = (t_ast *)malloc(sizeof(t_ast));
	if (!leaf)
		return (NULL);
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->type = CMD;
	leaf->cmd = t;
	return (leaf);
}

t_ast	*create_branch(t_token *t)
{
	t_ast	*branch;

	branch = (t_ast *)malloc(sizeof(t_ast));
	if (!branch)
		return (NULL);
	branch->left = NULL;
	branch->right = NULL;
	if (t->type == ANDOPER)
		branch->type = AND;
	else
		branch->type = OR;
	branch->cmd = t;
	return (branch);
}

/**
 * @brief Finds the logical operator (&& or ||) with the lowest precedence at
 * the shallowest depth in the token list.
 * 
 * First computes the lowest depth and then gets the right-most operator token
 * with that depth.
 * 
 * @param t Pointer to the head of the token list.
 * 
 * @param Pointer to the token with the lowest precedence at the lowest depth,
 * NULL if no logical operator is found.
 */
t_token	*get_lowest_precedence(t_token *t)
{
	int		min_depth;
	t_token	*min_op;
	t_token	*l;
	
	l = t;
	min_depth = l->depth;
	while (l)
	{
		if (l->depth < min_depth)
			min_depth = l->depth;
		l = l->nxt;
	}
	min_op = NULL;
	while (t)
	{
		if ((t->type == ANDOPER || t->type == OROPER) && t->depth == min_depth)
			min_op = t;
		t = t->nxt;
	}
	return (min_op);
}

/**
 * @brief Builds the syntax tree from the token list.
 * 
 * @param t Token list.
 * 
 * @return The tree's root, NULL if memory allocation fails.
 */
t_ast	*build_ast(t_token *t)
{
	t_ast	*node;
	t_token	*sep;
	t_token	*left;
	t_token	*right;

	sep = get_lowest_precedence(t);
	if (!sep)
		return (create_leaf(t));
	left = t;
	right = sep->nxt;
	sep->prv->nxt = NULL;
	sep->nxt->prv = NULL;
	sep->prv = NULL;
	sep->nxt = NULL;
	node = create_branch(sep);
	node->left = build_ast(left);
	node->right = build_ast(right);
	if (!node->left || !node->right)
		return (NULL);
	return (node);
}

static void print_token_op(t_token_type type)
{
	if (type == PIPE)
		printf("| ");
	else if (type == REDIRIN)
		printf("< ");
	else if (type == REDIROUT)
		printf("> ");
	else if (type == OUTAPPEND)
		printf(">> ");
	else if (type == INDELI)
		printf("<< ");
}

void print_ast(t_ast *node, int level)
{
	if (level == 0)
		printf("=========== AST ===========\n");
	if (!node)
		return;
	for (int i = 0; i < level; ++i)
		printf("  ");
	if (node->type == AND)
		printf("AND\n");
	else if (node->type == OR)
		printf("OR\n");
	else
	{
		printf("CMD: ");
		t_token *cmd = node->cmd;
		while (cmd)
		{
			if (cmd->type == TEXT)
				printf("%s ", cmd->str);
			else
				print_token_op(cmd->type);
			cmd = cmd->nxt;
		}
		printf("\n");
	}
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
	if (level == 0)
		printf("===========================\n");
}