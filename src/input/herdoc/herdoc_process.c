/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:59:44 by dsagong           #+#    #+#             */
/*   Updated: 2026/03/03 16:30:02 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "list.h"
#include "libft.h"
#include "expand.h"
#include "global.h"
#include <readline/readline.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "herdoc.h"
#define DELIM_PRINT "minishell: warning: here-document \
delimited by end-of-file (wanted `%s')\n"

static char	*process_line(char *line, t_delim_info *delim_info, t_envp *envp)
{
	char	*expanded;

	if (delim_info->quoted_flag)
		expanded = ft_strdup(line);
	else
		expanded = expand_process(line, envp);
	free(line);
	return (expanded);
}

static void	heredoc_child(t_delim_info delim_info, int write_fd, t_envp *envp)
{
	char	*line;
	char	*expanded;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line && printf(DELIM_PRINT, delim_info.cooked_delim))
			break ;
		if (ft_strcmp(line, delim_info.cooked_delim) == 0)
		{
			free(line);
			break ;
		}
		expanded = process_line(line, &delim_info, envp);
		if (!expanded)
			exit(EXIT_FAILURE);
		ft_putendl_fd(expanded, write_fd);
		free(expanded);
	}
	close(write_fd);
	exit(0);
}

/**
 * [Heredoc 설계 의도 및 시그널 처리]
 * 사용자의 Heredoc 입력과 쉘 메인 흐름의 완전한 분리.
 * * 1. 독립적인 프로세스 운용: 자식 프로세스에서 입력을 수행함으로써, 
 * 입력 중 Ctrl+C 발생 시 쉘 전체가 아닌 해당 작업만 즉시 취소되도록 구현
 * 2. 파이프를 통한 데이터 인계: 파싱 단계에서 입력된 데이터를 파이프 버퍼에 보존
 * 부모는 이 파이프의 읽기용 FD만 리스트에 안전하게 보관 후, 
 * 명령어 실행 시점에 STDIN으로 연결하여 데이터 전달
 * 3. 종료 상태 동기화: waitpid를 통한 자식의 상태 확인 및 
 * 비정상 종료 발생 시 할당된 FD 폐쇄 및 제어권 회수
 */
int	read_heredoc(t_prompt *prompt, t_delim_info delim_info)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) < 0)
		return (-2);
	pid = fork();
	if (pid < 0)
		return (-2);
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_child(delim_info, fd[1], prompt->envp_lst);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	if (g_exit_status != 0)
		return (close(fd[0]), -1);
	return (fd[0]);
}

/**
 * [Heredoc Workflow Controller]
 * 토큰 리스트를 순회하며 T_HEREDOC 타입을 찾아 처리
 * - 각 히어독 세션마다 고유한 FD를 생성하여 t_hd 리스트에 저장
 * - 입력 도중 오류(Ctrl+C 등) 발생 시 즉시 중단하고 리스트를 정리
 */
int	heredoc_process(t_prompt *prompt)
{
	t_token			*curr;
	t_delim_info	delim_info;
	int				fd;

	curr = prompt->token_lst;
	while (curr && curr->type != T_ERROR)
	{
		if (curr->type == T_HEREDOC && curr->next && curr->next->type == T_WORD)
		{
			delim_info = make_delim(curr->next->value);
			if (!delim_info.cooked_delim)
				return (0);
			fd = read_heredoc(prompt, delim_info);
			free(delim_info.cooked_delim);
			if (fd == -1)
				return (clear_token_list(&prompt->token_lst), 1);
			if (fd == -2 || !add_new_hd(&prompt->hd_lst, fd))
				return (0);
		}
		curr = curr->next;
	}
	return (1);
}
