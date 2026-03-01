/*
** quotes.c
**
** This file handles everything related to quotes in the shell input.
** Quotes are one of the trickiest parts of minishell because they
** change how the shell interprets everything inside them.
**
** The two types of quotes and what they do:
**
**   Single quotes '...'
**     Everything inside is completely literal. No expansion happens.
**     No special characters are interpreted. What you type is what you get.
**     Example: echo '$HOME' prints literally: $HOME
**     Example: echo 'hello   world' prints: hello   world (spaces preserved)
**
**   Double quotes "..."
**     Almost everything is literal, EXCEPT the dollar sign $.
**     Variable expansion still happens inside double quotes.
**     Example: echo "$HOME" prints: /home/student
**     Example: echo "hello   world" prints: hello   world (spaces preserved)
**
** What this file handles:
**   - Detecting whether we are inside single or double quotes
**   - Removing the quote characters themselves from the final result
**     (the quotes are instructions to the shell, not part of the output)
**   - Making sure expansion is skipped inside single quotes
**   - Making sure expansion still happens inside double quotes
**
** Think of quotes like a set of rules that say "treat everything
** inside me differently than you normally would."
*/