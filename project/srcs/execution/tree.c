/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ego <ego@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:13:57 by ego               #+#    #+#             */
/*   Updated: 2025/05/25 16:07:18 by ego              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints the command tokens in a formatted, shell-like style.
 *
 * Used internally to visualize a command node within the AST.
 *
 * @param t Pointer to the token list of a command.
 */
static void	print_cmd(t_token *cmd)
{
	while (cmd)
	{
		if (cmd->type == PIPE)
			printf("| ");
		else if (cmd->type == REDIRIN)
			printf("< ");
		else if (cmd->type == REDIROUT)
			printf("> ");
		else if (cmd->type == OUTAPPEND)
			printf(">> ");
		else if (cmd->type == INDELI)
			printf("<< ");
		else if (cmd->type == TEXT)
			printf("[%s] ", cmd->str);
		cmd = cmd->nxt;
	}
	printf("\n");
}

/**
 * @brief Recursively executes the syntax tree based on logical operations.
 * 
 * @brief - If the current node is a CMD, the command is expanded and executed
 * using `execute_pipeline`.
 * @brief - If the current node is AND or OR, executes left and conditionally
 * right.
 * 
 * @param d Pointer to the main shell data structure.
 * @param node Pointer to the root of the AST (or current subtree).
 * 
 * @return Exit code of the executed command(s), M_ERR if memory allocation
 * fails.
 */
int	execute_ast(t_data *d, t_ast *node)
{
	if (!node)
		return (0);
	if (node->type == CMD)
	{
		if (!substitute_list(&node->cmd, d))
			return (M_ERR);
		if (!node->cmd)
			return (g_last_exit_code);
		return (execute_pipeline(d, node->cmd));
	}
	g_last_exit_code = execute_ast(d, node->left);
	if (g_last_exit_code == M_ERR)
		clean_exit(d, errmsg(M_ERR_MSG, 0, 0, 1));
	d->pipe = free_pipeline(d->pipe);
	if ((node->type == AND && g_last_exit_code == 0)
		|| (node->type == OR && g_last_exit_code != 0))
		return (execute_ast(d, node->right));
	return (g_last_exit_code);
}

/**
 * @brief Pretty-prints the AST with indentation to visualize its structure.
 * 
 * - CMD nodes are shown with their tokens.
 * - AND/OR nodes are shown with branching.
 * - Optional header displays borders around the output.
 * 
 * @param node Pointer to the root of the AST (can be NULL).
 * @param level Current depth in the tree (should be 0 for root).
 * @param header Whether to print AST title borders (1 = yes, 0 = no).
 */
void	print_ast(t_ast *node, int level, int header)
{
	int	i;

	if (level == 0 && header)
		printf("=========== AST ===========\n");
	if (!node)
		return ;
	i = -1;
	while (++i < level - 1)
		printf("│   ");
	if (level > 0)
		printf("├── ");
	if (node->type == AND)
		printf("AND\n");
	else if (node->type == OR)
		printf("OR\n");
	else
	{
		printf("CMD: ");
		print_cmd(node->cmd);
	}
	print_ast(node->left, level + 1, 1);
	print_ast(node->right, level + 1, 1);
	if (level == 0 && header)
		printf("===========================\n");
}
