#ifndef F_UTILI_H
#define F_UTILI_H

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void set_color(int color);
void svuota_buffer(void);
void pulisci_schermo(void);
void salvataggio(void);
void stampa_separatore(void);
void stampa_bordo_superiore(void);
void stampa_bordo_inferiore(void);
#endif