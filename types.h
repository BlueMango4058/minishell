/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsagong <dsagong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:41:47 by dsagong           #+#    #+#             */
/*   Updated: 2026/03/03 16:43:47 by dsagong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <unistd.h>
# include <signal.h>

# define SUCCESS 0
# define FAILURE 1

# define SIG_INTERACTIVE 1
# define SIG_NON_INTERACTIVE 0
# define SIG_CHILD 2

/**
 * [환경 변수 리스트 구조체]
 * 쉘 실행 시점의 환경 변수를 연결 리스트로 관리
 * - Expansion 단계에서 '$' 문자를 만났을 때 실제 값을 조회하는 딕셔너리 역할 수행
 */
typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

/**
 * [토큰 타입 열거형]
 * 어휘 분석(Lexing) 시 문자열을 최소 의미 단위로 분류하기 위한 식별자
 * - T_CORRECT_FILNAME / T_WRONG_FILNAME: 환경 변수 확장 이후 
 * 파일명의 유효성을 검증하여 'ambiguous redirect' 처리를 돕는 방어적 타입
 */
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_ERROR,
	T_CORRECT_FILNAME,
	T_WRONG_FILNAME,
	T_END
}	t_token_type;

/**
 * [어휘 분석 결과물 (Token)]
 * 사용자 입력을 1차원적으로 분해한 렉서(Lexer)의 최종 산출물
 * - type: 현재 노드가 연산자인지, 일반 문자열인지 명시
 * - value: 따옴표가 제거되고 환경 변수가 치환된 순수 실행 문자열
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/**
 * [상태 머신 컨텍스트 열거형]
 * 현재 파싱 중인 문자가 따옴표 내부인지 외부인지를 실시간으로 추적
 * - 특수 문자(공백, 파이프, $)가 단순 문자로 취급되어야 할지(따옴표 내부),
 * 연산자로 작동해야 할지(일반 상태)를 결정하는 핵심 상태값
 */
typedef enum e_quote_state
{
	STATE_GENERAL,
	STATE_IN_SQUOTE,
	STATE_IN_DQUOTE
}	t_quote_state;

/**
 * [환경 변수 확장 임시 구조체]
 * 문자열 내의 환경 변수를 치환할 때 사용하는 헬퍼 구조체
 * - 복잡한 인덱스 계산과 문자열 동적 할당을 하나의 구조체로 묶어 메모리 누수 방지
 */
typedef struct s_exp
{
	t_quote_state	state;
	size_t			idx;
	char			*result;
}	t_exp;

/**
 * [문법 검사 결과 열거형]
 * 실행 전 단계의 Fail-Fast 방어막
 * - 닫히지 않은 따옴표나 잘못된 연산자 배치를 선제적으로 판별하여 반환
 */
typedef enum e_grammar_status
{
	GRAMMAR_OK,
	GRAMMAR_TOKEN_ERROR,
	GRAMMAR_EOF_ERROR,
}	t_grammar_status;

/**
 * [Heredoc 파이프 리스트]
 * 파싱 단계에서 자식 프로세스가 생성한 Heredoc 데이터의 파이프 읽기용 FD를 저장
 * - 실행부에서 이 FD들을 순차적으로 꺼내어 명령어의 STDIN으로 연결할 수 있도록 보관
 */
typedef struct s_hd
{
	int			fd;
	struct s_hd	*next;
}	t_hd;

/**
 * [파싱 프로세스 메인 컨테이너]
 * input_process의 시작부터 끝까지 데이터의 흐름을 쥐고 있는 마스터 구조체
 * - 초기 사용자 입력(input)부터 환경 변수(envp), 파싱 결과물(token_lst), 
 * 그리고 생성된 히어독 파일 디스크립터(hd_lst)까지 파서의 모든 문맥(Context)을 통합 관리
 */
typedef struct s_prompt
{
	char		*input;
	t_envp		*envp_lst;
	t_token		*token_lst;
	t_hd		*hd_lst;
}	t_prompt;

typedef struct s_filename
{
	char	*filename;
	int		hd;
	int		flag;
	int		append_mode;
}	t_filename;

typedef struct s_file
{
	t_filename		*input_file;
	t_filename		*output_file;
	struct s_file	*next;
}	t_file;

typedef struct s_cmd
{
	char			**args;
	t_file			*file;
	int				hd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_envp	*envp_list;
	char	**env_array;
	int		last_exit_status;
	int		exit_flag;
	int		signal_mode;
}	t_shell;

typedef struct s_exec_info
{
	int	cmd_index;
	int	cmd_count;
}	t_exec_info;

#endif
