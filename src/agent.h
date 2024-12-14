#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED
#include <stdio.h>
#include <gtk/gtk.h>

typedef struct {
  int annee,mois , jour;
  }date;
typedef struct {
    char id_reservation[20];       
    char cin[20];             
    date date_reservation;    
    int heure_debut;          
    int heure_fin;            
    int station_parking; 
} reservation;

typedef struct {
  char nom [20];
  char prenom[20];
  date dn;
  char cin [20];
  char mail_dagent[50];
  char num_telefone [20];
  date db;
  char region [20];
  char ville[20];
  int  statut;
  char role_agent[20];
  char parking_assigne[20];
  reservation rsv;
}agent;
void on_window_show(GtkWidget *widget, gpointer user_data);
void setup_treeview(GtkWidget *treeview);
void load_agents_into_treeview(GtkWidget *treeview);
void filter_treeview_by_cin(GtkWidget *treeview, const char *cin_filter);
agent cher(const char *filename1, const char *cin); 

reservation chercher_reserv_par_date(char *filename1, char *filename2, date date_reservation);


int verifier_date(date d);
int ajouter(char *filename, agent a);
int modifier(char *filename, char *cin, agent a);
int supprimer(char *filename, char *cin); 
      

extern const char *roles_agent[];          
extern const char *parkings_assignes[];    



int verifier_cin(const char *cin);//done
int verifier_telephone(const char *telephone);//done
int verifier_email(const char *email);//done




#endif //POINT_H_INCLUDED



