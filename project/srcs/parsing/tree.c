/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:44:32 by ego               #+#    #+#             */
/*   Updated: 2025/05/22 21:15:20 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Recursively frees all nodes of an abstract syntax tree (AST).
 *
 * Frees both subtrees and the associated command token list at each node.
 *
 * @param root Pointer to the root node of the tree.
 * 
 * @return Always returns NULL for convenience.
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

/**
 * @brief Creates a leaf node in the AST for a single command.
 *
 * Sets the node type to CMD and stores the command tokens.
 *
 * @param t Pointer to the list of tokens representing a command.
 * 
 * @return Pointer to the newly created leaf node, NULL if memory allocation
 * fails. Frees the token list and sets global error code in that case.
 */
t_ast	*create_leaf(t_token *t)
{
	t_ast	*leaf;

	leaf = (t_ast *)malloc(sizeof(t_ast));
	if (!leaf)
	{
		g_last_exit_code = M_ERR;
		token_free_list(&t);
		return (NULL);
	}
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->type = CMD;
	leaf->cmd = t;
	return (leaf);
}

/**
 * @brief Creates a branch node in the AST for a boolean operator (&& or ||).
 *
 * Sets the node type to AND or OR depending on the token type.
 *
 * @param t Pointer to the operator token (ANDOPER or OROPER).
 * @return Pointer to the newly created branch node, NULL if memory allocation
 * fails. Sets global error code if memory allocation fails.
 */
t_ast	*create_branch(t_token *t)
{
	t_ast	*branch;

	branch = (t_ast *)malloc(sizeof(t_ast));
	if (!branch)
	{
		g_last_exit_code = M_ERR;
		return (NULL);
	}
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
 * @brief Builds an abstract syntax tree (AST) from a token list.
 *
 * Recursively splits the token list on the lowest-precedence operator (&& or
 * ||), creating a binary tree where command nodes are leaves and operators
 * are branches.
 *
 * @param t Pointer to the head of the token list.
 * 
 * @return Pointer to the root of the AST, or NULL on memory allocation failure.
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
	node = create_branch(sep);
	if (!node)
	{
		token_free_list(&t);
		return (NULL);
	}
	sep->prv->nxt = NULL;
	sep->nxt->prv = NULL;
	sep->prv = NULL;
	sep->nxt = NULL;
	node->left = build_ast(left);
	node->right = build_ast(right);
	return (node);
}
