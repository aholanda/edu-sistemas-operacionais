
/**
 * $Date$
 *
 * Os fragmentos contidos neste arquivo foram extraidos
 * do arquivo de cabecalho sched.h do kernel do linux 
 * versao 2.6.38-11
 * Eles visam mostras as principais estruturas do 
 * escalonador do Linux.
 **/

/* Entrada da tabela de processos */
struct task_struct {
        /* Gerenciamento de arquivo */
        volatile long state;  /* estado do processos */
        void *stack; /* ponteiro da pilha */
        int prio, static_prio, normal_prio; /* prioridade */
        pid_t pid; /* ID do processo */
        pid_t tgid; /* grupo do processo */
        int exit_state; /* estado do processo */
        int exit_code, exit_signal; /* sinal */
        struct task_struct *parent; /* processo pai */
        cputime_t utime; /* tempo de cpu usado */

        /* Gerenciamento de arquivo */
        uid_t loginuid; /* ID do usuario */
        /* ... */
};
