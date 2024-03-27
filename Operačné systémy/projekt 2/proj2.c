#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctype.h>
#include <string.h>

int *NE = NULL;	// pocet elfov
int *NR = NULL; // pocet sobov
int *TE = NULL; // Maximální doba v milisekundách, po kterou skřítek pracuje samostatně
int *TR = NULL; // Maximální doba v milisekundách, po které se sob vrací z dovolené domů
int *elfID = NULL;
int *rdID = NULL;
int *counter = NULL; // pocitadlo jednotlivych procesov
FILE *out = NULL; //output subor
int *reindeer_count = NULL;
int *reindeer_count2 = NULL;
int *elf_count = NULL;
int *santa_control = NULL;
int *elf_count2 = NULL;
bool *christmas = NULL; // kontrola ci su vianoce
bool issleeping = false; // kontrola ci santa spi
bool *vrateny = NULL; // kontrola ci su vrateny vsetci sobovia z dovolenky

sem_t *s_write;
sem_t *s_elf;
sem_t *s_reindeer;
sem_t *s_santa_sleep;
sem_t *s_reindeer_santa;
sem_t *s_elf_count;
sem_t *s_santa_control;
sem_t *s_elf_count3;
sem_t *s_reindeer_wait;
sem_t *s_zatvorene;
sem_t *s_christmas;

void free_all();
//funkcia na inicializaciu semaforov a premennych + kontrola suboru a kontrola inicializovanych semaforov a premennych
int init(){
	out = fopen("proj2.out","w"); 
	if (out == NULL){
		fprintf(stderr, "Nepodarilo sa otvorit subor proj2.out\n");
		free_all();
		exit(1);
	} 
	int error = 0;
	s_write = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_write == MAP_FAILED){
		error = 1;
	}
	s_elf = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_elf == MAP_FAILED){
		error = 1;
	}
	s_reindeer = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_reindeer == MAP_FAILED){
		error = 1;
	}
	s_santa_sleep = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_santa_sleep == MAP_FAILED){
		error = 1;
	}
	s_elf_count = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_elf_count == MAP_FAILED){
		error = 1;
	}
	s_reindeer_santa = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_reindeer_santa == MAP_FAILED){
		error = 1;
	}
	s_santa_control = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_santa_control == MAP_FAILED){
		error = 1;
	}
	s_elf_count3 = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_elf_count3 == MAP_FAILED){
		error = 1;
	}
	s_reindeer_wait = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_reindeer_wait == MAP_FAILED){
		error = 1;
	}
	s_zatvorene = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_zatvorene == MAP_FAILED){
		error = 1;
	}
	s_christmas = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
	if (s_christmas == MAP_FAILED){
		error = 1;
	}
	if (error == 1){
		fprintf(stderr, "Problem s alokaciou pamate pre semafory\n");
		exit(1);
	}
	else {
		if (sem_init(s_write, 1, 1) == -1){
			error = 1;
		}
		if (sem_init(s_elf, 1, 1) == -1){
			error = 1;
		}
		if (sem_init(s_reindeer, 1, 1) == -1){
			error = 1;
		}
		if (sem_init(s_santa_sleep, 1, 0) == -1){
			error = 1;
		}
		if (sem_init(s_elf_count, 1, 1) == -1){
			error = 1;
		}
		if (sem_init(s_reindeer_santa, 1, 1) == -1){
			error = 1;
		}
		if (sem_init(s_santa_control, 1, 1) == -1){
			error = 1;
		}
		if (sem_init(s_elf_count3, 1, 0) == -1){
			error = 1;
		}
		if (sem_init(s_reindeer_wait, 1, 0) == -1){
			error = 1;
		}
		if (sem_init(s_zatvorene, 1, 0) == -1){
			error = 1;
		}
		if (sem_init(s_christmas, 1, 0) == -1){
			error = 1;
		}
	}
	if (error == 1){
		fprintf(stderr, "Problem s inicializaciou semaforov\n");
		exit(1);
	}
	else{
		NE = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (NE == MAP_FAILED){
			error = 1;
		}
		NR = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (NR == MAP_FAILED){
			error = 1;
		}
		TE = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (TE == MAP_FAILED){
			error = 1;
		}
		TR = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (TR == MAP_FAILED){
			error = 1;
		}
		counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (counter == MAP_FAILED){
			error = 1;
		}
		elfID = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (elfID == MAP_FAILED){
			error = 1;
		}
		rdID = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (rdID == MAP_FAILED){
			error = 1;
		}
		reindeer_count = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (reindeer_count == MAP_FAILED){
			error = 1;
		}
		reindeer_count2 = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (reindeer_count2 == MAP_FAILED){
			error = 1;
		}
		elf_count = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (elf_count == MAP_FAILED){
			error = 1;
		}
		santa_control = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0 , 0);
		if (santa_control == MAP_FAILED){
			error = 1;
		}
		elf_count2 = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (elf_count2 == MAP_FAILED){
			error = 1;
		} 
		christmas = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (christmas == MAP_FAILED){
			error = 1;
		} 
		vrateny = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, 0, 0);
		if (vrateny == MAP_FAILED){
			error = 1;
		}
		*counter = 1;
		*elfID = 1;
		*rdID = 1;	
		*reindeer_count = 0;
		*reindeer_count2 = 0;
		*elf_count = 0;
		*santa_control = 0;
		*elf_count2 = 0;
		*christmas = false;
		*vrateny = false;
	}
	if (error == 1){
		fprintf(stderr, "Problem s alokaciou pamate premennych\n");
		exit(1);
	}
	return error;
}
// funkcia  ktora sluzi na samotny vypis
void mywrite(char* action, int is, int ID){
	sem_wait(s_write);
	if (is == 1){
		fprintf(out, "%d: Elf %d: %s\n", *counter, ID, action);	
		(*counter)++;
	}		
	else if (is == 2){
		fprintf(out, "%d: RD %d: %s\n", *counter, ID, action);
		(*counter)++ ;
	}
	else{
		fprintf(out, "%d: Santa: %s\n", *counter, action);
		(*counter)++;
	}
	fflush(out);
	sem_post(s_write);
}
// funkcia volania santu, v ktorej sa kontroluje ci santa spi, pomaha elfom, zatvara workshop alebo zacina vianoce 
void santa(){
	if (issleeping == false){ 
		mywrite("going to sleep", 0, 0);
		issleeping = true;
	}
	sem_wait(s_santa_sleep);
	sem_wait(s_santa_control);
	if (*santa_control == 1){
		mywrite("helping elves", 0, 0);	
		sem_post(s_elf_count3);	
		sem_post(s_elf_count3);
		sem_post(s_elf_count3);
		issleeping = false;	
	}
	else if (*santa_control == 2){
		mywrite("closing workshop", 0, 0);
		*vrateny = true;
		for (int i = 0; i < *NE; i++){
			sem_post(s_christmas);
		}
		for (int i = 0; i < *NR; i++){
			sem_post(s_zatvorene);
		}
	}
	else if (*santa_control == 5){
		*christmas = true;
		mywrite("Christmas started", 0, 0);
		for (int i = 0; i < *NE; i++){
			sem_post(s_elf_count3);
		}
		exit(0);
	}
	sem_post(s_santa_control);	
	santa();
}
// funkcia volania elfa, ktory moze pracu zacat, ziadat o pomoc santu ak ziadaju traja elfovia, moze dostat pomoc ak nie su vianoce a ak su vianoce tak si elfovia zoberu dovolenku
void elf(){
	srand(getpid());
	sem_wait(s_elf);
	int elf_ID = *elfID;
	(*elfID)++;
	sem_post(s_elf);
	mywrite("started", 1, elf_ID);
	int delay = (rand() % (*TE + 1));
	usleep(delay * 1000);
	mywrite("need help", 1, elf_ID);
	sem_wait(s_elf_count);
	(*elf_count)++;
	(*elf_count2)++;
	if (*christmas == false && (*elf_count >= 3)){
		sem_wait(s_santa_control);
		*santa_control = 1;
		sem_post(s_santa_sleep);
		*elf_count = *elf_count - 3;
		sem_post(s_santa_control);
	}
	sem_post(s_elf_count);
	sem_wait(s_elf_count3);
	if (*christmas == false){
		mywrite("get help", 1, elf_ID);
	}
	sem_wait(s_christmas);
	mywrite("taking holidays", 1, elf_ID);
	exit(0);
}
// funkcia volajuca sobov, ktori mozu zacat, vratit sa z dovolenky a ked sa vsetci vratia tak volaju santu aby ich zapriahol, a santa vtedy zatvori dielnu a zapriahne sobov
void reindeer(){
	srand(getpid());
	sem_wait(s_reindeer);
	int reindeer_ID = *rdID;
	(*rdID)++;
	sem_post(s_reindeer);
	mywrite("rstarted", 2, reindeer_ID);
	int delay = (rand() % (*TR - *TR/2 + 1) + *TR/2);
	usleep(delay * 1000);
	(*reindeer_count)++;
	mywrite("return home", 2, reindeer_ID);
	if (*reindeer_count == *NR){
		sem_wait(s_santa_control);
		*santa_control = 2;
		sem_post(s_santa_sleep);
		sem_post(s_santa_control);
	}
	sem_wait(s_reindeer_santa);
	(*reindeer_count2)++;
	sem_wait(s_zatvorene);
	if (*vrateny == true){
		mywrite("get hitched", 2, reindeer_ID);	
	}
	if (*reindeer_count2 == *NR){
		sem_wait(s_santa_control);
		*santa_control = 5;
		sem_post(s_santa_sleep);
		sem_post(s_santa_control);
	}
	sem_post(s_reindeer_santa);
	exit(0);
}
// funkcia na kontrolu ci su stringy (zadane argumenty) zlozene len z cisiel
bool ismydigit(char *pole){
	int dlzka = strlen(pole);
	for (int x = 0; x < dlzka; x++){
		if (!isdigit(pole[x])){
			return false;
		}	
	}
	return true;
}
// funkcia na uvolnenie vsetkych semaforov a premennych
void free_all(){
	int error = 0;
	if (sem_destroy(s_write) == -1){
		error = 1;
	}
	if (sem_destroy(s_elf) == -1){
		error = 1;
	}
	if (sem_destroy(s_reindeer) == -1){
		error = 1; 
	}
	if (sem_destroy(s_santa_sleep) == -1){
		error = 1;
	}
	if (sem_destroy(s_elf_count) == -1){
		error = 1;
	}
	if (sem_destroy(s_reindeer_santa) == -1){
		error = 1;
	}
	if (sem_destroy(s_santa_control) == -1){
		error = 1;	
	}
	if (sem_destroy(s_elf_count3) == -1){
		error = 1;
	}
	if (sem_destroy(s_reindeer_wait) == -1){
		error = 1;
	}
	if (sem_destroy(s_zatvorene) == -1){
		error = 1;
	}
	if (sem_destroy(s_christmas) == -1){
		error = 1;
	}
	if (error == 1){
		fprintf(stderr, "Nepodarilo sa uvolnit semafor\n");
		exit(1);
	}
	munmap(s_write, sizeof(sem_t));
	munmap(s_elf, sizeof(sem_t));
	munmap(s_reindeer, sizeof(sem_t));
	munmap(s_santa_sleep, sizeof(sem_t));
	munmap(s_elf_count, sizeof(sem_t));
	munmap(s_reindeer_santa, sizeof(sem_t));
	munmap(s_santa_control, sizeof(sem_t));
	munmap(s_elf_count3, sizeof(sem_t));
	munmap(s_reindeer_wait, sizeof(sem_t));
	munmap(s_zatvorene, sizeof(sem_t));
	munmap(s_christmas, sizeof(sem_t));
	munmap(NE, sizeof(int));
	munmap(NR, sizeof(int));
	munmap(TE, sizeof(int));
	munmap(TR, sizeof(int));
	munmap(counter, sizeof(int));
	munmap(elfID, sizeof(int));
	munmap(rdID, sizeof(int));
	munmap(reindeer_count, sizeof(int));
	munmap(reindeer_count2, sizeof(int));
	munmap(elf_count, sizeof(int));
	munmap(elf_count2, sizeof(int));
	munmap(santa_control, sizeof(int));
	munmap(christmas, sizeof(bool));
	munmap(vrateny, sizeof(bool));
}
// main funkcia, kontroluje spravny pocet argumentov a ci su argumenty len z cisiel a v spravnych rozsahoch
int main(int argc, char *argv[]){
	if (argc == 5){
		if (ismydigit(argv[1]) && ismydigit(argv[2]) && ismydigit(argv[3]) && ismydigit(argv[4])){
			int argNE = atoi(argv[1]); 
			if (argNE <= 0 || argNE >= 1000){
				fprintf(stderr,"Argument NE musi byt v rozsahu (0, 1000)\n");
				exit(1);
			}
			int argNR = atoi(argv[2]);
			if (argNR <= 0 || argNR >= 20){
				fprintf(stderr,"Argument NR musi byt v rozsahu (0, 20)\n");
				exit(1);
			}
			int argTE = atoi(argv[3]); 
			if (argTE < 0 || argTE > 1000){
				fprintf(stderr,"Argument TE musi byt v rozsahu <0, 1000>\n");
				exit(1);
			} 
			int argTR = atoi(argv[4]);
			if (argTR < 0 || argTR > 1000){
				fprintf(stderr,"Argument TR musi byt v rozsahu <0, 1000>\n");
				exit(1);
			}
			init();
			*NE = argNE;
			*NR = argNR; 
			*TE = argTE;
			*TR = argTR; 
			int idSanta = fork();
			if (idSanta == 0){
				santa();
				exit(0);
			}
			for(int i = 0; i < argNE; i++){
				int id = fork();
				if (id == 0){
					elf();
				}
			}
			for(int i = 0; i < argNR; i++){
				int id = fork();
				if (id == 0){
					reindeer();
				}
			}
			}
		else{
			fprintf(stderr,"Minimalne jeden z argumentov ma neciselnu hodnotu\n");
			free_all();
			exit(1);
		}	
	}
	else{
		fprintf(stderr,"Nespravny pocet argumnetov\n");
		free_all();
		exit(1);
	}
	free_all();
	exit(0);
}
