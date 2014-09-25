#L‟obiettivo del progetto è quello di creare un programma in grado di gestire l‟esecuzione di 4 threads, che devono rispettivamente svolgere le seguenti funzioni:
#- T1 : legge da tastiera una sequenza di caratteri (S) arbitrariamente lunga fino a che non riconosce il carattere <CR>, ossia ENTER.
#- T2 : legge dal device “/dev/random” una stringa di caratteri R della dimensione di S, e successivamente, ne fa lo XOR byte-per-byte con S ottenendo Se=XOR(R,S).
#- T3 : accede ai dati contenuti in R e Se e calcola Sd=XOR(R,Se).
#- T4 : stampa a schermo l‟ultima stringa generata Sd.
#Inoltre il programma genera nella cartella “/var/log/threads” quattro file di log, che servono per verificare, a esecuzione terminata, la riuscita delle operazioni di ciascun thread.
#
#Linguaggio Utilizzato : C