/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aayasrah <aayasrah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:06:35 by aayasrah          #+#    #+#             */
/*   Updated: 2026/04/19 14:06:36 by aayasrah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** heredoc.c
**
** This file handles heredocs specifically - the << redirection.
** Heredoc is complex enough to deserve its own file.
**
** What is a heredoc?
**   Heredoc (here document) lets you type multiple lines of input
**   directly in the terminal, which then get fed as stdin to a command.
**   You start it with << DELIMITER and type your input line by line.
**   When you type a line that contains ONLY the delimiter, it stops.
**
**   Example:
**     cat << EOF
**     hello
**     world
**     EOF
**   This feeds "hello\nworld\n" as stdin to cat.
**
** How we implement it:
**   When the parser sees <<, we dont execute it immediately.
**   Before any execution happens, we go through ALL heredocs in
**   the command list and collect their input first.
**   We read line by line using readline() until we see the delimiter.
**   We store all the collected input, then during execution we
**   feed it to the command as its stdin.
**
** Special behaviors to handle:
**   - ctrl-C during heredoc input should cancel it (exit status 130)
**   - ctrl-D during heredoc shows a warning like bash does
**   - Variables should expand inside heredoc UNLESS the delimiter
**     was quoted (e.g. << 'EOF' means no expansion)
**
** Think of heredoc like a temporary document you create on the spot
** and immediately hand to a command to read from.
*/