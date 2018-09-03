#ifndef EXAME_H_INCLUDED
#define EXAME_H_INCLUDED

/* FUNÇÕES DE FUNCIONALIDADES - OK */
tipoAgendamento *adicionarNovoAgendamento(tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos);
void listarClientesComAgendamentos (tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos);
void registarAgendamento(tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos, int *quantAgendamentosRegistados);
void listarAgendamentosPorData (tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos);

/* FUNÇÕES AUXILIARES - OK */
int procurarAgendamento(tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos, int codigoUnico);
int procurarAgendamentoPorData(tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos, tipoData dataSearch);


/* Funções de teste */
void listarClientesComMaisAgendamentosReg (tipoAgendamento *pAgend, tipoCliente vetorClientes[MAX], int *quantClientes, int *quantAgendamentos, int *quantAgendamentosRegistados);

#endif // EXAME_H_INCLUDED
